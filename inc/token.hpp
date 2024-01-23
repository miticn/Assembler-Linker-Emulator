#pragma once
#include <string>
#include <list>
#include <cstdint>
#include "instruction.hpp"
using namespace std;



enum TokenType{LABEL, DIRECTIVE, COMMAND};

struct Token{
    virtual TokenType getType() = 0;
};

struct LabelToken : public Token{
    string name;
    string getName(){ return name; }
    TokenType getType() override {
        return TokenType::LABEL;
    }
    LabelToken(const string& name){ this->name = name; }
};

struct DirectiveToken : public Token{
    TokenType getType() override {
        return TokenType::DIRECTIVE;
    }
};

struct GlobalDirectiveToken : public DirectiveToken{
    string symbolName;
    string getName(){ return "global"; }
    string getSymbolName(){ return symbolName; }
    GlobalDirectiveToken(const string &symbolName){ this->symbolName = symbolName; }
};

struct ExternDirectiveToken : public DirectiveToken{
    string symbolName;
    string getName(){ return "extern"; }
    string getSymbolName(){ return symbolName; }
    ExternDirectiveToken(const string &symbolName){ this->symbolName = symbolName; }
};

struct SectionDirectiveToken : public DirectiveToken{
    string sectionName;
    string getName(){ return "section"; }
    string getSectionName(){ return sectionName; }
    SectionDirectiveToken(const string &sectionName){ this->sectionName = sectionName; }
};

struct CommandToken : public Token{
    virtual string getName() = 0;
    virtual uint32_t getInstruction() = 0;
    TokenType getType() override {
        return TokenType::COMMAND;
    }
};

struct HaltCommandToken : public CommandToken{
    string getName() override {
        return "halt";
    }
    uint32_t getInstruction() override {
        return 0;
    }
};

struct IntCommandToken : public CommandToken{
    string getName() override {
        return "int";
    }
    uint32_t getInstruction() override {
        return 0x10000000;
    }
};

struct IretCommandToken : public CommandToken{

    string getName() override {
        return "iret";
    }
    uint32_t getInstruction() override {

    }
};

struct RetCommandToken : public CommandToken{
    uint16_t disp = (int16_t)4;
    uint8_t regB = 14;
    uint8_t mod = 0b0011;
    uint8_t oc = 0b1001;
    string getName() override {
        return "ret";
    }
    uint32_t getInstruction() override {
        Instruction instruction(oc, mod, 0, regB, 0, disp);
        return instruction.getUintFromInstruction();
    }
};

struct XchgCommandToken : public CommandToken{
    uint8_t regB;
    uint8_t regC;
    uint8_t mod = 0b0000;
    uint8_t oc = 0b0100;
    string getName() override {
        return "xchg";
    }
    uint32_t getInstruction() override {
        Instruction instruction(oc, mod, 0, regB, regC, 0);
        return instruction.getUintFromInstruction();
    }
    XchgCommandToken(uint8_t reg1, uint8_t reg2){
        this->regB = reg1;
        this->regC = reg2;
    }
};

struct AddCommandToken : public CommandToken{
    uint8_t regA;
    uint8_t regB;
    uint8_t regC;
    uint8_t mod = 0b0000;
    uint8_t oc = 0b0101;
    string getName() override {
        return "add";
    }
    uint32_t getInstruction() override {
        Instruction instruction(oc, mod, regA, regB, regC, 0);
        cout<<instruction.getUintFromInstruction()<<endl;
        return instruction.getUintFromInstruction();
    }
    AddCommandToken(uint8_t reg1, uint8_t reg2){
        this->regA = reg2;
        this->regB = reg2;
        this->regC = reg1;
    }
};

struct SubCommandToken : public CommandToken{
    uint8_t regA;
    uint8_t regB;
    uint8_t regC;
    uint8_t mod = 0b0001;
    uint8_t oc = 0b0101;
    string getName() override {
        return "sub";
    }
    uint32_t getInstruction() override {
        Instruction instruction(oc, mod, regA, regB, regC, 0);
        cout<<instruction.getUintFromInstruction()<<endl;
        return instruction.getUintFromInstruction();
    }
    SubCommandToken(uint8_t reg1, uint8_t reg2){
        this->regA = reg2;
        this->regB = reg2;
        this->regC = reg1;
    }
};

struct MulCommandToken : public CommandToken{
    uint8_t regA;
    uint8_t regB;
    uint8_t regC;
    uint8_t mod = 0b0010;
    uint8_t oc = 0b0101;
    string getName() override {
        return "mul";
    }
    uint32_t getInstruction() override {
        Instruction instruction(oc, mod, regA, regB, regC, 0);
        cout<<instruction.getUintFromInstruction()<<endl;
        return instruction.getUintFromInstruction();
    }
    MulCommandToken(uint8_t reg1, uint8_t reg2){
        this->regA = reg2;
        this->regB = reg2;
        this->regC = reg1;
    }
};

struct DivCommandToken : public CommandToken{
    uint8_t regA;
    uint8_t regB;
    uint8_t regC;
    uint8_t mod = 0b0011;
    uint8_t oc = 0b0101;
    string getName() override {
        return "mul";
    }
    uint32_t getInstruction() override {
        Instruction instruction(oc, mod, regA, regB, regC, 0);
        cout<<instruction.getUintFromInstruction()<<endl;
        return instruction.getUintFromInstruction();
    }
    DivCommandToken(uint8_t reg1, uint8_t reg2){
        this->regA = reg2;
        this->regB = reg2;
        this->regC = reg1;
    }
};


struct NotCommandToken : public CommandToken{
    uint8_t regB;
    uint8_t mod = 0b0000;
    uint8_t oc = 0b0110;
    string getName() override {
        return "not";
    }
    uint32_t getInstruction() override {
        Instruction instruction(oc, mod, 0, regB, 0, 0);
        return instruction.getUintFromInstruction();
    }
    NotCommandToken(uint8_t reg1){
        this->regB = reg1;
    }
};


struct AndCommandToken : public CommandToken{
    uint8_t regA;
    uint8_t regB;
    uint8_t regC;
    uint8_t mod = 0b0001;
    uint8_t oc = 0b0110;
    string getName() override {
        return "and";
    }
    uint32_t getInstruction() override {
        Instruction instruction(oc, mod, regA, regB, regC, 0);
        return instruction.getUintFromInstruction();
    }
    AndCommandToken(uint8_t reg1, uint8_t reg2){
        this->regA = reg2;
        this->regB = reg2;
        this->regC = reg1;
    }
};

struct OrCommandToken : public CommandToken{
    uint8_t regA;
    uint8_t regB;
    uint8_t regC;
    uint8_t mod = 0b0010;
    uint8_t oc = 0b0110;
    string getName() override {
        return "or";
    }
    uint32_t getInstruction() override {
        Instruction instruction(oc, mod, regA, regB, regC, 0);
        return instruction.getUintFromInstruction();
    }
    OrCommandToken(uint8_t reg1, uint8_t reg2){
        this->regA = reg2;
        this->regB = reg2;
        this->regC = reg1;
    }
};


struct XorCommandToken : public CommandToken{
    uint8_t regA;
    uint8_t regB;
    uint8_t regC;
    uint8_t mod = 0b0011;
    uint8_t oc = 0b0110;
    string getName() override {
        return "xor";
    }
    uint32_t getInstruction() override {
        Instruction instruction(oc, mod, regA, regB, regC, 0);
        return instruction.getUintFromInstruction();
    }
    XorCommandToken(uint8_t reg1, uint8_t reg2){
        this->regA = reg2;
        this->regB = reg2;
        this->regC = reg1;
    }
};

struct ShlCommandToken : public CommandToken{
    uint8_t regA;
    uint8_t regB;
    uint8_t regC;
    uint8_t mod = 0b0000;
    uint8_t oc = 0b0111;
    string getName() override {
        return "shl";
    }
    uint32_t getInstruction() override {
        Instruction instruction(oc, mod, regA, regB, regC, 0);
        return instruction.getUintFromInstruction();
    }
    ShlCommandToken(uint8_t reg1, uint8_t reg2){
        this->regA = reg2;
        this->regB = reg2;
        this->regC = reg1;
    }
};


struct ShrCommandToken : public CommandToken{
    uint8_t regA;
    uint8_t regB;
    uint8_t regC;
    uint8_t mod = 0b0001;
    uint8_t oc = 0b0111;
    string getName() override {
        return "shr";
    }
    uint32_t getInstruction() override {
        Instruction instruction(oc, mod, regA, regB, regC, 0);
        return instruction.getUintFromInstruction();
    }
    ShrCommandToken(uint8_t reg1, uint8_t reg2){
        this->regA = reg2;
        this->regB = reg2;
        this->regC = reg1;
    }
};

struct CsrrdCommandToken : public CommandToken{
    uint8_t regA;
    uint8_t regB;
    uint8_t mod = 0b0000;
    uint8_t oc = 0b1001;
    string getName() override {
        return "csrrd";
    }
    uint32_t getInstruction() override {
        Instruction instruction(oc, mod, regA, regB, 0, 0);
        return instruction.getUintFromInstruction();
    }
    CsrrdCommandToken(uint8_t reg1, uint8_t reg2){
        this->regA = reg2;
        this->regB = reg1;
    }
};

struct CsrwrCommandToken : public CommandToken{
    uint8_t regA;
    uint8_t regB;
    uint8_t mod = 0b0100;
    uint8_t oc = 0b1001;
    string getName() override {
        return "csrwr";
    }
    uint32_t getInstruction() override {
        Instruction instruction(oc, mod, regA, regB, 0, 0);
        return instruction.getUintFromInstruction();
    }
    CsrwrCommandToken(uint8_t reg1, uint8_t reg2){
        this->regA = reg2;
        this->regB = reg1;
    }
};