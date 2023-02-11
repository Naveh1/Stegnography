#pragma once

#include "ImageHelper.h"
#include <opencv2/opencv.hpp>

/*
* This function gets a path to an image, then wrapping it by the wrapper ParsedImage
* The function opens the image using opencv, then iterates over it and saves it in vectors, the inner vectors are pointer to avoid garbage collection.
* 
* Path: the path to the image
* Return: the wrapped image
* 
*/
ParsedImage ImageHelper::getImage(const std::string& path)
{
    //Making sure opencv doesn't change the image
    cv::Mat image = cv::imread(path, cv::IMREAD_COLOR | cv::IMREAD_UNCHANGED);
    std::vector<std::vector<cv::Vec3b>*> parsedImage;

    cv::cvtColor(image, image, cv::COLOR_BGR2RGB);

    if (image.empty()) {
        std::cerr << "Error: Could not open or find the image" << std::endl;
        exit(0);
    }

    int rows = image.rows;
    int cols = image.cols;

    //Extracting the image for wrapping
    for (int i = 0; i < rows; i++)
    {
        std::vector<cv::Vec3b> *curr = new std::vector<cv::Vec3b>();
        for (int j = 0; j < cols; j++)
        {
            cv::Vec3b rgb = image.at<cv::Vec3b>(i, j);

            curr->emplace_back(rgb[0], rgb[1], rgb[2]);
        }

        parsedImage.emplace_back(curr);
    }

    return parsedImage;
}

/*
* This function gets a path and a wrapped image, and save the image in the path
* The function creats the image in a Mat, then unwrapps the wrapped image, and save it using imwrite
* 
* path: the path to the image
* img: the wrapped image to save
*/
void ImageHelper::writeImage(const std::string& path, const ParsedImage& img)
{
    std::vector<std::vector<cv::Vec3b>> data = img.getImage();

    int rows = data.size();
    int cols = data[0].size();

    //Creating the mat for the image
    cv::Mat image(rows, cols, CV_8UC3);

    //Unwrapping the image
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            image.at<cv::Vec3b>(i, j) = data[i][j];
        }
    }

    cv::cvtColor(image, image, cv::COLOR_RGB2BGR);


    //Saving the image to file
    if (!cv::imwrite(path, image, { cv::IMWRITE_PNG_COMPRESSION, 0 }))
    {
        std::cerr << "Error writing file " << path << std::endl;
    }
}
