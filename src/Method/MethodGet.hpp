/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodGet.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:37:50 by achaisne          #+#    #+#             */
/*   Updated: 2025/03/21 23:56:21 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef METHODGET_HPP
#define METHODGET_HPP

#include "IMethod.hpp"
#include "../Request/Request.hpp"
#include <map>
#include <dirent.h>  // For directory listing
#include <sstream>   // For building HTML directory listing
#include <iostream>

class MethodGet : public IMethod {
    private:

    public:
        MethodGet(Request &request);
        ~MethodGet();

        std::string generateDirectoryListing(const std::string &path);

        void handle();
};

#endif // METHODGET_HPP
