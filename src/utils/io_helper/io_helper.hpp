#ifndef IO_HELPER_HPP
#define IO_HELPER_HPP

#include <string>
#include <limits>
#include <iostream>

class IOHelper{
    public: 
        static void cls();
        static void pause();
        static std::string getLineInput(const std::string &prompt, bool clearBuffer = true);
};

#endif      