/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperthui <lperthui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:11:53 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/25 04:08:25 by lperthui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Data/Data.hpp"

std::vector<std::string>	split(std::string s) {
	std::stringstream			str(s);
	std::string					word;
	std::vector<std::string>	splited;

	while (str >> word) {
		splited.push_back(word);
	}

	return splited;
}

int isInVector(std::vector<std::string> vector, std::string string) {
	for (int i = 0; i < static_cast<int>(vector.size()); i++) {
		if (vector[i] == string) {
			return 1;
		}
	}
	return 0;
}

void addLimitElement(std::vector<std::string> &content, std::string &buf, bool &deny, std::vector<std::string> &clients, std::map<std::string, Limit> &keywords) {
	content = split(buf);
	std::map<std::string, Limit>::iterator key = keywords.find(content[0]);
	int arguments = content.size() - 1;
	if (key == keywords.end()) {
		throw std::logic_error("Error: config file: unrecognized argument: " + content[0]);
	}
	else if (key->second.getLimited() && (arguments < key->second.getMin() || arguments > key->second.getMax())) {
		throw std::logic_error("Error: config file: invalid argument on key: " + content[0]);
	}
	if (content.size() == 2 && content[0] == "deny" && content[1] == "all") {
		deny = 1;
	}
	else if (content.size() == 2 && content[0] == "allow") {
		clients.push_back(content[1]);
	}
	buf = "";
}

Methods	parseLimit(std::vector<std::string> key, std::ifstream &file) {
	std::map<std::string, Limit> keywords;
	keywords["deny"] = Limit(1, 1);
	keywords["allow"] = Limit(1, 1);
	
	bool deny = 0;
	std::vector<std::string> clients;
	std::vector<std::string> methods;
	char c;
	std::string buf;
	std::vector<std::string> content;

	for (int i = 1; i < static_cast<int>(key.size()); i++) {
		if (key[i] != "GET" && key[i] != "POST" && key[i] != "DELETE" && key[i] != "PUT" && key[i] != "HEAD" && key[i] != "OPTIONS" && key[i] != "PATCH" && key[i] != "TRACE" && key[i] != "CONNECT") { // a ajuster en fonction des methods que l on veut enlever
			throw std::logic_error("Error: config file: unrecognized method: " + key[i]);
		}
		if (isInVector(methods, key[i])) {
			throw std::logic_error("Error: config file: method: " + key[i] + " specified twice.");
		}
		methods.push_back(key[i]);
	}

	while (file.get(c)) {
		if (c == '{') {
			content = split(buf);
			throw std::logic_error("Error: config file: unrecognized argument: " + content[0]);
			buf = "";
		}
		else if (c == '}') {
			buf = "";
			Methods m(methods, clients, deny);
			return m;
		}
		else if (c == ';') {
			addLimitElement(content, buf, deny, clients, keywords);
		}
		else {
			buf += c;
		}
	}
	std::cout << "Erreure lors du parsing" << std::endl;
	throw std::exception();
}

void initKeywordsLocation(std::map<std::string, Limit>& keywords) {
	keywords["root"] = Limit(1, 1);
	keywords["autoindex"] = Limit(1, 1);
	keywords["return"] = Limit(1, 2);
	keywords["cgi_path"] = Limit(1, 1);
	keywords["index"] = Limit(1, 1);
}

void addLocationElement (std::map<std::string, Limit>& keywords, std::map<std::string, std::vector<std::string> >& data, std::map<int, File>& errorFiles, std::vector<std::string>& content, std::string& buf) {
	content = split(buf);
	std::map<std::string, Limit>::iterator key = keywords.find(content[0]);
	int arguments = content.size() - 1;
	if (key == keywords.end()) {
		throw std::logic_error("Error: config file: unrecognized argument: " + content[0]);
	}
	else if (key->second.getLimited() && (arguments < key->second.getMin() || arguments > key->second.getMax())) {
		throw std::logic_error("Error: config file: invalid argument on key: " + content[0]);
	}
	if (content[0] == "error_page") {
		for (int i = 1; i < static_cast<int>(content.size()) - 1; i++) {
			File file((content[content.size() - 1]), "");
			errorFiles[atoi(content[i].c_str())] = file;
		}
	}
	else {
		data[content[0]] = content;
	}
	buf = "";
}

std::string parseKey(std::vector<std::string>& key) {
	std::string path;

	if (key.size() > 2 && key[1] == "=" && key.size() == 3) {
		path = key[2];
	}
	else if (key.size() == 2) {
		path = key[1];
	}
	else {
		throw std::logic_error("Invalid location.");
	}
	return path;
}

Route	parseLocation(std::vector<std::string> key, std::ifstream &file) {
	std::map<std::string, Limit> keywords;
	std::map<std::string, std::vector<std::string> > data;
	std::map<int, File> errorFiles;
	Methods method;
	char c;
	std::string buf;
	std::vector<std::string> content;
	std::string path = parseKey(key);
	
	initKeywordsLocation(keywords);
	while (file.get(c)) {
		if (c == '{') {
			content = split(buf);
			if (content[0] == "limit_except")
				method = parseLimit(content, file);
			else
				throw std::logic_error("Error: config file: unrecognized argument: " + content[0]);
			buf = "";
		}
		else if (c == '}') {
			buf = "";
			Route r(data, path, method, errorFiles);
			return r;
		}
		else if (c == ';') {
			addLocationElement(keywords, data, errorFiles, content, buf);
		}
		else {
			buf += c;
		}
	}
	std::cout << "Erreure lors du parsing" << std::endl;
	throw std::exception();
}

void initServerKeywords(std::map<std::string, Limit>& keywords) {
	keywords["server_name"] = Limit();
	keywords["error_page"] = Limit();
	keywords["index"] = Limit();
	keywords["listen"] = Limit(1, 1);
	keywords["root"] = Limit(1, 1);
	keywords["client_max_body_size"] = Limit(1, 1);
}

void addServerElement(std::map<std::string, Limit>& keywords, std::map<std::string, std::vector<std::string> >& data, std::map<int, File>& errorFiles, std::string& buf, std::vector<std::string> &content) {
	content = split(buf);
	std::map<std::string, Limit>::iterator key = keywords.find(content[0]);
	int arguments = content.size() - 1;
	if (key == keywords.end()) {
		throw std::logic_error("Error: config file: unrecognized argument: " + content[0]);
	}
	else if (key->second.getLimited() && (arguments < key->second.getMin() || arguments > key->second.getMax())) {
		throw std::logic_error("Error: config file: invalid argument on key: " + content[0]);
	}
	if (content[0] == "error_page") {
		for (int i = 1; i < static_cast<int>(content.size()) - 1; i++) {
			File file((content[content.size() - 1]), "");
			errorFiles[atoi(content[i].c_str())] = file;
		}
	}
	else {
		data[content[0]] = content;
	}
	buf = "";
}

Server	parseServer(std::vector<std::string> key, std::ifstream &file) {
	(void) key;
	std::map<std::string, Limit> keywords;
	std::map<std::string, std::vector<std::string> > data;
	std::map<int, File> errorFiles;
	char c;
	std::string buf;
	std::vector<std::string> content;
	std::vector<Route> routes;
	
	initServerKeywords(keywords);
	while (file.get(c)) {
		if (c == '{') {
			content = split(buf);
			if (content[0] == "location")
				routes.push_back(parseLocation(content, file));
			else
				throw std::logic_error("Error: config file: unrecognized argument: " + content[0]);
			buf = "";
		}
		else if (c == '}') {
			buf = "";
			Server s(data, routes, errorFiles);
			return s;
		}
		else if (c == ';') {
			addServerElement(keywords, data, errorFiles, buf, content);
		}
		else {
			buf += c;
		}
	}
	std::cout << "Erreure lors du parsing" << std::endl;
	throw std::exception();
}

void addHttpElement(std::vector<std::string> &content, std::string &buf, std::map<std::string, Limit> &keywords, std::map<int, File> &errorFiles, std::map<std::string, std::vector<std::string> > &data) {
	content = split(buf);
	std::map<std::string, Limit>::iterator key = keywords.find(content[0]);
	int arguments = content.size() - 1;
	if (key == keywords.end()) {
		throw std::logic_error("Error: config file: unrecognized argument: " + content[0]);
	}
	else if (key->second.getLimited() && (arguments < key->second.getMin() || arguments > key->second.getMax())) {
		throw std::logic_error("Error: config file: invalid argument on key: " + content[0]);
	}
	if (content[0] == "error_page") {
		for (int i = 1; i < static_cast<int>(content.size()) - 1; i++) {
			File file((content[content.size() - 1]), "");
			errorFiles[atoi(content[i].c_str())] = file;
		}
	}
	else {
		data[content[0]] = content;
	}
	buf = "";
}

Http	parseHttp(std::vector<std::string> key, std::ifstream &file) {
	(void) key;
	std::map<std::string, Limit> keywords;
	keywords["error_page"] = Limit();
	keywords["client_max_body_size"] = Limit(1, 1);

	std::map<std::string, std::vector<std::string> > data;
	std::map<int, File> errorFiles;

	char c;
	std::string buf;
	std::vector<std::string> content;
	std::vector<Server> servers;

	while (file.get(c)) {
		if (c == '{') {
			content = split(buf);
			if (content[0] == "server")
				servers.push_back(parseServer(content, file));
			else
				throw std::logic_error("Error: config file: unrecognized argument: " + content[0]);
			buf = "";
		}
		else if (c == '}') {
			buf = "";
			Http h(data, servers, errorFiles);
			return h;
		}
		else if (c == ';') {
			addHttpElement(content, buf, keywords, errorFiles, data);
		}
		else {
			buf += c;
		}
	}
	std::cout << "Erreure lors du parsing" << std::endl;
	throw std::exception();
}

std::vector<std::string>	getValue(std::string key, std::map<std::string, std::vector<std::string> > data) {
	if (data.find(key) != data.end()) {
		return data[key];
	}
	throw std::logic_error("Key does not exist.");
}

// void printData(Data d) {
// 	Http http = d.getHttp();
// 	std::cout << "Http : _serverName : ";
// 	for (int i = 0; i < static_cast<int>(http.getServerName().size()); i++) {
// 		std::cout << http.getServerName()[i] << " | ";
// 	}
// 	std::cout << std::endl;
// 	std::cout << "Http : _errorFiles : ";
// 	for (int i = 0; i < static_cast<int>(http.getServerName().size()); i++) {
// 		for (std::map<int, File>::const_iterator it = http.getErrorFiles().begin(); it != http.getErrorFiles().end(); it++) {
// 			File f = it->second;
// 			std::cout << "Error : " << it->first << std::endl;
// 			std::cout << "File : _name : " << f.getName() << std::endl;
// 			std::cout << "File : _relativePath : " << f.getRelativePath() << std::endl;
// 			std::cout << "File : _root : " << f.getRoot() << std::endl;
// 			std::cout << "File : _extension : " << f.getExtension() << std::endl;
// 			std::cout << std::endl;
// 		}
// 	}
// 	std::cout << std::endl;
// 	std::cout << "Http : _clientMaxBody : " << http.getClientMaxBody() << std::endl;
// 	for (int i = 0; i < static_cast<int>(http.getServers().size()); i++) {
// 		Server s = http.getServers()[i];
// 		std::cout << "Server : _serverNames : ";
// 		for (int j = 0; j < static_cast<int>(s.getServerNames().size()); j++) {
// 			std::cout << s.getServerNames()[j] << " | ";
// 		}
// 		std::cout << std::endl << "Server : _listen : " << s.getListen() << std::endl;
// 		std::cout << std::endl << "Server : _clientMaxBodysize : " << s.getClientMaxBodysize() << std::endl;
// 		std::cout << "Server : _root : " << s.getRoot() << std::endl;
// 		for (int j = 0; j < static_cast<int>(s.getIndex().size()); j++) {
// 			File f = s.getIndex()[j];
// 			std::cout << "Server : File : _name : " << f.getName() << std::endl;
// 			std::cout << "Server : File : _relativePath : " << f.getRelativePath() << std::endl;
// 			std::cout << "Server : File : _root : " << f.getRoot() << std::endl;
// 			std::cout << "Server : File : _extension : " << f.getExtension() << std::endl;
// 			std::cout << std::endl;
// 		}
// 		// afficher _index
// 		for (int j = 0; j < static_cast<int>(s.getRoutes().size()); j++) {
// 			Route r = s.getRoutes()[j];
// 			//afficher errorFiles / methods / extensios
// 			std::cout << "Route : _location : " << r.getLocation() << std::endl;
// 			std::cout << "Route : _root : " << r.getRoot() << std::endl;
// 			std::cout << "Route : _errorFiles : ";
// 			for (std::map<int, File>::const_iterator it = r.getErrorFiles().begin(); it != r.getErrorFiles().end(); it++) {
// 				File f = it->second;
// 				std::cout << "Error : " << it->first << std::endl;
// 				std::cout << "File : _name : " << f.getName() << std::endl;
// 				std::cout << "File : _relativePath : " << f.getRelativePath() << std::endl;
// 				std::cout << "File : _root : " << f.getRoot() << std::endl;
// 				std::cout << "File : _extension : " << f.getExtension() << std::endl;
// 				std::cout << std::endl;
// 			}
// 			std::cout << std::endl;
// 			std::cout << "Route : _index : " << r.getIndex() << std::endl;
// 			std::cout << "Route : _redirection : " << r.getRedirection() << std::endl;
// 			std::cout << "Route : _redirectionCode : " << r.getRedirectionCode() << std::endl;
// 			std::string c = r.getAutoIndex() == 1 ? "true" : "false";
// 			std::cout << "Route : _autoIndex : " << c << std::endl;
// 			std::cout << "Route : _cgiPath : " << r.getCgiPath() << std::endl;
// 			Methods m = r.getMethods();
// 			std::cout << "Route : Methods : _allowedMethods : ";
// 			for (std::vector<std::string>::const_iterator it = m.getAllowedMethods().begin(); it != m.getAllowedMethods().end(); it++) {
// 				std::cout << *it << " | ";
// 			}
// 			std::cout << std::endl;
// 			std::cout << "Route : Methods : _allowedClients : ";
// 			for (std::vector<std::string>::const_iterator it = m.getAllowedClients().begin(); it != m.getAllowedClients().end(); it++) {
// 				std::cout << *it << " | ";
// 			}
// 			std::cout << std::endl;
// 			std::cout << "Route : Methods : _deny : " << m.getDeny() << std::endl;
// 			std::cout << "Route : _clientMaxBodysize : " << r.getClientMaxBodysize() << std::endl;
// 			std::cout << std::endl;
// 			std::cout << std::endl;
// 		}
// 	}
// }
