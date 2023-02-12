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

/*
std::string Decrypt::findMessage(ParsedImage& img)
{
    std::string best;
    std::vector<bool> noOffset, tmp;
    std::vector<unsigned char> curr, res;
    int score = -1, tmpScore = 0;

    std::set<std::string> wordList = Helper::loadWordList();

    for (int i = 0; i < BITS_CHECKED; i++)
    {
        noOffset = Decrypt::decrypt(img, i);
        for (int j = 0; j < BITS_IN_BYTE; j++)
        {
            tmp = noOffset;
            tmp.erase(tmp.begin(), tmp.begin() + j);
            curr = Helper::bits_to_bytes(tmp);

            if ((tmpScore = Helper::gradeMessage(curr, wordList)) > score)
            {
                score = tmpScore;
                //best = std::string(curr.begin(), curr.end());
                res = std::vector<unsigned char>(curr.begin(), curr.end());

                std::cout << i * BITS_IN_BYTE + j << ": " << Helper::getLongestSentence(curr, wordList) << std::endl;
            }

            std::cout << "Debug - iteration has ended." << std::endl;
        }
    }

    return Helper::getLongestSentence(res, wordList);
}*/



std::string Decrypt::findMessage(ParsedImage& img)
{
    std::string best, curr;
    std::vector<bool> tmp;
    std::vector<unsigned char> res;
    std::vector<std::vector<bool>> noOffset;

    std::set<std::string> wordList = Helper::loadWordList();

    for (int i = 0; i < BITS_CHECKED; i++)
        noOffset.emplace_back(Decrypt::decrypt(img, i));
    
    std::cout << "Beginning decryption..." << std::endl;
    

    for (int i = 0; i < BITS_IN_BYTE; i++)
    {
        std::map<int, std::string> words;
        for (int j = 0; j < BITS_CHECKED; j++)
        {
            tmp = std::vector<bool>(noOffset[j].begin() + i, noOffset[j].end());
            Helper::findAllWords(Helper::bits_to_bytes(tmp), wordList, words, i);
        }

        curr = Helper::getLongestSentence(words);

        if (curr.size() > best.size())
            best = curr;

        std::cout << "Completed iteration " << i << std::endl;
    }

    return best;
}

