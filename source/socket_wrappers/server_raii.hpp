#pragma once

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include <stdexcept>

class ServerSocket {
public:
    ServerSocket();
    ServerSocket(const ServerSocket&) = delete;
    ServerSocket& operator=(const ServerSocket&) = delete;
    ServerSocket(ServerSocket&&) noexcept;
    ServerSocket& operator=(ServerSocket&&) noexcept;
    int get_fd() const;
    ~ServerSocket();
private:
    int fd = -1; // file descriptor that holds the server socket
};