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


uint32_t Emulator::getGR(uint8_t registerId){
    if (registerId==0) return 0;
    return r[registerId];
}
void Emulator::setGR(uint8_t registerId, uint32_t value){
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
        os<<"r"<<i<<"="<<Emulator::formatToHex(emulator.getGR(i));
    };
    return os;
}

 void Emulator::run(){
    uint32_t current_time_config = 0xff;
    auto duration_ms = chrono::milliseconds(0);
    auto start_time = chrono::steady_clock::now();
    bool last_timer_interupt_disabled = true;
    while(!this->isHalted()){
        uint32_t tmp = pc;
        pc +=4;
        this->executeInstuction(this->memory.get32BitValueAtAddress(tmp));
        //Timer stuff
        if(this->timerInteruptEnabled()){
            if(current_time_config!=memory.get32BitValueAtAddress(tim_cfg_address) || last_timer_interupt_disabled){
                current_time_config = memory.get32BitValueAtAddress(tim_cfg_address);
                last_timer_interupt_disabled = false;
                switch (current_time_config){
                case 0x0:
                    duration_ms = chrono::milliseconds(500);
                    break;
                case 0x1:
                    duration_ms = chrono::milliseconds(1000);
                    break;
                case 0x2:
                    duration_ms = chrono::milliseconds(1500);
                    break;
                case 0x3:
                    duration_ms = chrono::milliseconds(2000);
                    break;
                case 0x4:
                    duration_ms = chrono::milliseconds(5000);
                    break;
                case 0x5:
                    duration_ms = chrono::milliseconds(10000);
                    break;
                case 0x6:
                    duration_ms = chrono::milliseconds(30000);
                    break;
                case 0x7:
                    duration_ms = chrono::milliseconds(60000);
                    break;
                default:
                    break;
                }
                start_time = chrono::steady_clock::now();
            }
            if(chrono::steady_clock::now() > start_time + duration_ms) {
                //timer interupt here
                push(status);
                push(pc);
                cause = 2;
                //status = status&(~0x1);
                pc = handler;
                start_time = chrono::steady_clock::now();
            }
        } else {
            last_timer_interupt_disabled = true;
        }
        //Terminal stuff
        if(this->terminalInteruptEnabled()){

        }

    }
 }


 void Emulator::loadHex(string inputFileName){
    std::ifstream hexFile(inputFileName);

    if (!hexFile.is_open()) {
        std::cerr << "Error opening the hex file." << std::endl;
        exit(1);
    }

    std::string line;
    while (std::getline(hexFile, line)) {
        std::stringstream ss(line);

        uint32_t address;
        char colon;
        ss >> std::hex >> address >> colon;

        uint32_t value;
        while (ss >> std::hex >> value) {
            memory.set8BitValueAtAddress(address, value);
            address++;
        }
    }

    hexFile.close();
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
        pc = getGR(regA)+getGR(regB) + disp;
    }
    else if(0b0001==mod){
        push(pc);
        pc = this->memory.get32BitValueAtAddress(getGR(regA)+getGR(regB) + disp);
    }

}
void Emulator::executeJump(uint8_t mod, uint8_t regA, uint8_t regB, uint8_t regC, uint16_t disp){
    switch (mod) {
    case 0b0000:
        pc = getGR(regA) + disp;
        break;
    case 0b0001:
        if (getGR(regB) == getGR(regC))
            pc = getGR(regA) + disp;
        break;
    case 0b0010:
        if (getGR(regB) != getGR(regC))
            pc = getGR(regA) + disp;
        break;
    case 0b0011:
        if (static_cast<int32_t>(getGR(regB)) > static_cast<int32_t>(getGR(regC)))
            pc = getGR(regA) + disp;
        break;
    case 0b1000:
        pc = memory.get32BitValueAtAddress(getGR(regA) + disp);
        break;
    case 0b1001:
        if (getGR(regB) == getGR(regC))
            pc = memory.get32BitValueAtAddress(getGR(regA) + disp);
        break;
    case 0b1010:
        if (getGR(regB) != getGR(regC))
            pc = memory.get32BitValueAtAddress(getGR(regA) + disp);
        break;
    case 0b1011:
        if (static_cast<int32_t>(getGR(regB)) > static_cast<int32_t>(getGR(regC)))
            pc = memory.get32BitValueAtAddress(getGR(regA) + disp);
        break;
    default:
        break;
    }

}
void Emulator::executeAtomicRegisterSwap(uint8_t mod, uint8_t regA, uint8_t regB, uint8_t regC, uint16_t disp){
    uint32_t temp = getGR(regB);
    setGR(regB, getGR(regC));
    setGR(regC, temp);
}
void Emulator::executeArithmeticOperation(uint8_t mod, uint8_t regA, uint8_t regB, uint8_t regC, uint16_t disp){
    switch (mod)
    {
    case 0b0000:
        setGR(regA, getGR(regB) + getGR(regC));
        break;
    case 0b0001:
        setGR(regA, getGR(regB) - getGR(regC));
        break;
    case 0b0010:
        setGR(regA, getGR(regB) * getGR(regC));
        break;
    case 0b0011:
        setGR(regA, getGR(regB) / getGR(regC));
        break;
    default:
        break;
    }
}
void Emulator::executeLogicOperation(uint8_t mod, uint8_t regA, uint8_t regB, uint8_t regC, uint16_t disp){
    switch (mod)
    {
    case 0b0000:
        setGR(regA, ~getGR(regB));
        break;
    case 0b0001:
        setGR(regA, getGR(regB) & getGR(regC));
        break;
    case 0b0010:
        setGR(regA, getGR(regB) | getGR(regC));
        break;
    case 0b0011:
        setGR(regA, getGR(regB) ^ getGR(regC));
        break;
    default:
        break;
    }
}
void Emulator::executeShiftOperation(uint8_t mod, uint8_t regA, uint8_t regB, uint8_t regC, uint16_t disp){
    switch (mod)
    {
    case 0b0000:
        setGR(regA, getGR(regB) << getGR(regC));
        break;
    case 0b0001:
        setGR(regA, getGR(regB) >> getGR(regC));
        break;
    default:
        break;
    }
}
void Emulator::executeStore(uint8_t mod, uint8_t regA, uint8_t regB, uint8_t regC, uint16_t disp){
    switch (mod){
    case 0b0000:
        this->memory.set32BitValueAtAddress(getGR(regA)+getGR(regB)+disp,getGR(regC));
        break;
    case 0b0010:
        this->memory.set32BitValueAtAddress(memory.get32BitValueAtAddress(getGR(regA)+getGR(regB)+disp),getGR(regC));
        break;
    case 0b0001:
        setGR(regA, getGR(regA)+disp);
        this->memory.set32BitValueAtAddress(getGR(regA), getGR(regC));
        break;
    default:
        break;
    }
}
void Emulator::executeLoad(uint8_t mod, uint8_t regA, uint8_t regB, uint8_t regC, uint16_t disp){
    switch (mod) {
    case 0b0000:
        setGR(regA, csr[regB]);
        break;
    case 0b0001:
        setGR(regA, getGR(regB) + disp);
        break;
    case 0b0010:
        setGR(regA, memory.get32BitValueAtAddress(getGR(regB) + getGR(regC) + disp));
        break;
    case 0b0011:
        setGR(regA, memory.get32BitValueAtAddress(getGR(regB)));
        setGR(regB, getGR(regB) + disp);
        break;
    case 0b0100:
        csr[regA] = getGR(regB);
        break;
    case 0b0101:
        csr[regA] = csr[regB] | disp;
        break;
    case 0b0110:
        csr[regA] = memory.get32BitValueAtAddress(getGR(regB) + getGR(regC) + disp);
        break;
    case 0b0111:
        csr[regA] = memory.get32BitValueAtAddress(getGR(regB));
        setGR(regB, getGR(regB) + disp);
        break;
    default:
        break;
    }
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename.hex>" << std::endl;
        return 1;
    }

    const std::string inputFileName = argv[1];

    Emulator myEmulator;
    myEmulator.loadHex(inputFileName);
    myEmulator.run();
    std::cout << myEmulator << std::endl;

    return 0;
}