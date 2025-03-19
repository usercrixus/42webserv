#include "MethodGet.hpp"
#include "../CGI/Cgi.hpp"
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
	std::stringstream buffer;
	std::string path = Data::getInstance()->getHttp().getServers()[_request.getServerId()].getRoot() + _request.getPath();
	std::cout << path << std::endl;
	/*
	if (path.compare(0, 4, "/cgi") == 0)
	{
		// TODO CGI
		Objectif :
		Remplir std::stringstream buffer; avec les données a renvoyer.
		// Cgi Cgi(_request, path);
		// _response.setStatus(Cgi.getStatus());
		// _response.setBody(Cgi.getBody());
		}
	else
	{
		// le reste
	}
	*/
	std::ifstream file(urlDecode(path).c_str());
    if (!file) {
		_response.setStatus(404);
		_response.setBody("404 Not Found");
	}
	else
	{
		std::ifstream file(urlDecode(path).c_str());
		if (!file) {
			_response.setStatus(404);
			_response.setBody("404 Not Found");
		}
		else
		{
			buffer << file.rdbuf();
			_response.setStatus(404);
			_response.setBody(buffer.str());
		}
		send(_request.getClient(), _response.toString().c_str(), _response.toString().size(), 0);
	}
}
