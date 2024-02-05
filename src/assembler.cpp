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

    //this->symtab.printSymbolTable();
    firstPass();
    cout<<"First pass done"<<endl;
    secondPass();
    this->symtab.printSymbolTable();
    
    std::ofstream outFile(outputFileName, std::ios::binary);
    // serialize symtab into file
    this->symtab.serialize(outFile);
    // serialize sections into file
    for (auto &section : this->sections) {
        section.serialize(outFile);
    }
}

void Assembler::printTokenList() {
    cout << "Token list: " << tokenList.size()<< endl;
    for (auto token : tokenList) {
        if (token->getType() == TokenType::LABEL) {
            LabelToken *labelToken = (LabelToken*)token;
            cout << "Label: " << labelToken->getLabelName()<< endl;
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

    for(uint32_t i = 0; i < symtab.symbols.size(); i++){
        symtab.symbols[i].index = i;
    }
}

void Assembler::processLabelTokenFirstPass(LabelToken* labelToken) {
    uint32_t symbolIndex = symtab.findSymbolIndex(labelToken->getLabelName());

    if (symbolIndex != 0 && symtab.symbols[symbolIndex].section_index != 0) {
        // Symbol already defined
        cout << "Error: Symbol " << labelToken->getLabelName() << " already defined" << endl;
        exit(1);
    }
    if (symbolIndex == 0) {
        // Add a new symbol if not found
        Symbol symbol = Symbol(sections[currentSectionIndex].getCurrentPosition(), Symbol::Type::NOTYPE, Symbol::Bind::LOCAL, labelToken->getLabelName(), currentSectionIndex);
        symtab.addSymbol(symbol);
    } else {
        // Update existing symbol
        symtab.symbols[symbolIndex].section_index = currentSectionIndex;
        symtab.symbols[symbolIndex].value = sections[currentSectionIndex].getCurrentPosition();
    }
    //relocatableSymbols.insert(labelToken->getLabelName());
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
        symbol.directive = Symbol::Directive::EXTERND;
        symtab.addSymbol(symbol);
    } else if (symtab.symbols[symbolIndex].directive == Symbol::Directive::NONED){
        symtab.symbols[symbolIndex].bind = Symbol::Bind::GLOBAL;
        symtab.symbols[symbolIndex].directive = Symbol::Directive::EXTERND;
    } else{
        cout << "Error: Symbol " << externToken->getSymbolName() << " already defined" << endl;
        exit(1);
    }
}

void Assembler::processGlobalDirectiveTokenFirstPass(GlobalDirectiveToken* globalToken) {
    // Process global directive tokens encountered during the first pass
    uint32_t symbolIndex = symtab.findSymbolIndex(globalToken->getSymbolName());
    if (symbolIndex == 0) {
        Symbol symbol = Symbol(0, Symbol::Type::NOTYPE, Symbol::Bind::GLOBAL, globalToken->getSymbolName(), 0);
        symbol.directive = Symbol::Directive::GLOBALD;
        symtab.addSymbol(symbol);
    } else if (symtab.symbols[symbolIndex].directive == Symbol::Directive::NONED){
        symtab.symbols[symbolIndex].bind = Symbol::Bind::GLOBAL;
        symtab.symbols[symbolIndex].directive = Symbol::Directive::GLOBALD;
    } else {
        cout << "Error: Symbol " << globalToken->getSymbolName() << " already defined" << endl;
        exit(1);
    }
}

void Assembler::processEquDirectiveTokenFirstPass(EquDirectiveToken* equToken) {
    // Process equ directive tokens encountered during the first pass
    uint32_t symbolIndex = symtab.findSymbolIndex(equToken->getSymbolName());
    if (symbolIndex==0 && symtab.symbols[symbolIndex].section_index == 0) {
        symtab.symbols[symbolIndex].section_index = ABS_SYMBOL_INDEX;
        symtab.symbols[symbolIndex].value = equToken->getValue();
    } else if (symbolIndex==0 && symtab.symbols[symbolIndex].section_index != 0) {
        cout << "Error: Symbol " << equToken->getName() << " already defined" << endl;
        exit(1);
    } else {
        Symbol symbol = Symbol(equToken->getValue(), Symbol::Type::NOTYPE, Symbol::Bind::LOCAL, equToken->getName(), ABS_SYMBOL_INDEX);
        symtab.addSymbol(symbol);
    }
}

void Assembler::updateCurrentSectionPosition(Token* token) {
    // Update the current section position based on token size
    if (currentSectionIndex != 0) 
        sections[currentSectionIndex].incPosition(token->getSize());
}

//****************SECOND PASS*****************//
void Assembler::secondPass() {
    resetSectionPositions();
    makeLiteralPools();    
    

    for (auto token : tokenList) {
        if (token->getType() == TokenType::DIRECTIVE) {
            processDirectiveTokenSecondPass(token);
        } else if (token->getType() == TokenType::COMMAND) {
            processCommandTokenSecondPass(token);
        }
        //updateCurrentSectionPosition(token);
    }
}

void Assembler::processDirectiveTokenSecondPass(Token* token) {
    DirectiveToken* directiveToken = (DirectiveToken*)token;
    if (directiveToken->getName() == "section") {
        processSectionDirectiveSecondPass(token);
    } else if (directiveToken->getName() == "word") {
        processWordDirectiveSecondPass(token);
    } else if (directiveToken->getName() == "skip") {
        processSkipDirectiveSecondPass(token);
    } else if (directiveToken->getName() == "ascii") {
        processAsciiDirectiveSecondPass(token);
    } else if (directiveToken->getName() == "end") {
        return;
    }
}

void Assembler::processSectionDirectiveSecondPass(Token* token) {
    SectionDirectiveToken* sectionToken = (SectionDirectiveToken*)token;
    this->currentSectionIndex = symtab.findSymbolIndex(sectionToken->getSectionName());
}

void Assembler::processWordDirectiveSecondPass(Token* token) {
    WordDirectiveToken* wordToken = (WordDirectiveToken*)token;
    if (wordToken->isBackpatchingNeeded()) {
        //is symbol
        uint32_t symbolIndex = this->symtab.findSymbolIndex(wordToken->getSymbol());
        if (symbolIndex == 0) {
            cout << "Error: Symbol " << wordToken->getSymbol() << " not defined" << endl;
            exit(1);
        } else if (symtab.symbols[symbolIndex].section_index == 0) { //is global and not defined
            sections[currentSectionIndex].add4Bytes(0);
            Relocation relocation = Relocation(sections[currentSectionIndex].getCurrentPosition() - 4, symbolIndex);
            sections[currentSectionIndex].relocationTable.push_back(relocation);
        } else { //is defined
            sections[currentSectionIndex].add4Bytes(symtab.symbols[symbolIndex].value);
            if(symtab.symbols[symbolIndex].section_index != ABS_SYMBOL_INDEX){
                Relocation relocation = Relocation(sections[currentSectionIndex].getCurrentPosition() - 4, symtab.symbols[symbolIndex].section_index);
                sections[currentSectionIndex].relocationTable.push_back(relocation);
            }
        }
    } else {
        //is literal
        sections[currentSectionIndex].add4Bytes(wordToken->getValue());
    }
}

void Assembler::processSkipDirectiveSecondPass(Token* token) {
    SkipDirectiveToken* skipToken = (SkipDirectiveToken*)token;
    for (int i = 0; i < skipToken->getSize(); i++) {
        sections[currentSectionIndex].addByte(0);
    }
}

void Assembler::processAsciiDirectiveSecondPass(Token* token) {
    AsciiDirectiveToken* asciiToken = (AsciiDirectiveToken*)token;
    for (auto c : asciiToken->getAsciiString()) {
        sections[currentSectionIndex].addByte(c);
    }
}

void Assembler::processCommandTokenSecondPass(Token* token) {
    CommandToken* commandToken = (CommandToken*)token;
    if (commandToken->isBackpatchingNeeded()) {
        OperandCommandToken* operandCommandToken = (OperandCommandToken*)commandToken;
        Operand* operand = operandCommandToken->getOperandPtr();
        uint32_t disp = 0;
        if(operand->hasLiteral()){
            //add to literal pool
            this->sections[currentSectionIndex].literal_pool->addLiteral(operand->literal);
            uint32_t offsetFromSectionStart = this->sections[currentSectionIndex].literal_pool->getLiteralOffset(operand->literal);
            disp = offsetFromSectionStart - this->sections[currentSectionIndex].getCurrentPosition() - 4;
        } else if (operand->hasSymbol()){
            uint32_t symbolIndex = symtab.findSymbolIndex(operand->symbol);
            if(operand->type==Operand::OperandType::MEMORY_REGISTER_OFFSET_SYMBOL){
                //backpatch directly to disp
                if(this->symtab.symbols[symbolIndex].section_index!= ABS_SYMBOL_INDEX){
                    cout << "Error: Symbol " << operand->symbol << " is not absolute(REG+SYMB)" << endl;
                    exit(1);
                }
                disp = this->symtab.symbols[symbolIndex].value;
                if(disp > 0xFFF){
                    cout << "Error: Symbol " << operand->symbol << " is too large for memory offset" << endl;
                    exit(1);
                }
            }
            else if (symbolIndex == 0) {
                cout << "Error: Symbol " << operand->symbol << " not declared" << endl;
                exit(1);
            } else if (symtab.symbols[symbolIndex].section_index == 0) { //is global and not defined
                if(!sections[currentSectionIndex].literal_pool->isSymbolPresent(operand->symbol)){
                    sections[currentSectionIndex].literal_pool->addSymbol(operand->symbol, 0);
                    Relocation relocation = Relocation(sections[currentSectionIndex].literal_pool->getSymbolOffset(operand->symbol), symbolIndex);
                    sections[currentSectionIndex].relocationTable.push_back(relocation);
                }
                disp = sections[currentSectionIndex].literal_pool->getSymbolOffset(operand->symbol) - sections[currentSectionIndex].getCurrentPosition() - 4;
            } else { //is defined
                if(!sections[currentSectionIndex].literal_pool->isSymbolPresent(operand->symbol)){
                    sections[currentSectionIndex].literal_pool->addSymbol(operand->symbol, symtab.symbols[symbolIndex].value);
                    if(symtab.symbols[symbolIndex].section_index != ABS_SYMBOL_INDEX){
                        Relocation relocation = Relocation(sections[currentSectionIndex].literal_pool->getSymbolOffset(operand->symbol), symtab.symbols[symbolIndex].section_index);
                        sections[currentSectionIndex].relocationTable.push_back(relocation);
                    }
                }
                disp = sections[currentSectionIndex].literal_pool->getSymbolOffset(operand->symbol) - sections[currentSectionIndex].getCurrentPosition() - 4;
            }
        }else{
            cout << "Error: Command " << commandToken->getName() << " has no operand" << endl;
            exit(1);
        }
        commandToken->disp = disp;
    }
    sections[currentSectionIndex].add4Bytes(commandToken->getInstruction());
}

void Assembler::resetSectionPositions() {
    this->currentSectionIndex = 0;
    for (auto &section : this->sections) {
        section.resetPosition();
    }
}

void Assembler::makeLiteralPools(){
    for (auto &section : this->sections) {
        section.makePool();
    }
}

int main(int argc, char *argv[]) {
    Assembler assembler;
    char *inputFileName = NULL;
    char *outputFileName = "output.o";

    // Parse command-line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            outputFileName = argv[i + 1];
            i++;
        } else if (argv[i][0] != '-') {
            inputFileName = argv[i];
        } else {
            printf("Unknown option: %s\n", argv[i]);
            return 1;
        }
    }

    // Check if an input file is provided
    if (inputFileName == NULL) {
        printf("Usage: %s [options] <input_file>\n", argv[0]);
        return 1;
    }

    assembler.assemble(inputFileName, outputFileName);

    return 0;
}