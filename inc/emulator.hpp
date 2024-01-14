#include <cstdint>
#include "emulator_memory.hpp"

class Emulator{
private:
    bool halted;
    uint32_t r[16];
    uint32_t status;
    uint32_t handler;
    uint32_t cause;
    EmulatorMemory memory;

public:
    bool isHalted() const { return halted;}
    uint32_t getGeneralRegister(uint8_t registerId);
    void setGeneralRegister(uint8_t registerId, uint32_t value);

};