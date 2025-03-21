#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <string>
#include <map>
#include <sys/socket.h>
#include <sstream>
#include <iostream>

#include "../Response/Response.hpp"

class Request {
	private:
		std::string _method;
		std::string _path;
		std::map<std::string, std::string> _headers;
		std::string _body;
		int _client;
		int _serverId;

	public:
		Request(const std::string& rawRequest, int client, int serverId);

		void parse(const std::string& rawRequest);

        std::map<std::string, std::string> getCookies() const;
        int getServerId() const;
		std::string getMethod() const;
		std::string getPath() const;
		std::string getHeader(const std::string& key) const;
		std::string getBody() const;
		int getClient() const;
};

#endif // REQUEST_HPP
