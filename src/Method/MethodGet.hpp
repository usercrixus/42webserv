/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodGet.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:37:50 by achaisne          #+#    #+#             */
/*   Updated: 2025/03/25 13:59:45 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef METHODGET_HPP
#define METHODGET_HPP

#include "IMethod.hpp"
#include "../Request/Request.hpp"
#include <map>
#include <dirent.h>
#include <sstream>
#include <iostream>

class MethodGet : public IMethod {
    private:

    public:
        MethodGet(Request &request);
        ~MethodGet();

        std::string generateDirectoryListing(const std::string &path);

        void handle();
        void handleMethodNotAllowed();
        void handleRedirection(Route &route);
        void handleContentRequest(std::string &path);
        void handleFileRequest(std::string &path);
        void sendResponse();
};

#endif
