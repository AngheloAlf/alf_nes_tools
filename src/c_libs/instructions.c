//
// Created by anghelo on 23-02-18.
//

#include "instructions.h"

struct instruction* initInstruction(unsigned char opcode, unsigned char bytesAmount, unsigned char byte1, unsigned char byte2, unsigned char type){
    struct instruction** instData = malloc(sizeof(struct instruction*));
    *instData = malloc(sizeof(struct instruction));
    (*instData)->opcode = opcode;
    (*instData)->byte1 = 0;
    (*instData)->byte2 = 0;
    if(bytesAmount > 0){
        (*instData)->byte1 = byte1;
    }
    if(bytesAmount > 1){
        (*instData)->byte2 = byte2;
    }
    (*instData)->bytesAmount = bytesAmount;
    (*instData)->type = type;

    return (*instData);
}

struct instruction* control_Branching_Opcodes(unsigned char* inst){
    struct instruction* instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_BRANCH);

    switch(inst[0]){
        case 0x10:
            printf("\tBranch on PLus\n");
            break;
        case 0x30:
            printf("\tBranch on MInus\n");
            break;
        case 0x50:
            printf("\tBranch on oVerflow Clear\n");
            break;
        case 0x70:
            printf("\tBranch on oVerflow Set\n");
            break;
        case 0x90:
            printf("\tBranch on Carry Clear\n");
            break;
        case 0xB0:
            printf("\tBranch on Carry Set\n");
            break;
        case 0xD0:
            printf("\tBranch on Not Equal\n");
            break;
        case 0xF0:
            printf("\tBranch on EQual\n");
            break;
        default:
            printf("\tINVALID\n");
            instData = NULL;
            break;
    }

    return instData;
}


struct instruction* controlInstructionOpcodes(unsigned char* inst){
    if((inst[0] & 0b11) != 0b00){
        // error
        return NULL;
    }
    struct instruction* instData = NULL;

    if((inst[0] & 0b0001000) == 0b0001000){ // Branching instructions
        instData =  control_Branching_Opcodes(inst);
    }

    else if(inst[0] == 0x8){
        instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED);
    }
    if(inst[0] == 0xc0){
        instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_IMMEDIATE);
    }
    return instData;
}


struct instruction* ALU_ORA_Opcode(unsigned char* inst){
    struct instruction* instData = NULL;
    switch(inst[0]){
        case 0x01:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_INDIRECT_X); // Indirect,X    ORA ($44,X)   $01  2   6
            break;
        case 0x05:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE); // Zero Page     ORA $44       $05  2   3
            break;
        case 0x09:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_IMMEDIATE); // Immediate     ORA #$44      $09  2   2
            break;
        case 0x0D:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE); // Absolute      ORA $4400     $0D  3   4
            break;
        case 0x11:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_INDIRECT_Y); // Indirect,Y    ORA ($44),Y   $11  2   5+
            break;
        case 0x15:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE_X); // Zero Page,X   ORA $44,X     $15  2   4
            break;
        case 0x19:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE_Y); // Absolute,Y    ORA $4400,Y   $19  3   4+
            break;
        case 0x1D:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE_X); // Absolute,X    ORA $4400,X   $1D  3   4+
            break;
        default:
            instData = NULL;
            break;
    }
    return instData;
}


struct instruction* ALUOpcodes(unsigned char* inst){
    if((inst[0] & 0b11) != 0b01){
        // Error
        return NULL;
    }
    if((inst[0] & 0b00100000) == 0b00100000){ // 0x20
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
    else if((inst[0] & 0b00000000) == 0b00000000){ // 0x00
        printf("ORA (bitwise OR with Accumulator)\n");
        return ALU_ORA_Opcode(inst);
    }
    else{
        printf("ERROR\n");
    }
    return NULL;
}


struct instruction* detectType(unsigned char* inst){
    unsigned char type = (unsigned char)(inst[0] & 0b11);
    struct instruction* instData = NULL;
    // printf("opcode: %i\ntype: %i\n", (unsigned int)inst[0], (unsigned int)type);
    printf("opcode: $");
    printfCharAsHex(inst[0]);
    printf("\n");
    if(type == 0b00){
        printf("\tControl instruction opcode\n");
        instData = controlInstructionOpcodes(inst);
    }
    else if(type == 0b01){
        printf("\tALU operation opcode\n");
        instData = ALUOpcodes(inst);

    }
    else if(type == 0b10){
        printf("\tread-modify-write (RMW) and data movement instructions opcode\n");
    }
    else{ // if(type == 0b11)
        printf("\tunoficial opcode\n");
    }
    return instData;
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
    char aux[4] = "\0\0\0";

    while(i < realPrgPageAmount){
        // printf("while(%i < %i){\n", i, realPrgPageAmount);
        // inst = newCharFromIndex(rom->prgRom, 3, i);
        // strncpy(inst, &(rom->prgRom[i]), 3);
        inst = (unsigned char*)strncpy(aux, (char *)&(rom->prgRom[i]), 3);
        // printf("\t\t%s\n", inst);
        //printf("new opcode: 0x");
        // printfCharAsHex(inst[0]);
        // printf("\n");

        instData = detectType(inst);
        // printf("instData address: %p\n", instData);
        printf("\n");
        if(instData == NULL){
            printf("\tunknow opcode: 0x%x - %i\n", inst[0], inst[0]);
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