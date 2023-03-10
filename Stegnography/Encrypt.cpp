#include "Encrypt.h"
#include "ParsedImage.hpp"
#include "Helper.hpp"


/*
* This function adds the message to the binary of the file
* The function converts the message to bits, then iterates over the image and set's every hideByte's bit of every byte to the correct bit in the message
* Img: the parsed image in a more comfertable format
* msg: the message to hide in the picture
* hideByte: the bit index which we hide in the message, 0 is for the least sifinificent bit
*/
void Encrypt::encrypt(ParsedImage& img, const std::string& msg, const int hideByte)
{
	int row = 0, col = 0;
	int tmp = 0;
	int byte = 0;
	unsigned char imgByte = '\0', msgByte = '\0';

	auto bits = Helper::msg_to_bits(msg);

	for (int i = 0; i < bits.size(); i++)
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

		img[row][col][tmp] = (imgByte & ~(1 << hideByte)) | (bits[i] << hideByte);		// imgByteWithoutBit | MessageByteWithOnlyBit
	}
}
