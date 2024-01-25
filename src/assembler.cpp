#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <list>
#include "../inc/token.hpp"
#include "../inc/assembler.hpp"
using namespace std;

using namespace std;
//initialise
list<Token*> Assembler::tokenList;

void Assembler::assemble(char *inputFileName, char *outputFileName) {
    printf("Assembling %s into %s...\n", inputFileName, outputFileName);
    
    FILE *inputFile = fopen(inputFileName, "r");
    if (!inputFile) {
        perror("Error opening input file");
        return;
    }

    // Set yyin to the input file
    yyin = inputFile;
    
    yyparse();


    fclose(inputFile);

    //print tokenList
    printTokenList();

    firstPass();
    secondPass();
}

void Assembler::printTokenList() {
    cout << "Token list: " << tokenList.size()<< endl;
    for (auto token : tokenList) {
        if (token->getType() == TokenType::LABEL) {
            LabelToken *labelToken = (LabelToken*)token;
            cout << "Label: " << labelToken->getName()<< endl;
        } else if (token->getType() == TokenType::DIRECTIVE) {
            cout << "Directive: " << ((DirectiveToken*)token)->getName() << endl;
        } else if (token->getType() == TokenType::COMMAND) {
            cout << "Command: " << ((CommandToken*)token)->getName() << endl;
            cout << "Instruction: " << ((CommandToken*)token)->getInstruction() << endl;
        }
    }
}

void Assembler::firstPass() {
    //iterate through tokenList and add to symtab all definitions
    for (auto token : tokenList) {
        if (token->getType() == TokenType::LABEL) {
            LabelToken *labelToken = (LabelToken*)token;

        } else if (token->getType() == TokenType::DIRECTIVE) {
            DirectiveToken *directiveToken = (DirectiveToken*)token;
            
            
        } else if (token->getType() == TokenType::COMMAND) {
            CommandToken *commandToken = (CommandToken*)token;
            
        }
        token->getSize();
    }
    
}

void Assembler::secondPass() {
    
    
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
