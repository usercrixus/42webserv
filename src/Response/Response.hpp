#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <string>
#include <sstream>
#include <iostream>
#include <ctime>
#include <iomanip>

#include "../Response/Response.hpp"

class Response {
private:
    std::string _headers;
    std::string _body;
    
    void setStatus(int statusCode);
    void setCurrentDate();
    void setServerName();
    void setConnection();
    void setContentLen();

public:
    Response();

    void setHeader(int statusCode);
    void setBody(const std::string& body);

    std::string toString() const;
};

#endif // RESPONSE_HPP
