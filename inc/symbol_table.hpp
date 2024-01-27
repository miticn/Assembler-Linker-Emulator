#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

struct Symbol{
    enum Type {NOTYPE,SECTION};
    enum Bind {LOCAL, GLOBAL};

    uint32_t value;
    Type type;
    Bind bind;
    string name;
    uint32_t section_index;//Ndx
    bool globalDirective;
    bool externDirective;

    Symbol(uint32_t value, Type type, Bind bind, const string& name, uint32_t section_index) : value(value), type(type), bind(bind), name(name), section_index(section_index) {}
};


class Symbol_table{
private:
    vector<Symbol> symbols;
    uint32_t insert_section_index;
public:
    Symbol_table(): insert_section_index(1) {symbols.push_back(Symbol(0, Symbol::Type::NOTYPE, Symbol::Bind::LOCAL, "UND", 0));}
    Symbol* addSection(const string& name){
        symbols.insert(symbols.begin() + insert_section_index, Symbol(0, Symbol::Type::SECTION, Symbol::Bind::LOCAL, name, insert_section_index));
        insert_section_index++;
        return &symbols[insert_section_index - 1];
    }
    void addSymbol(const string& name){
        symbols.push_back(Symbol(0, Symbol::Type::SECTION, Symbol::Bind::LOCAL, name, insert_section_index));
    }

    void addSymbol(const Symbol &symbol){
        symbols.push_back(symbol);
    }

    Symbol* findSymbol(const string& name) {
        for (auto& symbol : symbols) {
            if (symbol.name == name) {
                return &symbol;
            }
        }
        return nullptr;
    }

    void printSymbolTable() {
        cout << "Symbol Table:\n";
        for (const auto& symbol : symbols) {
            cout << "Name: " << symbol.name << ", Type: " << symbol.type << ", Bind: " << symbol.bind << ", Value: " << symbol.value << "\n";
        }
    }
};