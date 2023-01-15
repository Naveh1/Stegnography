#include "Decrypt.h"
#include "Encrypt.h"
#include "Helper.hpp"
#include "ParsedImage.hpp"

std::vector<unsigned char> Decrypt::decrypt(ParsedImage &img, const int byte)
{
    std::vector<bool> bitArray;

    for (int i = 0; i < img.getRows(); i++)
    {
        for (auto& j : img[i])
        {
            for (int k = 0; k < RGB_SIZE; k++)
                bitArray.emplace_back((j[k] >> byte) & 1);
        }
    }

    return Helper::bits_to_bytes(bitArray);
}
