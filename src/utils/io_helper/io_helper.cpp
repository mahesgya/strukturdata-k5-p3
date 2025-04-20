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

void IOHelper::pause(){
    std::cout << "\nTekan Enter untuk melanjutkan...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

