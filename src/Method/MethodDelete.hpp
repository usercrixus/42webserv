#ifndef METHODDELETE_HPP
#define METHODDELETE_HPP

#include "IMethod.hpp"
#include <iostream>

class MethodDelete : public IMethod {
public:
    void handle(const Request& request, Response& response) {
        response.setBody("DELETE method received for path: " + request.getPath());
    }
};

#endif // METHODDELETE_HPP
