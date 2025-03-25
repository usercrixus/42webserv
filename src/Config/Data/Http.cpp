/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Http.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperthui <lperthui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:02:45 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/25 04:36:33 by lperthui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Http.hpp"

Http::Http() {}

Http::Http(std::map<std::string, std::vector<std::string> > data, std::vector<Server> servers, std::map<int, File> errorFiles) {
	this->init(data, servers, errorFiles);
}

Http::~Http() {}

void setDefault(std::map<int, File> &files) {
	files[403] = File("html/errors/403.html", "");
	files[404] = File("html/errors/404.html", "");
	files[405] = File("html/errors/405.html", "");
	files[500] = File("html/errors/50x.html", "");
	files[502] = File("html/errors/50x.html", "");
	files[503] = File("html/errors/50x.html", "");
	files[504] = File("html/errors/50x.html", "");
}

void setDefaultErrors(std::map<int, File> &files) {
	std::map<int, File> defaultFiles;
	setDefault(defaultFiles);
	for (std::map<int, File>::iterator it = defaultFiles.begin(); it != defaultFiles.end(); it++) {
		if (files.find(it->first) == files.end()) {
			files[it->first] = it->second;
		}
	}
}

void	Http::init(std::map<std::string, std::vector<std::string> > data, std::vector<Server> servers, std::map<int, File> errorFiles) {
	if (servers.empty()) {
		throw std::logic_error("No server specified.");
	}
	_errorFiles = errorFiles;
	setDefaultErrors(_errorFiles);
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
