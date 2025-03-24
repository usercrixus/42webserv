/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMethod.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:38:02 by achaisne          #+#    #+#             */
/*   Updated: 2025/03/24 01:28:36 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMETHOD_HPP
#define IMETHOD_HPP

#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <algorithm>
#include <vector>
#include <sys/stat.h>
#include <iostream>


#include "../Request/Request.hpp"
#include "../Response/Response.hpp"
#include "../Config/Data/Data.hpp"

class IMethod {
    protected:
        Request _request;
        Response _response;

       public:
        IMethod(Request &request);
        virtual ~IMethod();

        Route *getRoute();
        std::string getPathError(int error);
        std::string getPageError(int error);
        std::string urlDecode(const std::string &str);
        std::string getFinalPath();
        bool isMethodAllowed(std::string method);
        bool isListingAllowed();
        bool isDirectory(const std::string &path);
        virtual void handle() = 0;
};

#endif // IMETHOD_HPP
