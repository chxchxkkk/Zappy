#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <cstdint>
#include <string>
#include <queue>
#include <mutex>

#define DATA_SIZE 4096

class Communicator
{
    public:
        Communicator(uint16_t port, char *hostname);
        ~Communicator() = default;
        void sendData(std::string data);
        void receiveData();
        std::string popData();
        void setRunning(bool);

    private:
        uint16_t port;
        char *hostname;
        int sockFd;
        std::queue<std::string> dataQueue;
        bool running = true;
        std::mutex dataQueueMutex;
};

#endif // COMMUNICATOR_H