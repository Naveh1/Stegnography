#pragma once
#include <iostream>
class ParsedImage;

class Encrypt
{
public:
	static void encrypt(const ParsedImage& img, const std::string& msg);
};