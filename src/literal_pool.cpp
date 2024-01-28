#include "../inc/literal_pool.hpp"

void LiteralPool::addSymbol(const string& name, uint32_t value) {
    if (poolMapSymbol.find(name) != poolMapSymbol.end()) {
        return;
    }
    poolMapSymbol[name] = this->offsetFromStartOfPool;
    
    pool.push_back(value >> 24);
    pool.push_back(value >> 16);
    pool.push_back(value >> 8);
    pool.push_back(value);


    this->offsetFromStartOfPool += 4;
}

void LiteralPool::addLiteral(uint32_t value) {
    if (poolMapLiteral.find(value) != poolMapLiteral.end()) {
        return;
    }
    poolMapLiteral[value] = this->offsetFromStartOfPool;
    pool.push_back(value >> 24);
    pool.push_back(value >> 16);
    pool.push_back(value >> 8);
    pool.push_back(value);
    this->offsetFromStartOfPool += 4;
}

uint32_t LiteralPool::getSymbolOffset(const string& name) {
    return poolMapSymbol[name];
}

uint32_t LiteralPool::getLiteralOffset(uint32_t value) {
    return poolMapLiteral[value];
}

uint32_t LiteralPool::getSize() {
    return pool.size()*4;
}