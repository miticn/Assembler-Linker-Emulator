#pragma once
#include <cstdint>
#include <map>
#include <fstream>
#include <sstream>

class EmulatorMemory{
private:
    //This is only ok for programs that need small amount of memmory
    std::map<uint32_t, uint8_t> memory;
public:
    uint8_t get8BitValueAtAddress(uint32_t address);
    uint32_t get32BitValueAtAddress(uint32_t address);
    void set8BitValueAtAddress(uint32_t address, uint8_t value);
    void set32BitValueAtAddress(uint32_t address, uint32_t value);
    EmulatorMemory();
};