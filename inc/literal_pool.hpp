#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
using namespace std;


class LiteralPool {
    unordered_map<uint32_t, uint32_t> poolMapLiteral;
    unordered_map<string, uint32_t> poolMapSymbol;
    uint32_t offsetFromStartOfPool = 0;
    uint32_t poolBase = 0;
    vector<uint8_t> *data;
public:
    LiteralPool(uint32_t poolBase, vector<uint8_t> *data);
    void addSymbol(const string& name, uint32_t value);
    void addLiteral(uint32_t value);

    uint32_t getSymbolOffset(const string& name);
    uint32_t getLiteralOffset(uint32_t value);

    uint32_t getPoolBase(){return poolBase;}
};