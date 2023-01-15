#include "Encrypt.h"
#include "ParsedImage.hpp"
#include "Helper.hpp"


/*
* This function adds the message to the binary of the file
* Img: the parsed image in a more comfertable format
* msg: the message to hide in the picture
* hideByte: the bit index which we hide in the message, 0 is for the least sifinificent bit
*/
void Encrypt::encrypt(ParsedImage& img, const std::string& msg, const int hideByte)
{
	int row = 0, col = 0;
	int tmp = 0;
	int byte = 0;
	unsigned char imgByte, msgByte;

	auto bits = Helper::msg_to_bits(msg);

	for (int i = 0; i < msg.size() * BITS_IN_BYTE; i++)
	{
		tmp = i / RGB_SIZE;
		row = tmp / img.getCols();
		col = tmp % img.getCols();

		tmp = i % RGB_SIZE;

		if (row >= img.getRows())
		{
			std::cerr << "Message is too big!" << std::endl;
			exit(0);
		}

		imgByte = img[row][col][tmp];
		//msgByte = msg[i / BITS_IN_BYTE];
		//byte = i % BITS_IN_BYTE;

		//Get the byte's most significent bit of msgByte - x = (msgByte >> (BITS_IN_BYTE - byte - 1)) & 1	- now using the bits array instead
		//Clearing hideByte's byte of imgByte - y =  imgByte &= ~(1 << hideByte);
		//Setting the hideByte's byte of imgByte to x - imgByte = (y | (x << hideByte))

		//img[row][col][tmp] = (imgByte & ~(1 << hideByte)) | (((msgByte >> (BITS_IN_BYTE - byte - 1)) & 1) << hideByte);
		img[row][col][tmp] = (imgByte & ~(1 << hideByte)) | (bits[i] << hideByte);
	}
}
