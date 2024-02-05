#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

#define ABS_SYMBOL_INDEX 0xFFFFFFFF
struct Symbol{
    enum Type {NOTYPE,SECTION};
    enum Bind {LOCAL, GLOBAL};
    enum Directive {NONED, GLOBALD, EXTERND};
    uint32_t index = 0;
    uint32_t value = 0;
    Type type = NOTYPE;
    Bind bind = LOCAL;
    string name;
    uint32_t section_index = 0;//Ndx
    Directive directive = NONED;

    Symbol(uint32_t value, Type type, Bind bind, const string& name, uint32_t section_index) 
    : value(value), type(type), bind(bind), name(name), section_index(section_index) {}
    Symbol(uint32_t index, uint32_t value, Type type, Bind bind, const string& name, uint32_t section_index) 
    : index(index), value(value), type(type), bind(bind), name(name), section_index(section_index) {}
};


class Symbol_table{
private:
    uint32_t insert_section_index = 1;
public:
    vector<Symbol> symbols;
    Symbol_table(): insert_section_index(1) {
        symbols = {Symbol(0, Symbol::Type::NOTYPE, Symbol::Bind::LOCAL, string("UND"), 0)};
    }
    void addSection(const string& name){
        symbols.insert(symbols.begin() + insert_section_index, Symbol(0, Symbol::Type::SECTION, Symbol::Bind::LOCAL, name, insert_section_index));
        insert_section_index++;
    }

    uint32_t findSymbolIndex(const string& name){
        for (uint32_t i = 0; i < symbols.size(); i++) {
            if (symbols[i].name == name) {
                return i;
            }
        }
        return 0;
    }

    uint32_t getNumSections() const {
        uint32_t numSections = 1;
        for (const Symbol& symbol : symbols) {
            if (symbol.type == Symbol::Type::SECTION) {
                ++numSections;
            }
        }
        return numSections;
    }
    
    void addSymbol(const Symbol &symbol){
        symbols.push_back(symbol);
    }

    void printSymbolTable() {
        cout << "Symbol Table:\n";
        int i = 0;
        //cout << symbols[0].name << endl;

        for (uint32_t i = 0; i < symbols.size(); i++) {
            cout << symbols[i].index << " "<< symbols[i].name << " " << symbols[i].value << " " << symbols[i].section_index << " " << ((symbols[i].bind==Symbol::Bind::GLOBAL)?"GLOBAL":"LOCAL") << " " << ((symbols[i].type==Symbol::Type::NOTYPE)?"NOTYPE":"SECTION")<< endl;
        }
    }

    void serialize(std::ostream& stream) const {
        // Serialize insert_section_index
        stream.write(reinterpret_cast<const char*>(&insert_section_index), sizeof(uint32_t));

        // Serialize the size of the symbol table
        uint32_t tableSize = symbols.size();
        stream.write(reinterpret_cast<const char*>(&tableSize), sizeof(uint32_t));

        // Serialize each symbol in the table
        for (const Symbol& symbol : symbols) {
            // Serialize symbol attributes
            stream.write(reinterpret_cast<const char*>(&symbol.index), sizeof(uint32_t));
            stream.write(reinterpret_cast<const char*>(&symbol.value), sizeof(uint32_t));
            stream.write(reinterpret_cast<const char*>(&symbol.type), sizeof(Symbol::Type));
            stream.write(reinterpret_cast<const char*>(&symbol.bind), sizeof(Symbol::Bind));

            // Serialize symbol name length and name
            uint32_t nameLength = symbol.name.size();
            stream.write(reinterpret_cast<const char*>(&nameLength), sizeof(uint32_t));
            stream.write(symbol.name.c_str(), nameLength);

            // Serialize section index
            stream.write(reinterpret_cast<const char*>(&symbol.section_index), sizeof(uint32_t));

            // Serialize flags
            stream.write(reinterpret_cast<const char*>(&symbol.directive), sizeof(Symbol::Directive));
        }
    }

    // Deserialization method
    void deserialize(std::istream& stream) {
        // Clear existing symbol table
        symbols.clear();

        // Deserialize insert_section_index
        stream.read(reinterpret_cast<char*>(&insert_section_index), sizeof(uint32_t));

        // Deserialize the size of the symbol table
        uint32_t tableSize;
        stream.read(reinterpret_cast<char*>(&tableSize), sizeof(uint32_t));

        // Deserialize each symbol in the table
        for (uint32_t i = 0; i < tableSize; ++i) {
            // Deserialize symbol 
            uint32_t index;
            uint32_t value;
            Symbol::Type type;
            Symbol::Bind bind;
            uint32_t nameLength;
            uint32_t sectionIndex;
            Symbol::Directive directive;

            stream.read(reinterpret_cast<char*>(&index), sizeof(uint32_t));
            stream.read(reinterpret_cast<char*>(&value), sizeof(uint32_t));
            stream.read(reinterpret_cast<char*>(&type), sizeof(Symbol::Type));
            stream.read(reinterpret_cast<char*>(&bind), sizeof(Symbol::Bind));

            // Deserialize symbol name length and name
            stream.read(reinterpret_cast<char*>(&nameLength), sizeof(uint32_t));
            char nameBuffer[nameLength + 1];
            stream.read(nameBuffer, nameLength);
            nameBuffer[nameLength] = '\0';
            std::string name(nameBuffer);

            // Deserialize section index
            stream.read(reinterpret_cast<char*>(&sectionIndex), sizeof(uint32_t));

            // Deserialize flags
            stream.read(reinterpret_cast<char*>(&directive), sizeof(Symbol::Directive));

            // Create and add the symbol to the symbol table
            symbols.emplace_back(index, value, type, bind, name, sectionIndex);
            symbols.back().directive = directive;
        }
    }

};