/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Events.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperthui <lperthui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 01:30:20 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/14 15:37:16 by lperthui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Events.hpp"

Events::Events() {}

Events::Events(std::map<std::string, std::vector<std::string> > data) {
	// std::cout << "Events constructed!" << std::endl;
	// for (std::map<std::string, std::vector<std::string> >::iterator it = data.begin(); it != data.end(); it++) {
	// 	std::cout << "Key : " << it->first << " | Value : ";
	// 	printVector(it->second);
	// 	std::cout << std::endl;
	// }
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

unsigned int Events::getWorkerConnections() {
	return _workerConnections;
}