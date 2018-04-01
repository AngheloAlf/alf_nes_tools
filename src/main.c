#include <stdio.h>

#include "c_libs/common.h"
#include "c_libs/AlfNes.h"

typedef struct{
    int nothing;
    int execute;
    int printfChr;
    int withNumber;
    char* fileName;
}Arguments;

Arguments* parseArguments(int argc, char* argv[]){
    Arguments* args = malloc(sizeof(Arguments));
    args->nothing = 0;
    args->execute = 0;
    args->printfChr = 0;
    args->withNumber = 0;

    args->fileName = "../roms/smb.nes"; // default
    if(argc > 1){
        printf("-----Arguments-----\n\n");
        args->fileName = argv[1];
        for(int i = 1; i < argc; i++){
            printf("\t%i: %s\n", i, argv[i]);

            if(strcmp("-nothing", argv[i]) == 0){
                args->nothing = 1;
                printf("\t\tnothing = 1\n");
            }
            else if(strcmp("-execute", argv[i]) == 0){
                args->execute = 1;
                printf("\t\texecute = 1\n");
            }
            else if(strcmp("-printfChr", argv[i]) == 0){
                args->printfChr = 1;
                printf("\t\tprintfChr = 1\n");
            }
            else if(strcmp("-withNumber", argv[i]) == 0){
                args->withNumber = 1;
                printf("\t\twithNumber = 1\n");
            }
        }
        printf("---Arguments end---\n\n");
    }

    return args;
}

int main(int argc, char* argv[]){
    int retVal = 0;

    Arguments* args = parseArguments(argc, argv);

    AlfNes* nes = initAlfNes();
    retVal = NesPowerUp(nes, args->fileName);
    if(retVal < 0){
        return retVal;
    }

    if(args->printfChr){
        printfChrRom(nes->rom, args->withNumber);
    }

    printf("\n\n");
    if(args->nothing){
        return 0;
    }
    
    if(args->execute){
        retVal = executeInstructions(nes->cpu, nes->ram, nes->rom);
        if(retVal < 0){
            return retVal;
        }
    }

    // printfRAM(ram, 0x6000, 0x8000);

    free(args);

    return 0;
}
