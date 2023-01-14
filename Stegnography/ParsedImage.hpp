#pragma once


#include <iostream>
#include <Vector>
#include <opencv2/opencv.hpp>


/*struct RgbTuple
{
	uint8_t Rbyte;
	uint8_t Gbyte;
	uint8_t Bbyte;
};*/

/*** A wrapper for std::vector<std::vector<cv::Vec3b>*> ***/
class ParsedImage
{
public:
	ParsedImage(std::vector<std::vector<cv::Vec3b>*>& parsedImage)
	{
		_parsedImage = parsedImage;
	}

	~ParsedImage()
	{
		for (auto& row : _parsedImage)
			delete row;
	}

	std::vector<cv::Vec3b>& operator[](const int i)
	{
		return *(_parsedImage[i]);
	}

	const std::vector<std::vector<cv::Vec3b>>& getImage() const
	{
		std::vector<std::vector<cv::Vec3b>> res;

		for (auto& i : _parsedImage)
			res.emplace_back(*i);

		return res;
	}

private:
	std::vector<std::vector<cv::Vec3b>*> _parsedImage;
};