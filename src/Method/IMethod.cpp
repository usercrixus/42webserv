/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMethod.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:37:59 by achaisne          #+#    #+#             */
/*   Updated: 2025/03/20 18:38:00 by achaisne         ###   ########.fr       */
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

std::string IMethod::urlDecode(const std::string& str)
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