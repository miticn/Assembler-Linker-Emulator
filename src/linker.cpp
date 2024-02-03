#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "../inc/linker.hpp"

#define MAX_FILES 10
#define MAX_SECTION_NAME 20

using namespace std;
Linker::Linker(vector<string> input_files, LinkerOptions options){
    this->input_files = input_files;
    this->options = options;
}

void Linker::mergeSecoundBaseObjectIntoFirst(BaseObject &base1, BaseObject &base2){
    //find overlapping symbols
    for(auto &sym : base2.symtab.symbols){
        for(auto &sym2 : base1.symtab.symbols){
            if(sym.name == sym2.name){
                
            }
        }
    }
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
    
}


void print_usage() {
    cout << "Usage: linker [options] <input_files>..." << endl;
    cout << "Options:" << endl;
    cout << "-o <output_filename>" << endl;
    cout << "--place=<section_name>@<address>" << endl;
    cout << "-hex" << endl;
    cout << "-relocatable" << endl;
}

int main(int argc, char *argv[]) {
    vector<string> input_files;
    LinkerOptions options;

    // Initialize options
    options.hex_flag = false;
    options.relocatable_flag = false;
    options.num_place_options = 0;

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
        } else if (string(argv[i]).find("--place=") == 0) {
            string place_arg = string(argv[i]).substr(8);  // Skip "--place="
            size_t pos = place_arg.find('@');
            if (pos != string::npos) {
                string section_name = place_arg.substr(0, pos);
                string address_str = place_arg.substr(pos + 1);
                options.place_options[options.num_place_options].section_name = section_name;
                options.place_options[options.num_place_options].address = stoul(address_str, nullptr, 0);
                options.num_place_options++;
            } else {
                cerr << "Error: Invalid --place argument." << endl;
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
    return 0;
}
