/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodGet.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:38:13 by achaisne          #+#    #+#             */
/*   Updated: 2025/03/25 01:23:30 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
std::string MethodGet::generateDirectoryListing(const std::string& path)
{
    DIR* dir;
    struct dirent* entry;
    std::stringstream listing;

    listing << "<html><head><title>Directory Listing</title></head><body>";
    listing << "<h1>Index of " << path << "</h1>";
    listing << "<ul>";

    if ((dir = opendir(path.c_str())) != NULL)
    {
        while ((entry = readdir(dir)) != NULL)
        {
            std::string name = entry->d_name;
            listing << "<li><a href=\"" << _request.getPath() + "/" + name << "\">" << name << "</a></li>";
        }
        closedir(dir);
    }
    else
    {
        listing << "<p>Error accessing directory content.</p>";
    }

    listing << "</ul></body></html>";
    return listing.str();
}

void MethodGet::handle()
{
	std::string path = getFinalPath();
	std::cout << "Final1 :" << path << std::endl;
	if (!isMethodAllowed("GET"))
		handleMethodNotAllowed();
	else
	{
		Route *route = getRoute();
		if (route && route->getRedirectionCode() != -1)

			handleRedirection(*route);
		else
			handleContentRequest(path);
	}
}

void MethodGet::handleMethodNotAllowed()
{
	_response.setBody(getPageError(405));
	_response.setHeader(405, getPathError(405));
	sendResponse();
}

void MethodGet::handleRedirection(Route& route)
{
	_response.setHeader(route.getRedirectionCode(), _request.getPath(), route);
	_response.setBody("");
	sendResponse();
}

void MethodGet::handleContentRequest(std::string& path)
{
	if (isDirectory(path) && isListingAllowed())
	{
		_response.setBody(generateDirectoryListing(path));
		_response.setHeader(200, _request.getPath());
	}
	else if (getRoute() && !getRoute()->getCgiPath().empty())
	{
		Cgi cgi(_request, path);
		_response.setBody(cgi.getBody());
		_response.setHeader(cgi.getStatus(), _request.getPath(), cgi.getCookies());
	}
	else
	{
		handleFileRequest(path);
	}
	sendResponse();
}

void MethodGet::handleFileRequest(std::string& path)
{
	std::ifstream file(path.c_str());
	if (isDirectory(path) || !file)
	{
		_response.setBody(getPageError(404));
		_response.setHeader(404, getPathError(404));
	}
	else
	{
		std::stringstream buffer;
		buffer << file.rdbuf();
		_response.setBody(buffer.str());
		_response.setHeader(200, _request.getPath());
	}
}

void MethodGet::sendResponse()
{
	send(_request.getClient(), _response.toString().c_str(), _response.toString().size(), 0);
}

