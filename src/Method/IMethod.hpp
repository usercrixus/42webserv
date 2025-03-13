#ifndef IMETHOD_HPP
#define IMETHOD_HPP

#include "../Request/Request.hpp"
#include "../Response/Response.hpp"

class IMethod {
    protected:
        Request _request;
        Response _response;

    public:
        IMethod(Request &request);
        virtual ~IMethod();
        
        virtual void handle() = 0;
};

#endif // IMETHOD_HPP
