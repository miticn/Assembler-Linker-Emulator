#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/assembler.hpp"

void Assembler::assemble(char *inputFileName, char *outputFileName) {
    printf("Assembling %s into %s...\n", inputFileName, outputFileName);
    

}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s [options] <input_file>\n", argv[0]);
        return 1;
    }

    char *outputFileName = "output.o";
    
    for (int i = 1; i < argc - 1; i++) {
        if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            outputFileName = argv[i + 1];
            i++;
        } else {
            printf("Unknown option: %s\n", argv[i]);
            return 1;
        }
    }

    char *inputFileName = argv[argc - 1];

    Assembler assembler;
    assembler.assemble(inputFileName, outputFileName);

    return 0;
}
