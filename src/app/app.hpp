#ifndef APP_H
#define APP_H

#include "../auth/auth.hpp"

class App {
    public: 
        void run();
    private:
        void handleCustomerLogin(Auth &auth);
        void handleAdminLogin();
        void displayMainMenu(Auth &auth);
        void displayUserMenu(Auth &auth);
        void displayAdminMenu(Auth &auth);
};

#endif