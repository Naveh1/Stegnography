#pragma once

#include <iostream>
#include <Vector>
#include <string>
#include <fstream>
#include <Set>
#include <Map>
#include <opencv2/opencv.hpp>


#define BITS_IN_BYTE 8
#define PUNCTUATION "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define ALLOWED_PUNCT ".,!? "
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

    static std::string getLongestSentence(const std::map<int, std::string>& words)
    {
        std::string longestWord, currWord;
        std::string temp;
        int next = 0;

        for (auto& word : words)
        {
            currWord = "";

            if (word.second == " ")
                continue;

            if (word.second == "would")
                std::cout << "..." << std::endl;

            next = word.first;

            while (words.count(next)) 
            {
                temp = words.at(next);
                currWord += temp;
                next += temp.size();

                //Checking if space
                if (!words.count(next))
                    break;

                next++;
                
                currWord += ' ';
            }

            if (currWord.size() > 5)
                std::cout << "";

            if (currWord.size() > longestWord.size())
                longestWord = currWord;
        }

        return longestWord;
    }

    static std::map<int, std::string> findAllWords(const std::vector<unsigned char>& msg, const std::set<std::string>& wordList,
        std::map<int, std::string>& words, const int offset)
    {
        int i = 0, j = 0;
        int curr = 0;
        char tmp = 0;
        std::string longest, currWord, carry;
        std::string word;
        std::string punct = ALLOWED_PUNCT;

        std::stringstream ss;
        const char ILLEGAL_CHAR = '\n';


        for (const unsigned char& a : msg)
        {
            if (isalpha(a))
                ss << a;
                //ss << (char)tolower(a);
            else if (punct.find(a) != std::string::npos)
                ss << a;
            else
                ss << ILLEGAL_CHAR;
        }


        while (!ss.eof())
        {
            j = i;
            word = ""; 

            while (!ss.eof() && (tmp = ss.get()) != ILLEGAL_CHAR)
            {
                if (i == 96703 && tmp == 'W')
                    std::cout << "." << std::endl;
                if (tmp == ' ') {
                    words[i] = (words.count(i) && words.at(i).size() > 1) ? words.at(i) : " ";
                    i++;
                    break;
                }
                else
                    word += tmp;
                i++;
            }

            if (tmp == ILLEGAL_CHAR)
                i++;

            while (stripEndOfWord(word, punct).size() > 0 && wordList.count(lower(stripEndOfWord(word, punct))) != 1)
            {
                if (stripEndOfWord(word, punct).size() > 1  && wordList.count(lower(stripEndOfWord(word.substr(0, word.size() - 1), punct))) == 1)
                    word = word.substr(0, word.size() - 1);
                else 
                {
                    j++;
                    word = word.substr(1);
                }
            }
            
            if (stripEndOfWord(word, punct).size() > 0)
                words[j] = (words.count(j) && 
                    words.at(j).size() > word.size()) ? words.at(j) : word;
        }

        return words;
    }

    static std::string lower(const std::string& str)
    {
        std::string res = str;

        for(int i = 0; i < res.size(); i++)
            if(isalpha(res[i]))
                res[i] = std::tolower(res[i]);

        return res;
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

    static std::string stripBeginningOfString(const std::string& word, const std::string& illegal)
    {
        if (word.size() && illegal.find_first_not_of(word[0]) != std::string::npos)
            return word.find_first_not_of(illegal) != std::string::npos ? word.substr(word.find_first_not_of(illegal)) : "";
        return word;
    }

    static std::string stripEndOfString(const std::string& word, const std::string& illegal)
    {
        if (word.size() && illegal.find_last_not_of(word[word.size() - 1]) != std::string::npos)
            return word.find_last_not_of(illegal) != std::string::npos ? word.substr(0, word.find_last_not_of(illegal) + 1) : "";
        return word;
    }

    static std::string stripEndOfWord(const std::string& word, const std::string& illegal)
    {
        if (word.size() && word.find_first_of(illegal) != std::string::npos)
            return word.substr(0, word.find_first_of(illegal));
        return word;
    }
};