#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <string>
#include <queue>

struct ReservationRequest {
    std::string userId;
    std::string userName;
    int roomId;
    std::string checkInDate;
    std::string checkOutDate;
};

class ReservationQueue {
private:
    std::queue<ReservationRequest> queue;
public:
    ReservationQueue() = default; 
    ReservationQueue(const std::queue<ReservationRequest>& q) : queue(q) {} 

    void addToQueue(const ReservationRequest& request);
    void showQueue() const;
    ReservationRequest getNextRequest();
    bool isEmpty() const;

    void saveToFile() const;
    void loadFromFile();
};

#endif 