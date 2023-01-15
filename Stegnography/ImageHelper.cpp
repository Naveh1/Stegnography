#include "ImageHelper.h"
#include <opencv2/opencv.hpp>


ParsedImage ImageHelper::getImage(const std::string& path)
{
    cv::Mat image = cv::imread(path, cv::IMREAD_COLOR);
    std::vector<std::vector<cv::Vec3b>*> parsedImage;

    if (image.empty()) {
        std::cerr << "Error: Could not open or find the image" << std::endl;
        exit(0);
    }

    int rows = image.rows;
    int cols = image.cols;

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

void ImageHelper::writeImage(const std::string& path, const ParsedImage& img)
{
    std::vector<std::vector<cv::Vec3b>> data = img.getImage();

    int rows = data.size();
    int cols = data[0].size();

    cv::Mat image(rows, cols, CV_8UC3);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            image.at<cv::Vec3b>(i, j) = data[i][j];
        }
    }

    if (!cv::imwrite(path, image))
    {
        std::cerr << "Error writing file " << path << std::endl;
    }
}
