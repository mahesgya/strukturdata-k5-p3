#include "io_helper.hpp"
#include <iostream>
#include <limits>

#ifdef _WIN32
    #include <cstdlib>
#else
    #include <unistd.h>
#endif

void IOHelper::cls(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

//Fungsi untuk menjeda

void IOHelper::pause(){
    std::cout << "\nTekan Enter untuk melanjutkan...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

//Fungsi untuk input sebuah string

std::string IOHelper::getLineInput(const std::string &prompt, bool clearBuffer) {
    std::string input;

    std::cout << prompt;
    if (clearBuffer) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::getline(std::cin, input);

    return input;
}
