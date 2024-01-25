#ifndef OPERAND_HPP
#define OPERAND_HPP

#include <string.h>
#include <iostream>

struct OperandJump{
    enum OperandJumpType{
        LITERAL,
        SYMBOL
    };
    OperandJumpType type;
    int literal;
    char* symbol;
    OperandJump(int literal){
        this->type = LITERAL;
        this->literal = literal;
        this->symbol = NULL;
    }
    OperandJump(char* symbol){
        this->type = SYMBOL;
        this->literal = 0; 
        this->symbol = symbol;
    }
    OperandJump(){}
};

typedef struct OperandJump OperandJump;

struct OperandData{
    enum OperandDataType{
        LITERAL_VALUE,          // $<literal> - value <literal>
        SYMBOL_VALUE,           // $<symbol> - value <symbol>
        MEMORY_LITERAL,         // <literal> - value from memory at address <literal>
        MEMORY_SYMBOL,          // <symbol> - value from memory at address <symbol>
        REGISTER_VALUE,         // %<reg> - value in register <reg>
        MEMORY_REGISTER,        // [%<reg>] - value from memory at address in register <reg>
        MEMORY_REGISTER_OFFSET_LITERAL,  // [%<reg> + <literal>] - value from memory at address <reg> + <literal>
        MEMORY_REGISTER_OFFSET_SYMBOL    // [%<reg> + <symbol>] - value from memory at address <reg> + <symbol>
    };
    OperandDataType type;
    uint32_t literal;
    char* symbol;
    uint8_t reg;
    bool isBackpatchingNeeded;
    OperandData(OperandDataType type, uint32_t literal, char* symbol, uint8_t reg){
        this->type = type;
        this->literal = literal;
        this->symbol = symbol;
        this->reg = reg;
        if (type == REGISTER_VALUE || type == MEMORY_REGISTER || type == MEMORY_REGISTER_OFFSET_LITERAL){
            if(type == MEMORY_REGISTER_OFFSET_LITERAL && literal > 0xFF){
                std::cout << "Error: literal too large for memory offset" << endl;
                exit(1);
            }
            this->isBackpatchingNeeded = false;
        } else {
            this->isBackpatchingNeeded = true;
        }
    }
};


#endif // OPERAND_HPP