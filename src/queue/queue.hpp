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
    void addToQueue(const ReservationRequest& request);
    ReservationRequest getNextRequest();
    bool isEmpty() const;
};

#endif // QUEUE_HPP