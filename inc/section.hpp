#pragma once
#include <cstdint>
#include <string>
using namespace std;
class Section{
private:
    string name;
    uint32_t size, current_position;
    uint8_t *data;
public:
    Section(const string &name){this->name = name;}
    uint32_t getSize() const { return size; }
    uint32_t getCurrentPosition() const { return current_position; }
    void resetPosition() { current_position = 0;}
    void incPosition();
};