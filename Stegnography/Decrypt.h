#pragma once

#include <iostream>
#include <Vector>
#include <Set>

#define BITS_CHECKED 2


class ParsedImage;

class Decrypt
{
public:
	static std::vector<bool> decrypt(ParsedImage& img, const int byte = 0);
	static std::string findMessage(ParsedImage& img);
};

