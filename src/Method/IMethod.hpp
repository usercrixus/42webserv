#ifndef IMETHOD_HPP
#define IMETHOD_HPP

#include "../Request/Request.hpp"
#include "../Response/Response.hpp"

class IMethod {
public:
    virtual ~IMethod() {}
    virtual void handle(const Request& request, Response& response) = 0;
};

#endif // IMETHOD_HPP
