//
// Created by anghelo on 25-02-18.
//

#ifndef ALF_NES_TOOLS_INSTCALLBACK_H
#define ALF_NES_TOOLS_INSTCALLBACK_H
void opcode_00(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);

#endif //ALF_NES_TOOLS_INSTCALLBACK_H

#include "instructions.h"
#include "cpu.h"
#include "ram.h"
