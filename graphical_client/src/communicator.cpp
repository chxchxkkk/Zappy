#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <netdb.h>
#include <iostream>
#include "communicator.hpp"

/**
 * @brief Communicator constructor, try to connect to host
 * @param port
 * @param hostname
 */
Communicator::Communicator(uint16_t port, char *hostname) : port(port), hostname(hostname)
{
    struct hostent *host = nullptr;
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);

    this->sockFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (this->sockFd == -1) {
        std::perror("socket");
        std::exit(84);
    }
    host = gethostbyname(hostname);
    std::memset(&addr, 0, len);
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;
    addr.sin_addr = *(reinterpret_cast<struct in_addr *>(host->h_addr_list[0]));
    if (h_errno != 0) {
        std::perror("gethostbyname");
        std::exit(84);
    }
    if (connect(this->sockFd, reinterpret_cast<const struct sockaddr *>(&addr), len) == -1) {
        std::perror("connect");
        std::exit(84);
    }
}

/**
 * @brief Add a line feed after data and send it over network
 * @param data
 */
void Communicator::sendData(std::string data)
{
    data += "\n";

    if (send(this->sockFd, data.c_str(), data.length(), 0) == -1) {
        std::perror("send");
        std::exit(84);
    }
}

void Communicator::receiveData()
{
    while (this->running) {
        ssize_t byteNumber;
        char buffer[DATA_SIZE];

        std::cout << "In thread" << std::endl;
        if ((byteNumber = recv(this->sockFd, buffer, DATA_SIZE, 0)) == -1) {
            std::perror("recv");
            std::exit(84);
        }
        buffer[byteNumber] = '\0';
        std::cout << "received : " << std::string(buffer) << std::endl;
        this->dataQueueMutex.lock();
        this->dataQueue.push(std::string(buffer));
        this->dataQueueMutex.unlock();
    }
}

std::string Communicator::popData()
{
    if (!this->dataQueueMutex.try_lock())
        return "";
    if (this->dataQueue.empty())
        return "";
    std::string tmp = this->dataQueue.front();
    this->dataQueue.pop();
    this->dataQueueMutex.unlock();
    return tmp;
}
