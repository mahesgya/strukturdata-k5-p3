#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string name;
    std::string phoneNumber;
    
public:
    User(const std::string& name, const std::string& phone);
    
    std::string getName() const;
    std::string getPhoneNumber() const;
    
    // Method
    void viewRoom() const;
    void makeReservation() const;
    void viewReservation() const;
    void viewQueue() const;
    void cancelReservation() const;

};

#endif