//
// Created by anghelo on 23-02-18.
//

#include "ram.h"

struct nesRam* initRam(){
    struct nesRam** ram = malloc(sizeof(struct nesRam*));
    (*ram)->ram = malloc(sizeof(unsigned char)*0x10000);

    return (*ram);
}

/*void freeRam(){

}
*/