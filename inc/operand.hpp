#ifndef OPERAND_HPP
#define OPERAND_HPP

#include <string.h>

struct OperandJump{
    enum OperandJumpType{
        LITERAL,
        SYMBOL
    };
    OperandJumpType type;
};
struct OperandJumpLiteral : public OperandJump{
    int literal;
    OperandJumpLiteral(int literal){
        this->type = LITERAL;
        this->literal = literal;
    }
};
struct OperandJumpSymbol : public OperandJump{
    char* symbol;
    OperandJumpSymbol(char* symbol){
        this->type = SYMBOL;
        this->symbol = symbol;
    }
};

struct OperandData{

};



#endif // OPERAND_HPP