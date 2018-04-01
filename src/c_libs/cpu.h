//
// Created by anghelo on 23-02-18.
//

#ifndef ALF_NES_TOOLS_CPU_H
#define ALF_NES_TOOLS_CPU_H

#include "common.h"

#include "instructions.h"
#include "ram.h"

// possible joysticks libs:
// - https://github.com/wgois/OIS
// - https://github.com/Tasssadar/libenjoy

// master clock (CLK):
// - NTSC:
//   -> CPU divide CLK by 12
//   -> PPU divide CLK by 4
//   -> 3 PPU ticks per CPU cycle
// - PAL:
//   -> CPU divide CLK by 16
//   -> PPU divide CLK by 5
//   -> 3.2 PPU ticks per CPU cycle

// https://wiki.nesdev.com/w/index.php/CPU_registers

NesCPURegisters* initRegisters();

// https://wiki.nesdev.com/w/index.php/CPU_power_up_state
int cpuPowerUp(NesCPURegisters *registers);
int resetCpu(NesCPURegisters* registers, NesRam* ram);

int executeInstructions(NesCPURegisters* registers, NesRam* ram, NesRom* rom);

// http://wiki.nesdev.com/w/index.php/CPU_status_flag_behavior
void setCarry(NesCPURegisters* registers);
void clearCarry(NesCPURegisters* registers);
char getCarry(NesCPURegisters* registers);
void setZero(NesCPURegisters* registers);
void clearZero(NesCPURegisters* registers);
char getZero(NesCPURegisters* registers);
void setInterrupt(NesCPURegisters* registers);
void clearInterrupt(NesCPURegisters* registers);
char getInterrupt(NesCPURegisters* registers);
void setDecimal(NesCPURegisters* registers);
void clearDecimal(NesCPURegisters* registers);
char getDecimal(NesCPURegisters* registers);
void setS(NesCPURegisters* registers);
void clearS(NesCPURegisters* registers);
char getS(NesCPURegisters* registers);
void setOverflow(NesCPURegisters* registers);
void clearOverflow(NesCPURegisters* registers);
char getOverflow(NesCPURegisters* registers);
void setNegative(NesCPURegisters* registers);
void clearNegative(NesCPURegisters* registers);
char getNegative(NesCPURegisters* registers);

void disablePC(NesCPURegisters* registers);
void enablePC(NesCPURegisters* registers);

void parseZeroNegative(NesCPURegisters* registers, char number);

void pushStack(NesCPURegisters* registers, NesRam* ram, unsigned char value);
unsigned char pullStack(NesCPURegisters* registers, NesRam* ram);

#endif //ALF_NES_TOOLS_CPU_H
