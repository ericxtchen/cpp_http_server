#pragma once

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include <stdexcept>

class ClientSocket {
public:
    explicit ClientSocket(int client_fd);
    ClientSocket(const ClientSocket&) = delete;
    ClientSocket& operator=(const ClientSocket&) = delete;
    ClientSocket(ClientSocket&& other) noexcept;
    ClientSocket& operator=(ClientSocket&& other) noexcept;
    int get_fd() const;
    ~ClientSocket();
private:
    int fd = -1;
};

