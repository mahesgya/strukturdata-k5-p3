#include "app.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "app.hpp"
using namespace std;

void App::run(){
    int instruction;

    do{
        cout << "\n=== APLIKASI RESERVASI KAMAR HOTEL ===\n";
        cout << "1. Lihat semua kamar\n";
        cout << "2. Tambah reservasi\n";
        cout << "3. Batalkan reservasi\n";
        cout << "4. Keluar\n";
        cout << "Pilih menu: ";
        cin >> instruction;
        
        switch (instruction)
        {
        case 1:
            showRooms(); 
            break;
        case 2:
            createReservation(); 
            break;
        case 3:
            cancelReservation(); 
            break;
        case 4:
            cout << "Terimakasih Sampai Jumpa Kembali😊"; 
            break;
        default:
            cout << "Pilihan Tidak Valid.";
            break;
        }


    }while(instruction != 4);
};

struct Room {
    int id;
    string type;
    int price;
    string status;
};

vector<Room> readRoomsFromCSV(const string& filename) {
    vector<Room> rooms;  
    ifstream file(filename);  // Buka file CSV

    // Cek apakah file berhasil dibuka
    if (!file.is_open()) {
        cerr << "Error membuka file!" << endl;
        return rooms;
    }

    string line;
    while (getline(file, line)) {  // Baca setiap baris dari file
        stringstream ss(line);  // Gunakan stringstream untuk memecah baris

        string id_str, type, price_str, status;
        getline(ss, id_str, ',');  // Ambil ID
        getline(ss, type, ',');    // Ambil type
        getline(ss, price_str, ',');  // Ambil harga
        getline(ss, status, ',');  // Ambil status

        // Konversi ID dan harga dari string ke integer
        int id = stoi(id_str);
        int price = stoi(price_str);

        // Simpan data ke dalam vector rooms
        rooms.push_back({id, type, price, status});
    }

    file.close();  // Tutup file setelah selesai membaca
    return rooms;
}

// Fungsi untuk menampilkan data kamar
void App::showRooms() {
    vector<Room> rooms = readRoomsFromCSV("rooms.csv");  // Mengambil data kamar dari file CSV
    for (const auto& room : rooms) {
        cout << "ID: " << room.id << ", Type: " << room.type
             << ", Price: " << room.price << ", Status: " << room.status << endl;
    }
}


void App::createReservation() {
    std::cout << "Membuat reservasi baru...\n";
}

void App::cancelReservation() {
    std::cout << "Membatalkan reservasi...\n";
}


