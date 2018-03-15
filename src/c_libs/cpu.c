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
    registers->statusRegister = 0x0; // P

    registers->disablePC = 0;

    return registers;
}

// https://wiki.nesdev.com/w/index.php/CPU_power_up_state
void powerUp(struct nesRegisters* registers, struct nesRam* ram){
	registers->statusRegister = 0x34; // P = $34[1] (IRQ disabled)[2]
	registers->accumulator = 0x0; // A, X, Y = 0
	registers->indexX = 0x0; // A, X, Y = 0
	registers->indexY = 0x0; // A, X, Y = 0
    // registers->programCounter = ;
	registers->stack = 0xFD; // S = $FD
    // registers->statusRegister = ;

    ram->ram[0x4017] = 0x0; // $4017 = $00 (frame irq enabled)
    ram->ram[0x4015] = 0x0; // $4015 = $00 (all channels disabled)
    for(size_t i = 0x4000; i <= 0x400F; i++){ // $4000-$400F = $00
    	ram->ram[i] = 0x0; // (not sure about $4010-$4013)
    }
    // All 15 bits of noise channel LFSR = $0000. The first time the LFSR is clocked from the all-0s state, it will shift in a 1.


    registers->disablePC = 0;
}

void resetCpu(struct nesRegisters* registers, struct nesRam* ram){
    // A, X, Y were not affected
    registers->stack += 3; // S was decremented by 3 (but nothing was written to the stack)
    // The I (IRQ disable) flag was set to true (status ORed with $04)
    // The internal memory was unchanged
    // APU mode in $4017 was unchanged
    // APU was silenced ($4015 = 0)

    registers->disablePC = 0;
}

int getInstsFromRam(unsigned char* inst, unsigned short programCounter, struct nesRam* ram){
	inst[0] = ram->ram[programCounter];
	if(programCounter+1 >= RAM_SIZE){
		return -1;
	}
	if(programCounter+2 >= RAM_SIZE){
		return -2;
	}
	inst[1] = ram->ram[programCounter+1];
	inst[2] = ram->ram[programCounter+2];
	return 0;
}

int executeInstructions(struct nesRegisters* registers, struct nesRam* ram, struct nesRom* rom){
    if(getResetVector(ram) + RAM_ROM_FIRST_PAGE >= RAM_SIZE){
        return -1;
    }
	registers->programCounter = (unsigned short)(getResetVector(ram) + RAM_ROM_FIRST_PAGE);
	unsigned char* inst = malloc(sizeof(unsigned char) * 3);
	int ret;
	struct instruction* instData = NULL;
    
	for(; registers->programCounter < RAM_SIZE && !registers->disablePC; registers->programCounter++){
		ret = getInstsFromRam(inst, registers->programCounter, ram);
		if(ret < 0){
			printf("\tinvalid RAM position\n");
			break;
		}

        printf("position~: %i\n", registers->programCounter-(getResetVector(ram) + RAM_ROM_FIRST_PAGE));
		instData = detectType(inst, 0);
        printf("\n");
        if(instData == NULL){
            printf("\t\tunknow opcode: $%x\n", inst[0]);
            printf("\t\tPC: 0x%x\n", registers->programCounter);
            printf("\t\tpointer: 0x%x\n", registers->programCounter-RAM_ROM_FIRST_PAGE);
            printf("\t\tposition~: %i\n", registers->programCounter-(getResetVector(ram) + RAM_ROM_FIRST_PAGE));
            break;
        }

        printf("\t\topcode sintax: ");
        printfCharAsHex(instData->opcode);
        if(instData->bytesAmount > 0){
            printf(" ");
            printfCharAsHex(instData->byte1);
        }
        if(instData->bytesAmount > 1){
            printf(" ");
            printfCharAsHex(instData->byte2);
        }

        printf("\n\n");

        instData->execute(instData, registers, ram);
        printf("\n\n");

        registers->programCounter += instData->bytesAmount;
        // sleep(1);

	}
    return 0;
}


// http://wiki.nesdev.com/w/index.php/CPU_status_flag_behavior
void setCarry(struct nesRegisters* registers){
    registers->statusRegister |= 0b00000001;
}
void clearCarry(struct nesRegisters* registers){
    registers->statusRegister &= 0b11111110;
}
char getCarry(struct nesRegisters* registers){
    return (char)(registers->statusRegister & 0b00000001);
}

void setZero(struct nesRegisters* registers){
    registers->statusRegister |= 0b00000010;
}
void clearZero(struct nesRegisters* registers){
    registers->statusRegister &= 0b11111101;
}
char getZero(struct nesRegisters* registers){
    return (char)((registers->statusRegister>>1) & 0b00000001);
}

void setInterrupt(struct nesRegisters* registers){
    registers->statusRegister |= 0b00000100;
}
void clearInterrupt(struct nesRegisters* registers){
    registers->statusRegister &= 0b11111011;
}
char getInterrupt(struct nesRegisters* registers){
    return (char)((registers->statusRegister>>2) & 0b00000001);
}

void setS(struct nesRegisters* registers, char s){
    s = (char)(s & 0b00000011)<<4;
    registers->statusRegister |= s;
}
char getS(struct nesRegisters* registers){
    return (char)((registers->statusRegister>>4) & 0b00000011);
}

void setOverflow(struct nesRegisters* registers){
    registers->statusRegister |= 0b01000000;
}
void clearOverflow(struct nesRegisters* registers){
    registers->statusRegister &= 0b10111111;
}
char getOverflow(struct nesRegisters* registers){
    return (char)((registers->statusRegister>>6) & 0b00000001);
}

void setNegative(struct nesRegisters* registers){
    registers->statusRegister |= 0b10000000;
}
void clearNegative(struct nesRegisters* registers){
    registers->statusRegister &= 0b01111111;
}
char getNegative(struct nesRegisters* registers){
    return (char)((registers->statusRegister>>7) & 0b00000001);
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
    if(number & 0b10000000){
        setNegative(registers);
    }
    else{
        clearNegative(registers);
    }
}

