//
// Created by anghelo on 23-02-18.
//

#ifndef ALF_NES_TOOLS_INSTRUCTIONS_H
#define ALF_NES_TOOLS_INSTRUCTIONS_H


#include <stdio.h>
#include "romParser.h"
#include "charOps.h"
#include "string.h"

struct instruction{
    // https://wiki.nesdev.com/w/index.php/CPU_unofficial_opcodes
    // http://www.6502.org/tutorials/6502opcodes.html

    unsigned char opcode;
    unsigned char byte1;
    unsigned char byte2;
    unsigned char bytesAmount;
    unsigned char type;
    /*
    types:
        0:  Accumulator
        1:  Immediate
        2:  Zero Page
        3:  Zero Page,X
        4:  Zero Page,Y
        5:  Absolute
        6:  Absolute,X
        7:  Absolute,Y
        8:  Indirect
        9:  Indirect,X
        10: Indirect,Y
        11: Implied
    */


};

struct instruction* detectType(unsigned char* inst);
void printfInstructions(struct nesRom* rom);
void iterateInstructions(struct nesRom* rom);


#endif //ALF_NES_TOOLS_INSTRUCTIONS_H
