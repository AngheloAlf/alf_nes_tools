//
// Created by anghelo on 15-03-18.
//

#include "rmw.h"


unsigned char ASL(NesCPURegisters* registers, unsigned char number){
    char carry = (char)(number & BIT_7)>>7;
    number = number<<1;
    if(carry){
        setCarry(registers);
    }
    else{
        clearCarry(registers);
    }

    parseZeroNegative(registers, number);

    return number;
}

unsigned char ROL(NesCPURegisters* registers, unsigned char number){
    char oldCarry = getCarry(registers);

    char carry = (char)((number & BIT_7)>>7);
    number = number<<1 | oldCarry;
    if(carry){
        setCarry(registers);
    }
    else{
        clearCarry(registers);
    }

    parseZeroNegative(registers, number);

    return number;
}

unsigned char LSR(NesCPURegisters* registers, unsigned char number){
    char carry = (char)((number & BIT_0));
    number = number>>1;
    if(carry){
        setCarry(registers);
    }
    else{
        clearCarry(registers);
    }

    parseZeroNegative(registers, number);

    return number;
}

unsigned char ROR(NesCPURegisters* registers, unsigned char number){
    char oldCarry = getCarry(registers);

    char carry = (char)((number & BIT_0));
    number = number>>1 | oldCarry<<7;
    if(carry){
        setCarry(registers);
    }
    else{
        clearCarry(registers);
    }

    parseZeroNegative(registers, number);

    return number;
}

void LDX(NesCPURegisters* registers, unsigned char number){
    registers->indexX = number;
    parseZeroNegative(registers, number);
}

unsigned char DEC(NesCPURegisters* registers, unsigned char number){
    number -= 1;
    parseZeroNegative(registers, number);
    return number;
}

unsigned char INC(NesCPURegisters* registers, unsigned char number){
    number += 1;
    parseZeroNegative(registers, number);
    return number;
}


