#include "server_raii.hpp"

ServerSocket::ServerSocket() : fd(socket(AF_INET, SOCK_STREAM, 0)) {
    if (fd < 0) {
        throw std::runtime_error("socket creation failed.");
    }

    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        close(fd);
        throw std::runtime_error("failed to bind socket");
    }
    if (listen(fd, 10) < 0) {
        close(fd);
        throw std::runtime_error("failed to listen on socket");
    }
}

ServerSocket::ServerSocket(ServerSocket&& other) noexcept : fd(other.fd) {
    other.fd = -1;
}

ServerSocket& ServerSocket::operator=(ServerSocket&& other) noexcept {
    if (this != &other) {
        if (fd >= 0) {
            close(fd);
        }
        fd = other.fd;
        other.fd = -1;
    }
    return *this;
}

int ServerSocket::get_fd() const {
    return fd;
}

ServerSocket::~ServerSocket() {
    if (fd >= 0) {
        close(fd);
    }
}