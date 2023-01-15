#pragma once
#include <iostream>
class ParsedImage;

#define RGB_SIZE 3
#define BITS_IN_BYTE 8

class Encrypt
{
public:
	static void encrypt(ParsedImage& img, const std::string& msg, const int hideByte = 0);
};