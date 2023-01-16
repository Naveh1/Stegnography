#pragma once


#include <iostream>
#include <Vector>
#include <opencv2/opencv.hpp>


/*** A wrapper for std::vector<std::vector<cv::Vec3b>*> ***/
class ParsedImage
{
public:
	//C'tor
	ParsedImage(std::vector<std::vector<cv::Vec3b>*> parsedImage)
	{
		_parsedImage = parsedImage;
	}

	//D'tor
	~ParsedImage()
	{
		for (auto& row : _parsedImage)
			delete row;
	}

	//Operator to get the i'th row
	std::vector<cv::Vec3b>& operator[](const int i)
	{
		return *(_parsedImage[i]);
	}

	/*
	* This function returns a copy of the inner img
	* The function converts the inner vectors to be non-pointers
	* 
	* Return: the copy of the inner image
	*/
	const std::vector<std::vector<cv::Vec3b>> getImage() const
	{
		std::vector<std::vector<cv::Vec3b>> res;

		for (auto& i : _parsedImage)
			res.emplace_back(*i);

		return res;
	}

	//Getters
	int getRows() const
	{
		return _parsedImage.size();
	}

	int getCols() const
	{
		return _parsedImage[0]->size();
	}

private:
	std::vector<std::vector<cv::Vec3b>*> _parsedImage;
};