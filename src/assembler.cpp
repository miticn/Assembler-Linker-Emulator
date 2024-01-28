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

    this->symtab.printSymbolTable();
    firstPass();
    cout<<"First pass done"<<endl;
    this->symtab.printSymbolTable();
    secondPass();

    // Write the data to the output file
    for (auto &section : this->sections) {
        section.mergeSectionAndPool();
    }
    
    std::ofstream outFile(outputFileName, std::ios::binary);
    //write string for object file
    outFile << "__OBJFILE__" << std::endl;
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
        exit(1);
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
        symtab.symbols[symbolIndex].bind = Symbol::Bind::GLOBAL;
        symtab.symbols[symbolIndex].externDirective = true;
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
        symtab.symbols[symbolIndex].bind = Symbol::Bind::GLOBAL;
        symtab.symbols[symbolIndex].globalDirective = true;
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
            exit(1);
        }
    } else {
        Symbol symbol = Symbol(equToken->getValue(), Symbol::Type::NOTYPE, Symbol::Bind::LOCAL, equToken->getName(), sectionIndex);
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

    for (auto token : tokenList) {
        if (token->getType() == TokenType::DIRECTIVE) {
            processDirectiveTokenSecondPass(token);
        } else if (token->getType() == TokenType::COMMAND) {
            processCommandTokenSecondPass(token);
        }
        //updateCurrentSectionPosition(token);
    }
    //merge section and literal pool both are vectors
    for (auto &section : this->sections) {
        section.data.insert(section.data.end(), section.literal_pool.pool.begin(), section.literal_pool.pool.end());
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
        } else if (symtab.symbols[symbolIndex].section_index == 0) {
            sections[currentSectionIndex].add4Bytes(0);
        } else {
            sections[currentSectionIndex].add4Bytes(symtab.symbols[symbolIndex].value);
            if (this->relocatableSymbols.find(symtab.symbols[symbolIndex].name) != this->relocatableSymbols.end()) {
                Relocation relocation = Relocation(sections[currentSectionIndex].getCurrentPosition() - 4, 0, this->currentSectionIndex);
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
    sections[currentSectionIndex].add4Bytes(commandToken->getInstruction());
    if (commandToken->isBackpatchingNeeded()) {
        OperandCommandToken* operandCommandToken = (OperandCommandToken*)token;
        Operand* operand = operandCommandToken->getOperandPtr();
        if (operand->hasLiteral()) {
            // Handle literal backpatching
            sections[currentSectionIndex].literal_pool.addLiteral(operand->literal);//safe operation
            uint32_t offsetFromPoolStart = sections[currentSectionIndex].literal_pool.getLiteralOffset(operand->literal);
            uint32_t disp = sections[currentSectionIndex].getSize() + offsetFromPoolStart - sections[currentSectionIndex].getCurrentPosition();
            if ((disp & 0xFFF) == disp)
                operandCommandToken->disp = disp;
            else {
                cout << "Error: Literal " << operand->literal << " too far away from instruction" << endl;
                exit(1);
            }

        } else if (operand->hasSymbol()) {
            if (this->symtab.findSymbolIndex(operand->symbol) != 0) {
                // check if symbol value is defined
                uint32_t symbolIndex = symtab.findSymbolIndex(operand->symbol);
                sections[currentSectionIndex].literal_pool.addSymbol(operand->symbol, symtab.symbols[symbolIndex].value);
                if (symtab.symbols[symtab.findSymbolIndex(operand->symbol)].section_index == 0) {
                    //add relocation
                }
                

            } else{
                cout << "Error: Symbol " << operand->symbol << " not defined" << endl;
            }
        } else {
            cout << "Error: Operand has no literal or symbol, can't be backpatched" << endl;
            exit(1);
        }
    }
}

void Assembler::resetSectionPositions() {
    this->currentSectionIndex = 0;
    for (auto &section : this->sections) {
        section.resetPosition();
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