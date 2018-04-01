//
// Created by anghelo on 30-03-18.
//

#ifndef ALF_NES_TOOLS_SAVEGAME_H
#define ALF_NES_TOOLS_SAVEGAME_H

#include <stdlib.h>

#include "common.h"


typedef struct{
    unsigned char* saveData;
    char* fileName;
    char hasSRAM;
}NesSaveGame;


NesSaveGame* initSaveGame();

int loadSaveGameFromFile(NesSaveGame* save, unsigned short SRAMSize, const char* saveFileName);

#endif //ALF_NES_TOOLS_SAVEGAME_H
