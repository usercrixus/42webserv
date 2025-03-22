#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <string>
#include <sstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <map>

#include "../Response/Response.hpp"
#include "../Config/Data/Route.hpp"

class Response {
private:
    std::string _headers;
    std::string _body;
    
    void setStatus(int statusCode);
    void setCurrentDate();
    void setServerName();
    void setMime(std::string path);
    void setConnection();
    void setContentLen();
    void setCookies(std::map<std::string, std::string> cookies);
    void setLocation(Route &route);

public:
    Response();

    void setHeader(int statusCode, std::string path, Route &route, const std::map<std::string, std::string>& cookies = std::map<std::string, std::string>());
    void setHeader(int statusCode, std::string path, const std::map<std::string, std::string>& cookies = std::map<std::string, std::string>());
    void setBody(const std::string &body);

    std::string toString() const;
};

std::string getMime(std::string fileName);

#endif // RESPONSE_HPP
