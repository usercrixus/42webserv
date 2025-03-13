#ifndef METHODPOST_HPP
#define METHODPOST_HPP

#include "IMethod.hpp"
#include <iostream>

class MethodPost : public IMethod {
public:
    MethodPost(Request &request);
    ~MethodPost();
    
    void handle();
};

#endif // METHODPOST_HPP
