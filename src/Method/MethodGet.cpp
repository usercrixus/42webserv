/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodGet.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:38:13 by achaisne          #+#    #+#             */
/*   Updated: 2025/03/20 18:55:17 by achaisne         ###   ########.fr       */
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

void MethodGet::handle()
{
	std::stringstream buffer;
	std::string path = Data::getInstance()->getHttp().getServers()[_request.getServerId()].getRoot() + _request.getPath();
	std::cout << path << std::endl;
	/* Gerer le routage qui peut etre different en fonction de la location 
	s'il y a un autre root dedans, ne pas prendre le root general "multipage-website" tout le temps, 
	ca gerera donc egalement le moment ou il faut appeler le CGI 
	Exemple :    location /content {
            	root   /var/www/content;
            	autoindex  off;
            	index      index.html;
        		} 
	--> Root sur /var/www/content quand location /content correspond au path*/
	if (path.compare(0, 4, "/cgi") == 0) //a modifier
	{
<<<<<<< HEAD
		Cgi cgi(_request, path);
		_response.setBody(cgi.getBody());
		_response.setHeader(cgi.getStatus());
=======
	Cgi Cgi(_request, path);
	_response.setBody(Cgi.getBody());
	_response.setHeader(Cgi.getStatus());
>>>>>>> 1e2e4a5e795325966634f3cab483e223bf250940
	}
	else
	{
		std::ifstream file(urlDecode(path).c_str());
		if (!file) {
			_response.setBody("404 Not Found");
			_response.setHeader(404);
		}
		else
		{
			buffer << file.rdbuf();
			_response.setBody(buffer.str());
			_response.setHeader(200);
		}
	}
	send(_request.getClient(), _response.toString().c_str(), _response.toString().size(), 0);
}
