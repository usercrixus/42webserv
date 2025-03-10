#include "Response.hpp"

Response::Response() : _status("HTTP/1.1 200 OK\r\n") {}

void Response::setStatus(int code) {
    switch (code) {
        case 200: _status = "HTTP/1.1 200 OK\r\n"; break;
        case 404: _status = "HTTP/1.1 404 Not Found\r\n"; break;
        case 500: _status = "HTTP/1.1 500 Internal Server Error\r\n"; break;
        default: _status = "HTTP/1.1 500 Internal Server Error\r\n";
    }
}

void Response::setHeader(const std::string& key, const std::string& value) {
    _headers += key + ": " + value + "\r\n";
}

void Response::setBody(const std::string& body) {
    _body = body;

    // C++98 compatible way to convert size_t to string
    std::stringstream ss;
    ss << _body.size();
    setHeader("Content-Length", ss.str());
}

std::string Response::toString() const {
    return _status + _headers + "\r\n" + _body;
}
