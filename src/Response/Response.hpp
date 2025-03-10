#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <string>
#include <sstream>
#include <iostream>

#include "../Response/Response.hpp"

class Response {
private:
    std::string _status;
    std::string _headers;
    std::string _body;

public:
    Response();

    void setStatus(int code);
    void setHeader(const std::string& key, const std::string& value);
    void setBody(const std::string& body);

    std::string toString() const;
};

#endif // RESPONSE_HPP
