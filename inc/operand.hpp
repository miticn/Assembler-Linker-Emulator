#ifndef OPERAND_HPP
#define OPERAND_HPP

#include <string.h>
#include <iostream>
#include <cstdint>
using namespace std;

struct Operand{
    enum OperandType{
        LITERAL_VALUE,          // data $<literal> | jmp <literal> - value <literal>
        SYMBOL_VALUE,           // data $<symbol> | jmp <symbol>- value <symbol>
        MEMORY_LITERAL,         // <literal> - value from memory at address <literal>
        MEMORY_SYMBOL,          // <symbol> - value from memory at address <symbol>
        REGISTER_VALUE,         // %<reg> - value in register <reg>
        MEMORY_REGISTER,        // [%<reg>] - value from memory at address in register <reg>
        MEMORY_REGISTER_OFFSET_LITERAL,  // [%<reg> + <literal>] - value from memory at address <reg> + <literal>
        MEMORY_REGISTER_OFFSET_SYMBOL    // [%<reg> + <symbol>] - value from memory at address <reg> + <symbol>
    };
    OperandType type;
    uint32_t literal;
    string symbol;

    bool hasLiteral() const {
        return literal != 0;
    }

    bool hasSymbol() const {
        return symbol != "";
    }
};

struct OperandJump : public Operand{
    OperandJump(uint32_t literal){
        this->type = LITERAL_VALUE;
        this->literal = literal;
        this->symbol = "";
    }
    OperandJump(string symbol){
        this->type = SYMBOL_VALUE;
        this->literal = 0; 
        this->symbol = symbol;
    }
    OperandJump(){}
};

struct OperandData : public Operand{
    uint8_t reg;
    OperandData(OperandType type, uint32_t literal, string symbol, uint8_t reg) {
        this->type = type;
        this->literal = literal;
        this->symbol = symbol;
        this->reg = reg;
    }
};


#endif // OPERAND_HPP