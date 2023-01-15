#include <iostream>
#include <string>

#include "ImageHelper.h"
#include "Encrypt.h"
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
    std::string fileName, msg;
    std::string end = ".png";

    std::cout << "Encrypting: please enter png image file name: ";
    std::cin >> fileName;

    if (fileName.find(".") == std::string::npos || fileName.substr(fileName.size() - end.size()) != end)
    {
        std::cout << "File isn't png file" << std::endl;
        return;
    }

    auto img = ImageHelper::getImage(fileName);

    std::cout << "Enter message to hide: ";
    std::cin >> msg;

    Encrypt::encrypt(img, msg);
    
    ImageHelper::writeImage(fileName.substr(0, fileName.size() - end.size()) + "_hidden" + end, img);       //Adding _hidden in the end of the file, before .png

    std::cout << "Encryptiong end." << std::endl;
}

void decrypt()
{
    std::cout << "Decrypting" << std::endl;
}

int main()
{
    int option = getOption();//0 FOR ENCRPYT 1 FOR DECRYPT

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