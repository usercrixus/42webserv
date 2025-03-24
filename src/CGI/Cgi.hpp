#ifndef CGI_HPP
# define CGI_HPP
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
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
		//Atributes
		int	_status;
		std::string _body;
		std::map<std::string, std::string> _cookies;
		//Privates fonctions
		std::string getPathInfo(std::string &path, std::string &root);
		std::string getQueryString(std::string &path);
		std::string getScriptFilename(const std::string& path);
		std::string getCgiPath(Request& request);
		void getQueryStringFromCookies(std::map<std::string, std::string>&, std::string&);
		void setCookies(std::string);
	public :
		Cgi(Request& request, std::string& path);
		~Cgi();
		std::map<std::string, std::string> getCookies(void);
		void HandleCgiGET(Request& request, std::string& path);
		void HandleCgiPOST(Request& request, std::string& path);
		int	getStatus();
		std::string getBody();
};

#endif