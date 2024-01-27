#pragma once
#include "symbol_table.hpp"
#include "instruction.hpp"
#include "section.hpp"
#include "../misc/flex.hpp"
#include "../misc/bison.hpp"
#include "literal_pool.hpp"
#include "relocation.hpp"
#include "token.hpp"
#include <list>

class Assembler{
private:
    
    Symbol_table symtab;
    vector<Section> sections;
    vector<Relocation> relocationTable;
    Section *currentSection = nullptr;
    uint32_t currentSectionIndex = 0;

public:
    static list<Token*> tokenList;
    void assemble(char *inputFileName, char *outputFileName);
    void firstPass();
    void secondPass();
    void printTokenList();
};