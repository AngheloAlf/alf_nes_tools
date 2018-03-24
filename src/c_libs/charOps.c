//
// Created by anghelo on 23-02-18.
//

#include "charOps.h"

void charCopy(unsigned char* dst, const unsigned char* src, size_t size){
    for(size_t i = 0; i < size; i++){
        dst[i] = src[i];
    }
}

unsigned char *newCharFromIndex(const unsigned char* src, size_t size, size_t start){
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

void printfAsColor(unsigned char character, int withNumber){
    // printf("\x1b[%im%i" ANSI_COLOR_RESET, character+30, character);
    if(withNumber){
        printf("\033[%im%i " ANSI_COLOR_RESET, character + 40, character);
    }
    else{
        printf("\033[%im  " ANSI_COLOR_RESET, character + 40);
    }
}

char* changeExtension(const char* word, const char* newExt, int lenExt){
    int oldLen = 0, lastDotLen = 0, lenChange = 0;
    char* newWord;

    for(int i = 0; word[i]!= 0x0; i++){
        if(word[i] == '.'){
            lastDotLen = i;
        }
        oldLen += 1;
    }

    if(lastDotLen != 0){
        lenChange = lastDotLen;
    }
    else{
        lenChange = oldLen;
    }
    newWord = malloc(sizeof(char)*(lenChange + lenExt + 2));

    for(int i = 0; i < lenChange; i++){
        newWord[i] = word[i];
    }
    newWord[lenChange] = '.';
    for(int i = 0; i < lenExt; i++){
        newWord[lenChange + i + 1] = newExt[i];
    }
    newWord[lenChange + lenExt + 1] = 0x0;

    return newWord;
}
