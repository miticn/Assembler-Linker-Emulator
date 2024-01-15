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
        return;
    }
    uint16_t disp = instruction & 0xfff;
    uint8_t regC = (instruction >> 12) & 0xf;
    uint8_t regB = (instruction >> 16) & 0xf;
    uint8_t regA = (instruction >> 20) & 0xf;
    uint8_t mod = (instruction >> 24) & 0xf;
    uint8_t oc = (instruction >> 28) & 0xf;

    switch (oc)
    {
    case 0b0001:
        /* software interupt */
        break;
    case 0b0010:
        /* function call */
        break;
    case 0b0011:
        /* jump */
        break;
    case 0b0100:
        /* atomic register swap */
        break;
    case 0b0101:
        /* arithmetic operation */
        break;
    case 0b0110:
        /* logic operation */
        break;
    case 0b0111:
        /* shift operation */
        break;
    case 0b1000:
        /* store */
        break;
    case 0b1001:
        /* load */
        break;
    
    default:
        break;
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

 void Emulator::run(){
    while(!this->isHalted()){
        uint32_t tmp = pc;
        pc +=4;
        this->executeInstuction(this->memory.get32BitValueAtAddress(tmp));
    }
 }


 void Emulator::loadHex(){

 }