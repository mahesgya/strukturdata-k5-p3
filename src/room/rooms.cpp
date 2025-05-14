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
