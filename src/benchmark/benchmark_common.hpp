#include <cstring>
#include <cstddef>
#include <cstdlib>
#include <ctime>

constexpr size_t ITERATIONS_SMALL = 1000000;
constexpr size_t ITERATIONS = 2000;

constexpr size_t SMALL_MIN = 1;
constexpr size_t SMALL_MAX = 1 << 10;
constexpr size_t BIG_MIN = 1 << 11;
constexpr size_t BIG_MAX = 1 << 22;

using byte = unsigned char;

constexpr byte CONTINUATION_BYTE = 0x8F;
constexpr byte ASCII_BYTE = 0x41;
constexpr byte TWO_BYTE_HEADER = 0xCF;
constexpr byte THREE_BYTE_HEADER = 0xEF;
constexpr byte SURROGATE_ED = 0xED;
constexpr byte SURROGATE_A = 0xA0;
constexpr byte SURROGATE_B = 0xB0;

void set_ascii_data(byte* data, std::size_t len)
{
    memset(data, ASCII_BYTE, len);
}

void set_surrogate_data(byte* data, std::size_t len)
{
    for(size_t i=0; i+6 <= len; i += 6) {
        data[i] = SURROGATE_ED;
        data[i+1] = SURROGATE_A;
        data[i+2] = CONTINUATION_BYTE;
        data[i+3] = SURROGATE_ED;
        data[i+4] = SURROGATE_B;
        data[i+5] = CONTINUATION_BYTE;
    }
    std::size_t remainder = len % 6;
    byte* end = data + len;
    memset(end-remainder, ASCII_BYTE, remainder);
}

void set_random_data(byte* data, std::size_t len)
{
    auto len_copy = len;
    std::srand(210399);
    std::size_t i = 0;
    while(len >= 6) {
        int random_number = std::rand() % 4;
        if(random_number == 0) {
            data[i] = ASCII_BYTE;
            --len; 
            ++i;
        }
        else if (random_number == 1) {
            data[i] = TWO_BYTE_HEADER;
            data[i+1] = CONTINUATION_BYTE;
            len -= 2; 
            i += 2;
        }
        else if (random_number == 2) {
            data[i] = THREE_BYTE_HEADER;
            data[i+1] = CONTINUATION_BYTE;
            data[i+2] = CONTINUATION_BYTE;
            len -= 3; 
            i += 3;
        }
        else {
            data[i] = SURROGATE_ED;
            data[i+1] = SURROGATE_A;
            data[i+2] = CONTINUATION_BYTE;
            data[i+3] = SURROGATE_ED;
            data[i+4] = SURROGATE_B;
            data[i+5] = CONTINUATION_BYTE;
            len -= 6; 
            i += 6;
        }
    }

    memset(data+i, ASCII_BYTE, len);
}
