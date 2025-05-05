#ifndef AUTH_H
#define AUTH_H

#include <string>
#include <vector>
#include "user.hpp"

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

    // Management
    bool saveUsers();
    bool loadUsers();

    // login / Regist
    bool loginOrRegister(const std::string &phone, const std::string &name = "");

    // login Admin
    bool loginAdmin(const std::string &phone, const std::string &password);

    // User management
    User *getCurrentUser() const;
    bool isUserLoggedIn() const;
    bool isAdmin() const;

    User *findUserByPhone(const std::string &phone);
};

#endif