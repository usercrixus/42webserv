#ifndef METHODPOST_HPP
#define METHODPOST_HPP

#include "IMethod.hpp"
#include <iostream>
#include <string.h>

class MethodPost : public IMethod {
public:
    MethodPost(Request &request);
    ~MethodPost();
    
    std::vector<std::string> getPathAndArgs();
	char **prepareArgv(const std::vector<std::string> &pathAndArgs);
	int createChildProcess(char **argv, int pipefd[2]);
	std::string readPipeOutput(int pipefd[0]);

    void handle();
};

#endif // METHODPOST_HPP
