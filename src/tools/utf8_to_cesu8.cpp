#include "utf8_to_cesu8.hpp"
#include "../cesu8.hpp"
#include "common.hpp"

#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
        if (argc != 3) {
                std::cerr << "Usage: " << argv[0] << " <input_filepath> <output_filepath>"
                          << std::endl;
                return 1;
        }

        std::vector<char> utf8_buffer = read_file_as_binary(argv[1]);
        size_t            byte_len    = utf8_buffer.size();
        size_t            cesu8_len   = cesu8_len_from_utf8(utf8_buffer.data(), byte_len);
        std::vector<char> cesu8_buffer;
        cesu8_buffer.resize(cesu8_len);
        copy_utf8_as_cesu8_buffer(cesu8_buffer.data(), utf8_buffer.data(), byte_len);

        if (!cesu8::is_valid_cesu8_scalar(
                (unsigned char*)cesu8_buffer.data(), cesu8_buffer.size())) {
                throw std::runtime_error("Invalid cesu8 after conversion");
        }

        std::ofstream fout(argv[2], std::ios::out | std::ios::binary);
        fout.write(cesu8_buffer.data(), cesu8_buffer.size());
        fout.close();

        std::cout << "Successfully converted \"" << argv[1] << "\" to cesu8 and stored as \""
                  << argv[2] << "\"" << std::endl;

        return 0;
}
