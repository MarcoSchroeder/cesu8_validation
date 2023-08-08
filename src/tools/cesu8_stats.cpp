#include "cesu8_stats.hpp"

#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    const char* filename = argv[1];
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::vector<char> buffer;
    const size_t initialBufferSize = 1024; // Initial buffer size
    buffer.reserve(initialBufferSize);

    char tempBuffer[initialBufferSize];
    while (file.read(tempBuffer, sizeof(tempBuffer))) {
        buffer.insert(buffer.end(), tempBuffer, tempBuffer + file.gcount());
    }

    if (!file.eof() && file.fail()) {
        std::cerr << "An error occurred while reading the file." << std::endl;
        return 1;
    }

    file.close();

    Cesu8Stats stats = validate_and_collect_stats(reinterpret_cast<byte*>(buffer.data()), buffer.size());
    std::cout << "Buffer size:\t" << buffer.size() << std::endl;
    std::cout << "Nr codepoints:\t" << stats.nr_codepoints << std::endl;
    std::cout << "Nr 1-byte:\t" << stats.nr_c1 << std::endl;
    std::cout << "Nr 2-byte:\t" << stats.nr_c2 << std::endl;
    std::cout << "Nr 3-byte:\t" << stats.nr_c3 << std::endl;
    std::cout << "Nr surrogate:\t" << stats.nr_surrogate << std::endl;
    return 0;
}