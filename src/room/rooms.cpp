#include "rooms.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>


RoomManager::RoomManager(const std::string& dataFile) : filename(dataFile) {
    loadRoomsFromCSV();
}

bool RoomManager::loadRoomsFromCSV() {
    rooms.clear(); 
    
    std::ifstream file(filename);  

    if (!file.is_open()) {
        std::cerr << "Error: Tidak dapat membuka file " << filename << std::endl;
        return false;
    }
    
    std::string line;
    while (getline(file, line)) {  
        if (line.empty()) continue;

        std::stringstream ss(line); 
        std::string id_str, type, price_str, status;

        getline(ss, id_str, ',');
        getline(ss, type, ',');
        getline(ss, price_str, ',');
        getline(ss, status, ',');
        int id = std::stoi(id_str);
        int price = std::stoi(price_str);

        rooms.push_back({id, type, price, status});
    }
    
    file.close();  
    return true;
}

bool RoomManager::saveRoomsToCSV() const {
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Tidak dapat membuka file " << filename << " untuk input data" << std::endl;
        return false;
    }
    
    for (const auto& room : rooms) {
        file << room.id << "," << room.type << "," << room.price << "," << room.status << std::endl;
    }
    
    file.close();
    return true;
}

//FEATURE FOR CUSTOMER (showAllRooms and showAvailableRooms)

void RoomManager::showAllRooms() const {
    if (rooms.empty()) {
        std::cout << "Tidak ada data kamar." << std::endl;
        return;
    }
    
    std::vector<Room> sortedRooms = rooms;
    std::sort(sortedRooms.begin(), sortedRooms.end(), [](const Room& a, const Room& b) {
        return a.price < b.price;
    });

    std::cout << "================= DAFTAR KAMAR =================" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << std::left
              << std::setw(6) << "ID"
              << std::setw(15) << "Tipe Kamar"
              << std::setw(10) << "Harga"
              << std::setw(10) << "Status" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;

    for (const auto& room : sortedRooms) {
        std::cout << std::left
                  << std::setw(6) << room.id
                  << std::setw(15) << room.type
                  << std::setw(10) << room.price
                  << std::setw(10) << room.status << std::endl;
    }

    std::cout << "------------------------------------------------" << std::endl;
}

void RoomManager::showAvailableRooms() const{
    if (rooms.empty()) {
        std::cout << "Tidak ada data kamar." << std::endl;
        return;
    }

    std::cout << "=== KAMAR TERSEDIA ===" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << "ID | Tipe Kamar | Harga" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    
    bool kamarDitemukan = false;
    
    for (const auto& room : rooms) {
        if (room.status == "tersedia") {
            std::cout << room.id << " | " << room.type << " | " << room.price << std::endl;
            kamarDitemukan = true;
        }
    }
    
    if (!kamarDitemukan) {
        std::cout << "Tidak ada kamar yang tersedia saat ini." << std::endl;
    }

    std::cout << "--------------------------------" << std::endl;
}

bool RoomManager::isRoomAvailable(int roomId) const {
      for (const auto& room : rooms) {
        if (room.id == roomId && room.status == "tersedia") {
            return true;
        }
    }
    return false;
}

bool RoomManager::isRoomExists(int roomId) const {
      for (const auto& room : rooms) {
        if (room.id == roomId) {
            return true;
        }
    }
    return false;
}

bool RoomManager::updateRoomStatus(int roomId, const std::string& status) {
    for (auto& room : rooms) {
        if (room.id == roomId) {
            room.status = status;
            saveRoomsToCSV(); 
            return true;
        }
    }
    return false;
}

Room* RoomManager::getRoomById(int roomId) {
    for (auto& room : rooms) {
        if (room.id == roomId) {
            return &room;
        }
    }
    return nullptr;
}

//FEATURE FOR ADMIN (addRoom, editRoom, and deleteRoom)

bool RoomManager::addRoom(const std::string& type, double price) {
    int newId = getNextRoomId();
    
    Room kamarBaru;
    kamarBaru.id = newId;
    kamarBaru.type = type;
    kamarBaru.price = price;
    kamarBaru.status = "tersedia";
    
    rooms.push_back(kamarBaru);
    return saveRoomsToCSV();
}

bool RoomManager::editRoom(int roomId, const std::string& type, double price) {
    for (auto& room : rooms) {
        if (room.id == roomId) {
            room.type = type;
            room.price = price;
            return saveRoomsToCSV();
        }
    }
    return false;
}

bool RoomManager::deleteRoom(int roomId) {
    for (auto it = rooms.begin(); it != rooms.end(); ++it) {
        if (it->id == roomId) {
            rooms.erase(it);
            return saveRoomsToCSV();
        }
    }
    return false;
}

int RoomManager::getNextRoomId() const {
    int maxId = 0;
    for (const auto& room : rooms) {
        if (room.id > maxId) {
            maxId = room.id;
        }
    }
    return maxId + 1;
}