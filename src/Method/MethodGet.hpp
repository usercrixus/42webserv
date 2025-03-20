/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodGet.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:37:50 by achaisne          #+#    #+#             */
/*   Updated: 2025/03/20 22:36:51 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef METHODGET_HPP
#define METHODGET_HPP

#include "IMethod.hpp"
#include "../Request/Request.hpp"

#include <iostream>

class MethodGet : public IMethod {
    private:

    public:
        MethodGet(Request &request);
        ~MethodGet();

        void handle();
};

#endif // METHODGET_HPP
