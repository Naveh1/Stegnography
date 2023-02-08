#include <iostream>
#include <string>

#include "ImageHelper.h"
#include "Encrypt.h"
#include "Decrypt.h"
#include "Helper.hpp"

enum options {ENCRYPT, DECRYPT, EXIT};


int getOption()
{
    int option = 0;


    std::cout << "Please pick an option: " << std::endl;
    std::cout << ENCRYPT << " - encrypt" << std::endl;
    std::cout << DECRYPT << " - decrypt" << std::endl;
    std::cout << EXIT << " - exit program" << std::endl;
    std::cin >> option;

    if (std::cin.fail()) {
        std::cout << "Invalid input, please enter an integer." << std::endl;
        exit(0);
    }

    return option;
}

/*
* This function encrypts given png image with given messsage
* The function first asks for the image and the message, then wrapping the image.
* After that, the function will encrypt the secret message in the image, and write it to a file, adding _hidden to the file name
*/
void encrypt()
{
    std::string fileName, msg;
    std::string end = ".png";

    std::cout << "Encrypting: please enter png image file name: ";
    std::cin >> fileName;

    if (fileName.find(".") == std::string::npos || fileName.substr(fileName.size() - end.size()) != end)    //Making sure the file is png
    {
        std::cout << "File isn't png file" << std::endl;
        return;
    }

    //Wrapping the image
    auto img = ImageHelper::getImage(fileName);

    std::cout << "Enter message to hide: ";
    std::cin >> msg;

    //Encrypting the message in the picture
    Encrypt::encrypt(img, msg);
    

    //Writing the image
    ImageHelper::writeImage(fileName.substr(0, fileName.size() - end.size()) + "_hidden" + end, img);       //Adding _hidden in the end of the file, before .png

    std::cout << "Encryptiong end." << std::endl << std::endl;
}

void decrypt()
{
    std::string fileName;
    //std::string end = "_hidden.png";
    std::string end = ".png";

    std::cout << "Decrypting: please enter file name: ";
    std::cin >> fileName;

    if (fileName.find(".") == std::string::npos || fileName.substr(fileName.size() - end.size()) != end)        //Making sure the file is hidden png
    {
        std::cout << "File isn't hidden png file" << std::endl;
        return;
    }

    auto img = ImageHelper::getImage(fileName);

    auto msg = Decrypt::findMessage(img);

    std::cout << "Secret message: " << msg;


    //std::cout << Helper::convertReadable(msg) << std::endl;

    std::cout << "Decryption end." << std::endl << std::endl;
}

int main()
{
    int option = 0;
    while (option != EXIT)
    {
        option = getOption();//0 FOR ENCRPYT 1 FOR DECRYPT

        switch (option)
        {
        case ENCRYPT:
            encrypt();
            break;
        case DECRYPT:
            decrypt();
            break;
        case EXIT:
            std::cout << "Goodbye." << std::endl;
            break;
        default:
            std::cout << "Invalid option." << std::endl;
        }

        std::cin.get();
    }

    return 0;
}