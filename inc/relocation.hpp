#pragma once
#include <cstdint>
#include <vector>
#include <ostream>
#include <istream>
using namespace std;

struct Relocation{
    uint32_t offset;
    uint32_t symbolIndex;
    uint32_t sectionIndex;
    Relocation() : offset(0), symbolIndex(0), sectionIndex(0) {}
    Relocation(uint32_t offset, uint32_t symbolIndex, uint32_t sectionIndex){
        this->offset = offset;
        this->symbolIndex = symbolIndex;
        this->sectionIndex = sectionIndex;
    }
    void serialize(std::ostream& stream) const {
        // Serialize offset, symbolIndex, and sectionIndex
        stream.write(reinterpret_cast<const char*>(&offset), sizeof(uint32_t));
        stream.write(reinterpret_cast<const char*>(&symbolIndex), sizeof(uint32_t));
        stream.write(reinterpret_cast<const char*>(&sectionIndex), sizeof(uint32_t));
    }

    // Deserialize function for Relocation
    void deserialize(std::istream& stream) {
        // Deserialize offset, symbolIndex, and sectionIndex
        stream.read(reinterpret_cast<char*>(&offset), sizeof(uint32_t));
        stream.read(reinterpret_cast<char*>(&symbolIndex), sizeof(uint32_t));
        stream.read(reinterpret_cast<char*>(&sectionIndex), sizeof(uint32_t));
    }
};
