/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodDelete.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:38:05 by achaisne          #+#    #+#             */
/*   Updated: 2025/03/20 18:53:51 by achaisne         ###   ########.fr       */
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
    std::string fullPath = Data::getInstance()->getHttp().getServers()[_request.getServerId()].getRoot() + _request.getPath();
    if (std::remove(fullPath.c_str()) != 0)
    {
        _response.setBody("404 Not Found");
        _response.setHeader(404);
    }
    else
    {
        _response.setBody("");
        _response.setHeader(204);
    }
	send(_request.getClient(), _response.toString().c_str(), _response.toString().size(), 0);
}
