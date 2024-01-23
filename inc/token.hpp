#pragma once
#include <string>
#include <list>
using namespace std;



enum TokenType{LABEL, DIRECTIVE, COMMAND};

struct Token{
    virtual TokenType getType() = 0;
};

static list<Token*> tokenList;

struct DirectiveToken : public Token{
    TokenType getType() override {
        return TokenType::DIRECTIVE;
    }
};

struct CommandToken : public Token{
    TokenType getType() override {
        return TokenType::COMMAND;
    }
};

struct LabelToken : public Token{
    string name;
    string getName(){ return name; }
    TokenType getType() override {
        return TokenType::LABEL;
    }
    LabelToken(const string& name){ this->name = name; }
};