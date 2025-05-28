#include "queue.hpp"
#include "queue"
#include <fstream>
#include <sstream>
#include <iostream>

const std::string QUEUE_FILE_PATH = "data/queue.csv";

void ReservationQueue::saveToFile() const
{
    std::ofstream file(QUEUE_FILE_PATH);
    std::queue<ReservationRequest> temp = queue;
    while (!temp.empty())
    {
        const auto &req = temp.front();
        file << req.userId << "," << req.userName << "," << req.roomId << "," << req.checkInDate << "," << req.checkOutDate << "\n";
        temp.pop();
    }
}

void ReservationQueue::showQueue() const
{
    if (queue.empty())
    {
        std::cout << "Antrean kosong.\n";
        return;
    }
    std::cout << "Daftar antrean reservasi:\n";
    std::queue<ReservationRequest> temp = queue;
    int nomor = 1;
    while (!temp.empty())
    {
        const auto &req = temp.front();
        std::cout << nomor++ << ". "
                << "  Nama: " << req.userName
                << ", RoomID: " << req.roomId
                << ", Check-In: " << req.checkInDate
                << ", Check-Out: " << req.checkOutDate
                << "\n";
        temp.pop();
    }
}

void ReservationQueue::loadFromFile()
{
    queue = std::queue<ReservationRequest>();
    std::ifstream file(QUEUE_FILE_PATH);
    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        std::stringstream ss(line);
        ReservationRequest req;

            std::getline(ss, req.userId, ',');
            std::getline(ss, req.userName, ',');
            std::string roomIdStr;
            std::getline(ss, roomIdStr, ',');
            req.roomId = std::stoi(roomIdStr);
            std::getline(ss, req.checkInDate, ',');
            std::getline(ss, req.checkOutDate, ',');
            queue.push(req);

    }
}

void ReservationQueue::addToQueue(const ReservationRequest &request)
{
    queue.push(request);
}

ReservationRequest ReservationQueue::getNextRequest()
{
    if (!queue.empty())
    {
        ReservationRequest request = queue.front();
        queue.pop();
        return request;
    }
    return {}; // Return empty request if queue is empty
}

bool ReservationQueue::isEmpty() const
{
    return queue.empty();
}