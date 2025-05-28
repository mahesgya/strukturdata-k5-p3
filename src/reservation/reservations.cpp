#include "reservations.hpp"
#include "queue.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

// Tambahkan instance queue
ReservationQueue reservationQueue;
// Di salah satu file .cpp
ReservationManager reservationManager("data/reservations.csv");

ReservationManager::ReservationManager(const std::string &file)
    : filename(file), roomManager("data/rooms.csv")
{
    loadReservationsFromCSV();
    getReservationNextId();
    reservationQueue.loadFromFile(); 
}

void ReservationManager::getReservationNextId()
{
    nextReservationId = 1;
    for (const auto &reservation : reservations)
    {
        if (reservation.id >= nextReservationId)
        {
            nextReservationId = reservation.id + 1;
        }
    }
}

bool ReservationManager::loadReservationsFromCSV()
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: Tidak dapat membuka file " << filename << " untuk membaca data" << std::endl;
        return false;
    }

    reservations.clear();
    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string idStr, userName, roomIdStr, userId, tanggalCheckIn, tanggalCheckOut, totalHargaStr, status;

        std::getline(ss, idStr, ',');
        std::getline(ss, userName, ',');
        std::getline(ss, roomIdStr, ',');
        std::getline(ss, userId, ',');
        std::getline(ss, tanggalCheckIn, ',');
        std::getline(ss, tanggalCheckOut, ',');
        std::getline(ss, totalHargaStr, ',');
        std::getline(ss, status, ',');

        Reservation reservation;
        reservation.id = std::stoi(idStr);
        reservation.name = userName;
        reservation.roomId = std::stoi(roomIdStr);
        reservation.userId = userId;
        reservation.tanggalCheckIn = tanggalCheckIn;
        reservation.tanggalCheckOut = tanggalCheckOut;
        reservation.totalHarga = std::stoi(totalHargaStr);
        reservation.status = status;

        reservations.push_back(reservation);
    }

    file.close();
    return true;
}



bool ReservationManager::saveReservationsToCSV() const {
    std::ofstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: Tidak dapat membuka file " << filename << " untuk input data" << std::endl;
        return false;
    }

    for (const auto &reservation : reservations)
    {
        file << reservation.id << ","
             << reservation.name << ","
             << reservation.roomId << ","
             << reservation.userId << ","
             << reservation.tanggalCheckIn << ","
             << reservation.tanggalCheckOut << ","
             << reservation.totalHarga << ","
             << reservation.status << std::endl;
    }

    file.close();
    return true;
}

void ReservationManager::processQueueForRoom(int roomId) {
    if (reservationQueue.isEmpty()) {
        std::cout << "Antrean kosong.\n";
        return;
    }

    // Buat antrean baru untuk menampung request yang tidak diproses
    std::queue<ReservationRequest> tempQueue;
    bool found = false;

    while (!reservationQueue.isEmpty()) {
        ReservationRequest request = reservationQueue.getNextRequest();
        // Jika request untuk kamar yang dipilih dan kamar tersedia
        if (request.roomId == roomId && roomManager.isRoomAvailable(roomId) && !found) {
            int resId = createReservation(request.userId, request.userName, request.roomId, request.checkInDate, request.checkOutDate);
            if (resId != -1) {
                std::cout << "Reservasi berhasil diproses untuk " << request.userName << " pada kamar " << request.roomId << ".\n";
                found = true; // hanya proses satu request untuk kamar ini
            } else {
                std::cout << "Gagal memproses reservasi untuk " << request.userName << ".\n";
                tempQueue.push(request);
            }
        } else {
            tempQueue.push(request);
        }
    }

    // Kembalikan antrean yang belum diproses ke queue utama
    reservationQueue = ReservationQueue(tempQueue);
    reservationQueue.saveToFile();

    if (!found) {
        std::cout << "Tidak ada antrean untuk kamar " << roomId << " atau kamar masih penuh.\n";
    }
}

void ReservationManager::processQueue() {
    while (!reservationQueue.isEmpty()) {
        ReservationRequest request = reservationQueue.getNextRequest();
        reservationQueue.saveToFile();
        if (roomManager.isRoomAvailable(request.roomId)) {
            createReservation(request.userId, request.userName, request.roomId, request.checkInDate, request.checkOutDate);
        } else {
            break; 
        }
    }
}

int ReservationManager::createReservation(const std::string& userId,const std::string& userName, int roomId, const std::string& checkInDate, const std::string& checkOutDate) {
    Room* room = roomManager.getRoomById(roomId);
    if (!room) {
        std::cout << "Kamar dengan ID " << roomId << " tidak ditemukan." << std::endl;
        return -1;
    }

    if (!roomManager.isRoomAvailable(roomId)) {
        std::cout << "Kamar tidak tersedia untuk dipesan. Apakah anda ingin masuk ke dalam antrean?\n";
        std::cout << "1. Ya\n2. Tidak\n";
        std::cout << "Pilihan: ";
        int pilihan;
        std::cin >> pilihan;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Bersihkan buffer

        if (pilihan == 1) {
            ReservationRequest request = {userId, userName, roomId, checkInDate, checkOutDate};
            reservationQueue.addToQueue(request);
            reservationQueue.saveToFile();
            std::cout << "Anda telah masuk ke dalam antrean.\n";
        } else {
            std::cout << "Anda tidak masuk ke dalam antrean.\n";
        }
        return -1;
    }

    Reservation newReservation;
    newReservation.id = nextReservationId++;
    newReservation.name = userName;
    newReservation.roomId = roomId;
    newReservation.userId = userId;
    newReservation.tanggalCheckIn = checkInDate;
    newReservation.tanggalCheckOut = checkOutDate;
    newReservation.totalHarga = room->price;
    newReservation.status = "aktif";

    reservations.push_back(newReservation);
    roomManager.updateRoomStatus(roomId, "terisi");
    saveReservationsToCSV();

    return newReservation.id;
}

void ReservationManager::showUserReservations(const std::string &userId) const
{
    bool adaReservasi = false;
    std::cout << "=== DAFTAR RESERVASI ANDA ===" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << "ID | ID Kamar | Check In | Check Out | Harga | Status" << std::endl;
    std::cout << "--------------------------------" << std::endl;

    for (const auto &reservation : reservations)
    {
        if (reservation.userId == userId)
        {
            std::cout << reservation.id << " | " << reservation.roomId << " | " << reservation.tanggalCheckIn << " | " << reservation.tanggalCheckOut << " | " << reservation.totalHarga << " | " << reservation.status << std::endl;
            adaReservasi = true;
        }
    }

    if (!adaReservasi)
    {
        std::cout << "Anda tidak memiliki riwayat pemesanan." << std::endl;
    }
    std::cout << "-----------------------------------------------------" << std::endl;
}

void ReservationManager::showAllReservations() const
{
    if (reservations.empty())
    {
        std::cout << "Tidak ada pesanan yang tersedia." << std::endl;
        return;
    }

    std::cout << "=== DAFTAR RESERVASI ===" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << "ID | ID Kamar | Check In | Check Out | Harga | Status" << std::endl;
    std::cout << "--------------------------------" << std::endl;

    for (const auto &reservation : reservations)
    {
        std::cout << reservation.id << " | " << reservation.roomId << " | " << reservation.tanggalCheckIn << " | " << reservation.tanggalCheckOut << " | " << reservation.totalHarga << " | " << reservation.status << std::endl;
    }

    std::cout << "-----------------------------------------------------" << std::endl;
}

void ReservationManager::cancelReservation(const std::string &userId)
{
    int userReservationStack[100]; 
    int top = -1;
    for (const auto &reservation : reservations)
    {
        if (reservation.userId == userId && reservation.status == "aktif")
        {
            userReservationStack[++top] = reservation.id;
        }
    }

    if (top == -1)
    {
        std::cout << "Anda tidak memiliki reservasi aktif yang dapat dibatalkan." << std::endl;
        return;
    }

    int cancelId = userReservationStack[top];

    const Reservation *latestReservation = nullptr;
    for (const auto &reservation : reservations)
    {
        if (reservation.id == cancelId)
        {
            latestReservation = &reservation;
            break;
        }
    }
    if (latestReservation)
    {
        std::cout << "Reservasi terbaru Anda:" << std::endl;
        std::cout << "ID: " << latestReservation->id << std::endl;
        std::cout << "Kamar: " << latestReservation->roomId << std::endl;
        std::cout << "Check In: " << latestReservation->tanggalCheckIn << std::endl;
        std::cout << "Check Out: " << latestReservation->tanggalCheckOut << std::endl;
        std::cout << "Harga: " << latestReservation->totalHarga << std::endl;
        std::cout << "Status: " << latestReservation->status << std::endl;
        std::cout << "-----------------------------------------------------" << std::endl;
        char konfirmasi;
        std::cout << "Apakah Anda yakin ingin membatalkan reservasi terbaru ini? (y/n): ";
        std::cin >> konfirmasi;
        if (konfirmasi == 'y' || konfirmasi == 'Y')
        {
            if (cancelReservation(cancelId))
            {
                std::cout << "Reservasi berhasil dibatalkan." << std::endl;
            }
            else
            {
                std::cout << "Gagal membatalkan reservasi." << std::endl;
            }
        }
        else
        {
            std::cout << "Pembatalan reservasi dibatalkan." << std::endl;
        }
    }
}

bool ReservationManager::cancelReservation(int reservationId)
{
    for (auto &reservation : reservations)
    {
        if (reservation.id == reservationId && reservation.status == "aktif")
        {
            reservation.status = "dibatalkan";
            roomManager.updateRoomStatus(reservation.roomId, "tersedia");
            saveReservationsToCSV();
            return true;
        }
    }
    return false;
}
