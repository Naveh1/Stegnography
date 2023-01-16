#include "Decrypt.h"
#include "Encrypt.h"
#include "Helper.hpp"
#include "ParsedImage.hpp"


/*
* A function to decrypt hidden message from image
* The function iterates over the image and saves the byte's bit of every byte of the image
* 
* img: A wrapped image with the secret image
* byte: the bit where the secret message was hidden in
* 
* Return: the message as an array
*/
std::vector<bool> Decrypt::decrypt(ParsedImage &img, const int byte)
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

    return bitArray;
}

std::string Decrypt::findMessage(ParsedImage& img)
{
    std::string best;
    std::vector<unsigned char> curr;
    int score = -1, tmpScore = 0;

    std::set<std::string> wordList = Helper::loadWordList();

    for (int i = 0; i < BITS_CHECKED; i++)
    {
        curr = Helper::bits_to_bytes(Decrypt::decrypt(img, i));

        if ((tmpScore = Helper::gradeMessage(curr, wordList)) > score)
        {
            score = tmpScore;
            best = std::string(curr.begin(), curr.end());
        }
    }

    return best;
}

