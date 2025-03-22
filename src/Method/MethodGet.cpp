/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodGet.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperthui <lperthui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:38:13 by achaisne          #+#    #+#             */
/*   Updated: 2025/03/22 12:36:20 by lperthui         ###   ########.fr       */
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
	std::string path;

	path = getFinalPath();
	if (!isMethodAllowed("GET"))
	{
		_response.setBody(getPageError(405));
		_response.setHeader(405, _request.getPath());
	}
	else if (isDirectory(path) && isListingAllowed())
	{
		_response.setBody(generateDirectoryListing(path));
		_response.setHeader(200, _request.getPath());
	}
	else if (path.compare(0, 4, "/cgi") == 0)
	{
		Cgi cgi(_request, path);
		_response.setBody(cgi.getBody());
		_response.setHeader(cgi.getStatus(), _request.getPath(), cgi.getCookies());
	}
	else
	{
		std::ifstream file(path.c_str());
		if (!file) {
			_response.setBody(getPageError(404));
			_response.setHeader(404, _request.getPath());
		}
		else
		{
			std::stringstream buffer;
			buffer << file.rdbuf();
			_response.setBody(buffer.str());
			_response.setHeader(200, _request.getPath());
		}
	}
	send(_request.getClient(), _response.toString().c_str(), _response.toString().size(), 0);
}
