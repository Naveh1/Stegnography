#pragma once

#include <iostream>
#include <Vector>
#include <string>
#include <fstream>
#include <Set>
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

    static int gradeMessage(const std::vector<unsigned char>& msg, const std::set<std::string>& wordList)
    {
        return getLongestSentence(msg, wordList).size();

        //Ignore the rest
        unsigned int grade = 0;
        std::string word, pWord, tmp;

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

            if (word.size() > 0 && word.find_first_of(PUNCTUATION) != std::string::npos
                && wordList.find(tmp = std::string(word, word.find_first_of(PUNCTUATION), word.find_last_of(PUNCTUATION))) != wordList.end())
            {
                grade += tmp.size() * tmp.size();     //Grade is proportional to the word size
                std::cout << tmp << std::endl;
            }
        }

        return grade;
    }


    static std::string getLongestSentence(const std::vector<unsigned char>& msg, const std::set<std::string>& wordList)
    {
        int words = 0, curr = 0;
        std::string longest, currWord;
        std::string word;
        std::string punct = ALLOWED_PUNCT;

        std::stringstream ss;
        const char ILLEGAL_CHAR = '\n';



        for (const unsigned char& a : msg)
        {
            if (isalpha(a))
                ss << (char)tolower(a);
            else if (punct.find(a) != std::string::npos)
                ss << a;
            else
                ss << ILLEGAL_CHAR;
        }


        while (ss >> word) 
        {
            //Removing leading junk incase its the first word in the sentence
            /*while (word.size() > 0 && !isalpha(word[0]))
            {
                curr = 0;
                currWord = "";
                word = word.substr(1);
            }*/

            if (word.find("would") != std::string::npos || word.find("this") != std::string::npos)
                std::cout << "Bingo!" << std::endl;

            //Removing leading unreadables
            if (word[0] == ILLEGAL_CHAR) {
                curr = 0;
                currWord = "";
                word = stripBeginningOfString(word, "" + ILLEGAL_CHAR);
            }

            //Checking if word is a word, without the punctuation and the unreadables in the end of the first word in it
            if (word.size() > 0 && wordList.find(stripEndOfWord(word, punct + ILLEGAL_CHAR)) != wordList.end())
            {
                curr++;
                currWord += " " + stripEndOfWord(word, "" + ILLEGAL_CHAR);
            }
            //Now we know this is might be the first word in the sentence, so we are trying to figure out where does it begin
            else
            {
                curr = 0;
                currWord = "";
                /*
                while (word.size() > 0 && wordList.find(stripEndOfWord(word, punct)) == wordList.end()) 
                {
                    word = word.substr(1);

                    word = stripBeginningOfString(word, "" + ILLEGAL_CHAR);
                }

                if (word.size() != 0)
                {
                    curr++;
                    currWord += " " + word;
                }*/
            }

            if (curr > words)
            {
                words = curr;
                longest = currWord;
            }

            if (word.find(ILLEGAL_CHAR) != std::string::npos) 
            {
                curr = 0;
                currWord = "";
            }
        }

        return stripBeginningOfString(stripEndOfString(longest, "" + ILLEGAL_CHAR), "" + ILLEGAL_CHAR);
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
        if (word.size() && illegal.find(word[0]) != std::string::npos)
            return word.find_first_not_of(illegal) != std::string::npos ? word.substr(word.find_first_not_of(illegal)) : "";
        return word;
    }

    static std::string stripEndOfString(const std::string& word, const std::string& illegal)
    {
        if (word.size() && illegal.find(word[word.size() - 1]) != std::string::npos)
            return word.find_last_not_of(illegal) != std::string::npos ? word.substr(0, word.find_last_not_of(illegal) + 1) : "";
        return word;
    }

    static std::string stripEndOfWord(const std::string& word, const std::string& illegal)
    {
        if (word.size() && word.find(illegal) != std::string::npos)
            return word.substr(0, word.find_first_of(illegal));
        return word;
    }
};