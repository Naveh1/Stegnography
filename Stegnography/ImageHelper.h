#pragma once

#include <iostream>
#include <Vector>

#include "ParsedImage.hpp"



class ImageHelper 
{
public:
	ParsedImage getImage(const std::string& path);
	void writeImage(const std::string& path, const ParsedImage& img);		//todo
};