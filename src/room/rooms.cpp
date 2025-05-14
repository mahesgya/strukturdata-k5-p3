#include "rooms.hpp"
#include <iostream>
#include <fstream>
#include <sstream>


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
        std::stringstream ss(line); 
        std::string id_str, type, price_str, status;

        getline(ss, id_str, ',');
        getline(ss, type, ',');
        getline(ss, price_str, ',');
        getline(ss, status, ',');
        
        try {
            int id = std::stoi(id_str);
            int price = std::stoi(price_str);

            rooms.push_back({id, type, price, status});
        } catch (const std::exception& e) {
            std::cerr << "Error: Format data tidak valid pada baris: " << line << std::endl;
        }
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

void RoomManager::showAllRooms() const {
    if (rooms.empty()) {
        std::cout << "Tidak ada kamar yang tersedia." << std::endl;
        return;
    }
    
    std::cout << "=== DAFTAR KAMAR ===" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << "ID | Tipe Kamar | Harga | Status" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    
    for (const auto& room : rooms) {
        std::cout << room.id << " | " << room.type << " | " 
                  << room.price << " | " << room.status << std::endl;
    }
    std::cout << "--------------------------------" << std::endl;
}

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