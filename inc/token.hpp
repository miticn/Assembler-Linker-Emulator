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
    virtual bool isBackpatchingNeeded(){
        return false;
    }
};

struct LabelToken : public Token{
    string name;
    uint32_t getSize() override {
        return 0;
    }
    string getName(){ return "label"; }
    string getLabelName(){ return name; }
    TokenType getType() override {
        return TokenType::LABEL;
    }
    LabelToken(const string& name){ this->name = name; }
};