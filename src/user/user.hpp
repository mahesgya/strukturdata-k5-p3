#ifndef USER_H
#define USER_H

#include <string>
#include "../room/rooms.hpp"

class User
{
private:
    std::string userId;
    std::string name;
    std::string phoneNumber;
    RoomManager roomManager; 

    static int lastId;
public:
    User(const std::string &name, const std::string &phone);
    User(const std::string &userId, const std::string &name, const std::string &phone);

    std::string getUserId() const;
    std::string getName() const;
    std::string getPhoneNumber() const;


    void viewRoom() const;
    void makeBooking() const;
    void cancelBooking() const;
    
    void addRoom();
    void editRoom();
    void deleteRoom();

    static void setLastId(int id);
    static int getLastId(); 
};

#endif