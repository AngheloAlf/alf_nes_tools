//
// Created by anghelo on 23-02-18.
//

#include "common.h"

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

int charLenUntilNull(const unsigned char* src){
    int len = 0;
    for(int i = 0; src[i] != 0; i++){
        len += 1;
    }
    return len;
}


/*
Return value:
  -> == 0: Handled correctly.
  -> != 0: Cannot be handled. Go panic D: .
*/
int handleErrorRet(int retVal){
    if(retVal >= 0){
        return 0;
    }
    switch(retVal){
        case ALF_NES_ERROR_CODE_NOT_IMPLEMENTED:
            printf("Not implemented\n");
            return retVal;
        case ALF_NES_ERROR_CODE_WRITE_ON_READ_ONLY:
            printf("write on read only\n");
            return retVal;
        case ALF_NES_ERROR_CODE_RAM_OUT_1:
        case ALF_NES_ERROR_CODE_RAM_OUT_2:
            printf("Pointer is out of the RAM\n");
            return retVal;
        case ALF_NES_ERROR_CODE_MAPPER_NOT_IMPLEMENTED:
            printf("Mapper not implemented\n");
            return retVal;
        case ALF_NES_ERROR_CODE_ROM_CANT_READ:
            printf("Can't read ROM file.\n");
            return retVal;
        case ALF_NES_ERROR_CODE_SAVE_CANT_READ:
            printf("Can't read Save file.\n");
            return retVal;
        case ALF_NES_ERROR_CODE_SAVE_SIZE_LESS_EXPECTED:
            printf("Save file size is less than expected.\n");
            return retVal;
        case ALF_NES_ERROR_CODE_MAPPER_WRONG_IMPLEMENTATION:
            printf("Mapper has wrong implementation.\n");
            return retVal;
        default:
            printf("Unknown return value.\n");
            return retVal;
    }
}
