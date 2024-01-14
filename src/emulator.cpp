#include "../inc/emulator.hpp"

Emulator::Emulator(){
    status = 0;
    handler = 0;
    cause = 0;
    for(uint8_t i = 0; i<NUMBER_OF_GENERAL_REGISTERS; i++){
        this->r[i] = 0;
    }
    pc = 0x40000000;
    halted = false;
}


uint32_t Emulator::getGeneralRegister(uint8_t registerId){
    if (registerId==0) return 0;
    return r[registerId];
}
void Emulator::setGeneralRegister(uint8_t registerId, uint32_t value){
    if (registerId==0) return;
    r[registerId] = value;
}

void Emulator::executeInstuction(uint32_t instruction){
    if(instruction == 0){
        halted = true;
    }
}

string Emulator::formatToHex(uint32_t value) {
    ostringstream oss;
    oss << "0x" << std::hex << std::setw(8) << std::setfill('0') << value;
    return oss.str();
}

ostream& operator<<(ostream &os, Emulator &emulator){
    os << "--------------------------------------------------------------------------";
    for(int i = 0; i<Emulator::NUMBER_OF_GENERAL_REGISTERS; i++){
        if (i%4==0) os << "\n";
        else os << "\t";
        os<<"r"<<i<<"="<<Emulator::formatToHex(emulator.getGeneralRegister(i));
    };
    return os;
}