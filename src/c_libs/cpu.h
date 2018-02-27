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
    unsigned char acumulator; // A
    unsigned char indexX; // X
    unsigned char indexY; // Y
    unsigned short programCounter; // PC
    unsigned char stack; // S
    unsigned char statusRegister; // P
};

struct nesRegisters* initRegisters();

// https://wiki.nesdev.com/w/index.php/CPU_power_up_state
void powerUp(struct nesRegisters* registers, struct nesRam* ram);
void resetCpu(struct nesRegisters* registers, struct nesRam* ram);

int executeInstructions(struct nesRegisters* registers, struct nesRam* ram, struct nesRom* rom);

#endif //ALF_NES_TOOLS_CPU_H
