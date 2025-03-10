#include "Socket.hpp"

Socket::Socket() {
    _fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_fd == -1) {
        throw std::runtime_error("Socket creation failed");
    }
}

// Destructor - Ensures socket is closed properly
Socket::~Socket() {
    if (_fd != -1) {
        close(_fd);
        std::cout << "Socket closed successfully." << std::endl;
    }
}

// Set socket options
void Socket::setOptions() {
    int opt = 1;
    if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        throw std::runtime_error("setsockopt failed");
    }
}

// Bind the socket
void Socket::bindSocket(sockaddr_in& address) {
    if (bind(_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        throw std::runtime_error("Bind failed");
    }
}

// Listen for incoming connections
void Socket::listenSocket(int backlog) {
    if (listen(_fd, backlog) < 0) {
        throw std::runtime_error("Listen failed");
    }
}

// Getter for the file descriptor
int Socket::getFd() const {
    return _fd;
}
