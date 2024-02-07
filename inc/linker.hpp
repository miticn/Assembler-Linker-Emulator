
#include <iostream>
#include <vector>
#include <string>
#include "../inc/symbol_table.hpp"
#include "../inc/section.hpp"
#include <unordered_map>

#define MAX_OPTIONS 10

using namespace std;
struct PlaceOption {
    string section_name;
    unsigned long address;
    PlaceOption(const string &section_name, unsigned long address){
        this->section_name = section_name;
        this->address = address;
    }
};

struct BaseObject{
    Symbol_table symtab;
    unordered_map<string, Section> sections;
    void changeIndex(uint32_t oldIndex, uint32_t newIndex){
        for(auto &sym : symtab.symbols){
            if(sym.section_index == oldIndex){
                sym.section_index = newIndex;
            }
            if(sym.index == oldIndex){
                sym.index = newIndex;
            }
        }
        //change index in sections realocation table
        for(auto &section : sections){
            for(auto &rel : section.second.relocationTable){
                if(rel.symbolIndex == oldIndex){
                    rel.symbolIndex = newIndex;
                }
            }
        }
    }

    static BaseObject loadFile(string inputFileName){
        BaseObject base;
        //deserializes the file and returns a BaseObject
        std::ifstream inFile(inputFileName, std::ios::binary);
        if (!inFile.is_open()) {
            cout << "Error: Unable to open file " << inputFileName << endl;
            exit(1);
        }

        base.symtab.deserialize(inFile);
        base.symtab.printSymbolTable();

        uint32_t num_sections = base.symtab.getNumSections();

        for (uint32_t i = 0; i < num_sections; i++) {
            Section section;
            section.deserialize(inFile);
            base.sections[section.getName()] = section;
        }

        inFile.close();

        return base;
    }

    void saveFile(const BaseObject& base, const string& outputFileName) {

        std::ofstream outFile(outputFileName, std::ios::binary);
        if (!outFile.is_open()) {
            cout << "Error: Unable to create or open file " << outputFileName << endl;
            exit(1);
        }

        base.symtab.serialize(outFile);

        for (const auto& section_pair : base.sections) {
            const Section& section = section_pair.second;
            section.serialize(outFile);
        }

        outFile.close();
    }

};

struct LinkerOptions {
    string output_filename;
    bool hex_flag;
    bool relocatable_flag;
    vector<PlaceOption> place_options;
};

class Linker{
    public:
        Linker(vector<string> input_files, LinkerOptions options);
        void outputFile();
    private:
        vector<string> input_files;
        LinkerOptions options;
        BaseObject base;
        vector<BaseObject> objects;
        void mergeSecoundBaseObjectIntoFirst(BaseObject &base1, BaseObject &base2);
        

};