#pragma once

#include <iostream>
#include <Vector>


#define BITS_IN_BYTE 8

class Helper
{
public:
	static std::vector<unsigned char> bits_to_bytes(const std::vector<bool>& bits)
	{
        unsigned char currByte = 0;
        std::vector<unsigned char> msg;

        //Converting the bits into bytes
        for (int i = 0; i < bits.size() / BITS_IN_BYTE; i++)
        {
            currByte = 0;
            for (int j = 0; j < bits.size() % BITS_IN_BYTE; j++)
                currByte |= bits[i + j] << j;                       //Building curr byte

            msg.emplace_back(currByte);
        }

        return msg;
	}

    static std::vector<bool> msg_to_bits(const std::string& msg)
    {
        std::vector<bool> bits;

        for (int i = 0; i < msg.size(); i++)
        {
            for (int j = 0; j < BITS_IN_BYTE; j++)
                bits.emplace_back((msg[i] >> (BITS_IN_BYTE - j - 1)) & 1);      //Getting the j'th most significent byte of the i'th char of msg
        }

        return bits;
    }
};