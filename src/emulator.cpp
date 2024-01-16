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
    if(instruction == 0x10000000){/* software interupt */
        push(status);
        push(pc);
        cause = 4;
        status = status&(~0x1);
        pc = handler;
    }
    uint16_t disp = instruction & 0xfff;
    uint8_t regC = (instruction >> 12) & 0xf;
    uint8_t regB = (instruction >> 16) & 0xf;
    uint8_t regA = (instruction >> 20) & 0xf;
    uint8_t mod = (instruction >> 24) & 0xf;
    uint8_t oc = (instruction >> 28) & 0xf;

    switch (oc) {
    case 0b0010:
        executeFunctionCall(mod, regA, regB, regC, disp);
        break;
    case 0b0011:
        executeJump(mod, regA, regB, regC, disp);
        break;
    case 0b0100:
        executeAtomicRegisterSwap(mod, regA, regB, regC, disp);
        break;
    case 0b0101:
        executeArithmeticOperation(mod, regA, regB, regC, disp);
        break;
    case 0b0110:
        executeLogicOperation(mod, regA, regB, regC, disp);
        break;
    case 0b0111:
        executeShiftOperation(mod, regA, regB, regC, disp);
        break;
    case 0b1000:
        executeStore(mod, regA, regB, regC, disp);
        break;
    case 0b1001:
        executeLoad(mod, regA, regB, regC, disp);
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


 void Emulator::loadHex(string inputFileName){

 }

uint32_t Emulator::pop(){
    uint32_t returnValue = memory.get32BitValueAtAddress(sp);
    sp = sp + 4;
    return returnValue;
}
void Emulator::push(uint32_t value){
    sp = sp - 4;
    memory.set32BitValueAtAddress(sp,value);
}
void Emulator::executeFunctionCall(uint8_t mod, uint8_t regA, uint8_t regB, uint8_t regC, uint16_t disp){
    if(0b0000==mod){
        push(pc);
        pc = r[regA]+r[regB] + disp;
    }
    else if(0b0001==mod){
        push(pc);
        pc = this->memory.get32BitValueAtAddress(r[regA]+r[regB] + disp);
    }

}
void Emulator::executeJump(uint8_t mod, uint8_t regA, uint8_t regB, uint8_t regC, uint16_t disp){
    switch (mod) {
    case 0b0000:
        pc = r[regA] + disp;
        break;
    case 0b0001:
        if (r[regB] == r[regC])
            pc = r[regA] + disp;
        break;
    case 0b0010:
        if (r[regB] != r[regC])
            pc = r[regA] + disp;
        break;
    case 0b0011:
        if (static_cast<int32_t>(r[regB]) > static_cast<int32_t>(r[regC]))
            pc = r[regA] + disp;
        break;
    case 0b1000:
        pc = memory.get32BitValueAtAddress(r[regA] + disp);
        break;
    case 0b1001:
        if (r[regB] == r[regC])
            pc = memory.get32BitValueAtAddress(r[regA] + disp);
        break;
    case 0b1010:
        if (r[regB] != r[regC])
            pc = memory.get32BitValueAtAddress(r[regA] + disp);
        break;
    case 0b1011:
        if (static_cast<int32_t>(r[regB]) > static_cast<int32_t>(r[regC]))
            pc = memory.get32BitValueAtAddress(r[regA] + disp);
        break;
    default:
        break;
    }

}
void Emulator::executeAtomicRegisterSwap(uint8_t mod, uint8_t regA, uint8_t regB, uint8_t regC, uint16_t disp){
    uint32_t temp = r[regB];
    r[regB] = r[regC];
    r[regC] = temp;
}
void Emulator::executeArithmeticOperation(uint8_t mod, uint8_t regA, uint8_t regB, uint8_t regC, uint16_t disp){
    switch (mod)
    {
    case 0b0000:
        r[regA] = r[regB] + r[regC];
        break;
    case 0b0001:
        r[regA] = r[regB] - r[regC];
        break;
    case 0b0010:
        r[regA] = r[regB] * r[regC];
        break;
    case 0b0011:
        r[regA] = r[regB] / r[regC];
        break;
    default:
        break;
    }
}
void Emulator::executeLogicOperation(uint8_t mod, uint8_t regA, uint8_t regB, uint8_t regC, uint16_t disp){
    switch (mod)
    {
    case 0b0000:
        r[regA] = ~r[regB];
        break;
    case 0b0001:
        r[regA] = r[regB] & r[regC];
        break;
    case 0b0010:
        r[regA] = r[regB] | r[regC];
        break;
    case 0b0011:
        r[regA] = r[regB] ^ r[regC];
        break;
    default:
        break;
    }
}
void Emulator::executeShiftOperation(uint8_t mod, uint8_t regA, uint8_t regB, uint8_t regC, uint16_t disp){
    switch (mod)
    {
    case 0b0000:
        r[regA] = r[regB] << r[regC];
        break;
    case 0b0001:
        r[regA] = r[regB] >> r[regC];
        break;
    default:
        break;
    }
}
void Emulator::executeStore(uint8_t mod, uint8_t regA, uint8_t regB, uint8_t regC, uint16_t disp){
    switch (mod){
    case 0b0000:
        this->memory.set32BitValueAtAddress(r[regA]+r[regB]+disp,r[regC]);
        break;
    case 0b0010:
        this->memory.set32BitValueAtAddress(memory.get32BitValueAtAddress(r[regA]+r[regB]+disp),r[regC]);
        break;
    case 0b0001:
        r[regA] = r[regA]+disp;
        this->memory.set32BitValueAtAddress(r[regA], r[regC]);
        break;
    default:
        break;
    }
}
void Emulator::executeLoad(uint8_t mod, uint8_t regA, uint8_t regB, uint8_t regC, uint16_t disp){
    switch (mod) {
    case 0b0000:
        r[regA] = csr[regB];
        break;
    case 0b0001:
        r[regA] = r[regB] + disp;
        break;
    case 0b0010:
        r[regA] = memory.get32BitValueAtAddress(r[regB] + r[regC] + disp);
        break;
    case 0b0011:
        r[regA] = memory.get32BitValueAtAddress(r[regB]);
        r[regB] += disp;
        break;
    case 0b0100:
        csr[regA] = r[regB];
        break;
    case 0b0101:
        csr[regA] = csr[regB] | disp;
        break;
    case 0b0110:
        csr[regA] = memory.get32BitValueAtAddress(r[regB] + r[regC] + disp);
        break;
    case 0b0111:
        csr[regA] = memory.get32BitValueAtAddress(r[regB]);
        r[regB] += disp;
        break;
    default:
        break;
    }
}