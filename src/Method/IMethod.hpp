#ifndef IMETHOD_HPP
#define IMETHOD_HPP

#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../Request/Request.hpp"
#include "../Response/Response.hpp"
#include "../Config/Data/Data.hpp"

class IMethod {
    protected:
        Request _request;
        Response _response;

    public:
        IMethod(Request &request);
        virtual ~IMethod();

		std::string urlDecode(const std::string &str);

		virtual void handle() = 0;
};

#endif // IMETHOD_HPP
