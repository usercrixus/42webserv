/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperthui <lperthui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:38:56 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/25 04:02:46 by lperthui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "File.hpp"

File::File() {}

File::File(std::string relativePath) : _relativePath(relativePath) {
	this->buildName();
	this->buildRelativePath();
	this->buildExtension();
}

File::File(std::string name, std::string root) : _name(name), _root(root) {
	this->buildRelativePath();
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
void File::buildRelativePath () {
	if (this->getRoot() == "") {
		_relativePath = this->getName();
	}
	else {
		_relativePath = this->getRoot() + "/" + this->getName();
	}
}

void File::buildExtension() {
	std::string file = this->getName();
	size_t ext = file.rfind('.');
	
	if (ext == std::string::npos) {
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
		_root = "";
	}
	else {
		_root = file.substr(0, ext - 1);
	}
}

//getters
std::string &File::getName() {
	return _name;
}

std::string &File::getRoot() {
	return _root;
}

const std::string &File::getRelativePath() const {
	return _relativePath;
}

std::string &File::getExtension() {
	return _extension;
}
