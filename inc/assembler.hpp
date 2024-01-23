#pragma once
#include "symbol_table.hpp"
#include "instruction.hpp"
#include "../misc/flex.hpp"
#include "../misc/bison.hpp"

class Assembler{
private:
    Symbol_table symtab;
    uint32_t locationCounter;

    vector<uint8_t> objectFile;

    void appendUint32(uint32_t uint);

public:

    void assemble(char *inputFileName, char *outputFileName);

    void directiveGlobal();
    void directiveExtern();
    void directiveSection();
    void directiveWord();
    void dircetiveSkip();
    void directiveASCII();
    void directiveEqu();
    void directiveEnd();

    //Always same output
    void commandHalt(){ this->appendUint32(Instruction(0,0,0,0,0,0).getUintFromInstruction()); }
    void commandInt();
    void commandIret();
    void commandRet();

    //Jump operands
    void commandCall();
    void commandJmp();
    void commandBeq();
    void commandBne();
    void commandBgt();

    //Registers as parameters
    void commandPush();
    void commandPop();
    void commandXchg();
    void commandAdd();
    void commandSub();
    void commandMul();
    void commandDiv();
    void commandNot();
    void commandAnd();
    void commandOr();
    void commandXor();
    void commandShl();
    void commandShr();

    //Data operands
    void commandLd();
    void commandSt();

    //Control and status regs
    void commandCsrrd();
    void commandCsrwr();
};