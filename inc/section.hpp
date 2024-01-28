#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "relocation.hpp"
#include "literal_pool.hpp"
using namespace std;
class Section{
private:
    string name;
    uint32_t size, current_position;
    
    
public:
    vector<uint8_t> data;
    LiteralPool literal_pool;
    vector<Relocation> relocationTable;
    
    Section(const string &name){this->name = name; size = 0; current_position = 0; data = {};}
    uint32_t getSize() const { return size; }
    uint32_t getCurrentPosition() const { return current_position; }
    void resetPosition() { current_position = 0;}
    void incPosition(uint32_t inc) { 
        current_position += inc;
        if (current_position > size) size = current_position;
    }
    void addByte(uint8_t byte) { data.push_back(byte); size++; current_position++; }
    void add4Bytes(uint32_t word) { 
        data.push_back(word >> 24);
        data.push_back(word >> 16); 
        data.push_back(word >> 8); 
        data.push_back(word); size += 4; 
        current_position += 4; 
    }
    string getName() const { return name; }
};