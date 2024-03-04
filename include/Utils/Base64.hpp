#pragma once

#include <array>
#include <string>
#include <string_view>

class Base64
{
public:
    Base64() = default;
    static std::string Encode(const std::string_view& data,
                              bool removePadding = false);
    ~Base64() = default;

private:
    static constexpr char PADDING_CHAR = '=';
    static constexpr std::array<char, 256> ENCODE_TABLE_0 = {
        'A', 'A', 'A', 'A', 'B', 'B', 'B', 'B', 'C', 'C', 'C', 'C', 'D', 'D',
        'D', 'D', 'E', 'E', 'E', 'E', 'F', 'F', 'F', 'F', 'G', 'G', 'G', 'G',
        'H', 'H', 'H', 'H', 'I', 'I', 'I', 'I', 'J', 'J', 'J', 'J', 'K', 'K',
        'K', 'K', 'L', 'L', 'L', 'L', 'M', 'M', 'M', 'M', 'N', 'N', 'N', 'N',
        'O', 'O', 'O', 'O', 'P', 'P', 'P', 'P', 'Q', 'Q', 'Q', 'Q', 'R', 'R',
        'R', 'R', 'S', 'S', 'S', 'S', 'T', 'T', 'T', 'T', 'U', 'U', 'U', 'U',
        'V', 'V', 'V', 'V', 'W', 'W', 'W', 'W', 'X', 'X', 'X', 'X', 'Y', 'Y',
        'Y', 'Y', 'Z', 'Z', 'Z', 'Z', 'a', 'a', 'a', 'a', 'b', 'b', 'b', 'b',
        'c', 'c', 'c', 'c', 'd', 'd', 'd', 'd', 'e', 'e', 'e', 'e', 'f', 'f',
        'f', 'f', 'g', 'g', 'g', 'g', 'h', 'h', 'h', 'h', 'i', 'i', 'i', 'i',
        'j', 'j', 'j', 'j', 'k', 'k', 'k', 'k', 'l', 'l', 'l', 'l', 'm', 'm',
        'm', 'm', 'n', 'n', 'n', 'n', 'o', 'o', 'o', 'o', 'p', 'p', 'p', 'p',
        'q', 'q', 'q', 'q', 'r', 'r', 'r', 'r', 's', 's', 's', 's', 't', 't',
        't', 't', 'u', 'u', 'u', 'u', 'v', 'v', 'v', 'v', 'w', 'w', 'w', 'w',
        'x', 'x', 'x', 'x', 'y', 'y', 'y', 'y', 'z', 'z', 'z', 'z', '0', '0',
        '0', '0', '1', '1', '1', '1', '2', '2', '2', '2', '3', '3', '3', '3',
        '4', '4', '4', '4', '5', '5', '5', '5', '6', '6', '6', '6', '7', '7',
        '7', '7', '8', '8', '8', '8', '9', '9', '9', '9', '+', '+', '+', '+',
        '/', '/', '/', '/'
    };
    static constexpr std::array<char, 256> ENCODE_TABLE_1 = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
        'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b',
        'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
        'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3',
        '4', '5', '6', '7', '8', '9', '+', '/', 'A', 'B', 'C', 'D', 'E', 'F',
        'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
        'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
        'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
        'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        '+', '/', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
        'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
        'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1',
        '2', '3', '4', '5', '6', '7', '8', '9', '+', '/', 'A', 'B', 'C', 'D',
        'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
        'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
        'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
        'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
        '8', '9', '+', '/'
    };
};
