#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "../inc/linker.hpp"
#include "../inc/linker_output.hpp"
#include <algorithm>

#define MAX_FILES 10
#define MAX_SECTION_NAME 20

using namespace std;
Linker::Linker(vector<string> input_files, LinkerOptions options){
    this->input_files = input_files;
    this->options = options;
}

void Linker::mergeSecoundBaseObjectIntoFirst(BaseObject &base1, BaseObject &base2){
    base2.symtab.symbols.erase(base2.symtab.symbols.begin());
    uint32_t offsetIndex = base1.symtab.symbols.size();
    for(auto &sym : base2.symtab.symbols){
        base2.changeIndex(sym.index, sym.index + offsetIndex);
    }

    //find overlapping sections
    for(uint32_t i = 0; i < base2.symtab.symbols.size(); i++){
        for(auto &sym : base1.symtab.symbols){
            auto &sym2 = base2.symtab.symbols[i];
            if(sym.name == sym2.name){
                //sections
                if(sym.type != sym2.type){
                    cerr << "Error: Symbol " << sym.name << " has conflicting types." << endl;
                    exit(1);
                } else if(sym.type == Symbol::Type::SECTION){
                    uint32_t oldIndex = sym2.section_index;
                    uint32_t newIndex = sym.section_index;
                    base2.changeIndex(oldIndex, newIndex);
                    base1.changeIndex(oldIndex, newIndex);
                    //merge sections
                    uint32_t offset = base1.sections[sym.name].data.size();
                    //everysymbol value that is dependent on the section needs to add the offset
                    for(auto &sym2 : base2.symtab.symbols){
                        if(sym2.section_index == sym.index){
                            sym2.value += offset;
                        }
                    }
                    base1.sections[sym.name].data.insert(base1.sections[sym.name].data.end(), base2.sections[sym2.name].data.begin(), base2.sections[sym2.name].data.end());
                    //merge relocation table
                    for(auto &rel : base2.sections[sym2.name].relocationTable){
                        rel.offset += offset;
                        base1.sections[sym.name].relocationTable.push_back(rel);
                    }
                    //remove section from base2
                    base2.sections.erase(sym2.name);
                    base2.symtab.symbols.erase(base2.symtab.symbols.begin() + i);
                    i--;
                    break;
                } else if(!((sym.directive == Symbol::Directive::EXTERND && sym2.directive == Symbol::Directive::GLOBALD
                || (sym.directive == Symbol::Directive::GLOBALD && sym2.directive == Symbol::Directive::EXTERND)))){
                    cerr << "Error: Symbol " << sym.name << " has conflicting directives." << endl;
                    exit(1);
                }
                
            }
        }
    }
    //find overlapping symbols
    for(uint32_t i = 0; i < base2.symtab.symbols.size(); i++){
        for(auto &sym : base1.symtab.symbols){
            auto &sym2 = base2.symtab.symbols[i];
            if((sym.name == sym2.name) 
            && (sym.directive == Symbol::Directive::EXTERND && sym2.directive == Symbol::Directive::GLOBALD
            || (sym.directive == Symbol::Directive::GLOBALD && sym2.directive == Symbol::Directive::EXTERND))){
                uint32_t oldIndex = sym2.index;
                uint32_t newIndex = sym.index;
                base2.changeIndex(oldIndex, newIndex);
                base1.changeIndex(oldIndex, newIndex);
                if(sym.directive == Symbol::Directive::EXTERND){
                    sym = sym2;
                }
                //remove symbol from base2
                base2.symtab.symbols.erase(base2.symtab.symbols.begin() + i);
                i--;
                break;
            }
        }
    }


    cout << "Merged base1:" << endl;
    base1.symtab.printSymbolTable();
    //merge the rest of the symbols
    for(auto &sym : base2.symtab.symbols){
        base1.symtab.symbols.push_back(sym);
    }

    cout << "Merged base2:" << endl;
    base1.symtab.printSymbolTable();
    //merge the rest of the sections
    for(auto &sec : base2.sections){
        base1.sections[sec.first] = sec.second;
    }
    //sort the symbols
    sort(base1.symtab.symbols.begin(), base1.symtab.symbols.end(), [](Symbol &a, Symbol &b){
        return a.index < b.index;
    });

    for(uint32_t i = 0; i < base1.symtab.symbols.size(); i++){
        if(base1.symtab.symbols[i].index != i){
            base1.changeIndex(base1.symtab.symbols[i].index, i);
        }
    }
    cout << "Merged basee:" << endl;
    base1.symtab.printSymbolTable();
}

void Linker::outputFile(){
    //load first file into base
    base = BaseObject::loadFile(input_files[0]);
    //load the rest of the files into objects
    for (int i = 1; i < input_files.size(); i++){
        objects.push_back(BaseObject::loadFile(input_files[i]));
    }
    //merge the objects into the base
    for(BaseObject &obj : objects){
        mergeSecoundBaseObjectIntoFirst(base,obj);
    }

    if(options.relocatable_flag){
        base.saveFile(this->base, options.output_filename);
        return;
    }

    base.symtab.printSymbolTable();
    LinkerOutput linkerOutput;
    uint32_t maxAddress = 0;
    if (options.hex_flag){
        for(PlaceOption placeOption: options.place_options){
            uint32_t section_index = 0;
            for(auto &symbol : base.symtab.symbols){
                if(symbol.name == placeOption.section_name) {
                    section_index = symbol.index;
                }
            }
            if (section_index == 0){
                cerr << "Error: Section " << placeOption.section_name << " not found." << endl;
                exit(1);
            }
            if(placeOption.address + base.sections[placeOption.section_name].getSize() > maxAddress)
                maxAddress = placeOption.address + base.sections[placeOption.section_name].getSize();
            
            linkerOutput.copySectionData(placeOption.address, base.sections[placeOption.section_name].data);
            for(auto &symbol : base.symtab.symbols){
                if(symbol.section_index == section_index) {
                    symbol.value += placeOption.address;
                }
            }
        }

        for(auto &symbol : base.symtab.symbols){
            if(symbol.type == Symbol::Type::SECTION && symbol.value == 0){
                linkerOutput.copySectionData(maxAddress, base.sections[symbol.name].data);
                for(auto &symbol_child : base.symtab.symbols){
                    if(symbol_child.section_index == symbol.index) {
                        symbol_child.value += maxAddress;
                    }
                }
                maxAddress += base.sections[symbol.name].getSize();
            }
        }
        

        //resolve relocations
        for(auto &section : base.sections){
            for(auto &relocation : section.second.relocationTable){
                uint32_t value = base.symtab.symbols[relocation.symbolIndex].value;
                uint32_t index_section = base.symtab.findSymbolIndex(section.first);
                uint32_t relocation_address = base.symtab.symbols[index_section].value+relocation.offset;
                value += linkerOutput.get32BitValueAtAddress(relocation_address);
                linkerOutput.set32BitValueAtAddress(relocation_address, value);
            }
        }


        linkerOutput.saveFile(options.output_filename);

    }
}


void print_usage() {
    cout << "Usage: linker [options] <input_files>..." << endl;
    cout << "Options:" << endl;
    cout << "-o <output_filename>" << endl;
    cout << "-place=<section_name>@<address>" << endl;
    cout << "-hex" << endl;
    cout << "-relocatable" << endl;
}

int main(int argc, char *argv[]) {
    vector<string> input_files;
    LinkerOptions options;

    // Initialize options
    options.hex_flag = false;
    options.relocatable_flag = false;

    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "-o") {
            if (i + 1 < argc) {
                options.output_filename = argv[i + 1];
                i++;  // Skip the next argument
            } else {
                cerr << "Error: Output filename not provided." << endl;
                print_usage();
                return 1;
            }
        } else if (string(argv[i]).find("-place=") == 0) {
            string place_arg = string(argv[i]).substr(7);  // Skip "--place="
            size_t pos = place_arg.find('@');
            if (pos != string::npos) {
                string section_name = place_arg.substr(0, pos);
                string address_str = place_arg.substr(pos + 1);
                options.place_options.push_back(PlaceOption(section_name,stoul(address_str, nullptr, 0)));
            } else {
                cerr << "Error: Invalid -place argument." << endl;
                print_usage();
                return 1;
            }
        } else if (string(argv[i]) == "-hex") {
            options.hex_flag = true;
        } else if (string(argv[i]) == "-relocatable") {
            options.relocatable_flag = true;
        } else {
            if (input_files.size() < MAX_FILES) {
                input_files.push_back({argv[i]});
            } else {
                cerr << "Error: Too many input files." << endl;
                return 1;
            }
        }
    }

    // Check for required options
    if (!((options.hex_flag || options.relocatable_flag) && !(options.hex_flag && options.relocatable_flag))) {
        cerr << "Error: Exactly one of -hex or -relocatable must be specified." << endl;
        print_usage();
        return 1;
    }
    Linker linker(input_files, options);
    linker.outputFile();
    return 0;
}
