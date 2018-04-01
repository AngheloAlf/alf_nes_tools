//
// Created by anghelo on 25-02-18.
//

#include "instCallback.h"
#include "alu.h"
#include "rmw.h"


// Control instructions

int opcode_00(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short programCounter = (unsigned short)(registers->programCounter + 2);
    pushStack(registers, ram, (unsigned char)(programCounter>>8));
    pushStack(registers, ram, (unsigned char)(programCounter & 0x00FF));

    pushStack(registers, ram, (unsigned char)(registers->statusRegister | 0x30));

    registers->programCounter = getIRQBRKVector(ram);

    registers->jumping = 1;
    registers->jumpingSubroutine += 1;
    return instData->cycles;
}

int opcode_04(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_08(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    pushStack(registers, ram, registers->statusRegister);
    return instData->cycles;
}

int opcode_0C(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_10(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    if(!getNegative(registers)){
        registers->programCounter += (char)loadNumberFromRamOrArg(instData, registers, ram);
        registers->jumping = 1;
        return instData->cycles + 1;
    }
    return instData->cycles;
}

int opcode_14(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_18(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    clearCarry(registers);
    return instData->cycles;
}

int opcode_1C(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_20(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short programCounter = (unsigned short)(registers->programCounter + 2);
    pushStack(registers, ram, (unsigned char)(programCounter>>8));
    pushStack(registers, ram, (unsigned char)(programCounter & 0x00FF));
    registers->programCounter = loadAddress(instData, registers, ram);

    registers->jumping = 1;
    registers->jumpingSubroutine += 1;
    return instData->cycles;
}

int opcode_24(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned char number = loadNumberFromRamOrArg(instData, registers, ram);

    if((registers->accumulator & number) == 0){
        setZero(registers);
    }
    else{
        clearZero(registers);
    }

    if(number & BIT_6){
        setOverflow(registers);
    }
    else{
        clearOverflow(registers);
    }

    if(number & BIT_7){
        setNegative(registers);
    }
    else{
        clearNegative(registers);
    }

    return instData->cycles;
}

int opcode_28(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    registers->statusRegister = pullStack(registers, ram);
    return instData->cycles;
}

int opcode_2C(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned char number = loadNumberFromRamOrArg(instData, registers, ram);

    if((registers->accumulator & number) == 0){
        setZero(registers);
    }
    else{
        clearZero(registers);
    }

    if(number & BIT_6){
        setOverflow(registers);
    }
    else{
        clearOverflow(registers);
    }

    if(number & BIT_7){
        setNegative(registers);
    }
    else{
        clearNegative(registers);
    }

    return instData->cycles;
}

int opcode_30(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    if(getNegative(registers)){
        registers->programCounter += (char)loadNumberFromRamOrArg(instData, registers, ram);
        registers->jumping = 1;
        return instData->cycles + 1;
    }
    return instData->cycles;
}

int opcode_34(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_38(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    setCarry(registers);
    return instData->cycles;
}

int opcode_3C(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_40(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    registers->statusRegister = pullStack(registers, ram);

    unsigned short low = (unsigned short)pullStack(registers, ram);
    unsigned short high = (unsigned short)(pullStack(registers, ram)<<8);
    registers->programCounter = high | low;

    registers->jumping = 1;
    registers->jumpingSubroutine -= 1;

    return instData->cycles;
}

int opcode_44(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_48(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    pushStack(registers, ram, (unsigned char)registers->accumulator);
    return instData->cycles;
}

int opcode_4C(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    registers->programCounter = loadNumberFromRamOrArg(instData, registers, ram);
    registers->jumping = 1;
    return instData->cycles;
}

int opcode_50(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    if(!getOverflow(registers)){
        registers->programCounter += (char)loadNumberFromRamOrArg(instData, registers, ram);
        registers->jumping = 1;
        return instData->cycles + 1;
    }
    return instData->cycles;
}

int opcode_54(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_58(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    clearInterrupt(registers);
    return instData->cycles;
}

int opcode_5C(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_60(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short low = (unsigned short)pullStack(registers, ram);
    unsigned short high = ((unsigned short)pullStack(registers, ram))<<8;
    registers->programCounter = (unsigned short)((high | low) + 1);

    registers->jumping = 1;
    registers->jumpingSubroutine -= 1;
    return instData->cycles;
}

int opcode_64(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_68(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    registers->accumulator = (char)pullStack(registers, ram);
    parseZeroNegative(registers, registers->accumulator);
    return instData->cycles;
}

int opcode_6C(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned short low = loadFromRam(ram, address);
    unsigned short high;
    if((address & 0x00FF) != 0x00FF){
        high = loadFromRam(ram, (unsigned short)(address + 1))<<8;
    }
    else{
        high = loadFromRam(ram, (unsigned short)(address&0x00FF))<<8;
    }
    registers->programCounter = high | low;
    registers->jumping = 1;
    return instData->cycles;
}

int opcode_70(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    if(getOverflow(registers)){
        registers->programCounter += (char)loadNumberFromRamOrArg(instData, registers, ram);
        registers->jumping = 1;
        return instData->cycles + 1;
    }
    return instData->cycles;
}

int opcode_74(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_78(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    setInterrupt(registers);
    return instData->cycles;
}

int opcode_7C(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_80(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_84(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    char retVal = storeIntoRam(ram, address, registers->indexY);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_88(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    registers->indexY = DEC(registers, registers->indexY);
    return instData->cycles;
}

int opcode_8C(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    char retVal = storeIntoRam(ram, address, registers->indexY);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_90(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    if(!getCarry(registers)){
        registers->programCounter += (char)loadNumberFromRamOrArg(instData, registers, ram);
        registers->jumping = 1;
        return instData->cycles + 1;
    }
    return instData->cycles;
}

int opcode_94(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    char retVal = storeIntoRam(ram, address, registers->indexY);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_98(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    registers->accumulator = registers->indexY;
    parseZeroNegative(registers, registers->indexY);
    return instData->cycles;
}

int opcode_9C(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = registers->indexY & (unsigned char)((address>>8) + 1);
    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_A0(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    registers->indexY = loadNumberFromRamOrArg(instData, registers, ram);
    parseZeroNegative(registers, registers->indexY);
    return instData->cycles;
}

int opcode_A4(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    registers->indexY = loadNumberFromRamOrArg(instData, registers, ram);
    parseZeroNegative(registers, registers->indexY);
    return instData->cycles;
}

int opcode_A8(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    registers->indexY = (unsigned char)registers->accumulator;
    parseZeroNegative(registers, registers->indexY);
    return instData->cycles;
}

int opcode_AC(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    registers->indexY = loadNumberFromRamOrArg(instData, registers, ram);
    parseZeroNegative(registers, registers->indexY);
    return instData->cycles;
}

int opcode_B0(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    if(getCarry(registers)){
        registers->programCounter += (char)loadNumberFromRamOrArg(instData, registers, ram);
        registers->jumping = 1;
        return instData->cycles + 1;
    }
    return instData->cycles;
}

int opcode_B4(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    registers->indexY = loadNumberFromRamOrArg(instData, registers, ram);
    parseZeroNegative(registers, registers->indexY);
    return instData->cycles;
}

int opcode_B8(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    clearOverflow(registers);
    return instData->cycles;
}

int opcode_BC(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    registers->indexY = loadNumberFromRamOrArg(instData, registers, ram);
    parseZeroNegative(registers, registers->indexY);
    return instData->cycles;
}

int opcode_C0(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char result = (char)registers->indexY - (char)loadNumberFromRamOrArg(instData, registers, ram);
    if(result > 0){
        setCarry(registers);
    }
    else{
        clearCarry(registers);
    }

    parseZeroNegative(registers, result);

    return instData->cycles;
}

int opcode_C4(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char result = (char)registers->indexY - (char)loadNumberFromRamOrArg(instData, registers, ram);
    if(result > 0){
        setCarry(registers);
    }
    else{
        clearCarry(registers);
    }

    parseZeroNegative(registers, result);

    return instData->cycles;
}

int opcode_C8(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    registers->indexY = INC(registers, registers->indexY);
    return instData->cycles;
}

int opcode_CC(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char result = (char)registers->indexY - (char)loadNumberFromRamOrArg(instData, registers, ram);
    if(result > 0){
        setCarry(registers);
    }
    else{
        clearCarry(registers);
    }

    parseZeroNegative(registers, result);

    return instData->cycles;
}

int opcode_D0(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    if(getZero(registers)){
        registers->programCounter += (char)loadNumberFromRamOrArg(instData, registers, ram);
        registers->jumping = 1;
        return instData->cycles + 1;
    }
    return instData->cycles;
}

int opcode_D4(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_D8(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    clearDecimal(registers);
    return instData->cycles;
}

int opcode_DC(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_E0(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char result = (char)registers->indexX - (char)loadNumberFromRamOrArg(instData, registers, ram);
    if(result > 0){
        setCarry(registers);
    }
    else{
        clearCarry(registers);
    }

    parseZeroNegative(registers, result);

    return instData->cycles;
}

int opcode_E4(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char result = (char)registers->indexX - (char)loadNumberFromRamOrArg(instData, registers, ram);
    if(result > 0){
        setCarry(registers);
    }
    else{
        clearCarry(registers);
    }

    parseZeroNegative(registers, result);

    return instData->cycles;
}

int opcode_E8(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    registers->indexX = INC(registers, registers->indexX);
    return instData->cycles;
}

int opcode_EC(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char result = (char)registers->indexX - (char)loadNumberFromRamOrArg(instData, registers, ram);
    if(result > 0){
        setCarry(registers);
    }
    else{
        clearCarry(registers);
    }

    parseZeroNegative(registers, result);

    return instData->cycles;
}

int opcode_F0(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    if(getZero(registers)){
        registers->programCounter += (char)loadNumberFromRamOrArg(instData, registers, ram);
        registers->jumping = 1;
        return instData->cycles + 1;
    }
    return instData->cycles;
}

int opcode_F4(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_F8(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    setDecimal(registers);
    return instData->cycles;
}

int opcode_FC(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}


// ALU opcodes

int opcode_01(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // ORA Indirect X
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = ORA(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_05(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // ORA Zero page
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = ORA(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_09(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // ORA Immediate
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = ORA(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_0D(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // ORA Absolute
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = ORA(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_11(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // ORA Indirect Y
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = ORA(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_15(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // ORA Zero page X
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = ORA(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_19(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // ORA Absolute Y
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = ORA(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_1D(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // ORA Absolute X
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = ORA(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_21(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // AND Indirect X
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = AND(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_25(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = AND(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_29(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = AND(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_2D(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = AND(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_31(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = AND(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_35(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = AND(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_39(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = AND(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_3D(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = AND(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_41(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = EOR(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_45(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = EOR(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_49(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = EOR(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_4D(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = EOR(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_51(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = EOR(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_55(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = EOR(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_59(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = EOR(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_5D(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = EOR(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_61(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // ADC Indirect X
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = ADC(registers, number);
    if(retVal != 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_65(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // ADC Zero Page
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = ADC(registers, number);
    if(retVal != 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_69(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // ADC Immediate
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = ADC(registers, number);
    if(retVal != 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_6D(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // ADC Absoulte
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = ADC(registers, number);
    if(retVal != 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_71(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // ADC Indirect Y
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = ADC(registers, number);
    if(retVal != 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_75(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // ADC Zero Page X
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = ADC(registers, number);
    if(retVal != 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_79(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // ADC Absolute Y
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = ADC(registers, number);
    if(retVal != 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_7D(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // ADC Absolute X
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = ADC(registers, number);
    if(retVal != 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_81(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short number = loadAddress(instData, registers, ram);
    int retVal = STA(registers, number, ram);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_85(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short number = loadAddress(instData, registers, ram);
    int retVal = STA(registers, number, ram);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_89(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_8D(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short number = loadAddress(instData, registers, ram);
    int retVal = STA(registers, number, ram);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_91(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short number = loadAddress(instData, registers, ram);
    int retVal = STA(registers, number, ram);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_95(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short number = loadAddress(instData, registers, ram);
    int retVal = STA(registers, number, ram);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_99(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short number = loadAddress(instData, registers, ram);
    int retVal = STA(registers, number, ram);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_9D(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short number = loadAddress(instData, registers, ram);
    int retVal = STA(registers, number, ram);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_A1(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = LDA(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_A5(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = LDA(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_A9(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = LDA(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_AD(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = LDA(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_B1(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = LDA(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_B5(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = LDA(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_B9(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = LDA(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_BD(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = LDA(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_C1(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = CMP(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_C5(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = CMP(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_C9(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = CMP(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_CD(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = CMP(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_D1(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = CMP(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_D5(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = CMP(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_D9(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = CMP(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_DD(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = CMP(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_E1(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = SBC(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_E5(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = SBC(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_E9(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = SBC(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_ED(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = SBC(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_F1(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = SBC(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_F5(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = SBC(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_F9(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = SBC(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_FD(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = SBC(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}


// RMW opcodes

int opcode_02(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // KIL
    // STP
    disablePC(registers);
    return 0x80000000;
}

int opcode_06(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = ASL(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_0A(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    registers->accumulator = ASL(registers, (unsigned char)registers->accumulator);
    return instData->cycles;
}

int opcode_0E(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = ASL(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_12(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // KIL
    // STP
    disablePC(registers);
    return 0x80000000;
}

int opcode_16(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = ASL(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_1A(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_1E(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = ASL(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_22(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // KIL
    // STP
    disablePC(registers);
    return 0x80000000;
}

int opcode_26(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = ROL(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_2A(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    registers->accumulator = (char)ROL(registers, (unsigned char)registers->accumulator);
    return instData->cycles;
}

int opcode_2E(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = ROL(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_32(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // KIL
    // STP
    disablePC(registers);
    return 0x80000000;
}

int opcode_36(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = ROL(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_3A(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_3E(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = ROL(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_42(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // KIL
    // STP
    disablePC(registers);
    return 0x80000000;
}

int opcode_46(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = LSR(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_4A(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    registers->accumulator = (char)LSR(registers, (unsigned char)registers->accumulator);
    return instData->cycles;
}

int opcode_4E(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = LSR(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_52(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // KIL
    // STP
    disablePC(registers);
    return 0x80000000;
}

int opcode_56(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = LSR(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_5A(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_5E(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = LSR(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_62(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // KIL
    // STP
    disablePC(registers);
    return 0x80000000;
}

int opcode_66(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = ROR(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_6A(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    registers->accumulator = (char)ROR(registers, (unsigned char)registers->accumulator);
    return instData->cycles;
}

int opcode_6E(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = ROR(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_72(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // KIL
    // STP
    disablePC(registers);
    return 0x80000000;
}

int opcode_76(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = ROR(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_7A(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_7E(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = ROR(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_82(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_86(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);

    char retVal = storeIntoRam(ram, address,registers->indexX);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_8A(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    registers->accumulator = (char)registers->indexX;
    parseZeroNegative(registers, registers->indexX);
    return instData->cycles;
}

int opcode_8E(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);

    char retVal = storeIntoRam(ram, address, registers->indexX);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_92(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // KIL
    // STP
    disablePC(registers);
    return 0x80000000;
}

int opcode_96(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);

    char retVal = storeIntoRam(ram, address, registers->indexX);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_9A(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    registers->stack = registers->indexX;
    return instData->cycles;
}

int opcode_9E(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = registers->indexX & (unsigned char)((address>>8) + 1);

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_A2(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned char number = loadNumberFromRamOrArg(instData, registers, ram);
    LDX(registers, number);
    return instData->cycles;
}

int opcode_A6(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned char number = loadNumberFromRamOrArg(instData, registers, ram);
    LDX(registers, number);
    return instData->cycles;
}

int opcode_AA(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    registers->indexX = (unsigned char)registers->accumulator;
    parseZeroNegative(registers, registers->indexX);
    return instData->cycles;
}

int opcode_AE(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned char number = loadNumberFromRamOrArg(instData, registers, ram);
    LDX(registers, number);
    return instData->cycles;
}

int opcode_B2(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // KIL
    // STP
    disablePC(registers);
    return 0x80000000;
}

int opcode_B6(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned char number = loadNumberFromRamOrArg(instData, registers, ram);
    LDX(registers, number);
    return instData->cycles;
}

int opcode_BA(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    registers->indexX = registers->stack;
    parseZeroNegative(registers, registers->indexX);
    return instData->cycles;
}

int opcode_BE(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned char number = loadNumberFromRamOrArg(instData, registers, ram);
    LDX(registers, number);
    return instData->cycles;
}

int opcode_C2(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_C6(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = DEC(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_CA(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    registers->indexX = DEC(registers, registers->indexX);
    return instData->cycles;
}

int opcode_CE(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = DEC(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_D2(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // KIL
    // STP
    disablePC(registers);
    return 0x80000000;
}

int opcode_D6(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = DEC(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_DA(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_DE(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = DEC(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_E2(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_E6(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = INC(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_EA(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // NOP
    return instData->cycles;
}

int opcode_EE(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = INC(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_F2(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // KIL
    // STP
    disablePC(registers);
    return 0x80000000;
}

int opcode_F6(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = INC(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_FA(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_FE(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = INC(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}


// unofficial opcodes
int opcode_03(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_07(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_0B(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_0F(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_13(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_17(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_1B(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_1F(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_23(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_27(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_2B(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_2F(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_33(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_37(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_3B(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_3F(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_43(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_47(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_4B(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_4F(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_53(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_57(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_5B(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_5F(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_63(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_67(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_6B(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_6F(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_73(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_77(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_7B(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_7F(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_83(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_87(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_8B(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_8F(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_93(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_97(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_9B(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_9F(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_A3(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_A7(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_AB(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_AF(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_B3(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_B7(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_BB(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_BF(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_C3(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_C7(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_CB(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_CF(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_D3(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_D7(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_DB(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_DF(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_E3(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_E7(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_EB(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_EF(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_F3(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_F7(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_FB(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_FF(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

