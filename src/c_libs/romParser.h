//
// Created by anghelo on 23-02-18.
//

#ifndef ALF_NES_TOOLS_ROMPARSER_H
#define ALF_NES_TOOLS_ROMPARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PRG_ROM_PAGE_SIZE 0x4000

struct nesRomHeader{
    unsigned char* header;
    unsigned char* consType;
    unsigned char prgPageAmount;
    unsigned char chrPageAmount;
    unsigned char flags6;
    unsigned char flags7;
    unsigned char flags8;
    unsigned char flags9;
    unsigned char flags10;
    unsigned char flags11;
    unsigned char flags12;
    unsigned char flags13;
    unsigned char flags14;
    unsigned char flags15;
    unsigned char typeVersion;

    unsigned int realPrgPageAmount;
    unsigned int realChrPageAmount;

    unsigned int mapperId;
    unsigned char subMapper;

    char hasSRAM;
    unsigned short SRAMSize;
};

struct nesPrgRom{
    unsigned char** prgRom; // [x][16384]
};


struct nesChrRom{
    unsigned char** chrRom; // [y][8192]
    struct tile** tiles;
};


struct nesRom{
    struct nesRomHeader* header;
    unsigned char* trainer; // [512 bytes]
    struct nesPrgRom* prgRom; // 16384 * x bytes
    struct nesChrRom* chrRom; // [8192 * y bytes]
    unsigned char* playChoiceInstRom; // [8192 bytes]
    unsigned char* playChoicePRom; // [16 bytes Data, 16 bytes CounterOut]
    unsigned char* title; // [127 or 128 byte]
};

long fileSize;

struct nesRomHeader* loadInesHeader(unsigned char* header);
struct nesRom* generateINesRom(struct nesRomHeader* header, unsigned char* trainer, struct nesPrgRom* prgRomData, struct nesChrRom* chrRomData, unsigned char* playChoiceInstRom, unsigned char* playChoicePRom, unsigned char* title);
struct nesRom* loadINesRom(FILE* filePtr, unsigned char* header);
struct nesRom* loadRom(char* filename);


#endif //ALF_NES_TOOLS_ROMPARSER_H

#include "chr.h"
#include "charOps.h"
