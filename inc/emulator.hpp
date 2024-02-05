#pragma once
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <termios.h>
#include <chrono>
#include "emulator_memory.hpp"

using namespace std;

class Emulator{
private:
    const static uint8_t NUMBER_OF_GENERAL_REGISTERS = 16;
    bool halted;
    uint32_t r[NUMBER_OF_GENERAL_REGISTERS];
    uint32_t csr[3];
    uint32_t &pc = r[15];
    uint32_t &sp = r[14];

    uint32_t &status = csr[0];
    uint32_t &handler = csr[1];
    uint32_t &cause = csr[2];
    EmulatorMemory memory;

    const static uint32_t term_out_address = 0xFFFFFF00;
    const static uint32_t term_in_address = 0xFFFFFF04;
    const static uint32_t tim_cfg_address = 0xFFFFFF10;

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

    bool timerInteruptEnabled(){return (status & 0b1)==0;}
    bool terminalInteruptEnabled(){return (status & 0b10)==0;}
    bool globalInteruptEnabled(){return (status & 0b100)==0;}

public:
    bool isHalted() const { return halted;}
    uint32_t getGR(uint8_t registerId);
    void setGR(uint8_t registerId, uint32_t value);
    void executeInstuction(uint32_t instruction);
    Emulator();

    friend ostream& operator<<(std::ostream &os, Emulator &emulator);
    static string formatToHex(uint32_t value);
    void run();
    void loadHex(string inputFileName);
};
