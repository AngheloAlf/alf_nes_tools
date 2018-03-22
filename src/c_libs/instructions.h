//
// Created by anghelo on 23-02-18.
//

#ifndef ALF_NES_TOOLS_INSTRUCTIONS_H
#define ALF_NES_TOOLS_INSTRUCTIONS_H


#include <stdio.h>
#include <string.h>

#include "romParser.h"
#include "charOps.h"
#include "cpu.h"
#include "instCallback.h"
#include "ram.h"


#define TYPE_ACCUMULATOR    0
#define TYPE_IMMEDIATE      1
#define TYPE_ZERO_PAGE      2
#define TYPE_ZERO_PAGE_X    3
#define TYPE_ZERO_PAGE_Y    4
#define TYPE_ABSOLUTE       5
#define TYPE_ABSOLUTE_X     6
#define TYPE_ABSOLUTE_Y     7
#define TYPE_INDIRECT       8
#define TYPE_INDIRECT_X     9
#define TYPE_INDIRECT_Y     10
#define TYPE_IMPLIED        11
#define TYPE_RELATIVE       12


#define SIZE_ACCUMULATOR    0
#define SIZE_IMMEDIATE      1
#define SIZE_ZERO_PAGE      1
#define SIZE_ZERO_PAGE_X    1
#define SIZE_ZERO_PAGE_Y    1
#define SIZE_ABSOLUTE       2
#define SIZE_ABSOLUTE_X     2
#define SIZE_ABSOLUTE_Y     2
#define SIZE_INDIRECT       2
#define SIZE_INDIRECT_X     1
#define SIZE_INDIRECT_Y     1
#define SIZE_IMPLIED        0
#define SIZE_RELATIVE       1


struct instruction{
    // https://wiki.nesdev.com/w/index.php/CPU_unofficial_opcodes
    // http://www.6502.org/tutorials/6502opcodes.html
    // http://www.obelisk.me.uk/6502/reference.html
    // http://nesdev.com/undocumented_opcodes.txt
    // http://www.emulator101.com/6502-addressing-modes.html

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
    int (*execute)(struct instruction*, struct nesRegisters*, struct nesRam*);

    char cycles;
};

struct instruction* detectType(unsigned char* inst, char extraCicles);
void printfInstructions(struct nesRom* rom);
void iterateInstructions(struct nesRom* rom);

unsigned short loadAddress(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
unsigned char loadNumberFromRamOrArg(struct instruction *instData, struct nesRegisters *registers, struct nesRam *ram);

void printfOpcodeSyntax(struct instruction* instData);
void printfInstruction(struct instruction* instData);

#endif //ALF_NES_TOOLS_INSTRUCTIONS_H
