/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodPost.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:37:54 by achaisne          #+#    #+#             */
/*   Updated: 2025/03/20 18:37:56 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef METHODPOST_HPP
#define METHODPOST_HPP

#include "IMethod.hpp"
#include <iostream>
#include <string.h>

class MethodPost : public IMethod {
public:
    MethodPost(Request &request);
    ~MethodPost();
    
    void createFile(std::string path);
    void handle();
};

#endif // METHODPOST_HPP
