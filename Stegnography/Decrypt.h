#pragma once

#include <iostream>
#include <Vector>
#include <Set>

#define BITS_CHECKED 3
#define PUNCTUATION ".,:;!?\"\'"
#define MAX_READABLE 127

class ParsedImage;

class Decrypt
{
public:
	static std::vector<bool> decrypt(ParsedImage& img, const int byte = 0);
	static std::string findMessage(ParsedImage& img);

private:
	static bool isReadable(const unsigned char ch);
	static int gradeMessage(const std::vector<unsigned char>& msg, const std::set<std::string>& wordList);
	static std::set<std::string> loadWordList();

	//static std::set<std::string> wordList;
};

