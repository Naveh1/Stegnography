#pragma once

#include <iostream>
#include <Vector>


class ParsedImage;

class Decrypt
{
public:
	static std::vector<unsigned char> decrypt(const ParsedImage& img, const int byte = 0);
};