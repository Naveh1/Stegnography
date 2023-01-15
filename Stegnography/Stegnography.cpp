#include <iostream>
#include <string>

#include "ImageHelper.h"

enum options {ENCRYPT, DECRYPT};


int getOption()
{
    int option = 0;


    std::cout << "Please pick an option: " << std::endl;
    std::cout << ENCRYPT << " - encrypt" << std::endl;
    std::cout << DECRYPT << " - decrypt" << std::endl;
    std::cin >> option;

    if (std::cin.fail()) {
        std::cout << "Invalid input, please enter an integer." << std::endl;
        exit(0);
    }

    return option;
}


void encrypt()
{
    std::string fileName;
    std::string end = ".png";

    std::cout << "Encrypting: please enter png image file name: ";
    std::cin >> fileName;

    if (fileName.substr(fileName.find(".")) != end)
    {
        std::cout << "File isn't png file" << std::endl;
    }

    auto img = ImageHelper::getImage(fileName);
    
    img[0][0] = 0;
    ImageHelper::writeImage(fileName.substr(0, fileName.size() - end.size()) + "_hidden" + end, img);

    std::cout << "Encryptiong end." << std::endl;
}

void decrypt()
{
    std::cout << "Decrypting" << std::endl;
}

int main()
{
    int option = getOption();

    switch (option)
    {
    case ENCRYPT:
        encrypt();
        break;
    case DECRYPT:
        decrypt();
        break;
    default:
        std::cout << "Invalid option." << std::endl;
        exit(0);
    }


    return 0;
}