#include "queue.hpp"

void ReservationQueue::addToQueue(const ReservationRequest& request) {
    queue.push(request);
}

ReservationRequest ReservationQueue::getNextRequest() {
    if (!queue.empty()) {
        ReservationRequest request = queue.front();
        queue.pop();
        return request;
    }
    return {}; // Return empty request if queue is empty
}

bool ReservationQueue::isEmpty() const {
    return queue.empty();
}