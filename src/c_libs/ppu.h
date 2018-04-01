//
// Created by anghelo on 29-03-18.
//

#ifndef ALF_NES_TOOLS_PPU_H
#define ALF_NES_TOOLS_PPU_H

#include "common.h"
#include "romParser.h"


NesPPU* initNesPPU();
int ppuPowerUp(NesPPU* ppu, NesRom* rom);
int resetNesPPU(NesPPU* ppu, NesRom* rom);
int loadChrIntoPPU(NesPPU* ppu, NesRom* rom);


#endif //ALF_NES_TOOLS_PPU_H
