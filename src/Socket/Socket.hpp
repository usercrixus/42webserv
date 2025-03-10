#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdexcept>
#include <iostream>

class Socket {
	private:
		int _fd;

	public:
		Socket();
		~Socket();

		void setOptions();
		void bindSocket(sockaddr_in& address);
		void listenSocket(int backlog);
		int getFd() const;
};

#endif // SOCKET_HPP
