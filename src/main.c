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
        rom = loadRom(defaultFileName);
    }

    if(rom == NULL){
    	return 1;
    }

    if(printfChr){
        printfChrRom(rom, withNumber);
    }

    struct nesRegisters* registers = initRegisters();
    /*
    unsigned char* asd = malloc(sizeof(unsigned char)*3);
    asd[0] = 0x69;
    asd[1] = 64*2;
    asd[2] = 0x00;
    struct instruction* instData = detectType(asd, 0);
    opcode_69(instData, registers, NULL);
    opcode_69(instData, registers, NULL);
    opcode_69(instData, registers, NULL);
    opcode_69(instData, registers, NULL);
    printf("%hhu\n", getCarry(registers));
    */

    struct nesRam* ram = initRam();

    // storeIntoRam(ram, 0x2007, 0x6f);

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
    // iterateInstructions(rom);

    return 0;
}
