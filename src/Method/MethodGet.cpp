/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodGet.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:38:13 by achaisne          #+#    #+#             */
/*   Updated: 2025/03/21 18:51:09 by achaisne         ###   ########.fr       */
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
	std::string path;

	path = getFinalPath();
	if (path.compare(0, 4, "/cgi") == 0)
	{
		Cgi cgi(_request, path);
		_response.setBody(cgi.getBody());
		_response.setHeader(cgi.getStatus(), cgi.getCookies());
	}
	else
	{
		std::ifstream file(path.c_str());
		if (!file) {
			_response.setBody(getPageError(404));
			_response.setHeader(404);
		}
		else
		{
			std::stringstream buffer;
			buffer << file.rdbuf();
			_response.setBody(buffer.str());
			_response.setHeader(200);
		}
	}
	send(_request.getClient(), _response.toString().c_str(), _response.toString().size(), 0);
}
