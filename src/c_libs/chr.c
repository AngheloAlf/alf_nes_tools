//
// Created by anghelo on 23-02-18.
//

#include "chr.h"

void iterateChrRom(struct nesRom* rom){
    /*
    unsigned int chrSize = rom->header->realChrPageAmount * 8 * 1024;
    unsigned char data[chrSize/16][8][8];
    *//*
	for(int i = 0; i < chrSize/16; i++){
		// rom->chrRom[i];


		for(int j = 0; j < 16; j++){
			unsigned char line = rom->chrRom[i*16 + j];

			unsigned char first  = (line & 0b11000000)>>6;
			unsigned char second = (line & 0b00110000)>>4;
			unsigned char third  = (line & 0b00001100)>>2;
			unsigned char fourth = (line & 0b00000011)>>0;

			if(j%2 == 0){
				data[i][j/2][0] = first;
				data[i][j/2][1] = second;
				data[i][j/2][2] = third;
				data[i][j/2][3] = fourth;
			}
			else{
				data[i][j/2][4] = first;
				data[i][j/2][5] = second;
				data[i][j/2][6] = third;
				data[i][j/2][7] = fourth;
			}

			unsigned char line = rom->chrRom[i*16 + j];

			unsigned char first  = (line & 0b11000000)>>6;
			unsigned char second = (line & 0b00110000)>>4;
			unsigned char third  = (line & 0b00001100)>>2;
			unsigned char fourth = (line & 0b00000011)>>0;

			printfAsColor(first);
			printfAsColor(second);
			printfAsColor(third);
			printfAsColor(fourth);
			// printf("%i%i%i%i", first, second, third, fourth);

			if((j+1) % 2 == 0){
				printf("\n");
			}
			*/
    /*}

    // printf("\n\n");
    // sleep(1);
}


for(int i = 0; i < chrSize/16/2; i += 4){
    for(int j = 0; j < 8; j++){
        for(int k = 0; k < 8; k++){
            printfAsColor(data[i/2][j][k]);
        }
        printf(" ");
        for(int k = 0; k < 8; k++){
            printfAsColor(data[i/2 + 1][j][k]);
        }
        printf(" ");
        for(int k = 0; k < 8; k++){
            printfAsColor(data[i/2 + 2][j][k]);
        }
        printf(" ");
        for(int k = 0; k < 8; k++){
            printfAsColor(data[i/2 + 3][j][k]);
        }
        printf("\n");
    }
    printf("\n\n");
    sleep(1);
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

    unsigned char pixel1Color = ((lineA & 0b10000000) >> 7) + (((lineB & 0b10000000) >> 7) << 1);
    unsigned char pixel2Color = ((lineA & 0b01000000) >> 6) + (((lineB & 0b01000000) >> 6) << 1);
    unsigned char pixel3Color = ((lineA & 0b00100000) >> 5) + (((lineB & 0b00100000) >> 5) << 1);
    unsigned char pixel4Color = ((lineA & 0b00010000) >> 4) + (((lineB & 0b00010000) >> 4) << 1);
    unsigned char pixel5Color = ((lineA & 0b00001000) >> 3) + (((lineB & 0b00001000) >> 3) << 1);
    unsigned char pixel6Color = ((lineA & 0b00000100) >> 2) + (((lineB & 0b00000100) >> 2) << 1);
    unsigned char pixel7Color = ((lineA & 0b00000010) >> 1) + (((lineB & 0b00000010) >> 1) << 1);
    unsigned char pixel8Color = ((lineA & 0b00000001) >> 0) + (((lineB & 0b00000001) >> 0) << 1);

    tileline->pixel1 = generatePixel(pixel1Color, 0, 0, 0, 0);
    tileline->pixel2 = generatePixel(pixel2Color, 0, 0, 0, 0);
    tileline->pixel3 = generatePixel(pixel3Color, 0, 0, 0, 0);
    tileline->pixel4 = generatePixel(pixel4Color, 0, 0, 0, 0);
    tileline->pixel5 = generatePixel(pixel5Color, 0, 0, 0, 0);
    tileline->pixel6 = generatePixel(pixel6Color, 0, 0, 0, 0);
    tileline->pixel7 = generatePixel(pixel7Color, 0, 0, 0, 0);
    tileline->pixel8 = generatePixel(pixel8Color, 0, 0, 0, 0);

    return tileline;
}

struct tile** generateTilesFromChrRom(unsigned char** chrRom, size_t chrPages){
    struct tile** tiles = malloc(sizeof(struct tile*) * chrPages);

    for(size_t i = 0; i < chrPages; i++){
        tiles[i] = malloc(sizeof(struct tile) * CHR_ROM_PAGE_SIZE/16);
        //printf("%i\n", (int)i);
        for(size_t j = 0; j < CHR_ROM_PAGE_SIZE; j += 16){
            //	printf("\tj: %i - %i\n", (int)j, (int)j/16);
            tiles[i][j/16].line1 = generateTileLine(chrRom[i][j], chrRom[i][j+1]);
            tiles[i][j/16].line2 = generateTileLine(chrRom[i][j+2], chrRom[i][j+3]);
            tiles[i][j/16].line3 = generateTileLine(chrRom[i][j+4], chrRom[i][j+5]);
            tiles[i][j/16].line4 = generateTileLine(chrRom[i][j+6], chrRom[i][j+7]);
            tiles[i][j/16].line5 = generateTileLine(chrRom[i][j+8], chrRom[i][j+9]);
            tiles[i][j/16].line6 = generateTileLine(chrRom[i][j+10], chrRom[i][j+11]);
            tiles[i][j/16].line7 = generateTileLine(chrRom[i][j+12], chrRom[i][j+13]);
            tiles[i][j/16].line8 = generateTileLine(chrRom[i][j+14], chrRom[i][j+15]);
        }
    }
    return tiles;
}
