#ifndef WEBSERVSOCKET_HPP
#define WEBSERVSOCKET_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <iostream>
#include <string>
#include <cstdlib> // for std::exit
#include <unistd.h> // for close()
#include <stdio.h>
#include <string.h>
#include "Socket.hpp"

#include "../Request/Request.hpp"
#include "../Config/Data/Data.hpp"

class WebservSocket {
	private:
		int _id;
		int _serverFd;
		struct sockaddr_in _address;
		Socket _socket;

	public:
		WebservSocket();
		~WebservSocket();

		int getServerFd() const;
		int getId() const;
		void setId(int id);
		void setupSocket();
};

#endif // WEBSERVSOCKET_HPP
