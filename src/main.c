#include "c_libs/romParser.h"
#include "c_libs/instructions.h"

int main(int argc, char* argv[]){
    int nothing = 0;
    int printfInst = 0;
    int execute = 0;
    int iterateChr = 0;

    char* defaultFileName = "../roms/smb.nes";
    char* fileName = NULL;
    int errorRet = 0;

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
            else if(strcmp("-printfInst", argv[i]) == 0){
                iterateChr = 1;
                printf("\t\t\titerateChr = 1\n");
            }
        }
        printf("---Arguments end---\n\n");
    }

    struct nesRom* rom = NULL;
    if(fileName != NULL){
        rom = loadRom(fileName);
    }
    if(rom == NULL){
        rom = loadRom(defaultFileName);
    }

    if(rom == NULL){
    	return 1;
    }

    struct nesRegisters* registers = initRegisters();
    struct nesRam* ram = initRam();

    powerUp(registers, ram);
    errorRet = parseRomToRam(ram, rom);
    if(errorRet != 0){
        return errorRet;
    }

    unsigned int reset = getResetVector(ram);
    printf("\tReset vector: $%x\n", reset);

    printf("\n\n");
    if(nothing){
        return 0;
    }
    
    if(execute){
        executeInstructions(registers, ram, rom);
    }
    if(printfInst){
        iterateInstructions(rom);
    }
    if(iterateChr){
        iterateChrRom(rom);
    }
    // iterateInstructions(rom);

    return 0;
}
