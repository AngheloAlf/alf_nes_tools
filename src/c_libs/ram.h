//
// Created by anghelo on 23-02-18.
//

#ifndef ALF_NES_TOOLS_RAM_H
#define ALF_NES_TOOLS_RAM_H

#include <stdlib.h>

struct nesRam{
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
    unsigned char* ram;
};

struct nesRam* initRam();

#endif //ALF_NES_TOOLS_RAM_H
