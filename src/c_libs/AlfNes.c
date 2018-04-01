//
// Created by anghelo on 30-03-18.
//

#include "AlfNes.h"


AlfNes* initAlfNes(){
    AlfNes* nes = malloc(sizeof(AlfNes));
    nes->cpu = initRegisters();
    nes->ram = initRam();
    nes->ppu = initNesPPU();
    nes->rom = NULL;
    nes->saveData = initSaveGame();

    return nes;
}

int NesPowerUp(AlfNes* nes, char* romFileName){
    int retVal, retValHandled;

    nes->rom = loadRom(romFileName);
    if(nes->rom == NULL){
        return ALF_NES_ERROR_CODE_ROM_CANT_READ;
    }

    retVal = cpuPowerUp(nes->cpu);
    if(retVal < 0){
        retValHandled = handleErrorRet(retVal);
        if(retValHandled < 0){
            return retValHandled;
        }
    }
    retVal = ramPowerUp(nes->ram);
    if(retVal < 0){
        retValHandled = handleErrorRet(retVal);
        if(retValHandled < 0){
            return retValHandled;
        }
    }
    retVal = ppuPowerUp(nes->ppu, nes->rom);
    if(retVal < 0){
        retValHandled = handleErrorRet(retVal);
        if(retValHandled < 0){
            return retValHandled;
        }
    }

    retVal = loadPrgIntoMemory(nes);
    if(retVal < 0){
        retValHandled = handleErrorRet(retVal);
        if(retValHandled < 0){
            return retValHandled;
        }
    }
    retVal = loadSaveData(nes);
    if(retVal < 0){
        retValHandled = handleErrorRet(retVal);
        if(retValHandled < 0){
            return retValHandled;
        }
    }

    return 0;
}

int loadPrgIntoMemory(AlfNes* nes){
    return parseRomToRam(nes->ram, nes->rom);
}

int loadSaveData(AlfNes* nes){
    int retVal = 0;

    if(nes->rom->header->hasSRAM){
        char* fileName = changeExtension(nes->rom->fileName, "ans", 3);

        retVal = loadSaveGameFromFile(nes->saveData, nes->rom->header->SRAMSize, fileName);
        if(retVal < 0){
            return retVal;
        }

        retVal = loadSaveIntoRam(nes->ram, nes->saveData->saveData, nes->rom->header->SRAMSize);
        if(retVal < 0){
            return retVal;
        }
    }

    return 0;
}
