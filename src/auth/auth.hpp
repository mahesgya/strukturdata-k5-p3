#ifndef AUTH_H
#define AUTH_H

#include <string>
#include <vector>
#include "../user/user.hpp"

class Auth
{
private:
    std::string userDbPath = "data/users.txt"; 

    std::vector<User *> users;
    User *currentUser;
    bool isLoggedIn;

    const std::string ADMIN_PHONE = "admin";
    const std::string ADMIN_PASSWORD = "admin123";

public:
    Auth();
    ~Auth();

    // Database Management
    bool saveUsersToFile();
    bool loadUsersFromFile();

    // User login/registration
    bool loginOrRegister(const std::string &phone, const std::string &name = "");

    // Admin login
    bool loginAdmin(const std::string &phone, const std::string &password);

    // User management
    User *getCurrentUser() const;
    bool isUserLoggedIn() const;
    bool isAdmin() const;

    // Helper methods
    User *findUserByPhone(const std::string &phone);
};

#endif