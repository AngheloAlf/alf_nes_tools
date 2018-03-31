//
// Created by anghelo on 30-03-18.
//

#include "saveGame.h"

NesSaveGame* initSaveGame(){
    NesSaveGame* save = malloc(sizeof(NesSaveGame));
    save->saveData = NULL;
    save->fileName = NULL;
    save->hasSRAM = 0;
    return save;
}

int loadSaveGameFromFile(NesSaveGame* save, unsigned short SRAMSize, const char* saveFileName){
    save->hasSRAM = 1;
    save->fileName = malloc(sizeof(char) * strlen(saveFileName));
    strcpy(save->fileName, saveFileName);

    save->saveData = calloc(SRAMSize, sizeof(char));
    FILE* filePtr = fopen(save->fileName, "rb");
    if(filePtr == NULL){
        filePtr = fopen(save->fileName, "wb");
        if(filePtr == NULL){
            return -7;
        }
        fwrite(save->saveData, 1, SRAMSize, filePtr);
        fclose(filePtr);
    }
    else{
        size_t readedSize = fread(save->saveData, 1, SRAMSize, filePtr);
        fclose(filePtr);
        if(readedSize != SRAMSize){
            return -8;
        }
    }

    return 0;
}
