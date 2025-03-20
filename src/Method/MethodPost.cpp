/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodPost.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:37:40 by achaisne          #+#    #+#             */
/*   Updated: 2025/03/20 22:33:28 by achaisne         ###   ########.fr       */
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
    try
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
        _response.setBody(std::string("201 Successfully Created"));
        _response.setHeader(201);
    }
    catch(const std::exception& e)
    {
        _response.setBody(std::string("500 Internal Server Error: ") + e.what());
        _response.setHeader(500);
    }
}

void MethodPost::handle()
{
    std::stringstream buffer;
	std::string path = urlDecode(Data::getInstance()->getHttp().getServers()[_request.getServerId()].getRoot() + _request.getPath());
	if (path.compare(0, 4, "/cgi") == 0) //a modifier
	{
		Cgi cgi(_request, path);
		_response.setBody(cgi.getBody());
		_response.setHeader(cgi.getStatus());
    }
    else
    {
        createFile(path);
    }
	send(_request.getClient(), _response.toString().c_str(), _response.toString().size(), 0);
}
