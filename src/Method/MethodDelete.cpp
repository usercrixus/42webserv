#include "MethodDelete.hpp"

MethodDelete::MethodDelete(Request &request):
IMethod(request)
{
}

MethodDelete::~MethodDelete()
{
}

bool MethodDelete::deleteFile(const std::string& path)
{
    if (std::remove(path.c_str()) == 0)
        return true;
    return false;
}

void MethodDelete::handle()
{
    Response response;
    std::string fullPath = Data::getInstance()->getHttp().getServers()[_request.getServerId()].getRoot() + _request.getPath();
    if (!deleteFile(urlDecode(fullPath)))
    {
        response.setBody("404 Not Found");
        response.setHeader(404);
    }
    else
    {
        response.setBody("204 No Content");
        response.setHeader(204);
    }
	send(_request.getClient(), _response.toString().c_str(), _response.toString().size(), 0);
}
