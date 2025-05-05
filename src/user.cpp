#include "../headers/user.hpp"
#include <iostream>

User::User(const std::string &name, const std::string &phone)
{
    this->name = name;
    this->phoneNumber = phone;
}

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

void User::makeReservation() const
{
    std::cout << "=== Buat Reservasi ===" << std::endl;
    std::cout << "====================" << std::endl;
}

void User::viewReservation() const 
{
    std::cout << "=== Lihat Reservasi ===" << std::endl;
    std::cout << "====================" << std::endl;   
}

void User::viewQueue() const
{
    std::cout << "=== Lihat Antrian ===" << std::endl;
    std::cout << "====================" << std::endl;
}
void User::cancelReservation() const 
{
    std::cout << "=== Cancel Reservasi ===" << std::endl;
    std::cout << "====================" << std::endl;
}