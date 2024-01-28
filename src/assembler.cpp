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
    cout<<"First pass done"<<endl;
    this->symtab.printSymbolTable();
    //secondPass();
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
    cout << "First pass started" << endl;

    // Iterate through the token list for the first pass
    for (auto token : tokenList) {
        if (token->getType() == TokenType::LABEL) {
            processLabelTokenFirstPass((LabelToken*)token);
        } else if (token->getType() == TokenType::DIRECTIVE) {
            processDirectiveTokenFirstPass((DirectiveToken*)token);
        }

        // Update the current section position
        updateCurrentSectionPosition(token);
    }
}

void Assembler::processLabelTokenFirstPass(LabelToken* labelToken) {
    // Process label tokens encountered during the first pass
    uint32_t sectionIndex = currentSectionIndex;
    uint32_t symbolIndex = symtab.findSymbolIndex(labelToken->getLabelName());

    if (symbolIndex != 0) {
        processExistingSymbolFirstPass(symbolIndex, labelToken, sectionIndex);
    } else {
        // Add a new symbol if not found
        Symbol symbol = Symbol(sections[currentSectionIndex].getCurrentPosition(), Symbol::Type::NOTYPE, Symbol::Bind::LOCAL, labelToken->getName(), sectionIndex);
        symtab.addSymbol(symbol);
    }
}

void Assembler::processExistingSymbolFirstPass(uint32_t symbolIndex, LabelToken* labelToken, uint32_t sectionIndex) {
    // Process existing symbols encountered during the first pass
    if (symtab.symbols[symbolIndex].section_index == 0) {
        symtab.symbols[symbolIndex].section_index = sectionIndex;
        symtab.symbols[symbolIndex].value = sections[currentSectionIndex].getCurrentPosition();
        relocatableSymbols.insert(labelToken->getLabelName());
    } else {
        cout << "Error: Symbol " << labelToken->getLabelName() << " already defined" << endl;
    }
}

void Assembler::processDirectiveTokenFirstPass(DirectiveToken* directiveToken) {
    // Process directive tokens encountered during the first pass
    if (directiveToken->getName() == "section") {
        processSectionDirectiveTokenFirstPass((SectionDirectiveToken*)directiveToken);
    } else if (directiveToken->getName() == "extern") {
        processExternDirectiveTokenFirstPass((ExternDirectiveToken*)directiveToken);
    } else if (directiveToken->getName() == "global") {
        processGlobalDirectiveTokenFirstPass((GlobalDirectiveToken*)directiveToken);
    } else if (directiveToken->getName() == "equ") {
        processEquDirectiveTokenFirstPass((EquDirectiveToken*)directiveToken);
    } else if (directiveToken->getName() == "end") {
        return;
    }
}

void Assembler::processSectionDirectiveTokenFirstPass(SectionDirectiveToken* sectionToken) {
    // Process section directive tokens encountered during the first pass
    symtab.addSection(sectionToken->getSectionName());
    currentSectionIndex = symtab.findSymbolIndex(sectionToken->getSectionName());
    sections.push_back(Section(sectionToken->getSectionName()));
}

void Assembler::processExternDirectiveTokenFirstPass(ExternDirectiveToken* externToken) {
    // Process extern directive tokens encountered during the first pass
    uint32_t symbolIndex = symtab.findSymbolIndex(externToken->getSymbolName());
    if (symbolIndex == 0) {
        Symbol symbol = Symbol(0, Symbol::Type::NOTYPE, Symbol::Bind::GLOBAL, externToken->getSymbolName(), 0);
        symbol.externDirective = true;
        symtab.addSymbol(symbol);
    } else {
        updateSymbolForDirective(symbolIndex);
    }
}

void Assembler::processGlobalDirectiveTokenFirstPass(GlobalDirectiveToken* globalToken) {
    // Process global directive tokens encountered during the first pass
    uint32_t symbolIndex = symtab.findSymbolIndex(globalToken->getSymbolName());
    if (symbolIndex == 0) {
        Symbol symbol = Symbol(0, Symbol::Type::NOTYPE, Symbol::Bind::GLOBAL, globalToken->getSymbolName(), 0);
        symbol.globalDirective = true;
        symtab.addSymbol(symbol);
    } else {
        updateSymbolForDirective(symbolIndex);
    }
}

void Assembler::processEquDirectiveTokenFirstPass(EquDirectiveToken* equToken) {
    // Process equ directive tokens encountered during the first pass
    uint32_t sectionIndex = currentSectionIndex;
    uint32_t symbolIndex = symtab.findSymbolIndex(equToken->getSymbolName());
    if (symbolIndex) {
        if (symtab.symbols[symbolIndex].section_index == 0) {
            symtab.symbols[symbolIndex].section_index = sectionIndex;
            symtab.symbols[symbolIndex].value = equToken->getValue();
        } else {
            cout << "Error: Symbol " << equToken->getName() << " already defined" << endl;
        }
    } else {
        Symbol symbol = Symbol(equToken->getValue(), Symbol::Type::NOTYPE, Symbol::Bind::LOCAL, equToken->getName(), sectionIndex);
        symtab.addSymbol(symbol);
    }
}

void Assembler::updateSymbolForDirective(uint32_t symbolIndex) {
    // Update symbol properties for directives encountered during the first pass
    symtab.symbols[symbolIndex].bind = Symbol::Bind::GLOBAL;
    symtab.symbols[symbolIndex].externDirective = true;
}

void Assembler::updateCurrentSectionPosition(Token* token) {
    // Update the current section position based on token size
    if (currentSectionIndex != 0) 
        sections[currentSectionIndex].incPosition(token->getSize());
}

/*
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
                this->currentSectionIndex = symtab.findSymbolIndex(sectionToken->getSectionName());
                this->sections.push_back(Section(sectionToken->getSectionName()));
                this->currentSection = &sections[currentSectionIndex];

            } else if(directiveToken->getName()=="word"){
                WordDirectiveToken *wordToken = (WordDirectiveToken*)token;
                if(wordToken->isBackpatchingNeeded()){
                    //symbol
                    uint32_t symbolIndex = this->symtab.findSymbolIndex(wordToken->getSymbol());
                    if(symbolIndex == 0){
                        cout << "Error: Symbol " << wordToken->getSymbol() << " not defined" << endl;
                    } else if (symtab.symbols[symbolIndex].section_index == 0){
                        //needs realocation
                        currentSection->add4Bytes(0);
                    } else{
                        currentSection->add4Bytes(symtab.symbols[symbolIndex].value);
                        if(this->relocatableSymbols.find(symtab.symbols[symbolIndex].name) != this->relocatableSymbols.end()){
                            Relocation relocation = Relocation(currentSection->getCurrentPosition()-4, 0, this->currentSectionIndex);
                            this->currentSection->relocationTable.push_back(relocation);
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
        if (currentSection != nullptr)
            currentSection->incPosition(token->getSize());
    }
    
}*/

int main(int argc, char *argv[]) {
    Assembler assembler;
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

    assembler.assemble(inputFileName, outputFileName);

    return 0;
}
