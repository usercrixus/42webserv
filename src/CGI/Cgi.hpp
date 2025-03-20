#ifndef CGI_HPP
# define CGI_HPP
#include <string>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "../Config/Data/Route.hpp"
#include "../Request/Request.hpp"
#include "../Config/Data/Data.hpp"

class Cgi
{
	private :
		int	_status;
		std::string _body;
	public :
		Cgi(Request& request, std::string& path);
		~Cgi();
		void HandleCgiGET(Request& request, std::string& path);
		void HandleCgiPOST(Request& request, std::string& path);
		int	getStatus();
		std::string getBody();
};

#endif