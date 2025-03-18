#include "Request.hpp"

Request::Request(const std::string& rawRequest, int client, int serverId):
_client(client),
_serverId(serverId)
{
    parse(rawRequest);
}

void Request::parse(const std::string& rawRequest)
{
    std::istringstream requestStream(rawRequest);
    std::string line;

    // Parse request line (e.g., "GET /index.html HTTP/1.1")
    if (std::getline(requestStream, line)) {
        std::istringstream lineStream(line);
        lineStream >> _method >> _path;
    }

    // Parse headers
    while (std::getline(requestStream, line) && line != "\r") {
        size_t colonPos = line.find(':');
        if (colonPos != std::string::npos) {
            std::string key = line.substr(0, colonPos);
            std::string value = line.substr(colonPos + 1);
            _headers[key] = value;
        }
    }

    // Extract body (C++98 compatible way)
    std::stringstream bodyStream;
    bodyStream << requestStream.rdbuf();
    _body = bodyStream.str();  // Copy the entire buffer into `_body`
}

int Request::getServerId() const
{
    return _serverId;
}

std::string Request::getMethod() const
{
    return _method;
}

std::string Request::getPath() const {
    return _path;
}

std::string Request::getHeader(const std::string& key) const
{
    return _headers.count(key) ? _headers.at(key) : "";
}

std::string Request::getBody() const {
    return _body;
}

int Request::getClient() const
{
    return _client;
}
