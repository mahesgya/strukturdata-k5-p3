#include <iostream>
#include <regex>
#include <string>
#include "validator.hpp"

bool isValidPhoneNumber(const std::string& phone){
    std::regex pattern("^(08|62)[0-9]{8,11}$");
    return std::regex_match(phone, pattern);
}

bool cekTahunKabisat(int tahun) {
    return (tahun % 4 == 0 && (tahun % 100 != 0 || tahun % 400 == 0));
}

bool validasiTanggal(const std::string& tanggal) {
    std::regex pola(R"(\d{2}-\d{2}-\d{4})");
    if (!std::regex_match(tanggal, pola)) {
        return false;
    }

    int hari, bulan, tahun;
    char pisah1, pisah2;

    std::istringstream streamtanggal(tanggal);
    streamtanggal >> hari >> pisah1 >> bulan >> pisah2 >> tahun;

    if (pisah1 != '-' || pisah2 != '-') return false;
    if (tahun < 1900 || tahun > 2100) return false;
    if (bulan < 1 || bulan > 12) return false;

    int hariPerBulan[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    
    if (cekTahunKabisat(tahun)) {
        hariPerBulan[1] = 29;
    }

    if (hari < 1 || hari > hariPerBulan[bulan - 1]) return false;

    return true;
}