#pragma once
#include "token.hpp"
#include "token_command_generic.hpp"

struct LdCommandToken : public CommandToken{
    OperandData operand;
    bool isBackpatchingNeeded() override {
        return operand.isBackpatchingNeeded;
    }
    string getName() override {
        return "ld";
    }
    LdCommandToken(OperandData operand, uint8_t reg1) : operand(operand){
        this->oc = 0b1001;
        this->regA = reg1;
        switch(operand.type){
            case OperandData::LITERAL_VALUE:
                if(operand.literal > 0xFF){
                    this->regB = 15;
                    this->mod = 0b0010;
                    //backpatch disp to literal table
                }
                else{
                    this->disp = operand.literal;
                    this->mod = 0b0001;
                    this->operand.isBackpatchingNeeded = false;
                }
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
                this->regB = operand.reg;
                this->mod = 0b0010;
                this->disp = operand.literal;
                break;
            case OperandData::MEMORY_REGISTER_OFFSET_SYMBOL:
                this->regB = operand.reg;
                this->mod = 0b0010;
                //backpatch disp
                break;
        }
        
    }
};



struct StCommandToken : public CommandToken{
    OperandData operand;
    string getName() override {
        return "st";
    }
    bool isBackpatchingNeeded() override {
        return operand.isBackpatchingNeeded;
    }
    StCommandToken(uint8_t reg1, OperandData operand) : operand(operand){
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
                break;
            case OperandData::MEMORY_SYMBOL:
                this->regA = 15;
                this->mod = 0b0010;
                //backpatch disp to symbol table
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
                break;
        }
        
    }
};