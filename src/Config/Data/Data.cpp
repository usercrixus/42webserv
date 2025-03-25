/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperthui <lperthui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:13:57 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/25 05:15:40 by lperthui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Data.hpp"

Data* Data::instance = NULL;

Data::Data()
{
	this->parseData(CONFIG_PATH);
	// printData(*this);
}

Data::Data(std::string path)
{
	this->parseData(path);
	// printData(*this);
}

Data::~Data() {}

void	Data::parseData(std::string configFile) {
	std::map<std::string, Limit> keywords;
	
	std::ifstream file(configFile.c_str());
	std::vector<Http> http;

	if (!file) {
		throw std::ios_base::failure("Error: Can't open file " + configFile);
	}

	char c;
	std::string buf;
	std::vector<std::string> content;

	while (file.get(c)) {
		if (c == '{') {
			content = split(buf);
			if (content[0] == "http")
				http.push_back(parseHttp(content, file));
			else
				throw std::logic_error("Error: config file: unrecognized argument: " + content[0]);
			buf = "";
		}
		else if (c == '}') {
			buf = "";
			return ;
		}
		else if (c == ';') {
			content = split(buf);
			std::map<std::string, Limit>::iterator key = keywords.find(content[0]);
			int arguments = content.size() - 1;
			if (key == keywords.end()) {
				throw std::logic_error("Error: config file: unrecognized argument: " + content[0]);
			}
			else if (key->second.getLimited() && (arguments < key->second.getMin() || arguments > key->second.getMax())) {
				throw std::logic_error("Error: config file: invalid argument on key: " + content[0]);
			}
			_data[content[0]] = content;
			buf = "";
		}
		else {
			buf += c;
		}
	}
	_http = http[0];
}

// getters

Http &Data::getHttp() {
	return _http;
}

Data* Data::getInstance() {
    if (!instance) {
        instance = new Data();
    }
    return instance;
}

Data* Data::getInstance(std::string path) {
	if (!instance) {
		instance = new Data(path);
    }
    return instance;
}

void Data::destroyInstance() {
	if (instance) {
		delete instance;
	}
	instance = NULL;
}
