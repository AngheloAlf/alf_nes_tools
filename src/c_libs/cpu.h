//
// Created by anghelo on 23-02-18.
//

#ifndef ALF_NES_TOOLS_CPU_H
#define ALF_NES_TOOLS_CPU_H

#include <stdlib.h>

struct nesRegisters{
    // https://wiki.nesdev.com/w/index.php/CPU_registers
    unsigned char acumulator; // A
    unsigned char indexX; // X
    unsigned char indexY; // Y
    unsigned short programCounter; // PC
    unsigned char stack; // S
    unsigned char statusRegister; // P
};

#endif //ALF_NES_TOOLS_CPU_H
