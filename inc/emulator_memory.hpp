#pragma once
#include <cstdint>
#include <map>
#include <fstream>
#include <sstream>

#define TERM_OUT_ADDRESS 0xFFFFFF00;
#define TERM_IN_ADDRESS 0xFFFFFF04;

class EmulatorMemory{
private:
    //This is only ok for programs that need small amount of memmory
    std::map<uint32_t, uint8_t> memory;
    uint32_t term_out_address = TERM_OUT_ADDRESS;
    uint32_t term_in_address = TERM_IN_ADDRESS;
    volatile uint8_t term_in_reg;
    friend class Terminal;
public:
    uint8_t get8BitValueAtAddress(uint32_t address);
    uint32_t get32BitValueAtAddress(uint32_t address);
    void set8BitValueAtAddress(uint32_t address, uint8_t value);
    void set32BitValueAtAddress(uint32_t address, uint32_t value);
    EmulatorMemory();
};