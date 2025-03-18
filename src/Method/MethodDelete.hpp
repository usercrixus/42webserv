#ifndef METHODDELETE_HPP
#define METHODDELETE_HPP

#include "IMethod.hpp"
#include <iostream>
#include <string.h>

class MethodDelete : public IMethod {
public:
    MethodDelete(Request &request);
    ~MethodDelete();
    std::vector<std::string> getPathAndArgs();
	char **prepareArgv(const std::vector<std::string> &pathAndArgs);
	int createChildProcess(char **argv, int pipefd[2]);
	std::string readPipeOutput(int pipefd[0]);
	void handle();
};

#endif // METHODDELETE_HPP
