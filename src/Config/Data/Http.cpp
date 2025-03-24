/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Http.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperthui <lperthui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:02:45 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/24 18:00:33 by lperthui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Http.hpp"

Http::Http() {}

Http::Http(std::map<std::string, std::vector<std::string> > data, std::vector<Server> servers, std::map<int, File> errorFiles) {
	this->init(data, servers, errorFiles);
}

Http::~Http() {}

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
		_clientMaxBody = atoi(value[1].c_str());
	}
	catch (std::exception & e) {
		_clientMaxBody = 1048576;
	}
	// reste a stocker les pages d'erreure.
}

//getters

std::vector<Server> &Http::getServers() {
	return _servers;
}
std::vector<std::string>			&Http::getServerName() {
	return _serverName;
}
Server				&Http::getDefaultServer() {
	return _defaultServer;
}
const std::map<int, File>	&Http::getErrorFiles() {
	return _errorFiles;
}
long long			&Http::getClientMaxBody() {
	return _clientMaxBody;
}
