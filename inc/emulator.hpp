#include <cstdint>
#include <iostream>
#include <iomanip>
#include "emulator_memory.hpp"

using namespace std;

class Emulator{
private:
    const static uint8_t NUMBER_OF_GENERAL_REGISTERS = 16;
    bool halted;
    uint32_t r[NUMBER_OF_GENERAL_REGISTERS];
    uint32_t &pc = r[15];
    uint32_t &sp = r[14];

    uint32_t status;
    uint32_t handler;
    uint32_t cause;
    EmulatorMemory memory;


public:
    bool isHalted() const { return halted;}
    uint32_t getGeneralRegister(uint8_t registerId);
    void setGeneralRegister(uint8_t registerId, uint32_t value);
    void executeInstuction(uint32_t instruction);
    Emulator();

    friend ostream& operator<<(std::ostream &os, Emulator &emulator);
    static string formatToHex(uint32_t value);
};

int main(){
    Emulator myEmulator;
    while(!myEmulator.isHalted()){
        myEmulator.executeInstuction(0);
    }
    std::cout << myEmulator << std::endl;
    return 0;
}