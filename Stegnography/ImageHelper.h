#pragma once

#include <iostream>
#include <Vector>

#include <opencv2/opencv.hpp>


struct RgbTuple
{
	uchar Rbyte;
	uchar Gbyte;
	uchar Bbyte;
};


class ImageHelper 
{
public:
	std::vector<std::vector<RgbTuple>> getImage(const std::string& path);
	void writeImage(const std::string& path, const std::vector<std::vector<RgbTuple>>& img);		//todo
};