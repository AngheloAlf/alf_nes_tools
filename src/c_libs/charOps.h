//
// Created by anghelo on 23-02-18.
//

#ifndef ALF_NES_TOOLS_CHAROPS_H
#define ALF_NES_TOOLS_CHAROPS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define ANSI_COLOR_BLACK   "\x1b[30m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_WHITE   "\x1b[37m"
#define ANSI_COLOR_RESET   "\x1b[0m"


#define BIT_0   0b00000001
#define BIT_1   0b00000010
#define BIT_2   0b00000100
#define BIT_3   0b00001000
#define BIT_4   0b00010000
#define BIT_5   0b00100000
#define BIT_6   0b01000000
#define BIT_7   0b10000000

#define HIGH_NIBBLE 0b11110000
#define LOW_NIBBLE  0b00001111


void charCopy(unsigned char* dst, const unsigned char* src, size_t size);
unsigned char *newCharFromIndex(const unsigned char* src, size_t size, size_t start);
void printfCharAsHex(unsigned char character);
void printfAsColor(unsigned char character, int withNumber);

char* changeExtension(const char* word, const char* newExt, int lenExt);

int charLenUntilNull(const unsigned char* src);


#endif //ALF_NES_TOOLS_CHAROPS_H
