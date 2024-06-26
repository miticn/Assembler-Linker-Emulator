#pragma once
#include "token.hpp"
#include "tns.hpp"

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
    bool isBackpatchingNeeded() override {
        return backpatch;
    }
    uint32_t value;
    string symbol;
    bool backpatch;
    string getName(){ return "word"; }
    uint32_t getValue(){ return value; }
    string getSymbol(){ return symbol; }
    WordDirectiveToken(uint32_t value, string symbol = "", bool backpatch = false)
        : value(value), symbol(symbol), backpatch(backpatch) {}
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
    string str;
    string getName(){ return "ascii"; }
    AsciiDirectiveToken(string str): str(str) {}
    uint32_t getSize() override {
        return str.size();
    }
    string getAsciiString(){ return str; }
};

struct EquDirectiveToken : public DirectiveToken{
    string symbolName;
    uint32_t value;
    ExpressionPostfix expression;
    string getName(){ return "equ"; }
    string getSymbolName(){ return symbolName; }
    uint32_t getValue(){ return value; }
    EquDirectiveToken(const string &symbolName, ExpressionPostfix expression): symbolName(symbolName), expression(expression) {}
    EquDirectiveToken(const string &symbolName, uint32_t value): symbolName(symbolName), value(value) {}
};

struct EndDirectiveToken : public DirectiveToken{
    string getName(){ return "end"; }
};





