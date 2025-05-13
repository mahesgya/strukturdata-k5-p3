#include <iostream>
#include <regex>
#include <string>
#include "phone_validator.hpp"

bool isValidPhoneNumber(const std::string& phone){
    std::regex pattern("^(08|62)[0-9]{8,11}$");
    return std::regex_match(phone, pattern);
}