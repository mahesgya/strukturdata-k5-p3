#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>
#include <vector>
#include "../room/rooms.hpp"

struct Reservation {
    int id;
    int roomId;
    std::string userId;
    std::string tanggalCheckIn;
    std::string tanggalCheckOut;
    double totalHarga;
    std::string status;
};

class ReservationManager{

};

#endif