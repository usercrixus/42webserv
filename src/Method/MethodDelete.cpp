#include "MethodDelete.hpp"

MethodDelete::MethodDelete(Request &request):
IMethod(request)
{
}

MethodDelete::~MethodDelete()
{
}

void MethodDelete::handle()
{
	Response response;
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
	char* argv[] = {
        strdup(path.c_str()),
		strdup("DELETE"),
        strdup(args.c_str()),
        NULL
    };

	int pipefd[2];
	pipe(pipefd);
	int pid;
	pid = fork();
	if (!pid)
	{
		close(pipefd[0]);
		dup2(STDIN_FILENO, pipefd[1]);
		if (execve(path.c_str(), argv, NULL) == -1)
		{
			free(argv[0]);
			free(argv[1]);
			free(argv[2]);
			throw std::runtime_error("Binary not found");
		}
	}
	else
	{
		close(pipefd[1]);
		waitpid(pid, NULL, 0);
		std::string output;
		ssize_t bytesRead;
		char buffer[4096];
		while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
			buffer[bytesRead] = '\0';  // Null-terminate buffer
			output += buffer;
		}
		close(pipefd[0]);
		response.setStatus(200);
		response.setBody(output);
		send(_request.getClient(), _response.toString().c_str(), _response.toString().size(), 0);
	}
}
