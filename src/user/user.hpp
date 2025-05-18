#ifndef USER_H
#define USER_H

#include <string>
#include "../room/rooms.hpp"
#include "../utils/uuid_generator/uuid_generator.hpp"
#include "../reservation/reservations.hpp"

class User
{
private:
    std::string userId;
    std::string name;
    std::string phoneNumber;
    RoomManager roomManager; 
    ReservationManager reservationManager;

public:
    User(const std::string &name, const std::string &phone, const std::string &userId = "");
    std::string getUserId() const;
    std::string getName() const;
    std::string getPhoneNumber() const;


    void viewRoom() const;
    void makeReservation() ;
    void cancelReservation();
    
    void addRoom();
    void editRoom();
    void deleteRoom();

    static void setLastId(int id);
    static int getLastId(); 
};

#endif