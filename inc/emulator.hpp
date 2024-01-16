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

    uint32_t pop();
    void push(uint32_t value);


    void executeFunctionCall(uint8_t mod, uint8_t regA, uint8_t regB, uint8_t regC, uint16_t disp);
    void executeJump(uint8_t mod, uint8_t regA, uint8_t regB, uint8_t regC, uint16_t disp);
    void executeAtomicRegisterSwap(uint8_t mod, uint8_t regA, uint8_t regB, uint8_t regC, uint16_t disp);
    void executeArithmeticOperation(uint8_t mod, uint8_t regA, uint8_t regB, uint8_t regC, uint16_t disp);
    void executeLogicOperation(uint8_t mod, uint8_t regA, uint8_t regB, uint8_t regC, uint16_t disp);
    void executeShiftOperation(uint8_t mod, uint8_t regA, uint8_t regB, uint8_t regC, uint16_t disp);
    void executeStore(uint8_t mod, uint8_t regA, uint8_t regB, uint8_t regC, uint16_t disp);
    void executeLoad(uint8_t mod, uint8_t regA, uint8_t regB, uint8_t regC, uint16_t disp);

public:
    bool isHalted() const { return halted;}
    uint32_t getGeneralRegister(uint8_t registerId);
    void setGeneralRegister(uint8_t registerId, uint32_t value);
    void executeInstuction(uint32_t instruction);
    Emulator();

    friend ostream& operator<<(std::ostream &os, Emulator &emulator);
    static string formatToHex(uint32_t value);
    void run();
    void loadHex();
};

int main(){
    Emulator myEmulator;
    myEmulator.loadHex();
    myEmulator.run();
    std::cout << myEmulator << std::endl;
    return 0;
}