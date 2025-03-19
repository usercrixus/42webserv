#include "Cgi.hpp"

void	Cgi::HandleCgiPOST(Request& request, std::string& path)
{
	(void)request;
	(void)path;
}

void	Cgi::HandleCgiGET(Request& request, std::string& path)
{
	std::string root = "CGI";
	std::string PATH_INFO = path;
	std::string SCRIPT_FILENAME = "script.php";
	std::string CGI_PATH = "/usr/bin/php";

	// if (path.find("/api") != 0)
	// {
	// 	_status = 404;
    //     _body = "404 Not Found";
    //     return;
    // }
	// if (path.find(".php") == std::string::npos) {
    //     _status = 404;
    //     _body = "404 Not Found - Not a PHP file";
    //     return;
    // }
    if (request.getMethod() != "GET")
	{
        _status = 405;
        _body = "405 Method Not Allowed";
        return;
    }
	int pipefd[2];
    if (pipe(pipefd) == -1) {
        _status = 500;
        _body = "500 Internal Server Error - Pipe failed";
        return;
    }
	std::vector<char*> argv;
    argv.push_back(const_cast<char*>(CGI_PATH.c_str()));
    argv.push_back(const_cast<char*>(SCRIPT_FILENAME.c_str()));
    argv.push_back(NULL);
	std::vector<std::string> env_strings;
    env_strings.push_back("REQUEST_METHOD=GET");
	env_strings.push_back("SCRIPT_FILENAME=script.php");
	env_strings.push_back("PATH_INFO=");
	env_strings.push_back("QUERY_STRING=name=alice");
	env_strings.push_back("CONTENT_LENGTH=0");
    env_strings.push_back("CONTENT_TYPE=");
	std::vector<char*> envp;
    for (size_t i = 0; i < env_strings.size(); ++i) {
        envp.push_back(const_cast<char*>(env_strings[i].c_str()));
    }
    envp.push_back(NULL);
	pid_t pid = fork();
    if (pid == -1) {
        _status = 500;
        _body = "500 Internal Server Error - Fork failed";
        close(pipefd[0]);
        close(pipefd[1]);
        return;
    }
	if (pid == 0)
	{
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        chdir("/home/gmorel/cercle5/webservgrp/src/CGI"); // Répertoire d'exécution
        execve(CGI_PATH.c_str(), argv.data(), envp.data());
        std::cerr << "Erreur lors de l'exécution du CGI\n";
        exit(1);
	}
	else
	{
		close(pipefd[1]);
        char buffer[1024];
        std::string response;
        ssize_t count;
        while ((count = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0)
		{
            buffer[count] = '\0';
            response += buffer;
        }
        close(pipefd[0]);
        waitpid(pid, NULL, 0);
		std::cout << "============" << response << std::endl;
        if (!response.empty()) {
            _status = 200;
            _body = response;
        } 
		else 
		{
            _status = 500;
            _body = "500 Internal Server Error - No output from CGI";
        }
	}

}

Cgi::Cgi(Request& request, std::string& path)
{
	if (request.getMethod() == "GET")
		HandleCgiGET(request, path);
	else if (request.getMethod() == "POST")
		HandleCgiPOST(request, path);
}

Cgi::~Cgi()
{

}

std::string Cgi::getBody()
{
	return _body;
}

int Cgi::getStatus()
{
	return _status;
}