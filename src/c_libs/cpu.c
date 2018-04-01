//
// Created by anghelo on 23-02-18.
//

#include "cpu.h"

NesCPURegisters* initRegisters(){
    NesCPURegisters* registers = malloc(sizeof(NesCPURegisters));

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
int cpuPowerUp(NesCPURegisters *registers){
    int retVal = 0;
	registers->statusRegister = 0x34; // P = $34[1] (IRQ disabled)
	registers->accumulator = 0x0; // A, X, Y = 0
	registers->indexX = 0x0; // A, X, Y = 0
	registers->indexY = 0x0; // A, X, Y = 0
    // registers->programCounter = ;
	registers->stack = 0xFD; // S = $FD
    // registers->statusRegister = ;

    registers->disablePC = 0;

    return retVal;
}

int resetCpu(NesCPURegisters* registers, NesRam* ram){
    // A, X, Y were not affected
    // registers->stack += 3; // S was decremented by 3 (but nothing was written to the stack)
    registers->statusRegister |= 0x04; // The I (IRQ disable) flag was set to true (status ORed with $04)
    // The internal memory was unchanged
    // APU mode in $4017 was unchanged
    // APU was silenced ($4015 = 0)

    registers->disablePC = 0;
    return 0;
}

int getInstsFromRam(unsigned char* inst, unsigned short programCounter, NesRam* ram){
	inst[0] = loadFromRam(ram, programCounter);
	if(programCounter+1 >= RAM_SIZE){
		return ALF_NES_ERROR_CODE_RAM_OUT_1;
	}
    inst[1] = loadFromRam(ram, (unsigned short)(programCounter+1));
	if(programCounter+2 >= RAM_SIZE){
		return ALF_NES_ERROR_CODE_RAM_OUT_2;
	}
	inst[2] = loadFromRam(ram, (unsigned short)(programCounter+2));
	return 0;
}

int executeInstructions(NesCPURegisters* registers, NesRam* ram, NesRom* rom){
    printf("data in reset vector\n$%x: $%x\n", getResetVector(ram), loadFromRam(ram, getResetVector(ram)));
    registers->programCounter = getResetVector(ram);
	unsigned char* inst = malloc(sizeof(unsigned char) * 3);
	int ret;
	Instruction* instData = NULL;
    
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
void setCarry(NesCPURegisters* registers){
    registers->statusRegister |= BIT_0;
}
void clearCarry(NesCPURegisters* registers){
    registers->statusRegister &= ~BIT_0;
}
char getCarry(NesCPURegisters* registers){
    return (char)(registers->statusRegister & BIT_0);
}

void setZero(NesCPURegisters* registers){
    registers->statusRegister |= BIT_1;
}
void clearZero(NesCPURegisters* registers){
    registers->statusRegister &= ~BIT_1;
}
char getZero(NesCPURegisters* registers){
    return (char)((registers->statusRegister & BIT_1)>>1);
}

void setInterrupt(NesCPURegisters* registers){
    registers->statusRegister |= BIT_2;
}
void clearInterrupt(NesCPURegisters* registers){
    registers->statusRegister &= ~BIT_2;
}
char getInterrupt(NesCPURegisters* registers){
    return (char)((registers->statusRegister & BIT_2)>>2);
}

void setDecimal(NesCPURegisters* registers){
    registers->statusRegister |= BIT_3;
}
void clearDecimal(NesCPURegisters* registers){
    registers->statusRegister &= ~BIT_3;
}
char getDecimal(NesCPURegisters* registers){
    return (char)((registers->statusRegister & BIT_3)>>3);
}

void setS(NesCPURegisters* registers){
    registers->statusRegister |= BIT_4;
}
void clearS(NesCPURegisters* registers){
    registers->statusRegister &= ~BIT_4;
}
char getS(NesCPURegisters* registers){
    return (char)((registers->statusRegister & BIT_4)>>4);
}

void setOverflow(NesCPURegisters* registers){
    registers->statusRegister |= BIT_6;
}
void clearOverflow(NesCPURegisters* registers){
    registers->statusRegister &= ~BIT_6;
}
char getOverflow(NesCPURegisters* registers){
    return (char)((registers->statusRegister & BIT_6)>>6);
}

void setNegative(NesCPURegisters* registers){
    registers->statusRegister |= BIT_7;
}
void clearNegative(NesCPURegisters* registers){
    registers->statusRegister &= ~BIT_7;
}
char getNegative(NesCPURegisters* registers){
    return (char)((registers->statusRegister & BIT_7)>>7);
}

void disablePC(NesCPURegisters* registers){
    registers->disablePC = 1;
}
void enablePC(NesCPURegisters* registers){
    registers->disablePC = 0;
}

void parseZeroNegative(NesCPURegisters* registers, char number){
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

void pushStack(NesCPURegisters* registers, NesRam* ram, unsigned char value){
    storeIntoRam(ram, (unsigned short)0x0100 + registers->stack, value);
    registers->stack -= 1;
}
unsigned char pullStack(NesCPURegisters* registers, NesRam* ram){
    registers->stack += 1;
    return loadFromRam(ram, (unsigned short)0x0100 + registers->stack);
}
