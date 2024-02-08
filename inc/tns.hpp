#pragma once
#include <string>
#include <vector>

#include "symbol_table.hpp"

using namespace std;

struct Element{
    enum Type{
        SYMBOL,
        CONSTANT,
        OPERATOR
    };

    Type type;
    char operatorr;
    string symbol;
    int constant;
    Element(string symbol){
        this->type = Type::SYMBOL;
        this->symbol = symbol;
        this->constant = 0;
        this->operatorr = ' ';
    }
    Element(int constant){
        this->type = Type::CONSTANT;
        this->constant = constant;
        this->symbol = "";
        this->operatorr = ' ';
    }
    Element(char operatorr){
        this->type = Type::OPERATOR;
        this->operatorr = operatorr;
        this->symbol = "";
        this->constant = 0;
    }
};

class ExpressionOperand{
    vector<int32_t> sections;

public:
    ExpressionOperand(uint32_t numberOfSections){
        sections.resize(numberOfSections+1);
        for(uint32_t i = 0; i < sections.size(); i++){
            sections[i] = 0;
        }
    }
    ExpressionOperand operator+(const ExpressionOperand &rhs){
        ExpressionOperand result(sections.size()-1);
        for(uint32_t i = 0; i < sections.size(); i++){
            result.sections[i] = sections[i] + rhs.sections[i];
        }
        return result;
    }
    ExpressionOperand operator-(const ExpressionOperand &rhs){
        ExpressionOperand result(sections.size()-1);
        for(uint32_t i = 0; i < sections.size(); i++){
            result.sections[i] = sections[i] - rhs.sections[i];
        }
        return result;
    }
    void incSection(uint32_t index){
        sections[index]++;
    }

    void addValue(int32_t value){
        sections[sections.size()-1] += value;
    }

    bool isValid(){
        bool first = true;
        for(uint32_t i = 0; i < sections.size()-1; i++){
            if(sections[i] != 0 && !first){
                return false;
            }
            if(sections[i] != 0){
                first = false;
            }
        }
        return true;
    }

    int32_t getValue(){
        return sections[sections.size()-1];
    }
    uint32_t getSection(){
        for(uint32_t i = 0; i < sections.size()-1; i++){
            if(sections[i] != 0){
                return i;
            }
        }
        return ABS_SYMBOL_INDEX;
    }
};

class ExpressionPostfix{
    vector<Element> expression;
    
public:
    bool areAllSymbolsKnown(Symbol_table &st){
        for(auto e : expression){
            if(e.type == Element::Type::SYMBOL){
                uint32_t index = st.findSymbolIndex(e.symbol);
                if(index == 0|| st.symbols[index].section_index == 0){
                    return false;
                } else if (st.symbols[index].directive == Symbol::Directive::EXTERND){
                    cout << "Error: Symbol not known at assembly" << endl;
                    exit(1);
                }
            }
        }
        return true;
    }

    void addElement(Element e){
        expression.push_back(e);
    }

    Symbol generateSymbol(const string &name, Symbol_table &st){
        vector<ExpressionOperand> stack;
        for(auto e : expression){
            if(e.type == Element::Type::SYMBOL){
                ExpressionOperand s = ExpressionOperand(st.getNumSections());
                uint32_t index = st.findSymbolIndex(e.symbol);
                uint32_t section_index = st.symbols[index].section_index;
                if(section_index != ABS_SYMBOL_INDEX){
                    s.incSection(section_index);
                }
                s.addValue(st.symbols[index].value);
                stack.push_back(s);
            } else if(e.type == Element::Type::OPERATOR){
                ExpressionOperand s2 = stack.back();
                stack.pop_back();
                ExpressionOperand s1 = stack.back();
                stack.pop_back();
                if(e.operatorr == '+'){
                    stack.push_back(s1 + s2);
                } else if(e.operatorr == '-'){
                    stack.push_back(s1 - s2);
                }
            } else if(e.type == Element::Type::CONSTANT){
                ExpressionOperand s = ExpressionOperand(st.getNumSections());
                s.addValue(e.constant);
                stack.push_back(s);
            }
        }
        if(stack.size() != 1 || !stack[0].isValid()){
            cout << "Error: Invalid expression of symbol " << name << endl;
            exit(1);
        }
        return Symbol(stack[0].getValue(), Symbol::Type::NOTYPE, Symbol::Bind::LOCAL, name, stack[0].getSection());
    }
};


struct TNSEntry{
    string symbol_name;
    ExpressionPostfix expr;
    TNSEntry(string symbol_name, ExpressionPostfix expr){
        this->symbol_name = symbol_name;
        this->expr = expr;
    }
};