/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Http.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:02:45 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/24 01:37:20 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Http.hpp"

Http::Http() {}

Http::Http(std::map<std::string, std::vector<std::string> > data, std::vector<Server> servers, std::map<int, File> errorFiles) {
	// std::cout << "Http constructed!" << std::endl;
	// for (std::map<std::string, std::vector<std::string> >::iterator it = data.begin(); it != data.end(); it++) {
	// 	std::cout << "Key : " << it->first << " | Value : ";
	// 	printVector(it->second);
	// 	std::cout << std::endl;
	// }
	this->init(data, servers, errorFiles);
}

Http::~Http() {}

// Http Http::operator=(Http &other) {
// 	this->_servers = other._servers;
// 	this->_serverName = other._serverName;
// 	this->_defaultServer = other._defaultServer;
// 	this->_errorFiles = other._errorFiles;
// 	this->_clientMaxBody = other._clientMaxBody;
// 	return *this;
// }

void	Http::init(std::map<std::string, std::vector<std::string> > data, std::vector<Server> servers, std::map<int, File> errorFiles) {
	if (servers.empty()) {
		throw std::logic_error("No server specified.");
	}
	_errorFiles = errorFiles;
	_servers = servers;
	_defaultServer = _servers[0];
	_serverName = _defaultServer.getServerNames();
	try {
		std::vector<std::string> value = getValue("client_max_body_size", data);
		_clientMaxBody = value[1];
	}
	catch (std::exception & e) {
		_clientMaxBody = "1M";
	}
	// reste a stocker les pages d'erreure.
}

//getters

std::vector<Server> &Http::getServers() {
	return _servers;
}
std::vector<std::string>			Http::getServerName() {
	return _serverName;
}
Server				Http::getDefaultServer() {
	return _defaultServer;
}
const std::map<int, File>&	Http::getErrorFiles() {
	return _errorFiles;
}
std::string			Http::getClientMaxBody() {
	return _clientMaxBody;
}
