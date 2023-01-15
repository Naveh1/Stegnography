#pragma once

#include <iostream>

class ParsedImage;

class Decrypt
{
public:
	std::string decrypt(const ParsedImage& img, const int byte = 0);
};