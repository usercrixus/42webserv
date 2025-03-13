#ifndef METHODDELETE_HPP
#define METHODDELETE_HPP

#include "IMethod.hpp"
#include <iostream>

class MethodDelete : public IMethod {
public:
    MethodDelete(Request &request);
    ~MethodDelete();
    
    void handle();
};

#endif // METHODDELETE_HPP
