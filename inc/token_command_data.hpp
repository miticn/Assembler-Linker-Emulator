#pragma once
#include "token.hpp"
#include "token_command_generic.hpp"

struct DataCommandToken : public OperandCommandToken{
    bool backpatching = false;
    OperandData operand;
    bool isBackpatchingNeeded() override {
        return backpatching;
    }
    Operand* getOperandPtr() override {
        return &operand;
    }
    DataCommandToken(OperandData operand) : operand(operand){}

};

struct LdCommandToken : public DataCommandToken{
    
    string getName() override {
        return "ld";
    }
    LdCommandToken(OperandData operand, uint8_t reg1) : DataCommandToken(operand){
        this->oc = 0b1001;
        this->regA = reg1;
        switch(operand.type){
            case OperandData::LITERAL_VALUE:
                this->regB = 15;
                this->mod = 0b0010;
                //backpatch disp to literal table
                this->backpatching = true;
                break;
            case OperandData::MEMORY_LITERAL:
                //this is basicly LITERAL_VALUE + MEMORY_REGISTER
                cout << "ERROR: LdCommandToken: MEMORY_LITERAL should be two instructions." << endl;
                exit(1);
                
                break;
            case OperandData::SYMBOL_VALUE:
                this->regB = 15;
                this->mod = 0b0010;
                //backpatch disp to symbol table
                this->backpatching = true;
                break;
            case OperandData::MEMORY_SYMBOL:
                //this is basicly SYMBOL_VALUE + MEMORY_REGISTER
                cout << "ERROR: LdCommandToken: MEMORY_SYMBOL should be two instructions." << endl;
                exit(1);
                break;
            case OperandData::REGISTER_VALUE:
                this->regB = operand.reg;
                this->mod = 0b0001;
                break;
            case OperandData::MEMORY_REGISTER:
                this->regB = operand.reg;
                this->mod = 0b0010;
                break;
            case OperandData::MEMORY_REGISTER_OFFSET_LITERAL:
                if(operand.literal > 0xFFF){
                    std::cout << "Error: literal too large for memory offset" << endl;
                    exit(1);
                }
                this->regB = operand.reg;
                this->mod = 0b0010;
                this->disp = operand.literal;
                break;
            case OperandData::MEMORY_REGISTER_OFFSET_SYMBOL:
                this->regB = operand.reg;
                this->mod = 0b0010;
                //backpatch disp
                this->backpatching = true;
                break;
        }
        
    }
};



struct StCommandToken : public DataCommandToken{
    string getName() override {
        return "st";
    }
    StCommandToken(uint8_t reg1, OperandData operand) : DataCommandToken(operand){
        this->oc = 0b1000;
        this->regC = reg1;
        switch(operand.type){
            case OperandData::LITERAL_VALUE:
                //We can't store register in literal
                cout<<"ERROR: StCommandToken: can't change literal value."<<endl;
                break;
            case OperandData::SYMBOL_VALUE:
                //We can't store register in symbol
                cout<<"ERROR: StCommandToken: can't change symbol value."<<endl;
                break;
            case OperandData::MEMORY_LITERAL:
                this->regA = 15;
                this->mod = 0b0010;
                //backpatch disp to literal table
                this->backpatching = true;
                break;
            case OperandData::MEMORY_SYMBOL:
                this->regA = 15;
                this->mod = 0b0010;
                //backpatch disp to symbol table
                this->backpatching = true;
                break;
            case OperandData::REGISTER_VALUE:
                this->oc = 0b1001;
                this->mod = 0b0001;
                this->regA = operand.reg;
                this->regB = reg1;
                this->regC = 0;
                break;
            case OperandData::MEMORY_REGISTER:
                this->mod = 0b0000;
                this->regA = operand.reg;
                break;
            case OperandData::MEMORY_REGISTER_OFFSET_LITERAL:
                this->mod = 0b0000;
                this->regA = operand.reg;
                this->disp = operand.literal;
                break;
            case OperandData::MEMORY_REGISTER_OFFSET_SYMBOL:
                this->mod = 0b0000;
                this->regA = operand.reg;
                //backpatch disp
                this->backpatching = true;
                break;
        }
        
    }
};