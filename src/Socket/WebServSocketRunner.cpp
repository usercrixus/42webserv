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


std::string WebServSocketRunner::readHeaders(int socketFd)
{
    std::string headers;
    char buffer[4096];
    int bytesRead;

    while ((bytesRead = recv(socketFd, buffer, sizeof(buffer) - 1, 0)) > 0)
    {
        buffer[bytesRead] = '\0';
        headers.append(buffer, bytesRead);
        if (headers.find("\r\n\r\n") != std::string::npos)
            break;
    }
    return headers;
}

int WebServSocketRunner::extractContentLength(const std::string& headers)
{
    size_t contentLengthPos = headers.find("Content-Length:");
    if (contentLengthPos == std::string::npos)
        return 0;  // Assume no body
    size_t start = contentLengthPos + 15;
    size_t end = headers.find("\r\n", start);
    return std::atoi(headers.substr(start, end - start).c_str());
}

std::string WebServSocketRunner::readBody(int socketFd, int contentLength)
{
    std::string body;
    char buffer[4096];
    int bytesRead;

    while (body.size() < static_cast<size_t>(contentLength))
    {
        bytesRead = recv(socketFd, buffer, sizeof(buffer) - 1, 0);
        if (bytesRead <= 0) 
            break;
        buffer[bytesRead] = '\0';
        body.append(buffer, bytesRead);
    }
    return body;
}

std::string WebServSocketRunner::readSocketData(int socketFd)
{
    std::string headers = readHeaders(socketFd);
    int contentLength = extractContentLength(headers);
    std::string body = readBody(socketFd, contentLength);

    return headers + body;
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