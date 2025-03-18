#ifndef METHODDELETE_HPP
#define METHODDELETE_HPP

#include "IMethod.hpp"
#include <iostream>
#include <string.h>

class MethodDelete : public IMethod {
public:
    MethodDelete(Request &request);
    ~MethodDelete();
    
    void handle();
};

#endif // METHODDELETE_HPP
