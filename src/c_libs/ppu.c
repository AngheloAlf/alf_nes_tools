//
// Created by anghelo on 29-03-18.
//

#include "ppu.h"

NesPPU_Registers* initPPURegisters(){
    NesPPU_Registers* registers = malloc(sizeof(NesPPU_Registers));

    registers->ppuCtrl = 0x0; // $2000
    registers->ppuMask = 0x0; // $2001
    registers->ppuStatus = 0xA0; // $2002

    registers->oamAddr = 0x0; // $2003
    registers->oamData = 0x0; // $2004

    registers->ppuScroll = 0x0; // $2005
    registers->ppuAddr = 0x0; // $2006
    registers->ppuData = 0x0; // $2007

    registers->oamDMA = 0x0; // $4014

    return registers;
}

NesVRAM* initNesVRAM(){
    NesVRAM* vram = malloc(sizeof(NesVRAM));
    vram->vram = calloc(0x4000, sizeof(unsigned char));
    return vram;
}

NesPPU_OAM* initNesOAM(){
    NesPPU_OAM* oam = malloc(sizeof(NesPPU_OAM));
    oam->oam = calloc(0x0100, sizeof(unsigned char));
    return oam;
}

NesPPU_CIRAM* initNesCIRAM(){
    NesPPU_CIRAM* ciram = malloc(sizeof(NesPPU_CIRAM));
    ciram->ciram_vram = calloc(0x0800, sizeof(unsigned char));
    return ciram;
}

NesPPU* initNesPPU(){
    NesPPU* ppu = malloc(sizeof(NesPPU));
    ppu->vram = initNesVRAM();
    ppu->oam = initNesOAM();
    ppu->registers = initPPURegisters();
    ppu->ciram_nametables = initNesCIRAM();
    ppu->oddFrame = 0x0;

    return ppu;
}

int ppuPowerUp(NesPPU* ppu, NesRom* rom){
    ppu->registers->ppuCtrl = 0x0; // $2000
    ppu->registers->ppuMask = 0x0; // $2001
    ppu->registers->ppuStatus = 0xA0; // $2002

    ppu->registers->oamAddr = 0x0; // $2003
    ppu->registers->oamData = 0x0; // $2004

    ppu->registers->ppuScroll = 0x0; // $2005
    ppu->registers->ppuAddr = 0x0; // $2006
    ppu->registers->ppuData = 0x0; // $2007

    ppu->registers->oamDMA = 0x0; // $4014

    if(rom->chrRom != NULL){
        int retVal = loadChrIntoPPU(ppu, rom);
        if(retVal < 0){
            return retVal;
        }
    }

    return 0;
}

int resetNesPPU(NesPPU* ppu, NesRom* rom){
    ppu->registers->ppuCtrl = 0x0;
    ppu->registers->ppuMask = 0x0;

    ppu->registers->ppuScroll = 0x0;
    ppu->registers->ppuData = 0x0;

    ppu->oddFrame = 0x0;

    if(rom->chrRom != NULL){
        int retVal = loadChrIntoPPU(ppu, rom);
        if(retVal < 0){
            return retVal;
        }
    }

    return 0;
}

int loadChrIntoPPU(NesPPU* ppu, NesRom* rom){
    if(rom->chrRom != NULL && rom->chrRom->chrRom != NULL){
        int page = chrPageToLoad(rom->header);
        if(page < 0){
            return page;
        }
        charCopy(ppu->vram->vram, rom->chrRom->chrRom[page], CHR_ROM_PAGE_SIZE);
    }
    return 0;
}
