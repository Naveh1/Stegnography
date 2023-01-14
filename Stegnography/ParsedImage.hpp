#pragma once


#include <iostream>
#include <Vector>

struct RgbTuple
{
	uchar Rbyte;
	uchar Gbyte;
	uchar Bbyte;
};



class ParsedImage
{
public:
	ParsedImage(std::vector<std::vector<RgbTuple>*>& parsedImage)
	{
		_parsedImage = parsedImage;
	}

	~ParsedImage()
	{
		for (auto& row : _parsedImage)
			delete row;
	}

	std::vector<RgbTuple>& operator[](const int i)
	{
		return *(_parsedImage[i]);
	}

private:
	std::vector<std::vector<RgbTuple>*> _parsedImage;
};