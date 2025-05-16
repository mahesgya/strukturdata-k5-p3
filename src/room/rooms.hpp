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
    void showAvailableRooms() const;

    bool addRoom(const std::string& type, double price);
    bool editRoom(int roomId, const std::string& type, double price);
    bool deleteRoom(int roomId);

    int getNextRoomId() const;
};

#endif 