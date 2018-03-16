//
// Created by anghelo on 23-02-18.
//

#ifndef ALF_NES_TOOLS_CPU_H
#define ALF_NES_TOOLS_CPU_H

#include <stdlib.h>

#include "ram.h"
#include "instructions.h"

struct nesRegisters{
    // https://wiki.nesdev.com/w/index.php/CPU_registers
    char accumulator; // A
    unsigned char indexX; // X
    unsigned char indexY; // Y
    unsigned short programCounter; // PC
    unsigned char stack; // S
    unsigned char statusRegister; // P

    unsigned char disablePC;
};

struct nesRegisters* initRegisters();

// https://wiki.nesdev.com/w/index.php/CPU_power_up_state
void powerUp(struct nesRegisters* registers, struct nesRam* ram);
void resetCpu(struct nesRegisters* registers, struct nesRam* ram);

int executeInstructions(struct nesRegisters* registers, struct nesRam* ram, struct nesRom* rom);

// http://wiki.nesdev.com/w/index.php/CPU_status_flag_behavior
void setCarry(struct nesRegisters* registers);
void clearCarry(struct nesRegisters* registers);
char getCarry(struct nesRegisters* registers);
void setZero(struct nesRegisters* registers);
void clearZero(struct nesRegisters* registers);
char getZero(struct nesRegisters* registers);
void setInterrupt(struct nesRegisters* registers);
void clearInterrupt(struct nesRegisters* registers);
char getInterrupt(struct nesRegisters* registers);
void setDecimal(struct nesRegisters* registers);
void clearDecimal(struct nesRegisters* registers);
char getDecimal(struct nesRegisters* registers);
void setS(struct nesRegisters* registers);
void clearS(struct nesRegisters* registers);
char getS(struct nesRegisters* registers);
void setOverflow(struct nesRegisters* registers);
void clearOverflow(struct nesRegisters* registers);
char getOverflow(struct nesRegisters* registers);
void setNegative(struct nesRegisters* registers);
void clearNegative(struct nesRegisters* registers);
char getNegative(struct nesRegisters* registers);

void disablePC(struct nesRegisters* registers);
void enablePC(struct nesRegisters* registers);

void parseZeroNegative(struct nesRegisters* registers, char number);

#endif //ALF_NES_TOOLS_CPU_H
