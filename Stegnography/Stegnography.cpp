#include <iostream>
#include <string>

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
    std::cout << "Encrypting" << std::endl;
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