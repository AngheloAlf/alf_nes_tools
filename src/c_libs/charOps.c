//
// Created by anghelo on 23-02-18.
//

#include "charOps.h"

void charCopy(unsigned char* dst, unsigned char* src, size_t size){
    for(size_t i = 0; i < size; i++){
        dst[i] = src[i];
    }
}

unsigned char *newCharFromIndex(unsigned char* src, size_t size, size_t start){
    unsigned char* dst = malloc(sizeof(unsigned char));
    for(size_t i = 0; i < size; i++){
        // printf("\tdst[%i] = src[%i] = %i;\n", i, start + i, src[start + i]);
        dst[i] = src[start + i];
    }
    return dst;
}

void printfCharAsHex(unsigned char character){
    if(character < 0x10){
        printf("0");
    }
    printf("%x", character);
}

void printfAsColor(unsigned char character){
    printf("\x1b[%im%i" ANSI_COLOR_RESET, character+30, character);
}
