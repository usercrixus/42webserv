/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:38:56 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/20 23:47:48 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "File.hpp"

File::File() {}

File::File(std::string absolutePath) : _absolutePath(absolutePath) {
	this->buildName();
	this->buildRoot();
	this->buildExtension();
}

File::File(std::string name, std::string root) : _name(name), _root(root) {
	this->buildAbsolutePath();
	this->buildExtension();
}

File::~File() {}

void printVector(std::vector<std::string> v) {
	std::vector<std::string>::iterator it = v.begin();
	it++;
	for(; it < v.end(); it++) {
		std::cout << *it << std::endl;
	}
}

//methods
void File::buildAbsolutePath () {
	if (this->getRoot() == "/") {
		_absolutePath = "/" + this->getName();
	}
	else {
		_absolutePath = this->getRoot() + "/" + this->getName();
	}
}

void File::buildExtension() {
	std::string file = this->getName();
	size_t ext = file.rfind('.');
	
	if (ext == std::string::npos) {
		// Gerer cas particulier
		_extension = "";
	}
	else {
		_extension = file.substr(ext + 1);
	}
}

void File::buildName() {
	std::string file = this->getName();
	size_t ext = file.rfind('/');
	
	if (ext == std::string::npos) {
		// Gerer cas particulier
		_name = "";
	}
	else {
		_name = file.substr(ext + 1);
	}
}

void File::buildRoot() {
	std::string file = this->getName();
	size_t ext = file.rfind('/');
	
	if (ext == std::string::npos) {
		// Gerer cas particulier
		_root = "";
	}
	else {
		_root = file.substr(0, ext - 1);
	}
}

//getters
std::string File::getName() {
	return _name;
}

std::string File::getRoot() {
	return _root;
}

std::string File::getAbsolutePath() const {
	return _absolutePath;
}

std::string File::getExtension() {
	return _extension;
}
