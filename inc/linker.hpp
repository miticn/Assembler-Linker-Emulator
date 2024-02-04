
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

        std::string header;
        inFile >> header;
        if (header != "__OBJFILE__") {
            cout << "Error: Invalid file format OBJFILE" << endl;
        }

        base.symtab.deserialize(inFile);

        inFile >> header;
        if (header != "__SECTIONS__") {
            cout << "Error: Invalid file format SECTIONS" << endl;
        }

        uint32_t num_sections = base.symtab.getNumSections();

        for (uint32_t i = 0; i < num_sections; i++) {
            Section section;
            section.deserialize(inFile);
            base.sections[section.getName()] = section;
        }

        inFile.close();

        return base;
    }
};

struct LinkerOptions {
    string output_filename;
    bool hex_flag;
    bool relocatable_flag;
    int num_place_options;
    PlaceOption place_options[MAX_OPTIONS];
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