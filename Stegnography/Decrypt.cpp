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
* A function to find hidden message in ParsedImage
* The function iterates over the different offsets and assembling the longest sentence possible from it
*
* img: A wrapped image with the secret image
*
* Return: The longest message possible
*/
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
    
    //The sentence is beginning at a random index, including in a middle of a byte, so we are trying to check each of the 8 bits
    for (int i = 0; i < BITS_IN_BYTE; i++)
    {
        std::map<int, std::string> words;

        //Each word is in one of BITS_CHECKED least significent bit
        for (int j = 0; j < BITS_CHECKED; j++)
        {
            //Applying the offset
            tmp = std::vector<bool>(noOffset[j].begin() + i, noOffset[j].end());
            Helper::findAllWords(Helper::bits_to_bytes(tmp), wordList, words, i);
        }
        //Assembling the sentence
        curr = Helper::getLongestSentence(words);

        if (curr.size() > best.size())
            best = curr;

        std::cout << "Completed iteration " << i << std::endl;
    }
    //Returning the longest sentence found
    return best;
}

