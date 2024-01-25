#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include <unordered_map>
using namespace std;


class LiteralPool {
    vector<uint32_t> pool;
    unordered_map<uint32_t, uint32_t> poolMapLiteral;
    unordered_map<string, uint32_t> poolMapSymbol;
    uint32_t poolOffset = 0;
public:
    void addSymbol(const string& name, uint32_t value);
    void addLiteral(uint32_t value);

    uint32_t getSymbolOffset(const string& name);
    uint32_t getLiteralOffset(uint32_t value);
    uint32_t getSize();

};