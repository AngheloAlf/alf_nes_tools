//
// Created by anghelo on 15-03-18.
//

#include "rmw.h"


unsigned char ASL(struct nesRegisters* registers, unsigned char number){
    char carry = (char)(number & 0b10000000)>>7;
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

unsigned char ROL(struct nesRegisters* registers, unsigned char number){
    char oldCarry = getCarry(registers);

    char carry = (char)((number & 0b10000000)>>7);
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

unsigned char LSR(struct nesRegisters* registers, unsigned char number){
    char carry = (char)((number & 0b00000001));
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

unsigned char ROR(struct nesRegisters* registers, unsigned char number){
    char oldCarry = getCarry(registers);

    char carry = (char)((number & 0b00000001));
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

void LDX(struct nesRegisters* registers, unsigned char number){
    registers->indexX = number;
    parseZeroNegative(registers, number);
}

unsigned char DEC(struct nesRegisters* registers, unsigned char number){
    number -= 1;
    parseZeroNegative(registers, number);
    return number;
}

unsigned char INC(struct nesRegisters* registers, unsigned char number){
    number += 1;
    parseZeroNegative(registers, number);
    return number;
}


