#include "./user.hpp"
#include <iostream>

// Constructor implementation
User::User(const std::string &name, const std::string &phone)
{
    this->name = name;
    this->phoneNumber = phone;
}

// Getter implementations
std::string User::getName() const
{
    return name;
}

std::string User::getPhoneNumber() const
{
    return phoneNumber;
}

void User::viewRoom() const
{
    std::cout << "=== Jadwal Tersedia ===" << std::endl;
    std::cout << "=======================" << std::endl;
}

void User::makeBooking() const
{
    std::cout << "=== Buat Booking ===" << std::endl;
    std::cout << "====================" << std::endl;
}

void User::cancelBooking() const 
{
    std::cout << "=== Cancel Booking ===" << std::endl;
    std::cout << "====================" << std::endl;
}