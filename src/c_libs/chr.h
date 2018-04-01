//
// Created by anghelo on 23-02-18.
//

#ifndef ALF_NES_TOOLS_CHR_H
#define ALF_NES_TOOLS_CHR_H

#include "common.h"
#include "romParser.h"

#define CHR_ROM_PAGE_SIZE 0x2000

struct pixel{
    unsigned char number;
    unsigned char color;
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

struct tileLine{
    struct pixel** pixels;
};

struct tile{
    struct tileLine** lines;
};

void printfChrRom(NesRom* rom, int withNumber);
struct pixel* generatePixel(unsigned char number, unsigned char color, unsigned char red, unsigned char green, unsigned char blue);
struct tileLine* generateTileLine(unsigned char lineA, unsigned char lineB);
struct tile** generateTilesFromChrRom(unsigned char** chrRom, size_t chrPages);


#endif //ALF_NES_TOOLS_CHR_H
