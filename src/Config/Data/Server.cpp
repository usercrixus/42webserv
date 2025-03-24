/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:08:04 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/24 01:30:24 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server() {};

Server::Server(std::map<std::string, std::vector<std::string> > data, std::vector<Route> routes, std::map<int, File> errorFiles) {
	// std::cout << "Server constructed!" << std::endl;
	// for (std::map<std::string, std::vector<std::string> >::iterator it = data.begin(); it != data.end(); it++) {
	// 	std::cout << "Key : " << it->first << " | Value : ";
	// 	printVector(it->second);
	// 	std::cout << std::endl;
	// }
	this->init(data, routes, errorFiles);
}

Server::~Server() {};

// Server Server::operator=(Server &other) {
// 	this->_routes = other._routes;
// 	this->_serverNames = other._serverNames;
// 	this->_listen = other._listen;
// 	this->_clientMaxBodysize = other._clientMaxBodysize;
// 	this->_root = other._root;
// 	this->_index = other._index;
// 	this->_errorFiles = other._errorFiles;
// 	return *this;
// }

void Server::init(std::map<std::string, std::vector<std::string> > data, std::vector<Route> routes, std::map<int, File> errorFiles) {
	// Voir si oblige d'avoir au moins une route ? Si oui verif + throw
	_routes = routes;
	_errorFiles = errorFiles;
	try {
		std::vector<std::string> value = getValue("server_name", data);
		if (value.size() == 1) {
			throw std::logic_error("Server has no name.");
		}
		for (int i = 1; i < static_cast<int>(value.size()); i++) {
			_serverNames.push_back(value[i]);
		}
	}
	catch (std::exception & e) {
		_serverNames[0] = "";
	}

	try {
		std::vector<std::string> value = getValue("listen", data);
		_listen = atoi(value[1].c_str());
	}
	catch (std::exception & e) {
		_listen = 80;
	}
	
	try {
		std::vector<std::string> value = getValue("root", data);
		_root = value[1];
	}
	catch (std::exception & e) {
		_root = "";
	}
	
	try {
		std::vector<std::string> value = getValue("client_max_body_size", data);
		_clientMaxBodysize = value[1];
	}
	catch (std::exception & e) {
		_clientMaxBodysize = "";
	}
	
	try {
		std::vector<std::string> value = getValue("index", data);
		if (value.size() == 1) {
			throw std::logic_error("No index.");
		}
		for (int i = 1; i < static_cast<int>(value.size()); i++) {
			_index.push_back(File(value[i], _root));
		}
	}
	catch (std::exception & e) {
		_serverNames[0] = "";
	}

}

//getters

std::vector<Route>			&Server::getRoutes() {
	return _routes;
}
std::vector<std::string>	Server::getServerNames() {
	return _serverNames;
}
unsigned int				Server::getListen() {
	return _listen;
}
std::string					Server::getRoot() {
	return _root;
}
std::vector<File>			Server::getIndex() {
	return _index;
}

std::string					Server::getClientMaxBodysize() {
	return _clientMaxBodysize;
}

const std::map<int, File>&	Server::getErrorFiles() {
	return _errorFiles;
}
