#pragma once
#include "symbol_table.hpp"
#include "instruction.hpp"
#include "section.hpp"
#include "../misc/flex.hpp"
#include "../misc/bison.hpp"

class Assembler{
private:
    
    Symbol_table symtab;
    list<Section> sections;
    vector<uint8_t> objectFile;

    void appendUint32(uint32_t uint);

public:
    static list<Token*> tokenList;
    void assemble(char *inputFileName, char *outputFileName);
    void firstPass();
};