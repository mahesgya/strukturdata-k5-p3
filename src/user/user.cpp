#include "./user.hpp"
#include <iostream>

User::User(const std::string &name, const std::string &phone)
    : name(name), phoneNumber(phone), roomManager("data/rooms.csv") 
{}


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
    roomManager.showAllRooms();
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

void User::addRoom() const
{
    std::cout << "=== TAMBAH KAMAR BARU ===" << std::endl;
    std::cout << "=======================" << std::endl;
}

void User::editRoom() const
{
    std::cout << "=== EDIT KAMAR ===" << std::endl;
    std::cout << "=======================" << std::endl;
}

void User::deleteRoom() const
{
    std::cout << "=== DELETE KAMAR ===" << std::endl;
    std::cout << "=======================" << std::endl;
}