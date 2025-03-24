/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperthui <lperthui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:58:20 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/24 18:05:19 by lperthui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Route.hpp"

Route::Route() {}

Route::Route(std::map<std::string, std::vector<std::string> > data, std::string location, Methods method, std::map<int, File> errorFiles) {
	// std::cout << "Route constructed!" << std::endl;
	// for (std::map<std::string, std::vector<std::string> >::iterator it = data.begin(); it != data.end(); it++) {
	// 	std::cout << "Key : " << it->first << " | Value : ";
	// 	printVector(it->second);
	// 	std::cout << std::endl;
	// }
	this->init(data, location, method, errorFiles);
}

Route::Route(const Route &route) {
	this->_files = route._files;
	this->_errorFiles = route._errorFiles;
	this->_methods = route._methods;
	this->_acceptedExtensions = route._acceptedExtensions;
	this->_defaultFile = route._defaultFile;
	this->_location = route._location;
	this->_root = route._root;
	this->_redirection = route._redirection;
	this->_redirectionCode = route._redirectionCode;
	this->_autoIndex = route._autoIndex;
	this->_cgi_path = route._cgi_path;
	this->_clientMaxBodysize = route._clientMaxBodysize;
}

Route::~Route() {}

//methods

void Route::init(std::map<std::string, std::vector<std::string> > data, std::string location, Methods method, std::map<int, File> errorFiles) {
	// reste a init la liste de fichier d'erreure le default file et _files
	_location = location;
	// verifier avant que les parametres dans fastcgiParam sont valide
	// _fastcgiParam = fastcgiParam;
	_methods = method;
	_errorFiles = errorFiles;
	try {
		std::vector<std::string> value = getValue("root", data);
		if (value.size() < 2) {
			throw std::invalid_argument("Incomplete root.");
		}
		_root = value[1];
	}
	catch (std::logic_error & e) {
		_root = "";
	}
	
	try {
		std::vector<std::string> value = getValue("return", data);
		if (value.size() == 1) {
			throw std::logic_error("No value in return.");
		}
		else if (value.size() == 2) {
			_redirection = "";
		}
		else if (value.size() > 2){
			_redirection = value[2];
		}
		// reste a gerer si size() > 3
		_redirectionCode = atoi(value[1].c_str());
	}
	catch (std::logic_error & e) {
		_redirection = "";
		_redirectionCode = -1;
	}
	
	try {
		std::vector<std::string> value = getValue("autoindex", data);
		if (value.size() < 2) {
			throw std::invalid_argument("Incomplete autoindex.");
		}
		if (value[1] == "on")
			_autoIndex = 1;
		else // gerer si ni on, ni off, ou si il n y a pas de param
			_autoIndex = 0;
	}
	catch (std::logic_error & e) {
		_autoIndex = 0;
	}

	try {
		std::vector<std::string> value = getValue("client_max_body_size", data);
		_clientMaxBodysize = value[1];
	}
	catch (std::logic_error & e) {
		_clientMaxBodysize = "";
	}
	
	try {
		std::vector<std::string> value = getValue("cgi_path", data);
		_cgi_path = value[1];
	}
	catch (std::logic_error & e) {
		_cgi_path = "";
	}
	try {
		std::vector<std::string> value = getValue("index", data);
		_index = value[1];
	}
	catch (std::logic_error & e) {
		_index = "";
	}
}

//getters

const std::map<std::string, File>&		Route::getFiles() {
	return _files;
}

const std::map<int, File>&				Route::getErrorFiles() {
	return _errorFiles;
}

Methods							&Route::getMethods() {
	return _methods;
}
const std::vector<std::string>&		Route::getAcceptedExtensions() {
	return _acceptedExtensions;
}

File							&Route::getDefaultFile() {
	return _defaultFile;
}

std::string						&Route::getLocation() {
	return _location;
}

std::string						&Route::getRoot() {
	return _root;
}

std::string						&Route::getRedirection() {
	return _redirection;
}

std::string						&Route::getCgiPath() {
	return _cgi_path;
}

int								&Route::getRedirectionCode() {
	return _redirectionCode;
}

bool							&Route::getAutoIndex() {
	return _autoIndex;
}

std::string						&Route::getClientMaxBodysize() {
	return _clientMaxBodysize;
}
