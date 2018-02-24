//
// Created by anghelo on 23-02-18.
//

#include "cpu.h"

struct nesRegisters* initRegisters(){
    struct nesRegisters** registers = malloc(sizeof(struct nesRegisters*));
    *registers = malloc(sizeof(struct nesRegisters));

    (*registers)->acumulator = 0x0;
    (*registers)->indexX = 0x0;
    (*registers)->indexY = 0x0;
    (*registers)->programCounter = 0x0;
    (*registers)->stack = 0x0;
    (*registers)->statusRegister = 0x0;

    return (*registers);
}
