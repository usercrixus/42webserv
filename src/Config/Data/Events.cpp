/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Events.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperthui <lperthui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 01:30:20 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/24 15:59:59 by lperthui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Events.hpp"

Events::Events() {}

Events::Events(std::map<std::string, std::vector<std::string> > data) {
	this->init(data);
}

Events::~Events() {}

void	Events::init(std::map<std::string, std::vector<std::string> > data) {
	try {
		std::vector<std::string> value = getValue("worker_connections", data);
		_workerConnections = atoi(value[1].c_str());
	}
	catch (std::exception & e) {
		_workerConnections = 512;
	}
}

// getters

unsigned int &Events::getWorkerConnections() {
	return _workerConnections;
}