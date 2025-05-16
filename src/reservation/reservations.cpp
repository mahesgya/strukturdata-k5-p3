#include "reservations.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

ReservationManager::ReservationManager(const std::string& file, RoomManager& rm) 
    : filename(file), roomManager(rm), nextReservationId(1) {
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
        std::string idStr, roomIdStr, userId, tanggalCheckIn, tanggalCheckOut, totalHargaStr, status;
        
        std::getline(ss, idStr, ',');
        std::getline(ss, roomIdStr, ',');
        std::getline(ss, userId, ',');
        std::getline(ss, tanggalCheckIn, ',');
        std::getline(ss, tanggalCheckOut, ',');
        std::getline(ss, totalHargaStr, ',');
        std::getline(ss, status, ',');
        
        Reservation reservation;
        reservation.id = std::stoi(idStr);
        reservation.roomId = std::stoi(roomIdStr);
        reservation.userId = userId;
        reservation.tanggalCheckIn = tanggalCheckIn;
        reservation.tanggalCheckOut= tanggalCheckOut;
        reservation.totalHarga = std::stod(totalHargaStr);
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