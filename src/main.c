#include <string.h>
#include "c_libs/romParser.h"
#include "c_libs/instructions.h"
#include "c_libs/chr.h"

int main(int argc, char* argv[]){
    int printfInst = 0;
    char* defaultFileName = "../roms/smb3.nes";
    char* fileName = NULL;

    if(argc > 1){
        printf("-----Arguments-----\n");
        fileName = argv[1];
        for(int i = 1; i < argc; i++){
            printf("\t%i: %s\n", i, argv[i]);
            if(strcmp("-printfInst", argv[i]) == 0){
                printfInst = 1;
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

    if(rom != NULL){
        if(printfInst){
            printfInstructions(rom);
        }
        // iterateInstructions(rom);
        // iterateChrRom(rom);
    }
    return 0;
}
