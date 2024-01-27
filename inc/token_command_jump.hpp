#pragma once
#include "token.hpp"
#include "token_command_generic.hpp"
struct JumpCommandToken : public OperandCommandToken{
    OperandJump operand;
    bool isBackpatchingNeeded() override {
        return true;
    }

    Operand* getOperandPtr() override {
        return &operand;
    }
};

struct JmpCommandToken : public JumpCommandToken{
    string getName() override {
        return "jmp";
    }
    JmpCommandToken(OperandJump operand){
        this->regA = 15;
        this->oc = 0b0011;
        this->mod = 0b0000;
        this->operand = operand;
    }
};

struct BeqCommandToken : public JumpCommandToken{
    string getName() override {
        return "beq";
    }
    BeqCommandToken(uint8_t reg1, uint8_t reg2, OperandJump operand){
        this->regA = 15;
        this->regB = reg1;
        this->regC = reg2;
        this->oc = 0b0011;
        this->mod = 0b0001;
        this->operand = operand;
    }
};

struct BneCommandToken : public JumpCommandToken{
    string getName() override {
        return "bne";
    }
    BneCommandToken(uint8_t reg1, uint8_t reg2, OperandJump operand){
        this->regA = 15;
        this->regB = reg1;
        this->regC = reg2;
        this->oc = 0b0011;
        this->mod = 0b0010;
        this->operand = operand;
    }
};

struct BgtCommandToken : public JumpCommandToken{
    string getName() override {
        return "bgt";
    }
    BgtCommandToken(uint8_t reg1, uint8_t reg2, OperandJump operand){
        this->regA = 15;
        this->regB = reg1;
        this->regC = reg2;
        this->oc = 0b0011;
        this->mod = 0b0011;
        this->operand = operand;
    }
};

struct CallCommandToken : public JumpCommandToken{
    string getName() override {
        return "call";
    }
    CallCommandToken(OperandJump operand){
        this->regA = 15;
        this->oc = 0b0010;
        this->mod = 0b0000;
        this->operand = operand;
    }
};