//
// Created by anghelo on 23-02-18.
//

#ifndef ALF_NES_TOOLS_CHAROPS_H
#define ALF_NES_TOOLS_CHAROPS_H

#include <stdlib.h>
#include <stdio.h>


#define ANSI_COLOR_BLACK   "\x1b[30m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_WHITE   "\x1b[37m"
#define ANSI_COLOR_RESET   "\x1b[0m"


void charCopy(unsigned char* dst, const unsigned char* src, size_t size);
unsigned char *newCharFromIndex(const unsigned char* src, size_t size, size_t start);
void printfCharAsHex(unsigned char character);
void printfAsColor(unsigned char character, int withNumber);

char* changeExtension(const char* word, const char* newExt, int lenExt);


#endif //ALF_NES_TOOLS_CHAROPS_H
