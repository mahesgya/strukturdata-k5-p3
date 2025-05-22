#include "./user.hpp"
#include <iostream>
#include <iomanip>

#include "../utils/validator/validator.hpp"

User::User(const std::string &name, const std::string &phone, const std::string &userId)
    : name(name), phoneNumber(phone), roomManager("data/rooms.csv"), reservationManager("data/reservations.csv")
{
    if (userId.empty())
    {
        this->userId = generateUUID();
    }
    else
    {
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

void User::makeReservation()
{
    roomManager.showAllRooms();

    std::string tanggalCheckIn, tanggalCheckOut;
    int idKamar;
    bool valid = false;

    do
    {
        std::cout << "Silahkan masukkan id kamar yang ingin di pesan: " << std::endl;
        std::cin >> idKamar;

        if (!roomManager.isRoomExists(idKamar))
            std::cout << "Kamar tidak ditemukan coba pilih id kamar yang lain.";

    } while (!roomManager.isRoomExists(idKamar));

    do
    {
        std::cout << "Silahkan masukkan tanggal Check In (dd-mm-yyyy): " << std::endl;
        std::cin >> tanggalCheckIn;

        if (!validasiTanggal(tanggalCheckIn))
            std::cout << "Tanggal tidak valid gunakan format dd-mm-yyyy.";
    } while (!validasiTanggal(tanggalCheckIn));

    do
    {
        std::cout << "Silahkan masukkan tanggal Check Out (dd-mm-yyyy): " << std::endl;
        std::cin >> tanggalCheckOut;

        if (!validasiTanggal(tanggalCheckOut))
            std::cout << "Tanggal tidak valid gunakan format dd-mm-yyyy.";
    } while (!validasiTanggal(tanggalCheckOut));

    reservationManager.createReservation(getUserId(), getName(), idKamar, tanggalCheckIn, tanggalCheckOut);
}

void User::cancelReservation()
{
    std::cout << "=== Cancel Booking ===" << std::endl;
    std::cout << "====================" << std::endl;
    reservationManager.cancelReservation(getUserId());
}

void User::addRoom()
{
    std::string roomType;
    double roomPrice;

    std::cout << "Silahkan Input Data Kamar yang Diperlukan" << std::endl;
    std::cout << "===========================================" << std::endl;

    std::cout << "1. Presidential" << std::endl;
    std::cout << "2. Suite" << std::endl;
    std::cout << "3. Deluxe" << std::endl;
    std::cout << "4. Superior" << std::endl;
    std::cout << "5. Standard" << std::endl;
    std::cout << "Tipe Kamar : ";

    int choice;
    std::cin >> choice;
    switch (choice) {
    case 1:
        roomType = "Presidential";
        break;
    case 2:
        roomType = "Suite";
        break;
    case 3:
        roomType = "Deluxe";
        break;
    case 4:
        roomType = "Superior";
        break;
    case 5:
        roomType = "Standard";
        break;
    default:
        std::cout << "Pilihan tidak valid. Silahkan coba lagi." << std::endl;
    }
    std::cout << "Harga per Malam: ";
    std::cin >> roomPrice;
    std::cout << std::endl;

    if (roomManager.addRoom(roomType, roomPrice))
    {
        std::cout << "Data Kamar Baru Berhasil dibuat Dengan Rincian Sebagai Berikut: " << std::endl;
        std::cout << "Tipe Kamar: " << roomType << std::endl;
        std::cout << "Harga Kamar: " << std::fixed << std::setprecision(0) << roomPrice << std::endl;
    }
    else
    {
        std::cout << "Data Kamar Baru Gagal dibuat." << std::endl;
    }
}

void User::editRoom()
{
    viewRoom();

    int roomId;
    std::string roomType;
    double roomPrice;

    std::cout << "Silakan masukkan ID kamar yang ingin diedit: " << std::endl;
    std::cout << "ID Kamar: ";
    std::cin >> roomId;
    std::cout << std::endl;

    std::cout << "Silakan masukkan data baru yang diperlukan: " << std::endl;
    std::cout << "===========================================" << std::endl;
    
    std::cout << "1. Presidential" << std::endl;
    std::cout << "2. Suite" << std::endl;
    std::cout << "3. Deluxe" << std::endl;
    std::cout << "4. Superior" << std::endl;
    std::cout << "5. Standard" << std::endl;
    std::cout << "Tipe Kamar baru: ";

    int choice;
    std::cin >> choice;
    switch (choice) {
    case 1:
        roomType = "Presidential";
        break;
    case 2:
        roomType = "Suite";
        break;
    case 3:
        roomType = "Deluxe";
        break;
    case 4:
        roomType = "Superior";
        break;
    case 5:
        roomType = "Standard";
        break;
    default:
        std::cout << "Pilihan tidak valid. Silahkan coba lagi." << std::endl;
    }

    std::cout << "Harga per malam baru: ";
    std::cin >> roomPrice;
    std::cout << std::endl;

    if (roomManager.editRoom(roomId, roomType, roomPrice))
    {
        std::cout << "Data kamar berhasil diubah dengan rincian sebagai berikut: " << std::endl;
        std::cout << "ID Kamar: " << roomId << std::endl;
        std::cout << "Tipe Kamar: " << roomType << std::endl;
        std::cout << "Harga Kamar: " << std::fixed << std::setprecision(0) << roomPrice << std::endl;
    }
    else
    {
        std::cout << "Data kamar gagal diubah." << std::endl;
    }
}

void User::deleteRoom()
{
    viewRoom();

    int roomId;

    std::cout << "Silakan masukkan ID kamar yang ingin dihapus: " << std::endl;
    std::cout << "ID Kamar: ";
    std::cin >> roomId;
    std::cout << std::endl;

    if (roomManager.deleteRoom(roomId))
    {
        std::cout << "Data kamar berhasil dihapus: " << std::endl;
        std::cout << "ID Kamar: " << roomId << std::endl;
    }
    else
    {
        std::cout << "Data kamar gagal dihapus." << std::endl;
    }
}

void User::showUserReservations()
{
    reservationManager.showUserReservations(getUserId());
}

void User::showAllReservations()
{
    reservationManager.showAllReservations();
}