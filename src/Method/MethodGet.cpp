#include "MethodGet.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept> 

MethodGet::MethodGet(Request &request):
IMethod(request)
{
}

MethodGet::~MethodGet()
{
}

void MethodGet::handle()
{
	std::string path = Data::getInstance()->getHttp().getServers()[_request.getServerId()].getRoot() + _request.getPath();
	std::cout << path << std::endl;
	// Cgi Cgi(_request, path);
	// _response.setStatus(Cgi.getStatus());
	// _response.setBody(Cgi.getBody());
	std::ifstream file(urlDecode(path).c_str());
    if (!file) {
		_response.setStatus(404);
		_response.setBody("404 Not Found");
	}
	else
	{
		std::stringstream buffer;
		buffer << file.rdbuf();
		_response.setStatus(404);
		_response.setBody(buffer.str());
	}
	send(_request.getClient(), _response.toString().c_str(), _response.toString().size(), 0);
}
