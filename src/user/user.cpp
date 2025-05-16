#include "./user.hpp"
#include <iostream>
#include <iomanip>

User::User(const std::string &name, const std::string &phone, const std::string &userId)
    : name(name), phoneNumber(phone), roomManager("data/rooms.csv")
{
    if (userId.empty()) {
        this->userId = generateUUID();
    } else {
        this->userId = userId;
    }
}

std::string User::getUserId() const
{
    return userId;
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

void User::addRoom() 
{
    std::cout << "=== TAMBAH KAMAR BARU ===" << std::endl;
    std::cout << "=======================" << std::endl << std::endl;

    std::string roomType;
    double roomPrice;

    std::cout << "Silahkan Input Data Kamar yang Diperlukan" << std::endl;
    std::cout << "Tipe Kamar: ";
    std::cin >> roomType;
    std::cout << "Harga per Malam: ";
    std::cin >> roomPrice;
    std::cout << std::endl;

    if(roomManager.addRoom(roomType, roomPrice)){
        std::cout << "Data Kamar Baru Berhasil dibuat Dengan Rincian Sebagai Berikut: " << std::endl;
        std::cout << "Tipe Kamar: " << roomType << std::endl;
        std::cout << "Harga Kamar: " << std::fixed << std::setprecision(0) << roomPrice << std::endl;
    }else{
        std::cout << "Data Kamar Baru Gagal dibuat." << std::endl;
    }
}

void User::editRoom() 
{
    std::cout << "=== EDIT KAMAR ===" << std::endl;
    std::cout << "=======================" << std::endl << std::endl;
    

    int roomId;
    std::string roomType;
    double roomPrice;
    
    std::cout << "Silakan masukkan ID kamar yang ingin diedit: " << std::endl;
    std::cout << "ID Kamar: ";
    std::cin >> roomId;
    std::cout << std::endl;

    std::cout << "Silakan masukkan data baru yang diperlukan: " << std::endl;
    std::cout << "Tipe Kamar baru: ";
    std::cin >> roomType;
    std::cout << "Harga per malam baru: ";
    std::cin >> roomPrice;
    std::cout << std::endl;

    if (roomManager.editRoom(roomId, roomType, roomPrice)) {
        std::cout << "Data kamar berhasil diubah dengan rincian sebagai berikut: " << std::endl;
        std::cout << "ID Kamar: " << roomId << std::endl;
        std::cout << "Tipe Kamar: " << roomType << std::endl;
        std::cout << "Harga Kamar: " << std::fixed << std::setprecision(0) << roomPrice << std::endl;
    } else {
        std::cout << "Data kamar gagal diubah." << std::endl;
    }
}


void User::deleteRoom() 
{
    std::cout << "=== DELETE KAMAR ===" << std::endl;
    std::cout << "=======================" << std::endl << std::endl;

    int roomId;
    
    std::cout << "Silakan masukkan ID kamar yang ingin dihapus: " << std::endl;
    std::cout << "ID Kamar: ";
    std::cin >> roomId;
    std::cout << std::endl;

    if (roomManager.deleteRoom(roomId)) {
        std::cout << "Data kamar berhasil dihapus: " << std::endl;
        std::cout << "ID Kamar: " << roomId << std::endl;
    } else {
        std::cout << "Data kamar gagal dihapus." << std::endl;
    }
}