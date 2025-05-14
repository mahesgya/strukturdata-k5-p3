#ifndef ROOMS_H
#define ROOMS_H

#include <string>
#include <vector>

struct Room {
    int id;
    std::string type;
    int price;
    std::string status;
};

class RoomManager {
private:
    std::vector<Room> rooms;
    std::string filename;

public:
    RoomManager(const std::string& dataFile);

    bool loadRoomsFromCSV();
    bool saveRoomsToCSV() const;
    
    void showAllRooms() const;
    Room* findRoomById(int id);
    
    std::vector<Room> getAvailableRooms() const;
    
    bool updateRoomStatus(int id, const std::string& newStatus);
    
    const std::vector<Room>& getAllRooms() const;
};

#endif 