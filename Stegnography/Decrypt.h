#pragma once

#include <iostream>
#include <Vector>

#define BITS_CHECKED 3

class ParsedImage;

class Decrypt
{
public:
	static std::vector<bool> decrypt(ParsedImage& img, const int byte = 0);
	static std::string findMessage(ParsedImage& img);

private:
	static int gradeMessage(const std::vector<unsigned char>& msg);
};