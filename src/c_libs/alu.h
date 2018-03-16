//
// Created by anghelo on 13-03-18.
//

#ifndef ALF_NES_TOOLS_ALU_H
#define ALF_NES_TOOLS_ALU_H

#include "instructions.h"

/*
return values:
    retVal == 0: ok
    retVal < 0: error code

errors codes:
    -1: not implemented
    -2: writeOnReadOnly
    -3:
    -4:

*/

// ORA (bitwise OR with Accumulator)
int ORA(struct nesRegisters *registers, char number);
// AND (bitwise AND with accumulator)
int AND(struct nesRegisters* registers, char number);
// EOR (bitwise Exclusive OR)
int EOR(struct nesRegisters* registers, char number);
// ADC (ADd with Carry)
int ADC(struct nesRegisters *registers, char number);
// STA (STore Accumulator)
int STA(struct nesRegisters* registers, unsigned short number, struct nesRam* ram);
// LDA (LoaD Accumulator)
int LDA(struct nesRegisters* registers, char number);
// CMP (CoMPare accumulator)
int CMP(struct nesRegisters* registers, char number);
// SBC (SuBtract with Carry)
int SBC(struct nesRegisters* registers, char number);


#endif //ALF_NES_TOOLS_ALU_H
