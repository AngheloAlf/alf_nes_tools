//
// Created by anghelo on 23-02-18.
//

#ifndef ALF_NES_TOOLS_RAM_H
#define ALF_NES_TOOLS_RAM_H

#include "common.h"
#include "romParser.h"


/*
    https://wiki.nesdev.com/w/index.php/CPU_memory_map
    Address range 	Size 	Device
    $0000-$07FF 	$0800 	2KB internal RAM
    $0800-$0FFF 	$0800 	Mirrors of $0000-$07FF
    $1000-$17FF 	$0800
    $1800-$1FFF 	$0800
    $2000-$2007 	$0008 	NES PPU registers
    $2008-$3FFF 	$1FF8 	Mirrors of $2000-2007 (repeats every 8 bytes)
    $4000-$4017 	$0018 	NES APU and I/O registers
    $4018-$401F 	$0008 	APU and I/O functionality that is normally disabled. See CPU Test Mode.
    $4020-$FFFF 	$BFE0 	Cartridge space: PRG ROM, PRG RAM, and mapper registers (See Note)
*/


/*
    Note: Most common boards and iNES mappers address ROM and Save/Work RAM in this format:

        $6000-$7FFF = Battery Backed Save or Work RAM
        $8000-$FFFF = Usual ROM, commonly with Mapper Registers (see MMC1 and UxROM for example)

    The CPU expects interrupt vectors in a fixed place at the end of the cartridge space:

        $FFFA-$FFFB = NMI vector
        $FFFC-$FFFD = Reset vector
        $FFFE-$FFFF = IRQ/BRK vector

    If a mapper doesn't fix $FFFA-$FFFF to some known bank (typically, along with the rest of the bank containing them, e.g. $C000-$FFFF for a 16KiB banking mapper) or use some sort of reset detection, the vectors need to be stored in all banks.
*/

NesRam* initRam();
void freeRam(NesRam* ram);

int ramPowerUp(NesRam* ram);

void setFirst16KbRom(NesRam* ram, const unsigned char* romPage);
void setLast16KbRom(NesRam* ram, const unsigned char* romPage);

unsigned short getNMIVector(NesRam* ram);
unsigned short getResetVector(NesRam* ram);
unsigned short getIRQBRKVector(NesRam* ram);

int parseRomToRam(NesRam* ram, NesRom* rom);

unsigned char loadFromRam(NesRam* ram, unsigned short address);
char storeIntoRam(NesRam* ram, unsigned short address, unsigned char number);
char storeIntoRamAndSetReadOnly(NesRam *ram, unsigned short address, unsigned char number);
int storeIntoRamAndDisableReadOnly(NesRam* ram, unsigned short address, unsigned char number);;

int loadSaveIntoRam(NesRam* ram, unsigned char* saveData, unsigned short SRAMSize);

void printfRAM(NesRam* ram, unsigned short start, unsigned short end);

#endif //ALF_NES_TOOLS_RAM_H
