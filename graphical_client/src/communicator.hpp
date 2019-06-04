#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <cstdint>
#include <string>

#define DATA_SIZE 4096

class Communicator
{
    public:
        Communicator(uint16_t port, char *hostname);
        void sendData(std::string data);
        void receiveData();

    private:
        uint16_t port;
        char *hostname;
        int sockFd;
};

#endif // COMMUNICATOR_H
