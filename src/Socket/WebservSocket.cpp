#include "WebservSocket.hpp"

WebservSocket::WebservSocket(int port) : _port(port), _serverFd(-1) {}

WebservSocket::~WebservSocket() {
    if (_serverFd != -1) {
        close(_serverFd);
        std::cout << "Server socket closed." << std::endl;
    }
}

void WebservSocket::setupSocket() {
    // Configure address
    _address.sin_family = AF_INET;
    _address.sin_addr.s_addr = INADDR_ANY;
    _address.sin_port = htons(_port);

    // Apply socket setup logic
    _socket.setOptions();
    _socket.bindSocket(_address);
    _socket.listenSocket(10);

    _serverFd = _socket.getFd();  // Store the file descriptor in _serverFd

    std::cout << "Server listening on port " << _port << std::endl;
}

void WebservSocket::setupPoll() {
    _fds[0].fd = _serverFd;
    _fds[0].events = POLLIN;
}

void WebservSocket::waitConnection()
{
    if (poll(_fds, 1, -1) == -1)
        throw std::runtime_error("waitConnection() error");
}

void WebservSocket::handleIncomingConnection() {
    if (_fds[0].revents & POLLIN) {
        int newClient = accept(_serverFd, NULL, NULL);
        if (newClient < 0) {
            throw std::runtime_error("handleIncomingConnection() error");
        } else {
            std::cout << "New client connected!" << std::endl;

            char buffer[1024];
            int bytesRead = recv(newClient, buffer, sizeof(buffer) - 1, 0);
            if (bytesRead <= 0) {
                close(newClient);
                return;
            }

            buffer[bytesRead] = '\0'; // Null-terminate the received data

            // Process the request
            Request request(buffer);
            Response response;

            // Determine the HTTP method
            IMethod* methodHandler = NULL;
            if (request.getMethod() == "GET") {
                methodHandler = new MethodGet();
            } else if (request.getMethod() == "POST") {
                methodHandler = new MethodPost();
            } else if (request.getMethod() == "DELETE") {
                methodHandler = new MethodDelete();
            } else {
                response.setStatus(405); // Method Not Allowed
                response.setBody("405 Method Not Allowed");
            }

            // Handle request with the appropriate class
            if (methodHandler) {
                methodHandler->handle(request, response);
                delete methodHandler; // Clean up the dynamically allocated object
            }

            // Send the response
            std::string fullResponse = response.toString();
            send(newClient, fullResponse.c_str(), fullResponse.size(), 0);
            close(newClient);
        }
    }
}

void WebservSocket::run() {
    while (true) {
        try
        {
            waitConnection();
            handleIncomingConnection();  // Handle new clients in its own function
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}

