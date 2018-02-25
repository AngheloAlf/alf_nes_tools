//
// Created by anghelo on 23-02-18.
//

#include "chr.h"

void printfColoredLine(struct tileLine* simpleLine){
    for(size_t l = 0; l < 8; l++){
        printfAsColor(simpleLine->pixels[l]->number);
    }
}

void iterateChrRom(struct nesRom* rom){
    size_t chrPages = rom->header->realChrPageAmount;
    // struct tile tiles;

    for(size_t i = 0; i < chrPages; i++){
        for(size_t j = 0; j < CHR_ROM_PAGE_SIZE/16; j+=8){
            // tiles = rom->chrRom->tiles[i][j];
            for(size_t k = 0; k < 8; k++){
                printfColoredLine(rom->chrRom->tiles[i][j].lines[k]);
                printf(" ");
                printfColoredLine(rom->chrRom->tiles[i][j+1].lines[k]);
                printf(" ");
                printfColoredLine(rom->chrRom->tiles[i][j+2].lines[k]);
                printf(" ");
                printfColoredLine(rom->chrRom->tiles[i][j+3].lines[k]);
                printf(" ");
                printfColoredLine(rom->chrRom->tiles[i][j+4].lines[k]);
                printf(" ");
                printfColoredLine(rom->chrRom->tiles[i][j+5].lines[k]);
                printf(" ");
                printfColoredLine(rom->chrRom->tiles[i][j+6].lines[k]);
                printf(" ");
                printfColoredLine(rom->chrRom->tiles[i][j+7].lines[k]);
                printf("\n");
            }
            printf("\n");
            // sleep(2);
            printf("\n");
        }
    }


    /*
    for(size_t i = 0; i < chrPages; i++){
        for(size_t j = 0; j < CHR_ROM_PAGE_SIZE/16; j+=2){
            // tiles = rom->chrRom->tiles[i][j];
            for(size_t k = 0; k < 8; k++){
                printfColoredLine(rom->chrRom->tiles[i][j].lines[k]);
                printfColoredLine(rom->chrRom->tiles[i][j+1].lines[k]);
                printf("\n");
            }
            // sleep(2);
            if((j+2)%8 == 0){
                printf("\n");
                sleep(2);
            }
        }
    }
    */
}


struct pixel* generatePixel(unsigned char number, unsigned char color, unsigned char red, unsigned char green, unsigned char blue){
    struct pixel* pixelData = malloc(sizeof(struct pixel));
    pixelData->number = number;
    pixelData->color = color;
    pixelData->red = red;
    pixelData->green = green;
    pixelData->blue = blue;
    return pixelData;
}

struct tileLine* generateTileLine(unsigned char lineA, unsigned char lineB){
    struct tileLine* tileline = malloc(sizeof(struct tileLine));
    tileline->pixels = malloc(sizeof(struct pixel*) * 8);

    unsigned char pixel1Color = (unsigned char)(((lineA & 0b10000000) >> 7) + (((lineB & 0b10000000) >> 7) << 1));
    unsigned char pixel2Color = (unsigned char)(((lineA & 0b01000000) >> 6) + (((lineB & 0b01000000) >> 6) << 1));
    unsigned char pixel3Color = (unsigned char)(((lineA & 0b00100000) >> 5) + (((lineB & 0b00100000) >> 5) << 1));
    unsigned char pixel4Color = (unsigned char)(((lineA & 0b00010000) >> 4) + (((lineB & 0b00010000) >> 4) << 1));
    unsigned char pixel5Color = (unsigned char)(((lineA & 0b00001000) >> 3) + (((lineB & 0b00001000) >> 3) << 1));
    unsigned char pixel6Color = (unsigned char)(((lineA & 0b00000100) >> 2) + (((lineB & 0b00000100) >> 2) << 1));
    unsigned char pixel7Color = (unsigned char)(((lineA & 0b00000010) >> 1) + (((lineB & 0b00000010) >> 1) << 1));
    unsigned char pixel8Color = (unsigned char)(((lineA & 0b00000001) >> 0) + (((lineB & 0b00000001) >> 0) << 1));

    tileline->pixels[0] = generatePixel(pixel1Color, 0, 0, 0, 0);
    tileline->pixels[1] = generatePixel(pixel2Color, 0, 0, 0, 0);
    tileline->pixels[2] = generatePixel(pixel3Color, 0, 0, 0, 0);
    tileline->pixels[3] = generatePixel(pixel4Color, 0, 0, 0, 0);
    tileline->pixels[4] = generatePixel(pixel5Color, 0, 0, 0, 0);
    tileline->pixels[5] = generatePixel(pixel6Color, 0, 0, 0, 0);
    tileline->pixels[6] = generatePixel(pixel7Color, 0, 0, 0, 0);
    tileline->pixels[7] = generatePixel(pixel8Color, 0, 0, 0, 0);

    return tileline;
}

struct tile** generateTilesFromChrRom(unsigned char** chrRom, size_t chrPages){
    struct tile** tiles = malloc(sizeof(struct tile*) * chrPages);

    for(size_t i = 0; i < chrPages; i++){
        tiles[i] = malloc(sizeof(struct tile) * CHR_ROM_PAGE_SIZE/16);
        for(size_t j = 0; j < CHR_ROM_PAGE_SIZE; j += 16){
            tiles[i][j/16].lines = malloc(sizeof(struct tileLine*) * 8);

            tiles[i][j/16].lines[0] = generateTileLine(chrRom[i][j], chrRom[i][j+8]);
            tiles[i][j/16].lines[1] = generateTileLine(chrRom[i][j+1], chrRom[i][j+1+8]);
            tiles[i][j/16].lines[2] = generateTileLine(chrRom[i][j+2], chrRom[i][j+2+8]);
            tiles[i][j/16].lines[3] = generateTileLine(chrRom[i][j+3], chrRom[i][j+3+8]);
            tiles[i][j/16].lines[4] = generateTileLine(chrRom[i][j+4], chrRom[i][j+4+8]);
            tiles[i][j/16].lines[5] = generateTileLine(chrRom[i][j+5], chrRom[i][j+5+8]);
            tiles[i][j/16].lines[6] = generateTileLine(chrRom[i][j+6], chrRom[i][j+6+8]);
            tiles[i][j/16].lines[7] = generateTileLine(chrRom[i][j+7], chrRom[i][j+7+8]);
        }
    }
    return tiles;
}
