#ifndef METHODGET_HPP
#define METHODGET_HPP

#include "IMethod.hpp"
#include "../Request/Request.hpp"

#include <iostream>

class MethodGet : public IMethod {
    private:

    public:
        MethodGet(Request &request);
        ~MethodGet();

        void handle();
};

#endif // METHODGET_HPP
