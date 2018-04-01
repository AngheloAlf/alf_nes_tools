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


#define ALF_NES_ERROR_CODE_NOT_IMPLEMENTED              (-1)
#define ALF_NES_ERROR_CODE_WRITE_ON_READ_ONLY           (-2)
#define ALF_NES_ERROR_CODE_RAM_OUT_1                    (-3)
#define ALF_NES_ERROR_CODE_RAM_OUT_2                    (-4)
#define ALF_NES_ERROR_CODE_MAPPER_NOT_IMPLEMENTED       (-5)
#define ALF_NES_ERROR_CODE_ROM_CANT_READ                (-6)
#define ALF_NES_ERROR_CODE_SAVE_CANT_READ               (-7)
#define ALF_NES_ERROR_CODE_SAVE_SIZE_LESS_EXPECTED      (-8)
#define ALF_NES_ERROR_CODE_MAPPER_WRONG_IMPLEMENTATION  (-9)
#define ALF_NES_ERROR_CODE_UNKNOWN_OPCODE               (-10)

/* errors codes:
    -1: not implemented
    -2: writeOnReadOnly
    -3:
    -4:
    -5: mapper not implemented
    -6: can't read rom
    -7: can't read save
    -8: size of save less than expected
    -9: wrong implementation of mapper
 */

/* constants */
#define PRG_ROM_PAGE_SIZE 0x4000
#define CHR_ROM_PAGE_SIZE 0x2000

#define RAM_SIZE 0x10000

#define RAM_ROM_FIRST_PAGE 0x8000
#define RAM_ROM_LAST_PAGE 0xC000
/* end constants */

/* structs: */
typedef struct{
    char accumulator; // A
    unsigned char indexX; // X
    unsigned char indexY; // Y
    unsigned short programCounter; // PC
    unsigned char stack; // S
    unsigned char statusRegister; // P

    unsigned char disablePC;
    unsigned char jumping;
    unsigned char jumpingSubroutine;
}NesCPURegisters;

typedef struct{
    unsigned char* ram;

    unsigned char* readOnlyRam;
    unsigned char writeOnReadOnly;
    unsigned short wroAddress; // write on read only address
    unsigned char wroValue; // write on read only value

    unsigned char* saveData;
}NesRam;

typedef struct instruction{
    unsigned char opcode;
    unsigned char byte1;
    unsigned char byte2;
    unsigned char bytesAmount;
    unsigned char type;

    int (*execute)(struct instruction*, NesCPURegisters*, NesRam*);

    char cycles;
}Instruction;


typedef struct{
    unsigned char* header;
    unsigned char* consType;
    unsigned char prgPageAmount;
    unsigned char chrPageAmount;
    unsigned char flags6;
    unsigned char flags7;
    unsigned char flags8;
    unsigned char flags9;
    unsigned char flags10;
    unsigned char flags11;
    unsigned char flags12;
    unsigned char flags13;
    unsigned char flags14;
    unsigned char flags15;
    unsigned char typeVersion;

    unsigned int realPrgPageAmount;
    unsigned int realChrPageAmount;

    unsigned int mapperId;
    unsigned char subMapper;

    char hasSRAM;
    unsigned short SRAMSize;
}NesRomHeader;

typedef struct{
    unsigned char** prgRom; // [x][16384]
}NesPrgRom;

typedef struct{
    unsigned char** chrRom; // [y][8192]
}NesChrRom;

typedef struct{
    NesRomHeader* header;
    unsigned char* trainer; // [512 bytes]
    NesPrgRom* prgRom; // 16384 * x bytes
    NesChrRom* chrRom; // [8192 * y bytes]
    unsigned char* playChoiceInstRom; // [8192 bytes]
    unsigned char* playChoicePRom; // [16 bytes Data, 16 bytes CounterOut]
    unsigned char* title; // [127 or 128 byte]

    char* fileName;
}NesRom;


typedef struct{
    unsigned char ppuCtrl; // $2000
    unsigned char ppuMask; // $2001
    unsigned char ppuStatus; // $2002

    unsigned char oamAddr; // $2003
    unsigned char oamData; // $2004

    unsigned char ppuScroll; // $2005
    unsigned char ppuAddr; // $2006
    unsigned char ppuData; // $2007

    unsigned char oamDMA; // $4014
}NesPPU_Registers;

typedef struct{
    unsigned char* vram;
}NesVRAM;

typedef struct{
    unsigned char* oam;
}NesPPU_OAM;

typedef struct{
    unsigned char* ciram_vram;
}NesPPU_CIRAM;

typedef struct{
    NesVRAM* vram;
    NesPPU_OAM* oam;
    NesPPU_Registers* registers;
    NesPPU_CIRAM* ciram_nametables;
    unsigned char oddFrame;
}NesPPU;


typedef struct{
    unsigned char* saveData;
    char* fileName;
    char hasSRAM;
}NesSaveGame;

/* end structs */


void charCopy(unsigned char* dst, const unsigned char* src, size_t size);
unsigned char *newCharFromIndex(const unsigned char* src, size_t size, size_t start);
void printfCharAsHex(unsigned char character);
void printfAsColor(unsigned char character, int withNumber);

char* changeExtension(const char* word, const char* newExt, int lenExt);

int charLenUntilNull(const unsigned char* src);

int handleErrorRet(int retVal);

#endif //ALF_NES_TOOLS_CHAROPS_H
