#include <iostream>
#include <fstream>
#include <sstream>

#include "./auth.hpp"

Auth::Auth()
{
    currentUser = nullptr;
    isLoggedIn = false;

    if (!loadUsersFromFile())
    {
        std::cerr << "Error: Failed to load user database." << std::endl;
    }
}

Auth::~Auth()
{
    for (auto &user : users)
    {
        delete user;
    }
    users.clear();
}

bool Auth::loadUsersFromFile()
{
    std::ifstream file(userDbPath);
    if (!file.is_open())
    {
        std::cerr << "Error: Cannot open user database file." << std::endl;
        return false;
    }

    for (auto &user : users)
    {
        delete user; 
    }
    users.clear(); 

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;

        size_t firstCommaPos = line.find(',');
        if (firstCommaPos != std::string::npos)
        {
            std::string name = line.substr(0, firstCommaPos);



            size_t secondCommaPos = line.find(',', firstCommaPos + 1);
            if (secondCommaPos != std::string::npos)
            {
                std::string phone = line.substr(firstCommaPos + 1, secondCommaPos - firstCommaPos - 1);
                std::string userId = line.substr(secondCommaPos + 1);

                User *user = new User(name, phone, userId);
                users.push_back(user);
            }
        }
    }

    file.close();
    std::cout << "User database loaded successfully." << std::endl;
    return true;
}

bool Auth::saveUsersToFile()
{
    std::ofstream file(userDbPath);
    if (!file.is_open())
    {
        std::cerr << "Error: Cannot open user database file for writing." << std::endl;
        return false;
    }

    for (auto &user : users)
    {
        if (user->getPhoneNumber() != ADMIN_PHONE)
        { 
            file << user->getName() << "," << user->getPhoneNumber() << "," << user->getUserId() << std::endl;
        }
    }

    file.close();
    std::cout << "User database saved successfully." << std::endl;
    return true;
}

bool Auth::loginOrRegister(const std::string &phone, const std::string &name)
{
    User *user = findUserByPhone(phone);

    if (user != nullptr)
    {
        currentUser = user;
        isLoggedIn = true;
        std::cout << "Selamat datang kembali, " << user->getName() << "!" << std::endl;
        return true;
    }
    else if (!name.empty())
    {
        User *newUser = new User(name, phone);
        users.push_back(newUser);
        currentUser = newUser;
        isLoggedIn = true;

        saveUsersToFile();

        std::cout << "Akun baru dibuat: " << name << " (" << phone << ")" << std::endl;
        std::cout << "User ID: " << newUser->getUserId() << std::endl;
        return true;
    }

    std::cout << "Nomor telepon " << phone << " belum terdaftar." << std::endl;
    return false;
}

bool Auth::loginAdmin(const std::string &phone, const std::string &password)
{
    if (phone == ADMIN_PHONE && password == ADMIN_PASSWORD)
    {
        currentUser = new User("Administrator", phone);
        isLoggedIn = true;
        std::cout << "Login admin berhasil!" << std::endl;
        return true;
    }
    return false;
}

User *Auth::getCurrentUser() const
{
    return currentUser;
}

bool Auth::isUserLoggedIn() const
{
    return isLoggedIn && currentUser != nullptr;
}

bool Auth::isAdmin() const
{
    return isLoggedIn && currentUser != nullptr &&
            currentUser->getPhoneNumber() == ADMIN_PHONE;
}

User *Auth::findUserByPhone(const std::string &phone)
{
    for (auto &user : users)
    {
        if (user->getPhoneNumber() == phone)
        {
            return user;
        }
    }
    return nullptr;
}
