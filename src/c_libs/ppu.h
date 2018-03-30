//
// Created by anghelo on 29-03-18.
//

#ifndef ALF_NES_TOOLS_PPU_H
#define ALF_NES_TOOLS_PPU_H

#include <stdlib.h>

#include "romParser.h"
#include "mappers.h"


typedef struct{
    unsigned char ppuCtrl; // $2000
    unsigned char ppuMask; // $2001
    unsigned char ppuStatus; // $2002

    unsigned char oamAddr; // $2003
    unsigned char oamData; // $2004

    unsigned char ppuScroll; // $2005
    unsigned char ppuAddr; // $2006
    unsigned char ppuData; // $2007

    unsigned char oamDMA; // $4014
}NesPPU_Registers;

typedef struct{
    unsigned char* vram;
}NesVRAM;

typedef struct{
    unsigned char* oam;
}NesPPU_OAM;

typedef struct{
    unsigned char* ciram_vram;
}NesPPU_CIRAM;

typedef struct{
    NesVRAM* vram;
    NesPPU_OAM* oam;
    NesPPU_Registers* registers;
    NesPPU_CIRAM* ciram_nametables;
    unsigned char oddFrame;
}NesPPU;


NesPPU* initNesPPU();
void resetNesPPU(NesPPU* ppu);
int parseChrRomToPPU(NesPPU* ppu, NesRom* rom);


#endif //ALF_NES_TOOLS_PPU_H
