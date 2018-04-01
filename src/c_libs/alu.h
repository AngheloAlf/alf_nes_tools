//
// Created by anghelo on 13-03-18.
//

#ifndef ALF_NES_TOOLS_ALU_H
#define ALF_NES_TOOLS_ALU_H

#include "common.h"

#include "cpu.h"
#include "ram.h"


/*
return values:
    retVal == 0: ok
    retVal < 0: error code
*/

// ORA (bitwise OR with Accumulator)
int ORA(NesCPURegisters *registers, char number);
// AND (bitwise AND with accumulator)
int AND(NesCPURegisters* registers, char number);
// EOR (bitwise Exclusive OR)
int EOR(NesCPURegisters* registers, char number);
// ADC (ADd with Carry)
int ADC(NesCPURegisters *registers, char number);
// STA (STore Accumulator)
int STA(NesCPURegisters* registers, unsigned short number, NesRam* ram);
// LDA (LoaD Accumulator)
int LDA(NesCPURegisters* registers, char number);
// CMP (CoMPare accumulator)
int CMP(NesCPURegisters* registers, char number);
// SBC (SuBtract with Carry)
int SBC(NesCPURegisters* registers, char number);


#endif //ALF_NES_TOOLS_ALU_H
