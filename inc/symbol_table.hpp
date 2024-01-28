#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

struct Symbol{
    enum Type {NOTYPE,SECTION};
    enum Bind {LOCAL, GLOBAL};

    uint32_t value = 0;
    Type type = NOTYPE;
    Bind bind = LOCAL;
    string name;
    uint32_t section_index = 0;//Ndx
    bool globalDirective = false;
    bool externDirective = false;

    Symbol(uint32_t value, Type type, Bind bind, const string& name, uint32_t section_index) 
    : value(value), type(type), bind(bind), name(name), section_index(section_index) {}
};


class Symbol_table{
private:
    uint32_t insert_section_index = 1;
public:
    vector<Symbol> symbols;
    Symbol_table(): insert_section_index(1) {
        symbols.push_back(Symbol(0, Symbol::Type::NOTYPE, Symbol::Bind::LOCAL, string("example"), 0));
    }
    void addSection(const string& name){
        symbols.insert(symbols.begin() + insert_section_index, Symbol(0, Symbol::Type::SECTION, Symbol::Bind::LOCAL, name, insert_section_index));
        insert_section_index++;
    }

    uint32_t getSymbolIndex(const string& name){
        for (uint32_t i = 0; i < symbols.size(); i++) {
            if (symbols[i].name == name) {
                return i;
            }
        }
        return 0;
    }

    uint32_t findSymbolIndex(const string& name){
        for (uint32_t i = 0; i < symbols.size(); i++) {
            if (symbols[i].name == name) {
                return i;
            }
        }
        return 0;
    }
    
    void addSymbol(const Symbol &symbol){
        symbols.push_back(symbol);
    }

    bool symbolExists(const string& name) {
        for (auto& symbol : symbols) {
            if (symbol.name == name) {
                return true;
            }
        }
        return false;
    }

    void printSymbolTable() {
        cout << "Symbol Table:\n";
        int i = 0;
        //cout << symbols[0].name << endl;

        for (uint32_t i = 0; i < symbols.size(); i++) {
            cout << i << " "<< symbols[i].name << " " << symbols[i].value << " " << symbols[i].section_index << " " << ((symbols[i].bind==Symbol::Bind::GLOBAL)?"GLOBAL":"LOCAL") << " " << ((symbols[i].type==Symbol::Type::NOTYPE)?"NOTYPE":"SECTION")<< endl;
        }
    }
};