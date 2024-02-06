#include "../inc/emulator_memory.hpp"
#include <iostream>

uint8_t EmulatorMemory::get8BitValueAtAddress(uint32_t address){
    if(address >= term_out_address && address < term_out_address + 4){
        return 0;
    }
    if(address > term_in_address && address < term_in_address + 4){
        return 0;
    }
    if(address == term_in_address){
        return term_in_reg;
    }
    if (memory.find(address) == memory.end())
        memory[address] = 0;
    return memory[address];
}

uint32_t EmulatorMemory::get32BitValueAtAddress(uint32_t address){
    uint32_t returnValue = 0;
    for(int i = 3; i>0; i--){
        uint8_t byteValue = get8BitValueAtAddress(address+i);
        returnValue |= byteValue;
        returnValue = returnValue << 8;
    }
    returnValue |= get8BitValueAtAddress(address);
    return returnValue;
}

void EmulatorMemory::set8BitValueAtAddress(uint32_t address, uint8_t value){
    if(address == term_out_address){
        printf("%c", value);
        fflush(stdout);
        return;
    }
    memory[address] = value;
}

void EmulatorMemory::set32BitValueAtAddress(uint32_t address, uint32_t value){
    for(int i = 0; i<4; i++){
        uint8_t byteValue = value;
        set8BitValueAtAddress(address+i, byteValue);
        value = value >> 8;
    }
}

EmulatorMemory::EmulatorMemory(){
    // std::cout << "max_size = " << memory.max_size() << std::endl;
}