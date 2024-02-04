#pragma once
#include "symbol_table.hpp"
#include "instruction.hpp"
#include "section.hpp"
#include "../misc/flex.hpp"
#include "../misc/bison.hpp"
#include "literal_pool.hpp"
#include "relocation.hpp"
#include "token.hpp"
#include "token_directive.hpp"
#include "token_command_data.hpp"
#include "token_command_jump.hpp"
#include "token_command_generic.hpp"
#include <list>
#include <unordered_set>

class Assembler{
private:
    
    Symbol_table symtab;
    vector<Section> sections;
    uint32_t currentSectionIndex = 0;
    //unordered_set<string> relocatableSymbols;


    void processLabelTokenFirstPass(LabelToken* labelToken);
    void processExistingSymbolFirstPass(uint32_t symbolIndex, LabelToken* labelToken, uint32_t sectionIndex);
    void processDirectiveTokenFirstPass(DirectiveToken* directiveToken);
    void processSectionDirectiveTokenFirstPass(SectionDirectiveToken* sectionToken);
    void processExternDirectiveTokenFirstPass(ExternDirectiveToken* externToken);
    void processGlobalDirectiveTokenFirstPass(GlobalDirectiveToken* globalToken);
    void processEquDirectiveTokenFirstPass(EquDirectiveToken* equToken);
    void updateSymbolForDirective(uint32_t symbolIndex);
    void updateCurrentSectionPosition(Token* token);



    void makeLiteralPools();
    void resetSectionPositions();

    void processDirectiveTokenSecondPass(Token* token);
    void processSectionDirectiveSecondPass(Token* token);
    void processWordDirectiveSecondPass(Token* token);
    void processBackpatchingForWordSecondPass(WordDirectiveToken* wordToken);
    void processSkipDirectiveSecondPass(Token* token);
    void processAsciiDirectiveSecondPass(Token* token);
    void processCommandTokenSecondPass(Token* token);
    void processDataBackpatchingSecondPass(Token* token);


public:
    Assembler(){
        sections.push_back(Section("UND"));
    }
    static list<Token*> tokenList;
    void assemble(char *inputFileName, char *outputFileName);
    void firstPass();
    void secondPass();
    void printTokenList();
};