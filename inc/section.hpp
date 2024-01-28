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
    uint32_t current_position;
    
    
public:
    vector<uint8_t> data;
    LiteralPool literal_pool;
    vector<Relocation> relocationTable;
    
    Section(const string &name){this->name = name; current_position = 0; data = {};}
    uint32_t getSize() const { return data.size(); }
    uint32_t getCurrentPosition() const { return current_position; }
    void resetPosition() { current_position = 0;}
    void incPosition(uint32_t inc) { 
        current_position += inc;
        if (current_position > data.size()) data.resize(current_position);
    }
    void addByte(uint8_t byte) { data[current_position++] = byte; }
    void add4Bytes(uint32_t word) { 
        data[current_position++] = (word >> 24);
        data[current_position++] = (word >> 16); 
        data[current_position++] = (word >> 8); 
        data[current_position++] = (word);
    }
    string getName() const { return name; }

    void mergeSectionAndPool() {
        size_t originalDataSize = data.size();
        data.resize(originalDataSize + literal_pool.pool.size());
        std::copy(literal_pool.pool.begin(), literal_pool.pool.end(), data.begin() + originalDataSize);
    }


    void serialize(std::ostream& stream) const {
        // Serialize section name
        uint32_t nameSize = name.size();
        stream.write(reinterpret_cast<const char*>(&nameSize), sizeof(uint32_t));
        stream.write(name.c_str(), nameSize);

        // Serialize size and current_position
        stream.write(reinterpret_cast<const char*>(&current_position), sizeof(uint32_t));

        // Serialize data
        uint32_t dataSize = data.size();
        stream.write(reinterpret_cast<const char*>(&dataSize), sizeof(uint32_t));
        stream.write(reinterpret_cast<const char*>(data.data()), dataSize * sizeof(uint8_t));

        // Serialize literal pool
        literal_pool.serialize(stream);

        // Serialize relocation table
        uint32_t relocationTableSize = relocationTable.size();
        stream.write(reinterpret_cast<const char*>(&relocationTableSize), sizeof(uint32_t));
        for (const auto& relocation : relocationTable) {
            relocation.serialize(stream);
        }
    }

    // Deserialization function
    void deserialize(std::istream& stream) {
        // Deserialize section name
        uint32_t nameSize;
        stream.read(reinterpret_cast<char*>(&nameSize), sizeof(uint32_t));
        char* nameBuffer = new char[nameSize + 1];
        stream.read(nameBuffer, nameSize);
        nameBuffer[nameSize] = '\0';
        name = nameBuffer;
        delete[] nameBuffer;

        // Deserialize size and current_position
        stream.read(reinterpret_cast<char*>(&current_position), sizeof(uint32_t));

        // Deserialize data
        uint32_t dataSize;
        stream.read(reinterpret_cast<char*>(&dataSize), sizeof(uint32_t));
        data.resize(dataSize);
        stream.read(reinterpret_cast<char*>(data.data()), dataSize * sizeof(uint8_t));

        // Deserialize literal pool
        literal_pool.deserialize(stream);

        // Deserialize relocation table
        uint32_t relocationTableSize;
        stream.read(reinterpret_cast<char*>(&relocationTableSize), sizeof(uint32_t));
        relocationTable.clear();
        relocationTable.reserve(relocationTableSize);
        for (uint32_t i = 0; i < relocationTableSize; ++i) {
            Relocation relocation;
            relocation.deserialize(stream);
            relocationTable.push_back(relocation);
        }
    }
};
