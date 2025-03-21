/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMethod.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:37:59 by achaisne          #+#    #+#             */
/*   Updated: 2025/03/21 18:44:56 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IMethod.hpp"

IMethod::IMethod(Request &request):
_request(request)
{
}

IMethod::~IMethod()
{
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