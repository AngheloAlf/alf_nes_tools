//
// Created by anghelo on 13-03-18.
//

#include "alu.h"


// ORA (bitwise OR with Accumulator)
int ORA(NesCPURegisters *registers, char number) {
    char result = registers->accumulator | number;

    parseZeroNegative(registers, result);

    registers->accumulator = result;
    return 0;
}

// AND (bitwise AND with accumulator)
int AND(NesCPURegisters* registers, char number){
    char result = registers->accumulator & number;

    parseZeroNegative(registers, result);

    registers->accumulator = result;
    return 0;
}

// EOR (bitwise Exclusive OR)
int EOR(NesCPURegisters* registers, char number){
    char result = registers->accumulator ^ number;

    parseZeroNegative(registers, result);

    registers->accumulator = result;
    return 0;
}

// ADC (ADd with Carry)
int ADC(NesCPURegisters *registers, char number) {
    // TODO: Implement BCD (Decimal mode)
    if(getDecimal(registers)){
        return ALF_NES_ERROR_CODE_NOT_IMPLEMENTED;
    }
    char carry = getCarry(registers);
    char sum = carry + number + registers->accumulator;
    short auxSum = carry + number + registers->accumulator;

    unsigned short veryAux = (unsigned short)(auxSum & 0x100) - (unsigned short)(sum & 0x100);
    if(veryAux){
        setCarry(registers);
    }
    else{
        clearCarry(registers);
    }
    if(auxSum > 127 || auxSum < -128){
        setOverflow(registers);
    }
    else{
        clearOverflow(registers);
    }

    parseZeroNegative(registers, sum);

    registers->accumulator = sum;

    return 0;
}

// STA (STore Accumulator)
int STA(NesCPURegisters* registers, unsigned short number, NesRam* ram){
    return storeIntoRam(ram, number, (unsigned char)registers->accumulator);
}

// LDA (LoaD Accumulator)
int LDA(NesCPURegisters* registers, char number){
    parseZeroNegative(registers, number);

    registers->accumulator = number;
    return 0;
}

// CMP (CoMPare accumulator)
int CMP(NesCPURegisters* registers, char number){
    char result = registers->accumulator - number;

    if(result >= 0){
        setCarry(registers);
    }
    else{
        clearCarry(registers);
    }

    parseZeroNegative(registers, result);

    return 0;
}

// SBC (SuBtract with Carry)
int SBC(NesCPURegisters* registers, char number){
    // TODO: Implement BCD (Decimal mode)
    if(getDecimal(registers)){
        return ALF_NES_ERROR_CODE_NOT_IMPLEMENTED;
    }
    char carry = getCarry(registers);
    char sum = 0;
    short auxSum = 0;
    sum = registers->accumulator - number - ((char)1 - carry);
    auxSum = registers->accumulator - number - ((char)1 - carry);

    unsigned short veryAux = (unsigned short)(auxSum & 0x100) - (unsigned short)(sum & 0x100);
    if(veryAux){
        setCarry(registers);
    }
    else{
        clearCarry(registers);
    }
    if(auxSum > 127 || auxSum < -128){
        setOverflow(registers);
    }
    else{
        clearOverflow(registers);
    }

    parseZeroNegative(registers, sum);

    registers->accumulator = sum;
    return 0;
}

