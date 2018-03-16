//
// Created by anghelo on 15-03-18.
//

#ifndef ALF_NES_TOOLS_RMW_H
#define ALF_NES_TOOLS_RMW_H

#include "cpu.h"

unsigned char ASL(struct nesRegisters* registers, unsigned char number);
unsigned char ROL(struct nesRegisters* registers, unsigned char number);
unsigned char LSR(struct nesRegisters* registers, unsigned char number);
unsigned char ROR(struct nesRegisters* registers, unsigned char number);
void LDX(struct nesRegisters* registers, unsigned char number);
unsigned char DEC(struct nesRegisters* registers, unsigned char number);
unsigned char INC(struct nesRegisters* registers, unsigned char number);

#endif //ALF_NES_TOOLS_RMW_H
