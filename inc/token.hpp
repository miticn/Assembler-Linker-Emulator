#pragma once
#include <string>
#include <list>
#include <cstdint>
#include "instruction.hpp"
#include "operand.hpp"
using namespace std;



enum TokenType{LABEL, DIRECTIVE, COMMAND};

struct Token{
    virtual uint32_t getSize() = 0;
    virtual TokenType getType() = 0;
    virtual string getName() = 0;
};

struct LabelToken : public Token{
    string name;
    uint32_t getSize() override {
        return 0;
    }
    string getName(){ return name; }
    TokenType getType() override {
        return TokenType::LABEL;
    }
    LabelToken(const string& name){ this->name = name; }
};

struct DirectiveToken : public Token{
    virtual uint32_t getSize() override {
        return 0;
    }
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

struct WordDirectiveToken : public DirectiveToken{
    uint32_t getSize() override {
        return 4;
    }
    uint32_t value;
    char *symbol;
    bool isBackpatchingNeeded;
    string getName(){ return "word"; }
    uint32_t getValue(){ return value; }
    WordDirectiveToken(uint32_t value, char * symbol = nullptr, bool isBackpatchingNeeded = false)
        : value(value), symbol(symbol), isBackpatchingNeeded(isBackpatchingNeeded) {}
};

struct SkipDirectiveToken : public DirectiveToken{
    uint32_t size;
    string getName(){ return "skip"; }
    SkipDirectiveToken(uint32_t size): size(size) {}
    uint32_t getSize() override {
        return size;
    }
};

struct AsciiDirectiveToken : public DirectiveToken{
    char *str;
    string getName(){ return "ascii"; }
    AsciiDirectiveToken(char *str): str(str) {}
    uint32_t getSize() override {
        return strlen(str);
    }
};

struct EquDirectiveToken : public DirectiveToken{
    string symbolName;
    uint32_t value;
    string getName(){ return "equ"; }
    string getSymbolName(){ return symbolName; }
    uint32_t getValue(){ return value; }
    EquDirectiveToken(const string &symbolName, uint32_t value): symbolName(symbolName), value(value) {}
};

struct EndDirectiveToken : public DirectiveToken{
    string getName(){ return "end"; }
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

struct JumpCommandToken : public CommandToken{
    OperandJump operand;
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


struct LdCommandToken : public CommandToken{
    OperandData operand;
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