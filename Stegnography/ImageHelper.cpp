#include "ImageHelper.h"
#include <opencv2/opencv.hpp>


ParsedImage ImageHelper::getImage(const std::string& path)
{
    cv::Mat image = cv::imread(path, cv::IMREAD_COLOR);
    std::vector<std::vector<RgbTuple>*> parsedImage;

    int rows = image.rows;
    int cols = image.cols;

    for (int i = 0; i < rows; i++)
    {
        std::vector<RgbTuple> *curr = new std::vector<RgbTuple>();
        for (int j = 0; j < cols; j++)
        {
            cv::Vec3b rgb = image.at<cv::Vec3b>(i, j);

            curr->emplace_back(rgb[0], rgb[1], rgb[2]);
        }

        parsedImage.emplace_back(curr);
    }

    return parsedImage;
}
