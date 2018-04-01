//
// Created by anghelo on 23-02-18.
//

#ifndef ALF_NES_TOOLS_ROMPARSER_H
#define ALF_NES_TOOLS_ROMPARSER_H

#include "common.h"


long fileSize;

NesRomHeader* loadInesHeader(unsigned char* header);
NesRom* generateINesRom(NesRomHeader* header, unsigned char* trainer, NesPrgRom* prgRomData, NesChrRom* chrRomData, unsigned char* playChoiceInstRom, unsigned char* playChoicePRom, unsigned char* title, char* fileName);
NesRom* loadINesRom(FILE* filePtr, unsigned char* header, char* fileName);
NesRom* loadRom(char* filename);


// Mappers:
int firstPageToLoad(NesRomHeader* header);
int secondPageToLoad(NesRomHeader* header);
int chrPageToLoad(NesRomHeader* header);


#endif //ALF_NES_TOOLS_ROMPARSER_H
