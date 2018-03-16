//
// Created by anghelo on 23-02-18.
//

#include "ram.h"

struct nesRam* initRam(){
    struct nesRam* ram = malloc(sizeof(struct nesRam));
    ram->ram = malloc(sizeof(unsigned char)*RAM_SIZE);
    ram->readOnlyRam = calloc(RAM_SIZE, sizeof(unsigned char));
    ram->writeOnReadOnly = 0;
    return ram;
}

void freeRam(struct nesRam* ram){
	free(ram->ram);
    free(ram->readOnlyRam);
	free(ram);
}

void setFirst16KbRom(struct nesRam* ram, const unsigned char* romPage){
	size_t size = 0x4000;
	for(unsigned short i = 0; i < size; i++){
        storeIntoRamWithoutReadOnly(ram, (unsigned short)(RAM_ROM_FIRST_PAGE + i), romPage[i]);
	}
}
void setLast16KbRom(struct nesRam* ram, const unsigned char* romPage){
	size_t size = 0x4000;
	for(size_t i = 0; i < size; i++){
        storeIntoRamWithoutReadOnly(ram, (unsigned short)(RAM_ROM_LAST_PAGE + i), romPage[i]);
	}
}

unsigned short getNMIVector(struct nesRam* ram){
	// $FFFA-$FFFB = NMI vector
	unsigned short upper = ((unsigned short)loadFromRam(ram, 0xFFFA))<<8;
	unsigned short lower = loadFromRam(ram, 0xFFFB);
	return upper | lower;
}

unsigned short getResetVector(struct nesRam* ram){
	// $FFFC-$FFFD = Reset vector
	unsigned short upper = ((unsigned short)loadFromRam(ram, 0xFFFC))<<8;
	unsigned short lower = loadFromRam(ram, 0xFFFD);
	return upper | lower;
}

unsigned short getIRQBRKVector(struct nesRam* ram){
	// $FFFE-$FFFF = IRQ/BRK vector
	unsigned short upper = ((unsigned short)loadFromRam(ram, 0xFFFE))<<8;
	unsigned short lower = loadFromRam(ram, 0xFFFF);
	return upper | lower;
}

int parseRomToRam(struct nesRam* ram, struct nesRom* rom){
	int firstPage = firstPageToLoad(rom->header->mapperId, rom->header->realPrgPageAmount);
	int secondPage = secondPageToLoad(rom->header->mapperId, rom->header->realPrgPageAmount);

	if(firstPage == -1 || secondPage == -1){
		printf("\n---ERROR---\n\tmapper %i not implemented\n", rom->header->mapperId);
		return -1;
	}

	setFirst16KbRom(ram, rom->prgRom->prgRom[firstPage]);
	setLast16KbRom(ram, rom->prgRom->prgRom[secondPage]);
	return 0;
}

unsigned char loadFromRam(struct nesRam* ram, unsigned short address){
    return ram->ram[address];
}
char storeIntoRam(struct nesRam* ram, unsigned short address, unsigned char number){
    if(ram->readOnlyRam[address]){
        ram->writeOnReadOnly = 1;
        return -2;
    }
    ram->writeOnReadOnly = 0;
    ram->ram[address] = number;
    return 0;
}
char storeIntoRamWithoutReadOnly(struct nesRam* ram, unsigned short address, unsigned char number){
    ram->ram[address] = number;
    if(ram->readOnlyRam[address]){
        return -2;
    }
    return 0;
}
