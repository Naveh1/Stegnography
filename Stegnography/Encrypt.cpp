#include "Encrypt.h"
#include "ParsedImage.hpp"


void Encrypt::encrypt(ParsedImage& img, const std::string& msg, const int hideByte)
{
	int row = 0, col = 0;
	int tmp = 0;
	int byte = 0;
	unsigned char imgByte, msgByte;

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
		msgByte = msg[i / BITS_IN_BYTE];
		byte = i % BITS_IN_BYTE;

		//Get the hideByte's byet of msgByte - x = (msgByte >> hideByte) & 1
		//Clearing byte's byte of imgByte - y =  imgByte &= ~(1 << byte);
		//Setting the byte's byte of imgByte to x - imgByte = (y | (x << byte))

		img[row][col][tmp] = (imgByte & ~(1 << byte)) | (((msgByte >> hideByte) & 1) << byte);
	}
}
