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
        storeIntoRamAndSetReadOnly(ram, (unsigned short) (RAM_ROM_FIRST_PAGE + i), romPage[i]);
	}
}
void setLast16KbRom(struct nesRam* ram, const unsigned char* romPage){
	size_t size = 0x4000;
	for(size_t i = 0; i < size; i++){
        storeIntoRamAndSetReadOnly(ram, (unsigned short) (RAM_ROM_LAST_PAGE + i), romPage[i]);
	}
}

unsigned short loadVector(struct nesRam* ram, unsigned short first, unsigned short second){
    unsigned short upper = ((unsigned short)(loadFromRam(ram, second))<<8);
    unsigned short lower = loadFromRam(ram, first);
    return upper | lower;
}

unsigned short getNMIVector(struct nesRam* ram){
	// $FFFA-$FFFB = NMI vector
    return loadVector(ram, 0xFFFA, 0xFFFB);
}

unsigned short getResetVector(struct nesRam* ram){
	// $FFFC-$FFFD = Reset vector
    return loadVector(ram, 0xFFFC, 0xFFFD);
}

unsigned short getIRQBRKVector(struct nesRam* ram){
	// $FFFE-$FFFF = IRQ/BRK vector
    return loadVector(ram, 0xFFFE, 0xFFFF);
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

void _mirrorRam(struct nesRam* ram, unsigned short address, unsigned char number, unsigned short start, unsigned short end,
                unsigned short length){
    unsigned short addressAux;
    if(address >= start && address <= end){
        addressAux = address - end;
        addressAux -= (addressAux/length)*length;
        for(unsigned short i = start; addressAux + i <= end; i += length){
            ram->ram[addressAux + i] = number;
        }
    }
}

void mirrorRam(struct nesRam* ram, unsigned short address, unsigned char number){
    _mirrorRam(ram, address, number, 0x0, 0x1FFF, 0x0800); // System memory mirror
    _mirrorRam(ram, address, number, 0x2000, 0x3FFF, 0x8); // PPU i/o registers
}

unsigned char loadFromRam(struct nesRam* ram, unsigned short address){
    return ram->ram[address];
}
char storeIntoRam(struct nesRam* ram, unsigned short address, unsigned char number){
    if(!ram->readOnlyRam[address]){
        ram->ram[address] = number;
        ram->writeOnReadOnly = 0;
        ram->wroAddress = 0;
        ram->wroValue = 0;

        mirrorRam(ram, address, number);
        return 0;
    }
    else{
        ram->writeOnReadOnly = 1;
        ram->wroAddress = address;
        ram->wroValue = number;
        return -2;
    }
}
char storeIntoRamAndSetReadOnly(struct nesRam *ram, unsigned short address, unsigned char number){
    char aux = 0;
    if(ram->readOnlyRam[address]){
        aux = -2;
    }

    ram->ram[address] = number;
    ram->readOnlyRam[address] = 1;
    ram->writeOnReadOnly = 0;
    ram->wroAddress = 0;
    ram->wroValue = 0;
    mirrorRam(ram, address, number);

    return aux;
}
