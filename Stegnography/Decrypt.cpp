#include "Decrypt.h"
#include "Encrypt.h"
#include "Helper.hpp"
#include "ParsedImage.hpp"

#include <fstream>
#include <string>
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

    for (int i = 0; i < BITS_CHECKED; i++)
    {
        curr = Helper::bits_to_bytes(Decrypt::decrypt(img, i));

        if ((tmpScore = gradeMessage(curr)) > score)
        {
            score = tmpScore;
            best = std::string(curr.begin(), curr.end());
        }
    }

    return best;
}

bool Decrypt::isReadable(const unsigned char ch)
{
    return ch <= MAX_READABLE;
}

int Decrypt::gradeMessage(const std::vector<unsigned char>& msg)
{
    unsigned int grade = 0;
    std::string word;
    

    loadWordList();

    std::stringstream ss;
    ss.str(std::string(msg.begin(), msg.end()));

    while (!ss.eof())
    {
        ss >> word;
        if (word.empty())
            continue;

        if (wordList.find(std::string(word, word.find_first_not_of(PUNCTUATION), word.find_last_not_of(PUNCTUATION))) != wordList.end())
            grade += word.size() * word.size();     //Grade is Proportional to the word size
    }

    return grade;
}

void Decrypt::loadWordList()
{
    if (wordList.size() == 0)
    {
        std::ifstream words("words.txt");
        std::string curr;

        while (std::getline(words, curr))
            wordList.insert(curr);
    }
}
