#pragma once
#include "token.hpp"
struct CommandToken : public Token{
    uint8_t oc = 0;
    uint8_t mod = 0;
    uint8_t regA = 0;
    uint8_t regB = 0;
    uint8_t regC = 0;
    uint16_t disp = 0;
    
    virtual string getName() = 0;
    virtual uint32_t getInstruction()  {
        Instruction instruction(oc, mod, regA, regB, regC, disp);
        return instruction.getUintFromInstruction();
    }
    TokenType getType() override {
        return TokenType::COMMAND;
    }
    uint32_t getSize() override {
        return 4;
    }
};

struct HaltCommandToken : public CommandToken{
    string getName() override {
        return "halt";
    }
};

struct IntCommandToken : public CommandToken{
    string getName() override {
        return "int";
    }
    IntCommandToken(){
        this->oc = 0b0001;
    }
};

struct RetCommandToken : public CommandToken{
    string getName() override {
        return "ret";
    }
    RetCommandToken(){
        this->disp = (int16_t)4;
        this->regB = 14;
        this->regA = 15;
        this->mod = 0b0011;
        this->oc = 0b1001;
    }
};

struct XchgCommandToken : public CommandToken{
    string getName() override {
        return "xchg";
    }
    XchgCommandToken(uint8_t reg1, uint8_t reg2){
        this->regB = reg1;
        this->regC = reg2;
        this->mod = 0b0000;
        this->oc = 0b0100;
    }
};

struct AddCommandToken : public CommandToken{
    string getName() override {
        return "add";
    }
    AddCommandToken(uint8_t reg1, uint8_t reg2){
        this->regA = reg2;
        this->regB = reg2;
        this->regC = reg1;
        this->mod = 0b0000;
        this->oc = 0b0101;
    }
};

struct SubCommandToken : public CommandToken{
    string getName() override {
        return "sub";
    }
    SubCommandToken(uint8_t reg1, uint8_t reg2){
        this->regA = reg2;
        this->regB = reg2;
        this->regC = reg1;
        this->mod = 0b0001;
        this->oc = 0b0101;
    }
};

struct MulCommandToken : public CommandToken{
    string getName() override {
        return "mul";
    }
    MulCommandToken(uint8_t reg1, uint8_t reg2){
        this->regA = reg2;
        this->regB = reg2;
        this->regC = reg1;
        this->mod = 0b0010;
        this->oc = 0b0101;
    }
};

struct DivCommandToken : public CommandToken{
    string getName() override {
        return "mul";
    }
    DivCommandToken(uint8_t reg1, uint8_t reg2){
        this->regA = reg2;
        this->regB = reg2;
        this->regC = reg1;
        this->mod = 0b0011;
        this->oc = 0b0101;
    }
};


struct NotCommandToken : public CommandToken{
    string getName() override {
        return "not";
    }
    NotCommandToken(uint8_t reg1){
        this->regB = reg1;
        this->mod = 0b0000;
        this->oc = 0b0110;
    }
};


struct AndCommandToken : public CommandToken{
    string getName() override {
        return "and";
    }
    AndCommandToken(uint8_t reg1, uint8_t reg2){
        this->regA = reg2;
        this->regB = reg2;
        this->regC = reg1;
        this->mod = 0b0001;
        this->oc = 0b0110;
    }
};

struct OrCommandToken : public CommandToken{
    string getName() override {
        return "or";
    }
    OrCommandToken(uint8_t reg1, uint8_t reg2){
        this->regA = reg2;
        this->regB = reg2;
        this->regC = reg1;
        this->mod = 0b0010;
        this->oc = 0b0110;
    }
};


struct XorCommandToken : public CommandToken{
    string getName() override {
        return "xor";
    }
    XorCommandToken(uint8_t reg1, uint8_t reg2){
        this->regA = reg2;
        this->regB = reg2;
        this->regC = reg1;
        this->mod = 0b0011;
        this->oc = 0b0110;
    }
};

struct ShlCommandToken : public CommandToken{
    string getName() override {
        return "shl";
    }
    ShlCommandToken(uint8_t reg1, uint8_t reg2){
        this->regA = reg2;
        this->regB = reg2;
        this->regC = reg1;
        this->mod = 0b0000;
        this->oc = 0b0111;
    }
};


struct ShrCommandToken : public CommandToken{
    string getName() override {
        return "shr";
    }
    ShrCommandToken(uint8_t reg1, uint8_t reg2){
        this->regA = reg2;
        this->regB = reg2;
        this->regC = reg1;
        this->mod = 0b0001;
        this->oc = 0b0111;
    }
};

struct CsrrdCommandToken : public CommandToken{
    string getName() override {
        return "csrrd";
    }
    CsrrdCommandToken(uint8_t reg1, uint8_t reg2){
        this->regA = reg2;
        this->regB = reg1;
        this->mod = 0b0000;
        this->oc = 0b1001;
    }
};

struct CsrwrCommandToken : public CommandToken{
    string getName() override {
        return "csrwr";
    }
    CsrwrCommandToken(uint8_t reg1, uint8_t reg2){
        this->regA = reg2;
        this->regB = reg1;
        this->mod = 0b0100;
        this->oc = 0b1001;
    }
};


struct PushCommandToken : public CommandToken{
    string getName() override {
        return "push";
    }
    PushCommandToken(uint8_t reg1){
        this->oc = 0b1000;
        this->mod = 0b0001;
        this->regC = reg1;
        this->disp = (int16_t)-4;
        this->regA = 14;
    }
};

struct PopCommandToken : public CommandToken{
    string getName() override {
        return "pop";
    }
    PopCommandToken(uint8_t reg1){
        this->oc = 0b1001;
        this->mod = 0b0011;
        this->regA = reg1;
        this->disp = (int16_t)4;
        this->regB = 14;
    }
};

struct PopStatusCommandToken : public CommandToken{
    string getName() override {
        return "pop_status";
    }
    PopStatusCommandToken(){
        this->oc = 0b1001;
        this->mod = 0b0111;
        this->regA = 0;
        this->disp = (int16_t)4;
        this->regB = 14;
    }
};