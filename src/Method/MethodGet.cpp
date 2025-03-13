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
	std::string path = "html/" + _request.getPath();
    std::ifstream file(path.c_str());
    if (!file) {
		_response.setStatus(404);
		_response.setBody("404 Not Found");
	}
	else
	{
		std::stringstream buffer;
		buffer << file.rdbuf();
		_response.setBody(buffer.str());
	}
	send(_request.getClient(), _response.toString().c_str(), _response.toString().size(), 0);
}
