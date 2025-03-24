/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Methods.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperthui <lperthui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:17:28 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/24 16:03:04 by lperthui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Methods.hpp"

Methods::Methods() : _deny(0) {}

Methods::Methods(std::vector<std::string> allowedMethods, std::vector<std::string> allowedClients, bool deny) : _allowedMethods(allowedMethods), _allowedClients(allowedClients), _deny(deny) {}

Methods::~Methods() {}

// getters
const std::vector<std::string>& Methods::getAllowedMethods() {
	return _allowedMethods;
}

const std::vector<std::string>& Methods::getAllowedClients() {
	return _allowedClients;
}
bool &Methods::getDeny() {
	return _deny;
}
