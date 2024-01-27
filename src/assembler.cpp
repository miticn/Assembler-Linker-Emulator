#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <list>
#include "../inc/token.hpp"
#include "../inc/token_command_generic.hpp"
#include "../inc/token_command_data.hpp"
#include "../inc/token_command_jump.hpp"
#include "../inc/token_directive.hpp"
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
    yyin = inputFile;
    yyparse();
    fclose(inputFile);

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
    for (auto token : tokenList) {
        if (token->getType() == TokenType::LABEL) {
            LabelToken *labelToken = (LabelToken*)token;
            uint32_t section_index = this->currentSectionIndex;
            Symbol *symbolInTable = this->symtab.findSymbol(labelToken->getName());
            if (symbolInTable) {
                if (symbolInTable->section_index == 0){
                    symbolInTable->section_index = section_index;
                    symbolInTable->value = currentSection->getCurrentPosition();
                    relocatableSymbols.insert(labelToken->getName());
                }
                else{
                    cout << "Error: Symbol " << labelToken->getName() << " already defined" << endl;
                }
            } else {
                Symbol symbol = Symbol(currentSection->getCurrentPosition(), Symbol::Type::NOTYPE, Symbol::Bind::LOCAL, labelToken->getName(), section_index);
                this->symtab.addSymbol(symbol);
            }
        } else if (token->getType() == TokenType::DIRECTIVE) {
            DirectiveToken *directiveToken = (DirectiveToken*)token;
            if(directiveToken->getName()=="section"){
                SectionDirectiveToken *sectionToken = (SectionDirectiveToken*)token;
                this->currentSectionIndex = (this->symtab.addSection(sectionToken->getSectionName()))->section_index;
                this->sections.push_back(Section(sectionToken->getSectionName()));
                this->currentSection = &sections[currentSectionIndex];
            }
            else if(directiveToken->getName()=="extern"){
                ExternDirectiveToken *externToken = (ExternDirectiveToken*)token;
                Symbol *symbolInTable = this->symtab.findSymbol(externToken->getSymbolName());
                if (symbolInTable == nullptr) {
                    uint32_t section_index = 0;
                    Symbol symbol = Symbol(0, Symbol::Type::NOTYPE, Symbol::Bind::GLOBAL, externToken->getSymbolName(), section_index);
                    symbol.externDirective = true;
                    this->symtab.addSymbol(symbol);
                } else{
                    symbolInTable->bind = Symbol::Bind::GLOBAL;
                    symbolInTable->externDirective = true;
                }
            }
            else if(directiveToken->getName()=="global"){
                GlobalDirectiveToken *globalToken = (GlobalDirectiveToken*)token;
                Symbol *symbolInTable = this->symtab.findSymbol(globalToken->getSymbolName());
                if (symbolInTable == nullptr) {
                    uint32_t section_index = 0;
                    Symbol symbol = Symbol(0, Symbol::Type::NOTYPE, Symbol::Bind::GLOBAL, globalToken->getSymbolName(), section_index);
                    symbol.globalDirective = true;
                    this->symtab.addSymbol(symbol);
                } else{
                    symbolInTable->bind = Symbol::Bind::GLOBAL;
                    symbolInTable->globalDirective = true;
                }

            }
            else if(directiveToken->getName()=="equ"){
                EquDirectiveToken *equToken = (EquDirectiveToken*)token;
                uint32_t section_index = this->currentSectionIndex;
                Symbol *symbolInTable = this->symtab.findSymbol(equToken->getName());
                if (symbolInTable) {
                    if (symbolInTable->section_index == 0){
                        symbolInTable->section_index = section_index;
                        symbolInTable->value = equToken->getValue();
                    }
                    else{
                        cout << "Error: Symbol " << equToken->getName() << " already defined" << endl;
                    }
                }else {
                    Symbol symbol = Symbol(equToken->getValue(), Symbol::Type::NOTYPE, Symbol::Bind::LOCAL, equToken->getName(), section_index);
                    this->symtab.addSymbol(symbol);
                }
            } else if(directiveToken->getName()=="end"){
                return;
            }  
        } 
        currentSection->incPosition(token->getSize());
    }
}

void Assembler::secondPass() {
    this->currentSection = nullptr;
    for(auto &section : this->sections){
        section.resetPosition();
    }

    for (auto token : tokenList) {
        if (token->getType() == TokenType::DIRECTIVE) {
            DirectiveToken *directiveToken = (DirectiveToken*)token;
            if(directiveToken->getName()=="section"){
                SectionDirectiveToken *sectionToken = (SectionDirectiveToken*)token;
                this->currentSectionIndex = (this->symtab.findSymbol(sectionToken->getSectionName()))->section_index;
                this->currentSection = &sections[currentSectionIndex];

            } else if(directiveToken->getName()=="word"){
                WordDirectiveToken *wordToken = (WordDirectiveToken*)token;
                if(wordToken->isBackpatchingNeeded()){
                    //symbol
                    Symbol *symbolInTable = this->symtab.findSymbol(wordToken->getSymbol());
                    if(symbolInTable == nullptr){
                        cout << "Error: Symbol " << wordToken->getSymbol() << " not defined" << endl;
                    } else if (symbolInTable->section_index == 0){
                        //needs realocation
                        currentSection->add4Bytes(0);
                    } else{
                        currentSection->add4Bytes(symbolInTable->value);
                        if(this->relocatableSymbols.find(symbolInTable->name) != this->relocatableSymbols.end()){
                            Relocation relocation = Relocation(currentSection->getCurrentPosition()-4, 0, this->currentSectionIndex);
                            this->relocationTable.push_back(relocation);
                        }

                    }
                } else{
                    //literal
                    currentSection->add4Bytes(wordToken->getValue());
                }

            } else if(directiveToken->getName() == "skip"){
                SkipDirectiveToken *skipToken = (SkipDirectiveToken*)token;
                for(int i = 0; i < skipToken->getSize(); i++){
                    currentSection->addByte(0);
                }

            } else if(directiveToken->getName() == "ascii"){
                AsciiDirectiveToken *asciiToken = (AsciiDirectiveToken*)token;
                for(auto c : asciiToken->getAsciiString()){
                    currentSection->addByte(c);
                }
            }
            else if(directiveToken->getName()=="end"){
                return;
            }  
        } else if(token->getType() == TokenType::COMMAND){
            CommandToken *commandToken = (CommandToken*)token;
            currentSection->add4Bytes(commandToken->getInstruction());
            if(commandToken->isBackpatchingNeeded()){
                //check if operand has literal or symbol
                DataCommandToken *dataCommandToken = (DataCommandToken*)token;
                Operand *operand = dataCommandToken->getOperandPtr();
                if(operand->hasLiteral()){

                }else if (operand->hasSymbol()){
                    if(this->relocatableSymbols.find(operand->symbol) != this->relocatableSymbols.end()){
                        //this->relocationTable.push_back(relocation);
                    }

                }else{
                    cout << "Error: Operand has no literal or symbol, can't be backpatched" << endl;
                }
                

                
                
            }
        }
        currentSection->incPosition(token->getSize());
    }
    
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
