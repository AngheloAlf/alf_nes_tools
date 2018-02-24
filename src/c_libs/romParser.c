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

    if(header[7]){
        // printf(".nes 1 or 2.0 detected\n");
        unsigned int prgPageAmount = romHeader->prgPageAmount;
        unsigned int aux = (unsigned int)romHeader->flags9 & 0b1111;
        aux <<= 8;
        prgPageAmount += aux;

        unsigned int chrPageAmount = romHeader->chrPageAmount;
        aux = (unsigned int)romHeader->flags9 & 0b11110000;
        aux <<= 4;
        chrPageAmount += aux;

        if(prgPageAmount*16384 + chrPageAmount*8192 < fileSize){ // TODO: If byte 7 AND $0C = $08,
            printf("NES 2.0 detected\n");
            romHeader->typeVersion = 2;
            romHeader->realPrgPageAmount = prgPageAmount;
            romHeader->realChrPageAmount = chrPageAmount;
        }
        else if(!header[12] && !header[13] && !header[14] && !header[15]){ // TODO: If byte 7 AND $0C = $00
            printf("iNES 1 detected\n");
            romHeader->typeVersion = 1;
        }
        else{
            printf("Problems detecting .nes version. Assuming iNES 1\n");
            romHeader->typeVersion = 1;
        }
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

struct nesRom* generateINesRom(struct nesRomHeader* header, unsigned char* trainer, struct nesPrgRom* prgRomData, struct nesChrRom* chrRomData, unsigned char* playChoiceInstRom, unsigned char* playChoicePRom, unsigned char* title){
    struct nesRom** rom = malloc(sizeof(struct nesRom*));
    *rom = malloc(sizeof(struct nesRom));

    if(header == NULL){
        // ERROR
        return NULL;
    }
    (*rom)->header = header;

    (*rom)->trainer = trainer;
    (*rom)->prgRom = prgRomData;
    (*rom)->chrRom = chrRomData;
    (*rom)->playChoiceInstRom = playChoiceInstRom;
    (*rom)->playChoicePRom = playChoicePRom;
    (*rom)->title = title;

    printf("rom: %p\n", *rom);

    return (*rom);
}

struct nesRom* loadINesRom(FILE* filePtr, unsigned char* header){
    /* load header */
    struct nesRomHeader* romHeader = loadInesHeader(header);
    if(romHeader == NULL){
        // ERROR
        return NULL;
    }

    unsigned char* trainer;
    if(romHeader->flags6 & 0b100){
        printf("\tloading trainer\n");
        trainer = malloc(sizeof(unsigned char) * 512);
        fread(trainer, 512, 1, filePtr);
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
        for(size_t i = 0; i < prgPages; i++){
            prgRom[i] = malloc(sizeof(unsigned char) * PRG_ROM_PAGE_SIZE);
            fread(prgRom[i], PRG_ROM_PAGE_SIZE, 1, filePtr);
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
        for(size_t i = 0; i < chrPages; i++){
            chrRom[i] = malloc(sizeof(unsigned char) * CHR_ROM_PAGE_SIZE);
            fread(chrRom[i], CHR_ROM_PAGE_SIZE, 1, filePtr);
        }
        tiles = generateTilesFromChrRom(chrRom, chrPages);
        chrRomData = generateChrRomData(chrRom, tiles);
    }
    else{
        printf("No chrRom");
    }

    /*
    unsigned char* chrRom;
    unsigned int chrRomSize = romHeader->realChrPageAmount * 8192;
    if(chrRomSize > 0){
        printf("\tloading %i bytes (%i KiB or %i pages) of chrRom\n", chrRomSize, chrRomSize/1024, chrRomSize/(1024*8));
        chrRom = malloc(sizeof(unsigned char) * chrRomSize);
        fread(chrRom, chrRomSize, 1, filePtr);
    }
    else{
        printf("\tno chrRom\n");
        chrRom = NULL;
    }*/

    // playChoice
    unsigned char* playChoiceInstRom = NULL;
    unsigned char* playChoicePRom = NULL;
    if(romHeader->flags7 & 0b10){
        printf("\tloading playChoice\n");

        playChoiceInstRom = malloc(sizeof(unsigned char) * 8192);
        fread(playChoiceInstRom, 8192, 1, filePtr);

        playChoicePRom = malloc(sizeof(unsigned char) * (16 + 16));
        fread(playChoicePRom, 16 + 16, 1, filePtr);
    }
    else{
        printf("\tno playChoice\n");
        playChoiceInstRom = NULL;
        playChoicePRom = NULL;
    }

    // title //
    unsigned char* title = malloc(sizeof(unsigned char) * 128);
    size_t readedBytes = fread(title, 128, 1, filePtr);
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

    struct nesRom* rom = generateINesRom(romHeader, trainer, prgRomData, chrRomData, playChoiceInstRom, playChoicePRom, title);
    printf("rom: %p\n", rom);
    return rom;
}

struct nesRom* loadRom(char* filename){
    size_t header_size = 16;
    unsigned char* header = malloc(sizeof(unsigned char) * header_size);

    FILE* filePtr = fopen(filename, "rb");

    if(filePtr == NULL){
        printf("The file %s does not exists.\n", filename);
        return NULL;
    }

    fseek(filePtr, 0, SEEK_END);
    fileSize = ftell(filePtr);
    fseek(filePtr, 0, SEEK_SET);

    fread(header, header_size, 1, filePtr);

    /*
    for(int i = 0; i < header_size; i++){
        printf("%i %c\n", (unsigned int)header[i], header[i]);
    }
    printf("\n");
    */

    struct nesRom* rom;

    if(header[0] == 'N' && header[1] == 'E' && header[2] == 'S' && header[3] == 0x1A){
        printf(".nes format detected\n");
        rom = loadINesRom(filePtr, header);
    }
        /* else if() */ // other formats...
    else{
        printf("Uncompatible format...\n");
        fclose(filePtr);
        return NULL;
    }

    // free(header);
    fclose(filePtr);

    printf("%.*s\n", 4, rom->header->consType);
    printf("%ld\n", fileSize);

    return rom;
}
