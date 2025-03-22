/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodDelete.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperthui <lperthui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:38:05 by achaisne          #+#    #+#             */
/*   Updated: 2025/03/22 12:35:40 by lperthui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MethodDelete.hpp"

MethodDelete::MethodDelete(Request &request):
IMethod(request)
{
}

MethodDelete::~MethodDelete()
{
}

void MethodDelete::handle()
{
    std::string path;

	path = getFinalPath();
	if (!isMethodAllowed("DELETE"))
	{
		_response.setBody(getPageError(405));
		_response.setHeader(405, _request.getPath());
	}
    else if (std::remove(path.c_str()) != 0)
    {
        _response.setBody("404 Not Found");
        _response.setHeader(404, _request.getPath());
    }
    else
    {
        _response.setBody("");
        _response.setHeader(204, _request.getPath());
    }
	send(_request.getClient(), _response.toString().c_str(), _response.toString().size(), 0);
}
