#include "Decrypt.h"
#include "Helper.hpp"
#include "ParsedImage.hpp"

std::vector<unsigned char> Decrypt::decrypt(const ParsedImage& img, const int byte)
{
    std::vector<bool> bitArray;

    //TODO: setup bitArray

    return Helper::bits_to_bytes(bitArray);
}
