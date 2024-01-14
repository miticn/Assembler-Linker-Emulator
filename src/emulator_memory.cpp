#include "../inc/emulator_memory.hpp"

uint8_t EmulatorMemory::get8BitValueAtAddress(uint32_t address){
    if (memory.find(address) == memory.end())
        memory[address] = 0;
    return memory[address];
}

uint32_t EmulatorMemory::get32BitValueAtAddress(uint32_t address){

}

void EmulatorMemory::set8BitValueAtAddress(uint32_t address, uint8_t value){
    memory[address] = value;
}

void EmulatorMemory::set32BitValueAtAddress(uint32_t address, uint32_t value){

}

EmulatorMemory::EmulatorMemory(){

}