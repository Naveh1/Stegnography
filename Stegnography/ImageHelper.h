#pragma once

#include <iostream>
#include <Vector>

#include "ParsedImage.hpp"


/***Helper for image handling***/
class ImageHelper 
{
public:
	static ParsedImage getImage(const std::string& path);
	static void writeImage(const std::string& path, const ParsedImage& img);		//todo
};