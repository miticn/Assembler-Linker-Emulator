#include "../inc/literal_pool.hpp"

LiteralPool::LiteralPool(uint32_t poolBase, vector<uint8_t> *data): poolBase(poolBase), data(data){}


void LiteralPool::addSymbol(const string& name, uint32_t value) {
    if (poolMapSymbol.find(name) != poolMapSymbol.end()) {
        return;
    }
    poolMapSymbol[name] = this->offsetFromStartOfPool+this->poolBase;
    
    data->push_back(value >> 24);
    data->push_back(value >> 16);
    data->push_back(value >> 8);
    data->push_back(value);


    this->offsetFromStartOfPool += 4;
}

void LiteralPool::addLiteral(uint32_t value) {
    if (poolMapLiteral.find(value) != poolMapLiteral.end()) {
        return;
    }
    poolMapLiteral[value] = this->offsetFromStartOfPool+this->poolBase;
    data->push_back(value >> 24);
    data->push_back(value >> 16);
    data->push_back(value >> 8);
    data->push_back(value);
    this->offsetFromStartOfPool += 4;
}

uint32_t LiteralPool::getSymbolOffset(const string& name) {
    return poolMapSymbol[name];
}

uint32_t LiteralPool::getLiteralOffset(uint32_t value) {
    return poolMapLiteral[value];
}
