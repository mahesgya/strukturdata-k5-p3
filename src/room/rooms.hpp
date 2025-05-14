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
    void showAllRooms() const;
};

#endif 