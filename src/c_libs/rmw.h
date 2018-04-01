//
// Created by anghelo on 15-03-18.
//

#ifndef ALF_NES_TOOLS_RMW_H
#define ALF_NES_TOOLS_RMW_H

#include "common.h"
#include "cpu.h"

unsigned char ASL(NesCPURegisters* registers, unsigned char number);
unsigned char ROL(NesCPURegisters* registers, unsigned char number);
unsigned char LSR(NesCPURegisters* registers, unsigned char number);
unsigned char ROR(NesCPURegisters* registers, unsigned char number);
void LDX(NesCPURegisters* registers, unsigned char number);
unsigned char DEC(NesCPURegisters* registers, unsigned char number);
unsigned char INC(NesCPURegisters* registers, unsigned char number);

#endif //ALF_NES_TOOLS_RMW_H
