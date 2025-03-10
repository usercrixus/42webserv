#ifndef METHODPOST_HPP
#define METHODPOST_HPP

#include "IMethod.hpp"
#include <iostream>

class MethodPost : public IMethod {
public:
    void handle(const Request& request, Response& response) {
        response.setBody("POST method received with body:\n" + request.getBody());
    }
};

#endif // METHODPOST_HPP
