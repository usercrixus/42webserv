#include "WebServSocketRunner.hpp"

WebServSocketRunner* WebServSocketRunner::instance = NULL;

WebServSocketRunner::WebServSocketRunner(int size, WebservSocket *webservSocket):
_serversSize(size)

{
	_fds = new struct pollfd[_serversSize];
    for (int i = 0; i < _serversSize; i++)
    {
        _webServerSockets[webservSocket[i].getServerFd()] = &webservSocket[i];
    }
}

WebServSocketRunner::~WebServSocketRunner()
{
	delete[] _fds;
}

void WebServSocketRunner::setupPoll()
{
    int index = 0;
    for (std::map<int, WebservSocket*>::iterator it = _webServerSockets.begin(); it != _webServerSockets.end(); ++it)
    {
        _fds[index].fd = it->first;
        _fds[index].events = POLLIN;
        index++;
    }
}

WebservSocket& WebServSocketRunner::waitConnection()
{
    int ret = poll(_fds, _serversSize, -1);
    if (ret == -1)
        throw std::runtime_error("waitConnection() error");

    for (int i = 0; i < _serversSize; i++)
    {
        if (_fds[i].revents & POLLIN)
        {
            int activeFd = _fds[i].fd;
            std::map<int, WebservSocket*>::iterator it = _webServerSockets.find(activeFd);
            if (it != _webServerSockets.end())
                return *(it->second);
            throw std::runtime_error("Unknown socket FD in poll().");
        }
    }
    throw std::runtime_error("waitConnection() called but no socket is ready.");
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

void WebServSocketRunner::handleIncomingConnection(WebservSocket &buffer)
{
    int newClient = accept(buffer.getServerFd(), NULL, NULL);
    if (newClient < 0)
        throw std::runtime_error("handleIncomingConnection() error");
    std::cout << "New client connected!" << std::endl;
    std::string requestData = readSocketData(newClient);
    if (!requestData.empty())
    {
        Request request(requestData, newClient, buffer.getId());
        IMethod* methodHandler = NULL;
        if (request.getMethod() == "GET")
            methodHandler = new MethodGet(request);
        else if (request.getMethod() == "POST")
            methodHandler = new MethodPost(request);
        else if (request.getMethod() == "DELETE")
            methodHandler = new MethodDelete(request);
        if (methodHandler)
        {
            methodHandler->handle();
            delete methodHandler;
        }
    }
    close(newClient);
}


void WebServSocketRunner::run()
{
	WebservSocket buffer;
    while (true) {
        try
        {
            buffer = waitConnection();
            handleIncomingConnection(buffer);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}

WebServSocketRunner* WebServSocketRunner::getInstance(int size, WebservSocket *webservSocket) {
	if (!instance) {
		instance = new WebServSocketRunner(size, webservSocket);
	}
	return instance;
}

void WebServSocketRunner::destroyInstance() {
	delete instance;
}