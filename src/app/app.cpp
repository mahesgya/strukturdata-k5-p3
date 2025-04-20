#include <iostream>
#include <cstdlib>
#include <limits>

#include "./app.hpp"
#include "../user/user.hpp"
#include "../auth/auth.hpp"
#include "../utils/phone_validator/phone_validator.hpp"
#include "../utils/io_helper/io_helper.hpp"

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

void App::displayMainMenu(Auth &auth)
{
  IOHelper::cls();
  std::cout << "====== Selamat Datang ======" << std::endl;
  std::cout << "1. Login Sebagai Pelanggan" << std::endl;
  std::cout << "2. Login Sebagai Admin" << std::endl;
  std::cout << "3. Exit" << std::endl;
  std::cout << std::endl
            << "Silahkan pilih menu: ";

  int choice;
  std::cin >> choice;

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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
  
  // Bersihkan buffer di awal jika perlu (jika ada input yang tersisa)
  if (std::cin.rdbuf()->in_avail() > 0) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  do
  {
    std::cout << "Masukkan nomor telepon: ";
    std::getline(std::cin, phone);

    if (!isValidPhoneNumber(phone))
    {
      std::cout << "Nomor tidak valid! Coba lagi.\n\n";
    }

  } while (!isValidPhoneNumber(phone));

  // Cek apakah user sudah terdaftar
  if (auth.findUserByPhone(phone) == nullptr)
  {
    // User belum terdaftar, minta nama dan nomor telepon
    std::cout << "Nomor belum terdaftar silahkan mendaftar akun." << "\n" << "Masukkan Nama Anda: ";

    std::string name;
    std::getline(std::cin, name);

    std::string phoneRegister;

    do
    {
      std::cout << "Masukkan nomor telepon: ";
      std::getline(std::cin, phoneRegister);

      if (!isValidPhoneNumber(phoneRegister))
      {
        std::cout << "Nomor tidak valid! Coba lagi.\n\n";
      }

    } while (!isValidPhoneNumber(phoneRegister));

    // Register dan login
    if (auth.loginOrRegister(phoneRegister, name))
    {
      IOHelper::cls();
      std::cout << "Akun baru berhasil dibuat!" << std::endl;
      IOHelper::pause();
      displayUserMenu(auth);
    }
  }
  else
  {
    // User sudah terdaftar, langsung login
    if (auth.loginOrRegister(phone))
    {
      IOHelper::cls();
      std::cout << "Login berhasil!" << std::endl;
      std::cout << "Selamat datang, " << auth.getCurrentUser()->getName() << "!" << std::endl;
      IOHelper::pause();
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
    IOHelper::cls();
    std::cout << "Login admin berhasil!" << std::endl;
    IOHelper::pause();
  }
  else
  {
    std::cout << "Login gagal! Username atau password salah." << std::endl;
    IOHelper::pause();
  }
}

void App::displayUserMenu(Auth &auth)
{
  IOHelper::cls();
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
    IOHelper::cls();
    auth.getCurrentUser()->viewRoom();
    IOHelper::pause();
    break;
  case 2:
    IOHelper::cls();
    auth.getCurrentUser()->makeBooking();
    IOHelper::pause();
    break;
  case 3:
    IOHelper::cls();
    auth.getCurrentUser()->cancelBooking();
    IOHelper::pause();
    break;
  case 4:
    std::cout << "Logout berhasil!" << std::endl;
    displayMainMenu(auth);
    break;
  default:
    std::cout << "Pilihan tidak valid!" << std::endl;
    IOHelper::pause();
    break;
  }

  displayUserMenu(auth); // Kembali ke menu utama setelah selesai
}
