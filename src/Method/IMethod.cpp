/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMethod.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:37:59 by achaisne          #+#    #+#             */
/*   Updated: 2025/03/22 17:42:40 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IMethod.hpp"
#include "MethodGet.hpp"

IMethod::IMethod(Request &request):
_request(request)
{
}

IMethod::~IMethod()
{
}

bool IMethod::isMethodAllowed(std::string method)
{
	int size = Data::getInstance()->getHttp().getServers()[_request.getServerId()].getRoutes().size();
	for (int i = 0; i < size; i++)
	{
		std::string location = Data::getInstance()->getHttp().getServers()[_request.getServerId()].getRoutes()[i].getLocation();
		if (location.compare(0, location.length(), _request.getPath()) == 0)
		{
			std::vector<std::string> allowedMethod = Data::getInstance()->getHttp().getServers()[_request.getServerId()].getRoutes()[i].getMethods().getAllowedMethods();

			if (std::find(allowedMethod.begin(), allowedMethod.end(), method) != allowedMethod.end())
				return true;
			else
				return false;
		}
	}
    return true;
}

bool IMethod::isListingAllowed()
{
	int size = Data::getInstance()->getHttp().getServers()[_request.getServerId()].getRoutes().size();
	for (int i = 0; i < size; i++)
	{
		std::string location = Data::getInstance()->getHttp().getServers()[_request.getServerId()].getRoutes()[i].getLocation();
		if (location.compare(0, location.length(), _request.getPath()) == 0)
			return (Data::getInstance()->getHttp().getServers()[_request.getServerId()].getRoutes()[i].getAutoIndex());
	}
    return true;
}

bool IMethod::isDirectory(const std::string &path)
{
    struct stat statbuf;
    if (stat(path.c_str(), &statbuf) != 0) {
        return false;
    }
    return S_ISDIR(statbuf.st_mode);
}

std::string IMethod::getFinalPath()
{
	std::string path;

	if (_request.getPath().compare("/") == 0)
		path = Data::getInstance()->getHttp().getServers()[_request.getServerId()].getIndex()[0].getRelativePath();
	else
		path = Data::getInstance()->getHttp().getServers()[_request.getServerId()].getRoot() + _request.getPath();
	path = urlDecode(path);

    int routesSize = Data::getInstance()->getHttp().getServers()[_request.getServerId()].getRoutes().size();
    int i = 0;
    while (i < routesSize)
    {
        std::string buffer = Data::getInstance()->getHttp().getServers()[_request.getServerId()].getRoutes()[i].getLocation();
        if (path.find(buffer) != std::string::npos)
            path.replace(path.find(buffer), buffer.size(), Data::getInstance()->getHttp().getServers()[_request.getServerId()].getRoutes()[i].getRoot());
        i++;
    }
    return path;
}

Route *IMethod::getRoute()
{
	int size = Data::getInstance()->getHttp().getServers()[_request.getServerId()].getRoutes().size();
	for (int i = 0; i < size; i++)
	{
		std::string location = Data::getInstance()->getHttp().getServers()[_request.getServerId()].getRoutes()[i].getLocation();
		if (location.compare(0, location.length(), _request.getPath()) == 0)
            return &Data::getInstance()->getHttp().getServers()[_request.getServerId()].getRoutes()[i];
    }
    return NULL;
}

std::string IMethod::getPageError(int error)
{
    std::map<int, File> errorFiles = Data::getInstance()->getHttp().getErrorFiles();
    std::map<int, File>::const_iterator it = errorFiles.find(error);
    std::stringstream buffer;
    if (it != errorFiles.end())
    {
        std::string path = it->second.getRelativePath();
        std::ifstream file(path.c_str());
        buffer << file.rdbuf();
        std::cout << "File Path: " << path << std::endl;
    }
    else
    {
        std::cerr << "Error file not found!" << std::endl;
    }
    return buffer.str();
}

std::string IMethod::urlDecode(const std::string &str)
{
    std::string decoded;
    for (size_t i = 0; i < str.length(); ++i)
	{
        if (str[i] == '%' && i + 2 < str.length())
		{
            decoded.push_back(static_cast<char>(std::strtol(str.substr(i + 1, 2).c_str(), NULL, 16)));
            i += 2;
        } else if (str[i] == '+') {
            decoded.push_back(' ');
        } else {
            decoded.push_back(str[i]);
        }
    }
    return decoded;
}