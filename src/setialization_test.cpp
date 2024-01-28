#include <iostream>
#include <fstream>
#include "../inc/section.hpp"
#include "../inc/literal_pool.hpp"
#include "../inc/symbol_table.hpp"

int main() {
    // Create a Symbol_table object
    Symbol_table symbolTable;

    // Add sections to the symbol table
    symbolTable.addSection("Text");
    symbolTable.addSection("Data");

    // Create Section instances
    Section textSection("Text");
    Section dataSection("Data");

    // Add symbols to the symbol table
    symbolTable.addSymbol(Symbol(0x100, Symbol::Type::SECTION, Symbol::Bind::GLOBAL, "main", 0));
    symbolTable.addSymbol(Symbol(0x200, Symbol::Type::SECTION, Symbol::Bind::LOCAL, "helper", 1));

    // Add data, literals, and relocations to the Text section
    textSection.addByte(0xAB);
    textSection.literal_pool.addLiteral(0xDEADBEEF);
    textSection.relocationTable.emplace_back(0x100, 0, 1); // Relocate 'main' symbol to index 1

    // Add data, literals, and relocations to the Data section
    dataSection.addByte(0xCD);
    dataSection.literal_pool.addLiteral(0xBAADF00D);
    dataSection.relocationTable.emplace_back(0x200, 1, 2); // Relocate 'helper' symbol to index 2

    // Serialize all objects into a single file
    std::ofstream outFile("serialized_data.bin", std::ios::binary);
    
    // Serialize Symbol_table
    symbolTable.serialize(outFile);

    // Serialize Section instances
    textSection.serialize(outFile);
    dataSection.serialize(outFile);

    outFile.close();

    // Deserialize objects from the single file
    std::ifstream inFile("serialized_data.bin", std::ios::binary);
    
    // Deserialize Symbol_table
    Symbol_table deserializedSymbolTable;
    deserializedSymbolTable.deserialize(inFile);

    // Deserialize Section instances
    Section deserializedTextSection("Placeholder");
    deserializedTextSection.deserialize(inFile);

    Section deserializedDataSection("Placeholder");
    deserializedDataSection.deserialize(inFile);

    inFile.close();

    // Verify deserialized Symbol_table
    deserializedSymbolTable.printSymbolTable();

    // Verify deserialized Text section
    std::cout << "Deserialized Text Section Data: ";
    for (auto byte : deserializedTextSection.data) {
        std::cout << std::hex << static_cast<int>(byte) << " ";
    }
    std::cout << std::endl;

    // Verify deserialized Data section
    std::cout << "Deserialized Data Section Data: ";
    for (auto byte : deserializedDataSection.data) {
        std::cout << std::hex << static_cast<int>(byte) << " ";
    }
    std::cout << std::endl;

    return 0;
}
