#ifndef METHODGET_HPP
#define METHODGET_HPP

#include "IMethod.hpp"
#include <iostream>

class MethodGet : public IMethod {
public:
    void handle(const Request& request, Response& response) {
        if (request.getPath() == "/") {
            response.setBody("Welcome to Webserv <3 !");
        } else if (request.getPath() == "/hello") {
            response.setBody("Hello World!");
        } else {
            response.setStatus(404);
            response.setBody("404 Not Found");
        }
    }
};

#endif // METHODGET_HPP
