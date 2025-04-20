#include <iostream>
#include <cstdlib>
#include <limits>

#include "./app.hpp"
#include "../user/user.hpp"
#include "../auth/auth.hpp"
#include "../utils/phone_validator/phone_validator.hpp"

using namespace std;

void App::run()
{
  Auth authSystem;

  bool isRunning = true;
  while (isRunning)
  {
    displayMainMenu(authSystem);
  }
}

void App::cls()
{
  system("cls");
}

void App::pause()
{
  std::cout << "\nTekan Enter untuk melanjutkan...";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cin.get();
}

void App::displayMainMenu(Auth &auth)
{
  cls();
  std::cout << "====== Selamat Datang ======" << std::endl;
  std::cout << "1. Login Sebagai Pelanggan" << std::endl;
  std::cout << "2. Login Sebagai Admin" << std::endl;
  std::cout << "3. Exit" << std::endl;
  std::cout << std::endl
            << "Silahkan pilih menu: ";

  int choice;
  std::cin >> choice;

  switch (choice)
  {
  case 1:
    handleCustomerLogin(auth);
    break;
  case 2:
    handleAdminLogin();
    break;
  case 3:
    std::cout << "Terima kasih telah menggunakan sistem kami!" << std::endl;
    exit(0);
  default:
    std::cout << "Pilihan tidak valid. Silahkan coba lagi." << std::endl;
  }
  std::cout << "==============================================================" << std::endl;
}

void App::handleCustomerLogin(Auth &auth)
{
  std::string phone;

  do
  {
    std::cout << "Masukkan nomor telepon: ";
    std::cin.ignore();
    std::getline(cin, phone);

    if (!isValidPhoneNumber(phone))
    {
      std::cout << "Nomor tidak valid! Coba lagi.\n\n";
    }

  } while (!isValidPhoneNumber(phone));

  // Cek apakah user sudah terdaftar
  if (auth.findUserByPhone(phone) == nullptr)
  {
    // User belum terdaftar, minta nama dan nomor telfon
    std::string name;
    std::cout << "Nomor belum terdaftar silahkan mendaftar akun." << "\n"
              << "Masukkan Nama Anda: ";
    std::cin.ignore(); // Clear buffer
    std::getline(std::cin, name);

    std::string phoneRegister;

    do
    {
      std::cout << "Masukkan nomor telepon: ";
      std::cin.ignore();
      std::getline(cin, phoneRegister);

      if (!isValidPhoneNumber(phoneRegister))
      {
        std::cout << "Nomor tidak valid! Coba lagi.\n\n";
      }

    } while (!isValidPhoneNumber(phoneRegister));


    // Register dan login
    if (auth.loginOrRegister(phoneRegister, name))
    {
      cls();
      std::cout << "Akun baru berhasil dibuat!" << std::endl;
      pause();
      displayUserMenu(auth);
    }
  }
  else
  {
    // User sudah terdaftar, langsung login
    if (auth.loginOrRegister(phone))
    {
      cls();
      std::cout << "Login berhasil!" << std::endl;
      std::cout << "Selamat datang, " << auth.getCurrentUser()->getName() << "!" << std::endl;
      pause();
      displayUserMenu(auth);
    }
  }
}

void App::handleAdminLogin()
{
  std::string phone, password;
  std::cout << "Masukkan username admin: ";
  std::cin >> phone;
  std::cout << "Masukkan password: ";
  std::cin >> password;

  Auth auth; // Create auth instance or pass it as parameter
  if (auth.loginAdmin(phone, password))
  {
    cls();
    std::cout << "Login admin berhasil!" << std::endl;
    pause();
  }
  else
  {
    std::cout << "Login gagal! Username atau password salah." << std::endl;
    pause();
  }
}

void App::displayUserMenu(Auth &auth)
{
  cls();
  std::cout << "=== MENU USER ===" << std::endl;
  std::cout << "1. Lihat Jadwal Tersedia" << std::endl;
  std::cout << "2. Buat Booking" << std::endl;
  std::cout << "3. Cancel Booking" << std::endl;
  std::cout << "4. Logout" << std::endl;
  std::cout << "Pilihan: ";

  int choice;
  std::cin >> choice;

  // Process user selection
  switch (choice)
  {
  case 1:
    cls();
    auth.getCurrentUser()->viewRoom();
    pause();
    break;
  case 2:
    cls();
    auth.getCurrentUser()->makeBooking();
    pause();
    break;
  case 3:
    cls();
    auth.getCurrentUser()->cancelBooking();
    pause();
    break;
  case 4:
    std::cout << "Logout berhasil!" << std::endl;
    break;
  default:
    std::cout << "Pilihan tidak valid!" << std::endl;
    pause();
    break;
  }

  displayMainMenu(auth); // Kembali ke menu utama setelah selesai
}
