#include "uuid_generator.hpp"
#include <random>
#include <chrono>
#include <sstream>

std::string generateUUID()
{
    auto now = std::chrono::system_clock::now().time_since_epoch().count();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(10000, 99999);

    std::stringstream ss;
    ss << now << dis(gen);
    return ss.str();
}