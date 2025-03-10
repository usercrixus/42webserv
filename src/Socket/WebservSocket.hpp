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

#include "WebservSocket.hpp"
#include "../Request/Request.hpp"
#include "../Method/MethodGet.hpp"
#include "../Method/MethodPost.hpp"
#include "../Method/MethodDelete.hpp"


class WebservSocket {
	private:
		int _port;
		int _serverFd;
		struct sockaddr_in _address;
		Socket _socket;
		struct pollfd _fds[1];

	public:
		WebservSocket(int port);
		~WebservSocket();

		void setupSocket();
		void setupPoll();
		void waitConnection();
		void handleIncomingConnection();
		void run();
};

#endif // WEBSERVSOCKET_HPP
