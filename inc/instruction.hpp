#pragma once
#include <cstdint>
class Instruction{
    uint16_t disp;
    uint8_t regC;
    uint8_t regB;
    uint8_t regA;
    uint8_t mod;
    uint8_t oc;
public:
    Instruction(uint8_t oc, uint8_t mod, uint8_t regA, uint8_t regB, uint8_t regC, uint16_t disp)
    : oc(oc), mod(mod), regA(regA), regB(regB), regC(regC), disp(disp) {}

    
    uint32_t getUintFromInstruction(){
        uint32_t result =  (disp & 0xfff) |
                ((uint32_t)(regC & 0xf) << 12) |
                ((uint32_t)(regB & 0xf) << 16) |
                ((uint32_t)(regA & 0xf) << 20) |
                ((uint32_t)(mod & 0xf) << 24) |
                ((uint32_t)(oc & 0xf) << 28);
        return (result & 0xff) << 24 | (result & 0xff00) << 8 | (result & 0xff0000) >> 8 | (result & 0xff000000) >> 24;
    }
};