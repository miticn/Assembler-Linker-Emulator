#pragma once
#include <cstdint>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
using namespace std;

class LinkerOutput{
private:
    map<uint32_t, uint8_t> memory;
public:
    void copySectionData(uint32_t address, vector<uint8_t> &data);
    uint8_t get8BitValueAtAddress(uint32_t address);
    uint32_t get32BitValueAtAddress(uint32_t address);
    void set8BitValueAtAddress(uint32_t address, uint8_t value);
    void set32BitValueAtAddress(uint32_t address, uint32_t value);
    bool isAddressUsed(uint32_t address);
    void saveFile(const string &outputFileName);
};