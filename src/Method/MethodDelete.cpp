#include "MethodDelete.hpp"
#include <iostream>
#include <vector>
#include <cstring>     // For strdup
#include <unistd.h>    // For pipe(), fork(), execve(), dup2()
#include <sys/wait.h>  // For waitpid()

MethodDelete::MethodDelete(Request &request):
IMethod(request)
{
}

MethodDelete::~MethodDelete()
{
}

// Splits the URL into path and args
std::vector<std::string> MethodDelete::getPathAndArgs()
{
    std::string path;
    std::string args;
    std::string fullPath = Data::getInstance()->getHttp().getServers()[_request.getServerId()].getRoot() + _request.getPath();
    size_t pos = fullPath.find('?');
    if (pos != std::string::npos)
    {
        path = fullPath.substr(0, pos);
        args = fullPath.substr(pos + 1);
    }
    else
    {
        path = fullPath;
        args.clear();
    }
    std::vector<std::string> result;
    result.push_back(path);
    result.push_back(args);

    return result;
}


// Prepares the argv array for execve()
char** MethodDelete::prepareArgv(const std::vector<std::string>& pathAndArgs)
{
    char** argv = new char*[4];
    argv[0] = strdup(pathAndArgs[0].c_str());
    argv[1] = strdup("DELETE");
    argv[2] = strdup(pathAndArgs[1].c_str());
    argv[3] = NULL;

    return argv;
}

// Executes the binary and captures the output
int MethodDelete::createChildProcess(char** argv, int pipefd[2])
{
    int pid = fork();
    if (pid == -1) {
        throw std::runtime_error("Fork failed");
    }
    if (pid == 0)  // Child process
    {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe
        close(pipefd[1]);               // Close write end after dup2()
        if (execve(argv[0], argv, NULL) == -1) {
            perror("execve error");
            _exit(EXIT_FAILURE);  // Important: Avoid running parent code in child
        }
    }
    return pid;
}

// Reads output from the pipe
std::string MethodDelete::readPipeOutput(int pipefd[0])
{
    close(pipefd[1]);
    std::string output;
    ssize_t bytesRead;
    char buffer[4096];
    while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytesRead] = '\0';
        output += buffer;
    }
    close(pipefd[0]);
    return output;
}

// Main handler that coordinates all the steps
void MethodDelete::handle()
{
    Response response;
    std::vector<std::string> pathAndArgs = getPathAndArgs();
    char** argv = prepareArgv(pathAndArgs);
    int pipefd[2];
    pipe(pipefd);
    int pid = createChildProcess(argv, pipefd);
    std::string output = readPipeOutput(pipefd);
    waitpid(pid, NULL, 0);
    response.setStatus(200);
    response.setBody(output);
    send(_request.getClient(), response.toString().c_str(), response.toString().size(), 0);
    free(argv[0]);
    free(argv[1]);
    free(argv[2]);
    delete[] argv;
}
