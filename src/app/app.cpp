#include <iostream>
#include <cstdlib>
#include <limits>

#include "./app.hpp"
#include "../user/user.hpp"
#include "../auth/auth.hpp"
#include "../utils/validator/validator.hpp"
#include "../utils/io_helper/io_helper.hpp"
#include "../queue/queue.hpp"
#include "../reservation/reservations.hpp"

// class ReservationQueue yang didefinisikan di queue.hpp
extern ReservationManager reservationManager;
extern ReservationQueue reservationQueue;
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

  if (std::cin.rdbuf()->in_avail() > 0)
  {
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

  if (auth.findUserByPhone(phone) == nullptr)
  {
    std::cout << "Nomor belum terdaftar silahkan mendaftar akun." << "\n"
              << "Masukkan Nama Anda: ";

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

  Auth auth;
  if (auth.loginAdmin(phone, password))
  {
    IOHelper::cls();
    std::cout << "Login admin berhasil!" << std::endl;
    IOHelper::pause();
    displayAdminMenu(auth);
  }
  else
  {
    std::cout << "Login gagal! Username atau password salah." << std::endl;
    IOHelper::pause();
  }
}

void App::displayUserMenu(Auth &auth)
{
  while (true)
  {
    IOHelper::cls();
    std::cout << "+======================================+" << std::endl;
    std::cout << "|            MENU UTAMA USER           |" << std::endl;
    std::cout << "+======================================+" << std::endl;
    std::cout << "|  1. Lihat Daftar Kamar               |" << std::endl;
    std::cout << "|  2. Lihat Riwayat Reservasi          |" << std::endl;
    std::cout << "|  3. Buat Reservasi                   |" << std::endl;
    std::cout << "|  4. Batalkan Reservasi               |" << std::endl;
    std::cout << "|  5. Lihat Antrean Reservasi          |" << std::endl;
    std::cout << "|  6. Logout                           |" << std::endl;
    std::cout << "+======================================+" << std::endl;
    std::cout << ">> Masukkan pilihan Anda (1-6): ";

    int choice;
    std::cin >> choice;

    switch (choice)
    {
    case 1:
      IOHelper::cls();
      auth.getCurrentUser()->viewRoom();
      IOHelper::pause();
      break;
    case 2:
      IOHelper::cls();
      auth.getCurrentUser()->showUserReservations();
      IOHelper::pause();
      break;
    case 3:
      IOHelper::cls();
      auth.getCurrentUser()->makeReservation();
      IOHelper::pause();
      break;
    case 4:
      IOHelper::cls();
      auth.getCurrentUser()->cancelReservation();
      IOHelper::pause();
      break;
    case 5:
      IOHelper::cls();
      reservationQueue.showQueue();
      IOHelper::pause();
      break;
    case 6:
      std::cout << "\nLogout berhasil. Sampai jumpa!\n"
                << std::endl;
      displayMainMenu(auth);
      IOHelper::pause();
      return;
    default:
      std::cout << "\nPilihan tidak valid! Silakan coba lagi.\n"
                << std::endl;
      IOHelper::pause();
      break;
    }
  }
}

void App::displayAdminMenu(Auth &auth)
{
  IOHelper::cls();
  std::cout << "+======================================+" << std::endl;
  std::cout << "|              MENU ADMIN              |" << std::endl;
  std::cout << "+======================================+" << std::endl;
  std::cout << "| 1. Lihat Daftar Kamar                |" << std::endl;
  std::cout << "| 2. Tambah Daftar Kamar               |" << std::endl;
  std::cout << "| 3. Edit Daftar Kamar                 |" << std::endl;
  std::cout << "| 4. Delete Kamar                      |" << std::endl;
  std::cout << "| 5. Lihat Semua Reservasi             |" << std::endl;
  std::cout << "| 6. Lihat Antrean Reservasi           |" << std::endl;
  std::cout << "| 7. Proses 1 Antrean Reservasi Manual |" << std::endl;
  std::cout << "| 8. Logout                            |" << std::endl;
  std::cout << "+======================================+" << std::endl;
  std::cout << ">> Masukkan pilihan Anda (1-8): ";

  int choice;
  std::cin >> choice;

  switch (choice)
  {
  case 1:
    IOHelper::cls();
    auth.getCurrentUser()->viewRoom();
    IOHelper::pause();
    break;
  case 2:
    IOHelper::cls();
    auth.getCurrentUser()->addRoom();
    IOHelper::pause();
    break;
  case 3:
    IOHelper::cls();
    auth.getCurrentUser()->editRoom();
    IOHelper::pause();
    break;
  case 4:
    IOHelper::cls();
    auth.getCurrentUser()->deleteRoom();
    IOHelper::pause();
    break;
  case 5:
    IOHelper::cls();
    auth.getCurrentUser()->showAllReservations();
    IOHelper::pause();
    break;
  case 6:
    IOHelper::cls();
    reservationQueue.showQueue();
    IOHelper::pause();
    break;
  case 7:
    IOHelper::cls();
    int roomId;
    std::cout << "Masukkan nomor kamar yang ingin diproses: ";
    std::cin >> roomId;
    reservationManager.processQueueForRoom(roomId);
    IOHelper::pause();
    break;
  case 8:
    std::cout << "Logout berhasil!" << std::endl;
    displayMainMenu(auth);
    break;
  default:
    std::cout << "Pilihan tidak valid!" << std::endl;
    IOHelper::pause();
    break;
  }

  displayAdminMenu(auth);
}
