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
