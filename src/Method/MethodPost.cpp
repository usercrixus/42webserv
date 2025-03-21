/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodPost.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:37:40 by achaisne          #+#    #+#             */
/*   Updated: 2025/03/21 15:53:40 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MethodPost.hpp"

MethodPost::MethodPost(Request &request):
IMethod(request)
{
}

MethodPost::~MethodPost()
{
}

void MethodPost::createFile(std::string path)
{
    std::ifstream file(path.c_str());
    if (!file) 
    {
        std::ofstream newFile(path.c_str(), std::ios::out);
        if (!newFile)
            throw std::runtime_error("Impossible to create the file");
        newFile << _request.getBody();
    }
    else 
    {
        std::ofstream replaceFile(path.c_str(), std::ios::out | std::ios::trunc);
        if (!replaceFile)
            throw std::runtime_error("Impossible to truncate the file");
        replaceFile << _request.getBody();
    }
}

void MethodPost::handle()
{
	std::string path;
	
	path = Data::getInstance()->getHttp().getServers()[_request.getServerId()].getRoot() + _request.getPath();
	path = urlDecode(path);
	path = getFinalPath(path);
	if (path.compare(0, 4, "/cgi") == 0) //a modifier
	{
		Cgi cgi(_request, path);
		_response.setBody(cgi.getBody());
		_response.setHeader(cgi.getStatus(), cgi.getCookies());
    }
    else
    {
        try
        {
            createFile(path);
            _response.setBody(std::string("201 Successfully Created"));
            _response.setHeader(201);
        }
        catch(const std::exception& e)
        {
            _response.setBody(getPageError(500));
            _response.setHeader(500);
        }
    }
	send(_request.getClient(), _response.toString().c_str(), _response.toString().size(), 0);
}
