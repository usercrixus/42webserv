#include "WebservSocket.hpp"
#include "../Method/IMethod.hpp"
#include "../Method/MethodDelete.hpp"
#include "../Method/MethodGet.hpp"
#include "../Method/MethodPost.hpp"

WebservSocket::WebservSocket(): _port(-1), _serverFd(-1) {}

WebservSocket::WebservSocket(int port) : _port(port), _serverFd(-1) {}

WebservSocket::~WebservSocket()
{
    if (_serverFd != -1) {
        close(_serverFd);
        std::cout << "Server socket closed." << std::endl;
    }
}

void WebservSocket::setId(int id)
{
    _id = id;
}

void WebservSocket::setupSocket()
{
    _address.sin_family = AF_INET;
    _address.sin_addr.s_addr = INADDR_ANY;
    _address.sin_port = htons(Data::getInstance()->getHttp().getServers()[_id].getListen());
    _socket.setOptions();
    _socket.bindSocket(_address);
    _socket.listenSocket(10);
    _serverFd = _socket.getFd();
    std::cout << "Server listening on port " << Data::getInstance()->getHttp().getServers()[_id].getListen() << std::endl;
}

void WebservSocket::setupPoll()
{
    _fds[0].fd = _serverFd;
    _fds[0].events = POLLIN;
}

void WebservSocket::waitConnection()
{
    if (poll(_fds, 1, -1) == -1)
        throw std::runtime_error("waitConnection() error");
}
std::string readSocketData(int socketFd)
{
    std::string data;
    char buffer[1024];
    int bytesRead;
    
    while (data.find("\r\n\r\n") == std::string::npos 
            && (bytesRead = recv(socketFd, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytesRead] = '\0';
        data.append(buffer, bytesRead);
    }
    return data;
}


void WebservSocket::handleIncomingConnection()
{
    if (_fds[0].revents & POLLIN) {
        int newClient = accept(_serverFd, NULL, NULL);
        if (newClient < 0) {
            throw std::runtime_error("handleIncomingConnection() error");
        }
        std::cout << "New client connected!" << std::endl;
        std::string requestData = readSocketData(newClient);
        if (!requestData.empty()) {
            Request request(requestData, newClient, _id);
            IMethod *methodHandler;
            methodHandler = NULL;
            if (request.getMethod() == "GET")
                methodHandler = new MethodGet(request);
            else if (request.getMethod() == "POST")
                methodHandler = new MethodPost(request);
            else if (request.getMethod() == "DELETE")
                methodHandler = new MethodDelete(request);
            methodHandler->handle();
            delete methodHandler;
        }
        close(newClient);
    }
}

void WebservSocket::run()
{
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

