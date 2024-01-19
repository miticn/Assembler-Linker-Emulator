#include <cstdint>
#include <string>
#include <vector>
using namespace std;

struct Symbol{
    enum Type {NOTYPE,SECTION};
    enum Bind {LOCAL, GLOBAL};

    uint32_t value;
    //uint32_t size;
    Type type;
    Bind bind;
    string name;
    uint32_t section_index;//Ndx

    Symbol(uint32_t value, Type type, Bind bind, const string& name, uint32_t section_index) : value(value), type(type), bind(bind), name(name), section_index(section_index) {}
};


class Symbol_table{
private:
    vector<Symbol> symbols;
    uint32_t insert_section_index;
public:
    Symbol_table(): insert_section_index(0) {}
    void addSection(const string& name){
        symbols.insert(symbols.begin() + insert_section_index, Symbol(0, Symbol::Type::SECTION, Symbol::Bind::LOCAL, name, insert_section_index));
        insert_section_index++;
    }
    void addSymbol(const string& name){
        symbols.push_back(Symbol(0, Symbol::Type::SECTION, Symbol::Bind::LOCAL, name, insert_section_index));
    }
};