#include "MethodPost.hpp"

MethodPost::MethodPost(Request &request):
IMethod(request)
{
}

MethodPost::~MethodPost()
{
}

// Splits the URL into path and args
std::vector<std::string> MethodPost::getPathAndArgs()
{
    std::string fullPath = Data::getInstance()->getHttp().getServers()[_request.getServerId()].getRoot() + _request.getPath();
    std::vector<std::string> result;
    result.push_back(fullPath);
    result.push_back(_request.getBody());

    return result;
}


// Prepares the argv array for execve()
char** MethodPost::prepareArgv(const std::vector<std::string>& pathAndArgs)
{
    char** argv = new char*[4];
    argv[0] = strdup(pathAndArgs[0].c_str());
    argv[1] = strdup("POST");
    argv[2] = strdup(pathAndArgs[1].c_str());
    argv[3] = NULL;

    return argv;
}

// Executes the binary and captures the output
int MethodPost::createChildProcess(char** argv, int pipefd[2])
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
std::string MethodPost::readPipeOutput(int pipefd[0])
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
void MethodPost::handle()
{
    Response response;
    std::vector<std::string> pathAndArgs = getPathAndArgs();
    char** argv = prepareArgv(pathAndArgs);
    int pipefd[2];
    pipe(pipefd);
    int pid = createChildProcess(argv, pipefd);
    std::string output = readPipeOutput(pipefd);
    waitpid(pid, NULL, 0);
    response.setBody(output);
    response.setHeader(200);
    send(_request.getClient(), response.toString().c_str(), response.toString().size(), 0);
    free(argv[0]);
    free(argv[1]);
    free(argv[2]);
    delete[] argv;
}
