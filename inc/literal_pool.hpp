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
public:
    vector<uint8_t> pool;
    void addSymbol(const string& name, uint32_t value);
    void addLiteral(uint32_t value);

    uint32_t getSymbolOffset(const string& name);
    uint32_t getLiteralOffset(uint32_t value);
    uint32_t getSize();

    void serialize(std::ostream& stream) const {
        // Serialize poolMapLiteral size and entries
        uint32_t mapLiteralSize = poolMapLiteral.size();
        stream.write(reinterpret_cast<const char*>(&mapLiteralSize), sizeof(uint32_t));
        for (const auto& entry : poolMapLiteral) {
            stream.write(reinterpret_cast<const char*>(&entry.first), sizeof(uint32_t));
            stream.write(reinterpret_cast<const char*>(&entry.second), sizeof(uint32_t));
        }

        // Serialize poolMapSymbol size and entries
        uint32_t mapSymbolSize = poolMapSymbol.size();
        stream.write(reinterpret_cast<const char*>(&mapSymbolSize), sizeof(uint32_t));
        for (const auto& entry : poolMapSymbol) {
            uint32_t nameSize = entry.first.size();
            stream.write(reinterpret_cast<const char*>(&nameSize), sizeof(uint32_t));
            stream.write(entry.first.c_str(), nameSize);
            stream.write(reinterpret_cast<const char*>(&entry.second), sizeof(uint32_t));
        }

        // Serialize offsetFromStartOfPool
        stream.write(reinterpret_cast<const char*>(&offsetFromStartOfPool), sizeof(uint32_t));

        // Serialize pool size and content
        uint32_t poolSize = pool.size();
        stream.write(reinterpret_cast<const char*>(&poolSize), sizeof(uint32_t));
        stream.write(reinterpret_cast<const char*>(pool.data()), poolSize * sizeof(uint8_t));
    }

    // Deserialization function
    void deserialize(std::istream& stream) {
        // Deserialize poolMapLiteral
        uint32_t mapLiteralSize;
        stream.read(reinterpret_cast<char*>(&mapLiteralSize), sizeof(uint32_t));
        for (uint32_t i = 0; i < mapLiteralSize; ++i) {
            uint32_t key, value;
            stream.read(reinterpret_cast<char*>(&key), sizeof(uint32_t));
            stream.read(reinterpret_cast<char*>(&value), sizeof(uint32_t));
            poolMapLiteral[key] = value;
        }

        // Deserialize poolMapSymbol
        uint32_t mapSymbolSize;
        stream.read(reinterpret_cast<char*>(&mapSymbolSize), sizeof(uint32_t));
        for (uint32_t i = 0; i < mapSymbolSize; ++i) {
            uint32_t nameSize;
            stream.read(reinterpret_cast<char*>(&nameSize), sizeof(uint32_t));
            char* nameBuffer = new char[nameSize + 1]; // +1 for null terminator
            stream.read(nameBuffer, nameSize);
            nameBuffer[nameSize] = '\0';
            std::string name(nameBuffer);
            delete[] nameBuffer;

            uint32_t value;
            stream.read(reinterpret_cast<char*>(&value), sizeof(uint32_t));
            poolMapSymbol[name] = value;
        }

        // Deserialize offsetFromStartOfPool
        stream.read(reinterpret_cast<char*>(&offsetFromStartOfPool), sizeof(uint32_t));

        // Deserialize pool
        uint32_t poolSize;
        stream.read(reinterpret_cast<char*>(&poolSize), sizeof(uint32_t));
        pool.resize(poolSize);
        stream.read(reinterpret_cast<char*>(pool.data()), poolSize * sizeof(uint8_t));
    }
};