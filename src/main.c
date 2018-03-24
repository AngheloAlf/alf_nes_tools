#include "c_libs/romParser.h"
#include "c_libs/instructions.h"

int main(int argc, char* argv[]){
    int nothing = 0;
    int printfInst = 0;
    int execute = 0;
    int printfChr = 0;
    int withNumber = 0;

    char* defaultFileName = "../roms/smb.nes";
    char* fileName = NULL;
    int retVal = 0;

    if(argc > 1){
        printf("-----Arguments-----\n");
        fileName = argv[1];
        for(int i = 1; i < argc; i++){
            printf("\t%i: %s\n", i, argv[i]);

            if(strcmp("-nothing", argv[i]) == 0){
                nothing = 1;
                printf("\t\t\tnothing = 1\n");
            }

            else if(strcmp("-execute", argv[i]) == 0){
                execute = 1;
                printf("\t\t\texecute = 1\n");
            }

            else if(strcmp("-printfInst", argv[i]) == 0){
                printfInst = 1;
                printf("\t\t\tprintfInst = 1\n");
            }

            else if(strcmp("-printfChr", argv[i]) == 0){
                printfChr = 1;
                printf("\t\t\tprintfChr = 1\n");
            }
            else if(strcmp("-withNumber", argv[i]) == 0){
                withNumber = 1;
                printf("\t\t\twithNumber = 1\n");
            }
        }
        printf("---Arguments end---\n\n");
    }

    struct nesRom* rom = NULL;
    if(fileName != NULL){
        rom = loadRom(fileName);
    }
    if(rom == NULL){
        fileName = defaultFileName;
        rom = loadRom(defaultFileName);
    }

    if(rom == NULL){
    	return -6;
    }

    if(printfChr){
        printfChrRom(rom, withNumber);
    }

    struct nesRegisters* registers = initRegisters();
    struct nesRam* ram = initRam();

    powerUp(registers, ram);

    retVal = parseRomToRam(ram, rom);
    if(retVal < 0){
        return retVal;
    }

    retVal = parseSaveToRam(ram, rom, fileName);
    if(retVal < 0){
        printf("retVal: %i", retVal);
        return retVal;
    }

    unsigned int reset = getResetVector(ram);
    printf("\tReset vector: $%x\n", reset);

    printf("\n\n");
    if(nothing){
        return 0;
    }
    
    if(execute){
        retVal = executeInstructions(registers, ram, rom);
        if(retVal < 0){
            return retVal;
        }
    }
    if(printfInst){
        iterateInstructions(rom);
    }

    //printfRAM(ram, 0x6000, 0x8000);

    return 0;
}
