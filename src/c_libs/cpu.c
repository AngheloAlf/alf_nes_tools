//
// Created by anghelo on 23-02-18.
//

#include "cpu.h"

struct nesRegisters* initRegisters(){
    struct nesRegisters* registers = malloc(sizeof(struct nesRegisters));

    registers->accumulator = 0x0; // A
    registers->indexX = 0x0; // X
    registers->indexY = 0x0; // Y
    registers->programCounter = 0x0; // PC
    registers->stack = 0x0; // S
    registers->statusRegister = BIT_5; // P

    registers->disablePC = 0;
    registers->jumping = 0;
    registers->jumpingSubroutine = 0;

    return registers;
}

// https://wiki.nesdev.com/w/index.php/CPU_power_up_state
void powerUp(struct nesRegisters* registers, struct nesRam* ram){
	registers->statusRegister = 0x34; // P = $34[1] (IRQ disabled)
	registers->accumulator = 0x0; // A, X, Y = 0
	registers->indexX = 0x0; // A, X, Y = 0
	registers->indexY = 0x0; // A, X, Y = 0
    // registers->programCounter = ;
	registers->stack = 0xFD; // S = $FD
    // registers->statusRegister = ;

    storeIntoRam(ram, 0x4017, 0x0); // $4017 = $00 (frame irq enabled)
    storeIntoRam(ram, 0x4015, 0x0); // $4015 = $00 (all channels disabled)
    for(unsigned short i = 0x4000; i <= 0x400F; i++){ // $4000-$400F = $00
    	storeIntoRam(ram, i, 0x0); // (not sure about $4010-$4013)
    }
    // All 15 bits of noise channel LFSR = $0000. The first time the LFSR is clocked from the all-0s state, it will shift in a 1.


    registers->disablePC = 0;
}

void resetCpu(struct nesRegisters* registers, struct nesRam* ram){
    // A, X, Y were not affected
    // registers->stack += 3; // S was decremented by 3 (but nothing was written to the stack)
    registers->statusRegister |= 0x04; // The I (IRQ disable) flag was set to true (status ORed with $04)
    // The internal memory was unchanged
    // APU mode in $4017 was unchanged
    // APU was silenced ($4015 = 0)

    registers->disablePC = 0;
}

int getInstsFromRam(unsigned char* inst, unsigned short programCounter, struct nesRam* ram){
	inst[0] = loadFromRam(ram, programCounter);
	if(programCounter+1 >= RAM_SIZE){
		return -3;
	}
	if(programCounter+2 >= RAM_SIZE){
		return -4;
	}
	inst[1] = loadFromRam(ram, (unsigned short)(programCounter+1));
	inst[2] = loadFromRam(ram, (unsigned short)(programCounter+2));
	return 0;
}

int executeInstructions(struct nesRegisters* registers, struct nesRam* ram, struct nesRom* rom){
    printf("data in reset vector\n$%x: $%x\n", getResetVector(ram), loadFromRam(ram, getResetVector(ram)));
    registers->programCounter = getResetVector(ram);
	unsigned char* inst = malloc(sizeof(unsigned char) * 3);
	int ret;
	struct instruction* instData = NULL;
    
	for(; registers->programCounter < RAM_SIZE && !registers->disablePC; registers->programCounter++){
		ret = getInstsFromRam(inst, registers->programCounter, ram);
		if(ret < 0){
			printf("\tinvalid RAM position\n");
			break;
		}

        printf("position: 0x%x ~ %hu\n", registers->programCounter, registers->programCounter);
		instData = detectType(inst, 0);
        if(instData == NULL){
            printf("\n\n");
            printf("\t\tunknown opcode: $%x\n", inst[0]);
            printf("\t\tPC: 0x%x\n", registers->programCounter);
            break;
        }

        printf("\topcode syntax: ");
        printfOpcodeSyntax(instData);


        int retVal = instData->execute(instData, registers, ram);
        if(retVal <= 0){
            printfInstruction(instData);
            printf("retVal: %i\n", retVal);
            return retVal;
        }
        // printf("\n\n");

        if(!registers->jumping){
            registers->programCounter += instData->bytesAmount;
        }
        else{
            registers->jumping = 0;
        }
        // sleep(1);

	}
    return 0;
}


// http://wiki.nesdev.com/w/index.php/CPU_status_flag_behavior
void setCarry(struct nesRegisters* registers){
    registers->statusRegister |= BIT_0;
}
void clearCarry(struct nesRegisters* registers){
    registers->statusRegister &= ~BIT_0;
}
char getCarry(struct nesRegisters* registers){
    return (char)(registers->statusRegister & BIT_0);
}

void setZero(struct nesRegisters* registers){
    registers->statusRegister |= BIT_1;
}
void clearZero(struct nesRegisters* registers){
    registers->statusRegister &= ~BIT_1;
}
char getZero(struct nesRegisters* registers){
    return (char)((registers->statusRegister & BIT_1)>>1);
}

void setInterrupt(struct nesRegisters* registers){
    registers->statusRegister |= BIT_2;
}
void clearInterrupt(struct nesRegisters* registers){
    registers->statusRegister &= ~BIT_2;
}
char getInterrupt(struct nesRegisters* registers){
    return (char)((registers->statusRegister & BIT_2)>>2);
}

void setDecimal(struct nesRegisters* registers){
    registers->statusRegister |= BIT_3;
}
void clearDecimal(struct nesRegisters* registers){
    registers->statusRegister &= ~BIT_3;
}
char getDecimal(struct nesRegisters* registers){
    return (char)((registers->statusRegister & BIT_3)>>3);
}

void setS(struct nesRegisters* registers){
    registers->statusRegister |= BIT_4;
}
void clearS(struct nesRegisters* registers){
    registers->statusRegister &= ~BIT_4;
}
char getS(struct nesRegisters* registers){
    return (char)((registers->statusRegister & BIT_4)>>4);
}

void setOverflow(struct nesRegisters* registers){
    registers->statusRegister |= BIT_6;
}
void clearOverflow(struct nesRegisters* registers){
    registers->statusRegister &= ~BIT_6;
}
char getOverflow(struct nesRegisters* registers){
    return (char)((registers->statusRegister & BIT_6)>>6);
}

void setNegative(struct nesRegisters* registers){
    registers->statusRegister |= BIT_7;
}
void clearNegative(struct nesRegisters* registers){
    registers->statusRegister &= ~BIT_7;
}
char getNegative(struct nesRegisters* registers){
    return (char)((registers->statusRegister & BIT_7)>>7);
}

void disablePC(struct nesRegisters* registers){
    registers->disablePC = 1;
}
void enablePC(struct nesRegisters* registers){
    registers->disablePC = 0;
}

void parseZeroNegative(struct nesRegisters* registers, char number){
    if(number == 0){
        setZero(registers);
    }
    else{
        clearZero(registers);
    }
    if(number & BIT_7){
        setNegative(registers);
    }
    else{
        clearNegative(registers);
    }
}

void pushStack(struct nesRegisters* registers, struct nesRam* ram, unsigned char value){
    storeIntoRam(ram, (unsigned short)0x0100 + registers->stack, value);
    registers->stack -= 1;
}
unsigned char pullStack(struct nesRegisters* registers, struct nesRam* ram){
    registers->stack += 1;
    return loadFromRam(ram, (unsigned short)0x0100 + registers->stack);
}
