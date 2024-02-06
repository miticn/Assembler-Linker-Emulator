#include "../inc/linker_output.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>

uint8_t LinkerOutput::get8BitValueAtAddress(uint32_t address){
    if (memory.find(address) == memory.end())
        memory[address] = 0;
    return memory[address];
}

uint32_t LinkerOutput::get32BitValueAtAddress(uint32_t address){
    uint32_t returnValue = 0;
    for(int i = 3; i>0; i--){
        returnValue |= get8BitValueAtAddress(address+i);
        returnValue = returnValue << 8;
    }
    returnValue |= get8BitValueAtAddress(address);
    return returnValue;
}

void LinkerOutput::set8BitValueAtAddress(uint32_t address, uint8_t value){
    memory[address] = value;
}

void LinkerOutput::set32BitValueAtAddress(uint32_t address, uint32_t value){
    for(int i = 0; i<4; i++){
        uint8_t byteValue = value;
        set8BitValueAtAddress(address+i, byteValue);
        value = value >> 8;
    }
}

bool LinkerOutput::isAddressUsed(uint32_t address){
    return memory.find(address) != memory.end();
}

void LinkerOutput::copySectionData(uint32_t address, vector<uint8_t> &data){
    for(int i = 0; i<data.size(); i++){
        if (isAddressUsed(address+i)){
            cerr << "Error: Overlapping sections at address " << address+i << endl;
            exit(1);
        }
        set8BitValueAtAddress(address+i, data[i]);
    }
}

void LinkerOutput::saveFile(const string &filename) {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << " for writing." << std::endl;
        return;
    }

    auto it = memory.begin();
    while (it != memory.end()) {
        auto pair = *it;
        outputFile << std::hex << std::setfill('0') << std::setw(4) << pair.first << ": ";
        for (int i = 0; i < 8; ++i) {
            if (i != 0 && i % 8 == 0)
                outputFile << " ";
            if (memory.find(pair.first + i) != memory.end())
                outputFile << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(memory.at(pair.first + i)) << " ";
            else
                outputFile << "   ";
        }
        outputFile << std::endl;

        // Move iterator to the next 8th element
        int i = 0;
        while(i++ < 8 && it != memory.end())
            std::advance(it, 1);
    }

    outputFile.close();
    std::cout << "Memory contents saved to " << filename << " successfully." << std::endl;
}
