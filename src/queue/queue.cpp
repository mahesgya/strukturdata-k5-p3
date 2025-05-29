#include "queue.hpp"
#include "queue"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

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

    std::cout << "========================= DAFTAR ANTREAN RESERVASI =========================\n";
    std::cout << "----------------------------------------------------------------------------\n";
    std::cout << std::left
              << std::setw(5) << "No"
              << std::setw(20) << "Nama"
              << std::setw(10) << "RoomID"
              << std::setw(15) << "Check-In"
              << std::setw(15) << "Check-Out" << "\n";
    std::cout << "----------------------------------------------------------------------------\n";

    std::queue<ReservationRequest> temp = queue;
    int nomor = 1;
    while (!temp.empty())
    {
        const auto &req = temp.front();
        std::cout << std::left
                  << std::setw(5) << nomor++
                  << std::setw(20) << req.userName
                  << std::setw(10) << req.roomId
                  << std::setw(15) << req.checkInDate
                  << std::setw(15) << req.checkOutDate << "\n";
        temp.pop();
    }

    std::cout << "----------------------------------------------------------------------------\n";
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
    return {}; 
}

bool ReservationQueue::isEmpty() const
{
    return queue.empty();
}