//
// Created by anghelo on 23-02-18.
//

#include "instructions.h"

struct instruction* initInstruction(unsigned char opcode, unsigned char bytesAmount, unsigned char byte1, unsigned char byte2, unsigned char type){
    struct instruction** instData = malloc(sizeof(struct instruction*));
    *instData = malloc(sizeof(struct instruction));
    //printf("something here?\n");
    //printf("%i %i %i \n", opcode, byte1, byte2);
    //printf("(*instData)->opcode = opcode = %i;\n", opcode);
    (*instData)->opcode = opcode;
    //printf("(*instData)->byte1 = 0;;\n");
    (*instData)->byte1 = 0;
    //printf("(*instData)->byte2 = 0;;\n");
    (*instData)->byte2 = 0;
    if(bytesAmount > 0){
        //	printf("(*instData)->byte1 = byte1;;\n");
        (*instData)->byte1 = byte1;
    }
    if(bytesAmount > 1){
        //	printf("(*instData)->byte2 = byte2;;\n");
        (*instData)->byte2 = byte2;
    }
    //printf("(*instData)->bytesAmount = bytesAmount;;\n");
    (*instData)->bytesAmount = bytesAmount;
    //printf("(*instData)->type = type;;\n");
    (*instData)->type = type;

    //printf("or here?\n");
    // printf("instData address: %p\n", *instData);
    return (*instData);
}


struct instruction* controlInstructionOpcodes(unsigned char* inst){
    if((inst[0] & 0b11) != 0b00){
        // error
        return NULL;
    }
    printfCharAsHex(inst[0]);
    printfCharAsHex(inst[1]);
    printfCharAsHex(inst[2]);
    printf("\n");

    if(inst[0] == 0x8){
        //printf("\t::coso::\n");
        struct instruction* instData = initInstruction(inst[0], 0, inst[1], inst[2], 11);
        // printf("instData address: %p\n", instData);
        return instData;
    }
    if(inst[0] == 0xc0){
        struct instruction* instData = initInstruction(inst[0], 1, inst[1], inst[2], 1);
        // printf("instData address: %p\n", instData);
        return instData;
    }
    return NULL;
}


struct instruction* ALUOpcodes(unsigned char* inst){
    if((inst[0] & 0b11) != 0b01){
        // Error
        return NULL;
    }
    if((inst[0] & 0b00000000) == 0b00000000){ // 0x00
        printf("ORA (bitwise OR with Accumulator)\n");
    }
    else if((inst[0] & 0b00100000) == 0b00100000){ // 0x20
        printf("AND (bitwise AND with accumulator) \n");
    }
    else if((inst[0] & 0b01000000) == 0b01000000){ // 0x40
        printf("EOR (bitwise Exclusive OR)\n");
    }
    else if((inst[0] & 0b01100000) == 0b01100000){ // 0x60
        printf("ADC (ADd with Carry) (or NOP)\n");
    }
    else if((inst[0] & 0b10000000) == 0b10000000){ // 0x80
        printf("STA (STore Accumulator)\n");
    }
    else if((inst[0] & 0b10100000) == 0b10100000){ // 0xA0
        printf("LDA (LoaD Accumulator)\n");
    }
    else if((inst[0] & 0b11000000) == 0b11000000){ // 0xC0
        printf("CMP (CoMPare accumulator)\n");
    }
    else if((inst[0] & 0b11100000) == 0b11100000){ // 0xE0
        printf("SBC (SuBtract with Carry)\n");
    }
    else{
        printf("ERROR\n");
    }
    return NULL;
}


struct instruction* detectType(unsigned char* inst){
    unsigned char type = inst[0] & 0b11;
    struct instruction* instData;
    printf("opcode: %i\ntype: %i\n", (unsigned int)inst[0], (unsigned int)type);
    if(type == 0b00){
        printf("\tControl instruction opcode\n");

        instData = controlInstructionOpcodes(inst);
        // printf("instData address: %p\n", instData);
        return instData;
    }
    else if(type == 0b01){
        printf("\tALU operation opcode\n");

        instData = ALUOpcodes(inst);
        return instData;

    }
    else if(type == 0b10){
        printf("\tread-modify-write (RMW) and data movement instructions opcode\n");
    }
    else{ // if(type == 0b11)
        printf("\tunoficial opcode\n");
    }
    return NULL;
}

void printfInstructions(struct nesRom* rom){
    printf("pages: %i\n", rom->header->realPrgPageAmount);
    // sleep(5);

    for(unsigned int i = 0; i < rom->header->realPrgPageAmount*1024; i++){
        for(unsigned int j = 0; j < 16; j++){
            /*
            if(rom->prgRom[i*16 + j] < 0x10){
                printf("0");
            }
            printf("%x ", rom->prgRom[i*16 + j]);
            */
        }

        //printf("  |  ");
        /*
        for(unsigned int j = 0; j < 16; j++){
            if(rom->prgRom[i*16 + j] == '\n'){
                printf("\\n ");
            }
            else if(rom->prgRom[i*16 + j] == '\t'){
                printf("\\t ");
            }
            else{
                printf("%c ", rom->prgRom[i*16 + j]);
            }
        }
        */

        //printf("|");

        //printf("\n");

        if((i+1)%8 == 0){
            // sleep(1);
            //printf("\n");
        }
    }
}

void iterateInstructions(struct nesRom* rom){
    printf("\nIterating instructions: \n\n");
    unsigned char* inst;// = malloc(sizeof(unsigned char) * 4);
    //inst[3] = '\0';
    struct instruction* instData;
    unsigned int i = 0;
    unsigned int realPrgPageAmount = rom->header->realPrgPageAmount*16*1024;
    char aux[4] = "\0\0\0\0";

    while(i < realPrgPageAmount){
        printf("while(%i < %i){\n", i, realPrgPageAmount);
        //inst = newCharFromIndex(rom->prgRom, 3, i);
        ///strncpy(inst, &(rom->prgRom[i]), 3);
        inst = (unsigned char*)strncpy(aux, (char *)&(rom->prgRom[i]), 3);
        printf("\t\t%s\n", inst);
        printf("new opcode: 0x");
        printfCharAsHex(inst[0]);
        printf("\n");

        instData = detectType(inst);
        // printf("instData address: %p\n", instData);
        if(instData == NULL){
            printf("unknow opcode: 0x%x - %i\n", inst[0], inst[0]);
            printf("\ti: %i\n", i);
            break;
        }

        printf("opcode sintax:\n");
        printfCharAsHex(instData->opcode);
        if(instData->bytesAmount > 0){
            printf(" ");
            printfCharAsHex(instData->byte1);
        }
        if(instData->bytesAmount > 1){
            printf(" ");
            printfCharAsHex(instData->byte2);
        }

        printf("\n");



        i += instData->bytesAmount;

        // free(instData);

        i++;
        sleep(3);
        printf("\nending loop\n\ti = %i\n\n", i);
    }

/*
	for(unsigned int i = 0; i < rom->header->realPrgPageAmount*16*1024; i++){
		printf("here i go again\n");
		charCopyFromIndex(inst, rom->prgRom, 3, i);
		printf("charCopyFromIndex(inst, rom->prgRom, 3, i); done\n");
		instData = detectType(inst);
		printf("instData address: %p\n", instData);
		if(instData == NULL){
			printf("unknow opcode: 0x%x - %i\n", inst[0], inst[0]);
			break;
		}
		printf("\n");

		printf("im goning to i += instData->bytesAmount;\n");
		i += instData->bytesAmount;
		printf("sum done;:..\n");

		printf("free(instData);\n");
		free(instData);
		printf("free done;\n");
	}*/
    return;
}