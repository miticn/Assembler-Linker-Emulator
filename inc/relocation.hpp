#pragma once
#include <cstdint>
#include <vector>
using namespace std;

struct Relocation{
    uint32_t offset;
    uint32_t symbolIndex;
    uint32_t sectionIndex;
    Relocation(uint32_t offset, uint32_t symbolIndex, uint32_t sectionIndex){
        this->offset = offset;
        this->symbolIndex = symbolIndex;
        this->sectionIndex = sectionIndex;
    }
};
