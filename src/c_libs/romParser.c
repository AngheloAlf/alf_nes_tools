//
// Created by anghelo on 23-02-18.
//

#include "romParser.h"

struct nesRomHeader* loadInesHeader(unsigned char* header){
    struct nesRomHeader* romHeader = malloc(sizeof(struct nesRomHeader));

    romHeader->header = malloc(sizeof(unsigned char) * 16);
    charCopy(romHeader->header, header, 16);

    romHeader->consType = malloc(sizeof(unsigned char) * 4);
    charCopy(romHeader->consType, header, 4);

    romHeader->prgPageAmount = header[4];
    romHeader->chrPageAmount = header[5];
    romHeader->flags6 = header[6];
    romHeader->flags7 = header[7];
    romHeader->flags8 = header[8];
    romHeader->flags9 = header[9];
    romHeader->flags10 = header[10];
    romHeader->flags11 = header[11];
    romHeader->flags12 = header[12];
    romHeader->flags13 = header[13];
    romHeader->flags14 = header[14];
    romHeader->flags15 = header[15];

    romHeader->realPrgPageAmount = romHeader->prgPageAmount;
    romHeader->realChrPageAmount = romHeader->chrPageAmount;

    romHeader->mapperId = (unsigned int)(((romHeader->flags6) & HIGH_NIBBLE)>>4 | (romHeader->flags7 & HIGH_NIBBLE));
    romHeader->subMapper = 0;


    unsigned int prgPageAmount = romHeader->prgPageAmount;
    unsigned int aux = (unsigned int)romHeader->flags9 & LOW_NIBBLE;
    aux <<= 8;
    prgPageAmount += aux;

    unsigned int chrPageAmount = romHeader->chrPageAmount;
    aux = (unsigned int)romHeader->flags9 & HIGH_NIBBLE;
    aux <<= 4;
    chrPageAmount += aux;

    romHeader->hasSRAM = (char)((romHeader->flags6&BIT_1)>>1);
    romHeader->SRAMSize = 0;
    if(romHeader->hasSRAM){
        romHeader->SRAMSize = 0x2000;
    }

    if(((romHeader->flags7 & 0x0C) == 0x08) && (prgPageAmount*PRG_ROM_PAGE_SIZE + chrPageAmount*CHR_ROM_PAGE_SIZE < fileSize)){
        printf("NES 2.0 detected\n");
        romHeader->typeVersion = 2;
        romHeader->realPrgPageAmount = prgPageAmount;
        romHeader->realChrPageAmount = chrPageAmount;

        romHeader->mapperId |= (unsigned int)((romHeader->flags8 & LOW_NIBBLE)<<8);
        romHeader->subMapper = (unsigned char)((romHeader->flags8 & HIGH_NIBBLE)>>4);

        if(romHeader->hasSRAM){
            romHeader->SRAMSize = (unsigned short)((romHeader->flags10&HIGH_NIBBLE>>4) * 0x80);
        }

    }
    else if(((romHeader->flags7 & 0x0C) == 0x00) && !header[12] && !header[13] && !header[14] && !header[15]){ // TODO: If byte 7 AND $0C = $00
        printf("iNES 1 detected\n");
        romHeader->typeVersion = 1;
    }
    else{
        printf("archaic iNES detected\n");
        romHeader->typeVersion = 0;
    }

    return romHeader;
}

struct nesPrgRom* generatePrgRomData(unsigned char** prgRom){
    struct nesPrgRom* prgRomData = malloc(sizeof(struct nesPrgRom));
    prgRomData->prgRom = prgRom;

    return prgRomData;
}

struct nesChrRom* generateChrRomData(unsigned char** chrRom, struct tile** tiles){
    struct nesChrRom* chrRomData = malloc(sizeof(struct nesChrRom));
    chrRomData->chrRom = chrRom;
    chrRomData->tiles = tiles;

    return chrRomData;
}

NesRom* generateINesRom(struct nesRomHeader* header, unsigned char* trainer, struct nesPrgRom* prgRomData, struct nesChrRom* chrRomData, unsigned char* playChoiceInstRom, unsigned char* playChoicePRom, unsigned char* title, char* fileName){
    NesRom* rom = malloc(sizeof(NesRom));

    if(header == NULL){
        // ERROR
        return NULL;
    }
    rom->header = header;

    rom->trainer = trainer;
    rom->prgRom = prgRomData;
    rom->chrRom = chrRomData;
    rom->playChoiceInstRom = playChoiceInstRom;
    rom->playChoicePRom = playChoicePRom;
    rom->title = title;

    rom->fileName = malloc(sizeof(char) * strlen(fileName));
    strcpy(rom->fileName, fileName);

    return rom;
}

NesRom* loadINesRom(FILE* filePtr, unsigned char* header, char* fileName){
    /* load header */
    struct nesRomHeader* romHeader = loadInesHeader(header);
    if(romHeader == NULL){
        // ERROR
        return NULL;
    }

    unsigned char* trainer;
    if(romHeader->flags6 & BIT_2){
        printf("\tloading trainer\n");
        trainer = malloc(sizeof(unsigned char) * 512);
        fread(trainer, 1, 512, filePtr);
    }
    else{
        printf("\tno trainer\n");
        trainer = NULL;
    }


    // prgRom
    struct nesPrgRom* prgRomData = NULL;
    size_t prgPages = romHeader->realPrgPageAmount;
    if(prgPages > 0){
        unsigned char** prgRom = malloc(sizeof(unsigned char*) * prgPages);
        printf("\tloading %i bytes (%i KiB or %i pages) of prgRom\n", (int)prgPages*PRG_ROM_PAGE_SIZE, (int)prgPages*PRG_ROM_PAGE_SIZE/1024, (int)prgPages);
        // fread(prgRom, prgPages, PRG_ROM_PAGE_SIZE, filePtr);
        for(size_t i = 0; i < prgPages; i++){
            prgRom[i] = malloc(sizeof(unsigned char) * PRG_ROM_PAGE_SIZE);
            fread(prgRom[i], 1, PRG_ROM_PAGE_SIZE, filePtr);
        }
        prgRomData = generatePrgRomData(prgRom);
    }
    else{
        // TODO: free
        printf("\tbad rom\n");
        return NULL;
    }

    // chrRom
    struct nesChrRom* chrRomData = NULL;
    size_t chrPages = romHeader->realChrPageAmount;
    if(chrPages > 0){
        struct tile** tiles = NULL;
        unsigned char** chrRom = malloc(sizeof(unsigned char*) * chrPages);
        printf("\tloading %i bytes (%i KiB or %i pages) of chrRom\n", (int)chrPages*CHR_ROM_PAGE_SIZE, (int)chrPages*CHR_ROM_PAGE_SIZE/1024, (int)chrPages);
        // fread(chrRom, chrPages, CHR_ROM_PAGE_SIZE, filePtr);
        for(size_t i = 0; i < chrPages; i++){
            chrRom[i] = malloc(sizeof(unsigned char) * CHR_ROM_PAGE_SIZE);
            fread(chrRom[i], 1, CHR_ROM_PAGE_SIZE, filePtr);
        }
        tiles = generateTilesFromChrRom(chrRom, chrPages);
        chrRomData = generateChrRomData(chrRom, tiles);
    }
    else{
        printf("\tno chrRom\n");
    }


    // playChoice
    unsigned char* playChoiceInstRom = NULL;
    unsigned char* playChoicePRom = NULL;
    if(romHeader->flags7 & BIT_1){
        printf("\tloading playChoice\n");

        playChoiceInstRom = malloc(sizeof(unsigned char) * 8192);
        fread(playChoiceInstRom, 1, 8192, filePtr);

        playChoicePRom = malloc(sizeof(unsigned char) * (16 + 16));
        fread(playChoicePRom, 1, 16 + 16, filePtr);
    }
    else{
        printf("\tno playChoice\n");
        playChoiceInstRom = NULL;
        playChoicePRom = NULL;
    }

    // title //
    unsigned char* title = malloc(sizeof(unsigned char) * 128);
    size_t readedBytes = fread(title, 1, 128, filePtr);
    if(readedBytes >= 127 && readedBytes <= 128){
        printf("\tloading %zd bytes of title\n", readedBytes);
        // yada yada
    }
    else{
        printf("\tno title\n");
        printf("\t\treadedBytes of title: %zd\n", readedBytes);
        free(title);
        title = NULL;
    }

    printf("\tmapper: %i\n", romHeader->mapperId);

    NesRom* rom = generateINesRom(romHeader, trainer, prgRomData, chrRomData, playChoiceInstRom, playChoicePRom, title, fileName);
    // printf("rom: %p\n", rom);
    return rom;
}

NesRom* loadRom(char* filename){
    printf("loading ROM: %s\n", filename);
    size_t header_size = 16;
    unsigned char* header = malloc(sizeof(unsigned char) * header_size);

    FILE* filePtr = fopen(filename, "rb");

    if(filePtr == NULL){
        printf("ERROR: The file %s does not exists.\n", filename);
        return NULL;
    }

    fseek(filePtr, 0, SEEK_END);
    fileSize = ftell(filePtr);
    fseek(filePtr, 0, SEEK_SET);

    fread(header, 1, header_size, filePtr);

    /*
    for(int i = 0; i < header_size; i++){
        printf("%i %c\n", (unsigned int)header[i], header[i]);
    }
    printf("\n");
    */

    NesRom* rom;

    if(header[0] == 'N' && header[1] == 'E' && header[2] == 'S' && header[3] == 0x1A){
        printf(".nes (iNES) format detected\n");
        rom = loadINesRom(filePtr, header, filename);
    }
    else if(header[0] == 'N' && header[1] == 'E' && header[2] == 'S' && header[3] == 'M' && header[4] == 0x1A){
        printf(".nsf (music) format detected\n");
        printf("format not implemented yet\n");
        return NULL;
    }
    else if(header[0] == 'U' && header[1] == 'N' && header[2] == 'I' && header[3] == 'F'){
        printf(".unf (UNIF) format detected\n"); // .unf or .unif
        printf("format not implemented yet\n");
        return NULL;
    }
    /* else if() */ // other formats...
    else{
        printf("Uncompatible format...\n");
        fclose(filePtr);
        return NULL;
    }

    // free(header);
    fclose(filePtr);

    // printf("filesize: %ld\n", fileSize);

    return rom;
}



// Mappers:

int firstPageToLoad(NesRomHeader* header){
    int page;
    switch(header->mapperId){
        case 0:
            if(header->realPrgPageAmount > 2){
                page = ALF_NES_ERROR_CODE_MAPPER_WRONG_IMPLEMENTATION;
            }
            else{
                page = 0;
            }
            break;
        default:
            page = ALF_NES_ERROR_CODE_MAPPER_NOT_IMPLEMENTED;
            break;
    }
    return page;
}

int secondPageToLoad(NesRomHeader* header){
    int page;
    switch(header->mapperId){
        case 0:
            if(header->realPrgPageAmount > 2){
                page = ALF_NES_ERROR_CODE_MAPPER_WRONG_IMPLEMENTATION;
            }
            else if(header->realPrgPageAmount == 2){
                page = 1;
            }
            else{
                page = 0;
            }
            break;
        default:
            page = ALF_NES_ERROR_CODE_MAPPER_NOT_IMPLEMENTED;
            break;
    }
    return page;
}

int chrPageToLoad(NesRomHeader* header){
    int page;
    switch(header->mapperId){
        case 0:
            if(header->realChrPageAmount > 1){
                page = ALF_NES_ERROR_CODE_MAPPER_WRONG_IMPLEMENTATION;
            }
            else{
                page = 0;
            }
            break;
        default:
            page = ALF_NES_ERROR_CODE_MAPPER_NOT_IMPLEMENTED;
            break;
    }
    return page;
}

