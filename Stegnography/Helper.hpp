#pragma once

#include <iostream>
#include <Vector>
#include <string>
#include <fstream>
#include <Set>
#include <opencv2/opencv.hpp>


#define BITS_IN_BYTE 8
#define PUNCTUATION ".,:;!?\"\'"
#define MAX_READABLE 127

class Helper
{
public:
	static std::vector<unsigned char> bits_to_bytes(const std::vector<bool>& bits, const int offset = 0)
	{
        unsigned char currByte = 0;
        std::vector<unsigned char> msg;

        //Converting the bits into bytes
        for (int i = offset; i < bits.size() / BITS_IN_BYTE; i++)
        {
            currByte = 0;
            for (int j = 0; j < BITS_IN_BYTE; j++)
            {
                currByte |= bits[i * BITS_IN_BYTE + j] << (BITS_IN_BYTE - j - 1);                       //Building curr byte
            }

            msg.emplace_back(currByte);
        }

        return msg;
	}

    static std::vector<bool> msg_to_bits(const std::string& msg)
    {
        std::vector<bool> bits;

        for (int i = 0; i < msg.size(); i++)
        {
            for (int j = 0; j < BITS_IN_BYTE; j++)
                bits.emplace_back((msg[i] >> (BITS_IN_BYTE - j - 1)) & 1);      //Getting the j'th most significent byte of the i'th char of msg
        }

        /*for (int i = 0; i < BITS_IN_BYTE; i++)
            bits.emplace_back(0);                   //Adding null terminator byte in the end of the message*/

        return bits;
    }



    static bool isReadable(const unsigned char ch)
    {
        return ch <= MAX_READABLE;
    }

    static int gradeMessage(const std::vector<unsigned char>& msg, const std::set<std::string>& wordList)
    {
        unsigned int grade = 0;
        std::string word, pWord;

        std::stringstream ss;
        ss.str(std::string(msg.begin(), msg.end()));

        while (!ss.eof())
        {
            word = "";
            ss >> pWord;
            if (pWord.empty())
                continue;

            for (const char ch : pWord)
            {
                if (isReadable(ch))
                    word += ch;
                else
                    break;
            }

            if (word.size() > 0 && word.find_first_not_of(PUNCTUATION) != std::string::npos
                && wordList.find(std::string(word, word.find_first_not_of(PUNCTUATION), word.find_last_not_of(PUNCTUATION))) != wordList.end())
                grade += word.size() * word.size();     //Grade is Proportional to the word size
        }

        return grade;
    }

    static std::set<std::string> loadWordList()
    {
        std::set<std::string> wordList;
        if (wordList.size() == 0)
        {
            std::ifstream words("words.txt");
            std::string curr;

            while (std::getline(words, curr))
                wordList.insert(curr);
        }

        return wordList;
    }

    static std::string convertReadable(const std::string& str)
    {
        std::string res;

        for (const char ch : str)
            if(Helper::isReadable(ch))
                res += ch;
        return res;
    }
};