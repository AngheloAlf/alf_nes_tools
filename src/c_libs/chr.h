//
// Created by anghelo on 23-02-18.
//

#ifndef ALF_NES_TOOLS_CHR_H
#define ALF_NES_TOOLS_CHR_H

#include "romParser.h"
#include "charOps.h"

#define CHR_ROM_PAGE_SIZE 8192

struct pixel{
    unsigned char number;
    unsigned char color;
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

struct tileLine{
    struct pixel* pixel1;
    struct pixel* pixel2;
    struct pixel* pixel3;
    struct pixel* pixel4;
    struct pixel* pixel5;
    struct pixel* pixel6;
    struct pixel* pixel7;
    struct pixel* pixel8;
};

struct tile{
    struct tileLine* line1;
    struct tileLine* line2;
    struct tileLine* line3;
    struct tileLine* line4;
    struct tileLine* line5;
    struct tileLine* line6;
    struct tileLine* line7;
    struct tileLine* line8;
};


struct pixel* generatePixel(unsigned char number, unsigned char color, unsigned char red, unsigned char green, unsigned char blue);
struct tileLine* generateTileLine(unsigned char lineA, unsigned char lineB);
struct tile** generateTilesFromChrRom(unsigned char** chrRom, size_t chrPages);


#endif //ALF_NES_TOOLS_CHR_H
