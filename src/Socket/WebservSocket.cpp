#include "WebservSocket.hpp"
#include "../Method/IMethod.hpp"
#include "../Method/MethodDelete.hpp"
#include "../Method/MethodGet.hpp"
#include "../Method/MethodPost.hpp"

WebservSocket::WebservSocket(): _serverFd(-1) {}

WebservSocket::~WebservSocket()
{
    if (_serverFd != -1) {
        close(_serverFd);
        std::cout << "Server socket closed." << std::endl;
    }
}

int WebservSocket::getServerFd() const
{
    return _serverFd;
}

int WebservSocket::getId() const
{
    return _id;
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



