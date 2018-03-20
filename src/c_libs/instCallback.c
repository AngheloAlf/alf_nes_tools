//
// Created by anghelo on 25-02-18.
//

#include "instCallback.h"
#include "alu.h"
#include "rmw.h"


// Control instructions

int opcode_00(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short programCounter = (unsigned short)(registers->programCounter + 2);
    pushStack(registers, ram, (unsigned char)(programCounter>>8));
    pushStack(registers, ram, (unsigned char)(programCounter & 0x00FF));

    pushStack(registers, ram, (unsigned char)(registers->statusRegister | 0x30));

    registers->programCounter = getIRQBRKVector(ram);

    registers->jumping = 1;
    registers->jumpingSubroutine += 1;
    return instData->cycles;
}

int opcode_04(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_08(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    pushStack(registers, ram, registers->statusRegister);
    return instData->cycles;
}

int opcode_0C(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_10(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    if(!getNegative(registers)){
        registers->programCounter += (char)loadNumberFromRamOrArg(instData, registers, ram);
        registers->jumping = 1;
        return instData->cycles + 1;
    }
    return instData->cycles;
}

int opcode_14(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_18(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    clearCarry(registers);
    return instData->cycles;
}

int opcode_1C(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_20(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short programCounter = (unsigned short)(registers->programCounter + 2);
    pushStack(registers, ram, (unsigned char)(programCounter>>8));
    pushStack(registers, ram, (unsigned char)(programCounter & 0x00FF));
    registers->programCounter = loadAddress(instData, registers, ram);

    registers->jumping = 1;
    registers->jumpingSubroutine += 1;
    return instData->cycles;
}

int opcode_24(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned char number = loadNumberFromRamOrArg(instData, registers, ram);

    if((registers->accumulator & number) == 0){
        setZero(registers);
    }
    else{
        clearZero(registers);
    }

    if(number & 0b01000000){
        setOverflow(registers);
    }
    else{
        clearOverflow(registers);
    }

    if(number & 0b10000000){
        setNegative(registers);
    }
    else{
        clearNegative(registers);
    }

    return instData->cycles;
}

int opcode_28(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    registers->statusRegister = pullStack(registers, ram);
    return instData->cycles;
}

int opcode_2C(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned char number = loadNumberFromRamOrArg(instData, registers, ram);

    if((registers->accumulator & number) == 0){
        setZero(registers);
    }
    else{
        clearZero(registers);
    }

    if(number & 0b01000000){
        setOverflow(registers);
    }
    else{
        clearOverflow(registers);
    }

    if(number & 0b10000000){
        setNegative(registers);
    }
    else{
        clearNegative(registers);
    }

    return instData->cycles;
}

int opcode_30(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    if(getNegative(registers)){
        registers->programCounter += (char)loadNumberFromRamOrArg(instData, registers, ram);
        registers->jumping = 1;
        return instData->cycles + 1;
    }
    return instData->cycles;
}

int opcode_34(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_38(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    setCarry(registers);
    return instData->cycles;
}

int opcode_3C(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_40(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    registers->statusRegister = pullStack(registers, ram);

    unsigned short low = (unsigned short)pullStack(registers, ram);
    unsigned short high = (unsigned short)(pullStack(registers, ram)<<8);
    registers->programCounter = high | low;

    registers->jumping = 1;
    registers->jumpingSubroutine -= 1;

    return instData->cycles;
}

int opcode_44(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_48(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    pushStack(registers, ram, (unsigned char)registers->accumulator);
    return instData->cycles;
}

int opcode_4C(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    registers->programCounter = loadNumberFromRamOrArg(instData, registers, ram);
    registers->jumping = 1;
    return instData->cycles;
}

int opcode_50(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    if(!getOverflow(registers)){
        registers->programCounter += (char)loadNumberFromRamOrArg(instData, registers, ram);
        registers->jumping = 1;
        return instData->cycles + 1;
    }
    return instData->cycles;
}

int opcode_54(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_58(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    clearInterrupt(registers);
    return instData->cycles;
}

int opcode_5C(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_60(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short low = (unsigned short)pullStack(registers, ram);
    unsigned short high = ((unsigned short)pullStack(registers, ram))<<8;
    registers->programCounter = (unsigned short)((high | low) + 1);

    registers->jumping = 1;
    registers->jumpingSubroutine -= 1;
    return instData->cycles;
}

int opcode_64(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_68(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    registers->accumulator = (char)pullStack(registers, ram);
    parseZeroNegative(registers, registers->accumulator);
    return instData->cycles;
}

int opcode_6C(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
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

int opcode_70(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    if(getOverflow(registers)){
        registers->programCounter += (char)loadNumberFromRamOrArg(instData, registers, ram);
        registers->jumping = 1;
        return instData->cycles + 1;
    }
    return instData->cycles;
}

int opcode_74(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_78(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    setInterrupt(registers);
    return instData->cycles;
}

int opcode_7C(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_80(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_84(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    char retVal = storeIntoRam(ram, address, registers->indexY);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_88(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    registers->indexY = DEC(registers, registers->indexY);
    return instData->cycles;
}

int opcode_8C(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    char retVal = storeIntoRam(ram, address, registers->indexY);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_90(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    if(!getCarry(registers)){
        registers->programCounter += (char)loadNumberFromRamOrArg(instData, registers, ram);
        registers->jumping = 1;
        return instData->cycles + 1;
    }
    return instData->cycles;
}

int opcode_94(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    char retVal = storeIntoRam(ram, address, registers->indexY);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_98(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    registers->accumulator = registers->indexY;
    parseZeroNegative(registers, registers->indexY);
    return instData->cycles;
}

int opcode_9C(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = registers->indexY & (unsigned char)((address>>8) + 1);
    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_A0(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    registers->indexY = loadNumberFromRamOrArg(instData, registers, ram);
    parseZeroNegative(registers, registers->indexY);
    return instData->cycles;
}

int opcode_A4(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    registers->indexY = loadNumberFromRamOrArg(instData, registers, ram);
    parseZeroNegative(registers, registers->indexY);
    return instData->cycles;
}

int opcode_A8(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    registers->indexY = (unsigned char)registers->accumulator;
    parseZeroNegative(registers, registers->indexY);
    return instData->cycles;
}

int opcode_AC(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    registers->indexY = loadNumberFromRamOrArg(instData, registers, ram);
    parseZeroNegative(registers, registers->indexY);
    return instData->cycles;
}

int opcode_B0(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    if(getCarry(registers)){
        registers->programCounter += (char)loadNumberFromRamOrArg(instData, registers, ram);
        registers->jumping = 1;
        return instData->cycles + 1;
    }
    return instData->cycles;
}

int opcode_B4(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    registers->indexY = loadNumberFromRamOrArg(instData, registers, ram);
    parseZeroNegative(registers, registers->indexY);
    return instData->cycles;
}

int opcode_B8(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    clearOverflow(registers);
    return instData->cycles;
}

int opcode_BC(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    registers->indexY = loadNumberFromRamOrArg(instData, registers, ram);
    parseZeroNegative(registers, registers->indexY);
    return instData->cycles;
}

int opcode_C0(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
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

int opcode_C4(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
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

int opcode_C8(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    registers->indexY = INC(registers, registers->indexY);
    return instData->cycles;
}

int opcode_CC(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
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

int opcode_D0(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    if(getZero(registers)){
        registers->programCounter += (char)loadNumberFromRamOrArg(instData, registers, ram);
        registers->jumping = 1;
        return instData->cycles + 1;
    }
    return instData->cycles;
}

int opcode_D4(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_D8(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    clearDecimal(registers);
    return instData->cycles;
}

int opcode_DC(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_E0(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
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

int opcode_E4(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
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

int opcode_E8(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    registers->indexX = INC(registers, registers->indexX);
    return instData->cycles;
}

int opcode_EC(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
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

int opcode_F0(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    if(getZero(registers)){
        registers->programCounter += (char)loadNumberFromRamOrArg(instData, registers, ram);
        registers->jumping = 1;
        return instData->cycles + 1;
    }
    return instData->cycles;
}

int opcode_F4(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_F8(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    setDecimal(registers);
    return instData->cycles;
}

int opcode_FC(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}


// ALU opcodes

int opcode_01(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // ORA Indirect X
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = ORA(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_05(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // ORA Zero page
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = ORA(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_09(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // ORA Immediate
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = ORA(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_0D(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // ORA Absolute
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = ORA(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_11(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // ORA Indirect Y
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = ORA(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_15(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // ORA Zero page X
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = ORA(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_19(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // ORA Absolute Y
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = ORA(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_1D(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // ORA Absolute X
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = ORA(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_21(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // AND Indirect X
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = AND(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_25(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = AND(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_29(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = AND(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_2D(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = AND(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_31(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = AND(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_35(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = AND(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_39(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = AND(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_3D(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = AND(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_41(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = EOR(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_45(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = EOR(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_49(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = EOR(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_4D(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = EOR(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_51(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = EOR(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_55(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = EOR(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_59(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = EOR(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_5D(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = EOR(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_61(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // ADC Indirect X
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = ADC(registers, number);
    if(retVal != 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_65(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // ADC Zero Page
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = ADC(registers, number);
    if(retVal != 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_69(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // ADC Immediate
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = ADC(registers, number);
    if(retVal != 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_6D(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // ADC Absoulte
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = ADC(registers, number);
    if(retVal != 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_71(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // ADC Indirect Y
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = ADC(registers, number);
    if(retVal != 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_75(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // ADC Zero Page X
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = ADC(registers, number);
    if(retVal != 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_79(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // ADC Absolute Y
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = ADC(registers, number);
    if(retVal != 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_7D(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // ADC Absolute X
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = ADC(registers, number);
    if(retVal != 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_81(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short number = loadAddress(instData, registers, ram);
    int retVal = STA(registers, number, ram);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_85(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short number = loadAddress(instData, registers, ram);
    int retVal = STA(registers, number, ram);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_89(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_8D(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short number = loadAddress(instData, registers, ram);
    int retVal = STA(registers, number, ram);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_91(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short number = loadAddress(instData, registers, ram);
    int retVal = STA(registers, number, ram);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_95(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short number = loadAddress(instData, registers, ram);
    int retVal = STA(registers, number, ram);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_99(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short number = loadAddress(instData, registers, ram);
    int retVal = STA(registers, number, ram);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_9D(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short number = loadAddress(instData, registers, ram);
    int retVal = STA(registers, number, ram);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_A1(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = LDA(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_A5(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = LDA(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_A9(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = LDA(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_AD(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = LDA(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_B1(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = LDA(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_B5(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = LDA(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_B9(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = LDA(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_BD(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = LDA(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_C1(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = CMP(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_C5(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = CMP(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_C9(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = CMP(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_CD(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = CMP(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_D1(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = CMP(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_D5(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = CMP(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_D9(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = CMP(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_DD(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = CMP(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_E1(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = SBC(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_E5(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = SBC(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_E9(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = SBC(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_ED(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = SBC(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_F1(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = SBC(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_F5(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = SBC(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_F9(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = SBC(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_FD(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    char number = (char) loadNumberFromRamOrArg(instData, registers, ram);
    int retVal = SBC(registers, number);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}


// RMW opcodes

int opcode_02(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // KIL
    // STP
    disablePC(registers);
    return 0x80000000;
}

int opcode_06(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = ASL(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_0A(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    registers->accumulator = ASL(registers, (unsigned char)registers->accumulator);
    return instData->cycles;
}

int opcode_0E(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = ASL(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_12(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // KIL
    // STP
    disablePC(registers);
    return 0x80000000;
}

int opcode_16(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = ASL(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_1A(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_1E(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = ASL(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_22(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // KIL
    // STP
    disablePC(registers);
    return 0x80000000;
}

int opcode_26(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = ROL(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_2A(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    registers->accumulator = (char)ROL(registers, (unsigned char)registers->accumulator);
    return instData->cycles;
}

int opcode_2E(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = ROL(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_32(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // KIL
    // STP
    disablePC(registers);
    return 0x80000000;
}

int opcode_36(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = ROL(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_3A(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_3E(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = ROL(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_42(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // KIL
    // STP
    disablePC(registers);
    return 0x80000000;
}

int opcode_46(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = LSR(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_4A(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    registers->accumulator = (char)LSR(registers, (unsigned char)registers->accumulator);
    return instData->cycles;
}

int opcode_4E(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = LSR(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_52(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // KIL
    // STP
    disablePC(registers);
    return 0x80000000;
}

int opcode_56(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = LSR(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_5A(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_5E(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = LSR(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_62(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // KIL
    // STP
    disablePC(registers);
    return 0x80000000;
}

int opcode_66(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = ROR(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_6A(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    registers->accumulator = (char)ROR(registers, (unsigned char)registers->accumulator);
    return instData->cycles;
}

int opcode_6E(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = ROR(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_72(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // KIL
    // STP
    disablePC(registers);
    return 0x80000000;
}

int opcode_76(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = ROR(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_7A(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_7E(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = ROR(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_82(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_86(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);

    char retVal = storeIntoRam(ram, address,registers->indexX);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_8A(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    registers->accumulator = (char)registers->indexX;
    parseZeroNegative(registers, registers->indexX);
    return instData->cycles;
}

int opcode_8E(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);

    char retVal = storeIntoRam(ram, address, registers->indexX);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_92(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // KIL
    // STP
    disablePC(registers);
    return 0x80000000;
}

int opcode_96(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);

    char retVal = storeIntoRam(ram, address, registers->indexX);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_9A(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    registers->stack = registers->indexX;
    return instData->cycles;
}

int opcode_9E(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = registers->indexX & (unsigned char)((address>>8) + 1);

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_A2(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned char number = loadNumberFromRamOrArg(instData, registers, ram);
    LDX(registers, number);
    return instData->cycles;
}

int opcode_A6(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned char number = loadNumberFromRamOrArg(instData, registers, ram);
    LDX(registers, number);
    return instData->cycles;
}

int opcode_AA(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    registers->indexX = (unsigned char)registers->accumulator;
    parseZeroNegative(registers, registers->indexX);
    return instData->cycles;
}

int opcode_AE(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned char number = loadNumberFromRamOrArg(instData, registers, ram);
    LDX(registers, number);
    return instData->cycles;
}

int opcode_B2(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // KIL
    // STP
    disablePC(registers);
    return 0x80000000;
}

int opcode_B6(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned char number = loadNumberFromRamOrArg(instData, registers, ram);
    LDX(registers, number);
    return instData->cycles;
}

int opcode_BA(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    registers->indexX = registers->stack;
    parseZeroNegative(registers, registers->indexX);
    return instData->cycles;
}

int opcode_BE(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned char number = loadNumberFromRamOrArg(instData, registers, ram);
    LDX(registers, number);
    return instData->cycles;
}

int opcode_C2(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_C6(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = DEC(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_CA(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    registers->indexX = DEC(registers, registers->indexX);
    return instData->cycles;
}

int opcode_CE(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = DEC(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_D2(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // KIL
    // STP
    disablePC(registers);
    return 0x80000000;
}

int opcode_D6(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = DEC(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_DA(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_DE(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = DEC(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_E2(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_E6(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = INC(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_EA(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // NOP
    return instData->cycles;
}

int opcode_EE(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = INC(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_F2(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // KIL
    // STP
    disablePC(registers);
    return 0x80000000;
}

int opcode_F6(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = INC(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}

int opcode_FA(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    // Unofficial NOP
    return instData->cycles;
}

int opcode_FE(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short address = loadAddress(instData, registers, ram);
    unsigned char result = INC(registers, loadFromRam(ram, address));

    char retVal = storeIntoRam(ram, address, result);
    if(retVal < 0){
        return retVal;
    }
    return instData->cycles;
}


// unofficial opcodes
int opcode_03(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_07(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_0B(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_0F(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_13(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_17(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_1B(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_1F(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_23(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_27(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_2B(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_2F(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_33(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_37(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_3B(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_3F(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_43(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_47(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_4B(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_4F(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_53(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_57(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_5B(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_5F(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_63(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_67(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_6B(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_6F(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_73(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_77(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_7B(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_7F(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_83(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_87(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_8B(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_8F(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_93(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_97(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_9B(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_9F(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_A3(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_A7(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_AB(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_AF(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_B3(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_B7(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_BB(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_BF(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_C3(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_C7(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_CB(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_CF(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_D3(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_D7(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_DB(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_DF(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_E3(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_E7(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_EB(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_EF(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_F3(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_F7(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_FB(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

int opcode_FF(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    printf("\tinstruction %x not implemented\n\n", instData->opcode);
    return 0;
}

