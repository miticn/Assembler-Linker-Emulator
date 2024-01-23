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
    uint8_t oc = 0;
    uint8_t mod = 0;
    uint8_t regA = 0;
    uint8_t regB = 0;
    uint8_t regC = 0;
    uint16_t disp = 0;
    
    virtual string getName() = 0;
    virtual uint32_t getInstruction()  {
        Instruction instruction(oc, mod, regA, regB, regB, disp);
        return instruction.getUintFromInstruction();
    }
    TokenType getType() override {
        return TokenType::COMMAND;
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