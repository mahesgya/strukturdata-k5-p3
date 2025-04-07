#include "app.hpp"
#include <iostream>
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

//Hanya Contoh Dulu
void App::showRooms() {
    std::cout << "Menampilkan daftar kamar...\n";
}

void App::createReservation() {
    std::cout << "Membuat reservasi baru...\n";
}

void App::cancelReservation() {
    std::cout << "Membatalkan reservasi...\n";
}


