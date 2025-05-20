#include "reservations.hpp"
#include "../queue/queue.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

// Tambahkan instance queue
ReservationQueue reservationQueue;

ReservationManager::ReservationManager(const std::string& file) 
    : filename(file), roomManager("data/rooms.csv") {
    loadReservationsFromCSV();
    getReservationNextId();
}

void ReservationManager::getReservationNextId() {
    nextReservationId = 1;
    for (const auto& reservation : reservations) {
        if (reservation.id >= nextReservationId) {
            nextReservationId = reservation.id + 1;
        }
    }
}

bool ReservationManager::loadReservationsFromCSV() {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Tidak dapat membuka file " << filename << " untuk membaca data" << std::endl;
        return false;
    }
    
    reservations.clear();
    std::string line;
    
    while (std::getline(file, line)) {
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
        reservation.tanggalCheckOut= tanggalCheckOut;
        reservation.totalHarga = std::stoi(totalHargaStr);
        reservation.status = status;
        
        reservations.push_back(reservation);
    }
    
    file.close();
    return true;
}

bool ReservationManager::saveReservationsToCSV() const {
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Tidak dapat membuka file " << filename << " untuk input data" << std::endl;
        return false;
    }
    
    for (const auto& reservation : reservations) {
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
void ReservationManager::processQueue() {
    while (!reservationQueue.isEmpty()) {
        ReservationRequest request = reservationQueue.getNextRequest();
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
        std::cout << "Kamar tidak tersedia untuk dipesan. Memasukkan ke dalam antrian." << std::endl;
        ReservationRequest request = {userId, userName, roomId, checkInDate, checkOutDate};
        reservationQueue.addToQueue(request);
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

bool ReservationManager::cancelReservation(int reservationId) {
    for (auto it = reservations.begin(); it != reservations.end(); ++it) {
        if (it->id == reservationId && it->status == "aktif") {
            it->status = "batal";
            
            roomManager.updateRoomStatus(it->roomId, "tersedia");
            
            saveReservationsToCSV();
            return true;
        }
    }
    
    std::cout << "Reservasi dengan ID " << reservationId << " tidak ditemukan atau sudah dibatalkan." << std::endl;
    return false;
}

void ReservationManager::showUserReservations(const std::string& userId) const {
    if(reservations.empty()){
        std::cout << "Anda tidak memiliki riwayat pemesanan." << std::endl;
        return;
    }

    std::cout << "=== DAFTAR RESERVASI ANDA ===" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << "ID | ID Kamar | Check In | Check Out | Harga | Status" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    
    for (const auto& reservation : reservations ){
        if(reservation.userId == userId)
            std:: cout << reservation.id << " | " << reservation.roomId << " | " << reservation.tanggalCheckIn << " | " << reservation.tanggalCheckOut << " | " << reservation.totalHarga << " | " << reservation.status << std::endl;
    }

    std::cout << "-----------------------------------------------------" << std::endl;

}

void ReservationManager::showAllReservations() const {
    if(reservations.empty()){
        std::cout << "Tidak ada pesanan yang tersedia." << std::endl;
        return;
    }

    std::cout << "=== DAFTAR RESERVASI ===" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << "ID | ID Kamar | Check In | Check Out | Harga | Status" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    
    for (const auto& reservation : reservations ){
        std:: cout << reservation.id << " | " << reservation.roomId << " | " << reservation.tanggalCheckIn << " | " << reservation.tanggalCheckOut << " | " << reservation.totalHarga << " | " << reservation.status << std::endl;
    }

    std::cout << "-----------------------------------------------------" << std::endl;

}

