#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <string>
#include <map>

class Request {
	private:
		std::string _method;
		std::string _path;
		std::map<std::string, std::string> _headers;
		std::string _body;

	public:
		Request(const std::string& rawRequest);

		std::string getMethod() const;
		std::string getPath() const;
		std::string getHeader(const std::string& key) const;
		std::string getBody() const;

		void parse(const std::string& rawRequest);
};

#endif // REQUEST_HPP
