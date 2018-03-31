//
// Created by anghelo on 30-03-18.
//

#ifndef ALF_NES_TOOLS_ALFNES_H
#define ALF_NES_TOOLS_ALFNES_H

#include "cpu.h"
#include "ram.h"
#include "ppu.h"
#include "romParser.h"
#include "saveGame.h"

#include "charOps.h"


typedef struct{
    NesCPURegisters* cpu;
    NesRam* ram;
    NesPPU* ppu;
    NesRom* rom;
    NesSaveGame* saveData;
}AlfNes;

AlfNes* initAlfNes();
int NesPowerUp(AlfNes* nes, char* romFileName);

int loadPrgIntoMemory(AlfNes* nes);
int loadSaveData(AlfNes* nes);

#endif //ALF_NES_TOOLS_ALFNES_H
