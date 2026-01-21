#include "client_raii.hpp"

ClientSocket::ClientSocket(int client_fd) : fd(client_fd) {
    if (fd < 0) {
        throw std::runtime_error("invalid client socket");
    }
}

ClientSocket::ClientSocket(ClientSocket&& other) noexcept : fd(other.fd) {
    other.fd = -1;
}

ClientSocket& ClientSocket::operator=(ClientSocket&& other) noexcept {
    if (this != &other) {
        if (fd >= 0) {
            close(fd);
        }
        fd = other.fd;
        other.fd = -1;
    }
    return *this;
}

int ClientSocket::get_fd() const {
    return fd;
}

ClientSocket::~ClientSocket() {
    if (fd >= 0) {
        close(fd);
    }
}