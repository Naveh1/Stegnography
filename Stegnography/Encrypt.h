#pragma once
#include <iostream>
class ParsedImage;

#define RGB_SIZE 3


/*
* A class to encrypt a message into a wrapped img
*/
class Encrypt
{
public:
	static void encrypt(ParsedImage& img, const std::string& msg, const int hideByte = 0);
};