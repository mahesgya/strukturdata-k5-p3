#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>
#include <vector>
#include "../room/rooms.hpp"

struct Reservation {
    int id;
    int roomId;
    std::string name;
    std::string userId;
    std::string tanggalCheckIn;
    std::string tanggalCheckOut;
    double totalHarga;
    std::string status;
};

class ReservationManager{
    private:
        std::vector<Reservation> reservations;
        std::string filename;
        RoomManager roomManager;
        int nextReservationId;
        
        void getReservationNextId();
    public:
        ReservationManager(const std::string& file);
    
        bool loadReservationsFromCSV();
        bool saveReservationsToCSV() const;
        
        int createReservation(const std::string& userId, const std::string& userName, int roomId, 
                            const std::string& checkInDate, const std::string& checkOutDate);
        void cancelReservation(const std::string &userId);
        bool cancelReservation(int reservationId);

        void processQueueForRoom(int roomId);
        void processQueue();
        
        void showUserReservations(const std::string& userId) const;
        void showAllReservations() const; 
    
        std::vector<Reservation> getUserReservations(const std::string& userId) const;
        Reservation* getReservationById(int reservationId);
};

#endif