//
// Created by anghelo on 13-03-18.
//

#include "alu.h"


int ADC(struct instruction* instData, struct nesRegisters* registers, char number){
    char carry = getCarry(registers);
    char sum = 0;
    short auxSum = 0;
    sum = carry + number + registers->accumulator;
    auxSum = carry + number + registers->accumulator;

    unsigned short veryAux = (unsigned short)(auxSum & 0x100) - (unsigned short)(sum & 0x100);
    if(veryAux){
        setCarry(registers);
    }
    else{
        clearCarry(registers);
    }
    if(sum == 0){
        setZero(registers);
    }
    else{
        clearZero(registers);
    }
    if(auxSum > 127 || auxSum < -128){
        setOverflow(registers);
    }
    else{
        clearOverflow(registers);
    }
    if(sum < 0){
        setNegative(registers);
    }
    else{
        clearNegative(registers);
    }

    registers->accumulator = sum;

    return 0;
}
