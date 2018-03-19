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

void mirrorRam(struct nesRam* ram, unsigned short address, unsigned char number){
    if(address >= 0x0 && address <= 0x07FF){ // System memory mirror
        for(unsigned short i = 0x0800; address + i <= 0x1FFF; i+=0x0800){
            ram->ram[address + i] = number;
        }
    }

    if(address >= 0x2000 && address <= 0x2007){ // PPU i/o registers
        for(unsigned short i = 0x0008; address + i <= 0x3FFF; i+=0x8){
            ram->ram[address + i] = number;
        }
    }
}

unsigned char loadFromRam(struct nesRam* ram, unsigned short address){
    return ram->ram[address];
}
char _storeIntoRam(struct nesRam* ram, unsigned short address, unsigned char number, char writeOnReadOnly){
    if(writeOnReadOnly | !ram->readOnlyRam[address]){
        ram->ram[address] = number;
        ram->writeOnReadOnly = 0;
        ram->wroAddress = 0;
        ram->wroValue = 0;

        mirrorRam(ram, address, number);
    }
    else{
        ram->writeOnReadOnly = 1;
        ram->wroAddress = address;
        ram->wroValue = number;
    }
    if(ram->readOnlyRam[address]){
        return -2;
    }
    return 0;
}
char storeIntoRam(struct nesRam* ram, unsigned short address, unsigned char number){
    return _storeIntoRam(ram, address, number, 0);
}
char storeIntoRamWithoutReadOnly(struct nesRam* ram, unsigned short address, unsigned char number){
    return _storeIntoRam(ram, address, number, 1);
}
