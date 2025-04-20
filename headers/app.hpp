#ifndef APP_HPP
#define APP_HPP

#include "auth.hpp"

class App {
    public: 
        void run();
    private:
    void handleCustomerLogin(Auth &auth);
    void handleAdminLogin();
    void displayMainMenu(Auth &auth);
    void displayUserMenu(Auth &auth);
    void cls();
    void pause();
};

#endif