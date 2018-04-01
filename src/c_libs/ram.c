//
// Created by anghelo on 23-02-18.
//

#include "ram.h"

NesRam* initRam(){
    NesRam* ram = malloc(sizeof(NesRam));
    ram->ram = malloc(sizeof(unsigned char)*RAM_SIZE);
    ram->readOnlyRam = calloc(RAM_SIZE, sizeof(unsigned char));
    ram->writeOnReadOnly = 0;
    ram->wroAddress = 0;
    ram->wroValue = 0;
    ram->saveData = NULL;
    return ram;
}

void freeRam(NesRam* ram){
	free(ram->ram);
    free(ram->readOnlyRam);
    if(ram->saveData != NULL){
        free(ram->saveData);
    }
	free(ram);
}

int ramPowerUp(NesRam* ram){
    int retVal = 0;

    storeIntoRamAndDisableReadOnly(ram, 0x4017, 0x0); // $4017 = $00 (frame irq enabled)
    storeIntoRamAndDisableReadOnly(ram, 0x4015, 0x0); // $4015 = $00 (all channels disabled)
    for(unsigned short i = 0x4000; i <= 0x400F; i++){ // $4000-$400F = $00
        storeIntoRamAndDisableReadOnly(ram, i, 0x0); // (not sure about $4010-$4013)
    }
    // All 15 bits of noise channel LFSR = $0000. The first time the LFSR is clocked from the all-0s state, it will shift in a 1.

    return retVal;
}

void setFirst16KbRom(NesRam* ram, const unsigned char* romPage){
	size_t size = 0x4000;
	for(unsigned short i = 0; i < size; i++){
        storeIntoRamAndSetReadOnly(ram, (unsigned short) (RAM_ROM_FIRST_PAGE + i), romPage[i]);
	}
}
void setLast16KbRom(NesRam* ram, const unsigned char* romPage){
	size_t size = 0x4000;
	for(size_t i = 0; i < size; i++){
        storeIntoRamAndSetReadOnly(ram, (unsigned short) (RAM_ROM_LAST_PAGE + i), romPage[i]);
	}
}

unsigned short loadVector(NesRam* ram, unsigned short first, unsigned short second){
    unsigned short upper = ((unsigned short)(loadFromRam(ram, second))<<8);
    unsigned short lower = loadFromRam(ram, first);
    return upper | lower;
}

unsigned short getNMIVector(NesRam* ram){
	// $FFFA-$FFFB = NMI vector
    return loadVector(ram, 0xFFFA, 0xFFFB);
}

unsigned short getResetVector(NesRam* ram){
	// $FFFC-$FFFD = Reset vector
    return loadVector(ram, 0xFFFC, 0xFFFD);
}

unsigned short getIRQBRKVector(NesRam* ram){
	// $FFFE-$FFFF = IRQ/BRK vector
    return loadVector(ram, 0xFFFE, 0xFFFF);
}

int parseRomToRam(NesRam* ram, NesRom* rom){
	int firstPage = firstPageToLoad(rom->header);
	int secondPage = secondPageToLoad(rom->header);

	if(firstPage < 0 || secondPage < 0){
		printf("\n---ERROR---\n\tmapper %i not implemented or bad implemented\n", rom->header->mapperId);
        if(firstPage < 0){
            return firstPage;
        }
        else{
            return secondPage;
        }
	}

    setFirst16KbRom(ram, rom->prgRom->prgRom[firstPage]);
	setLast16KbRom(ram, rom->prgRom->prgRom[secondPage]);
	return 0;
}

void _mirrorRam(NesRam* ram, unsigned short address, unsigned char number, unsigned short start, unsigned short end,
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

void mirrorRam(NesRam* ram, unsigned short address, unsigned char number){
    _mirrorRam(ram, address, number, 0x0, 0x1FFF, 0x0800); // System memory mirror
    _mirrorRam(ram, address, number, 0x2000, 0x3FFF, 0x8); // PPU i/o registers
}

unsigned char loadFromRam(NesRam* ram, unsigned short address){
    return ram->ram[address];
}
char storeIntoRam(NesRam* ram, unsigned short address, unsigned char number){
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
        return ALF_NES_ERROR_CODE_WRITE_ON_READ_ONLY;
    }
}
char storeIntoRamAndSetReadOnly(NesRam *ram, unsigned short address, unsigned char number){
    char aux = 0;
    if(ram->readOnlyRam[address]){
        aux = ALF_NES_ERROR_CODE_WRITE_ON_READ_ONLY;
    }

    ram->ram[address] = number;
    ram->readOnlyRam[address] = 1;
    ram->writeOnReadOnly = 0;
    ram->wroAddress = 0;
    ram->wroValue = 0;
    mirrorRam(ram, address, number);

    return aux;
}

int storeIntoRamAndDisableReadOnly(NesRam* ram, unsigned short address, unsigned char number){
    int retVal = 0;
    if(ram->readOnlyRam[address]){
        retVal = ALF_NES_ERROR_CODE_WRITE_ON_READ_ONLY;
    }

    ram->ram[address] = number;
    ram->readOnlyRam[address] = 0;
    ram->writeOnReadOnly = 0;
    ram->wroAddress = 0;
    ram->wroValue = 0;
    mirrorRam(ram, address, number);

    return retVal;
}

int loadSaveIntoRam(NesRam* ram, unsigned char* saveData, unsigned short SRAMSize){
    unsigned short ramUsed = 0x2000;
    if(SRAMSize < ramUsed){
        ramUsed = SRAMSize;
    }
    for(int i = 0; i*ramUsed < 0x2000; i++){
        charCopy(&(ram->ram[0x6000+i*ramUsed]), saveData, ramUsed);
    }
    return 0;
}

void printfRAM(NesRam* ram, unsigned short start, unsigned short end){
    int aux = 0;
    for(int i = start; i < end; i++){
        printf("0x");
        printfCharAsHex(ram->ram[i]);
        printf(" ");
        aux += 1;
        if(aux == 16){
            aux = 0;
            printf("\n");
        }
    }
}
