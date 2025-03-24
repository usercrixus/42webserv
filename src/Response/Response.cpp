#include "Response.hpp"

Response::Response() {}

void Response::setStatus(int statusCode) {
    switch (statusCode) {
        case 200: _headers += "HTTP/1.1 200 OK\r\n"; break;
        case 204: _headers += "HTTP/1.1 204 No Content\r\n"; break; 
        case 301: _headers += "HTTP/1.1 301 Moved Permanently\r\n"; break;
        case 302: _headers += "HTTP/1.1 302 Found\r\n"; break;
        case 303: _headers += "HTTP/1.1 303 See Other\r\n"; break;
        case 307: _headers += "HTTP/1.1 307 Temporary Redirect\r\n"; break;
        case 308: _headers += "HTTP/1.1 308 Permanent Redirect\r\n"; break;
        case 404: _headers += "HTTP/1.1 404 Not Found\r\n"; break;
        case 500: _headers += "HTTP/1.1 500 Internal Server Error\r\n"; break;
        default: _headers += "HTTP/1.1 500 Internal Server Error\r\n";
    }
}

void Response::setCurrentDate()
{
    const char* days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    const char* months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                            "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    std::time_t now = std::time(NULL);
    std::tm* gmt = std::gmtime(&now);

    std::ostringstream dateStream;
    dateStream << "Date: " << days[gmt->tm_wday] << ", "
               << std::setw(2) << std::setfill('0') << gmt->tm_mday << " "
               << months[gmt->tm_mon] << " "
               << (gmt->tm_year + 1900) << " "
               << std::setw(2) << std::setfill('0') << gmt->tm_hour << ":"
               << std::setw(2) << std::setfill('0') << gmt->tm_min << ":"
               << std::setw(2) << std::setfill('0') << gmt->tm_sec
               << " GMT";

    _headers += dateStream.str() + "\r\n";
}

void Response::setServerName()
{
    _headers += "Server: PERCHAMOR V1.0\r\n";
}

void Response::setConnection()
{
    _headers += "Connection: close\r\n";
}

void Response::setContentLen()
{
    std::ostringstream oss;
    oss << "Content-Length: " << _body.size() << "\r\n";
    _headers += oss.str();
}

void Response::setCookies(std::map<std::string, std::string> cookies)
{
    for (std::map<std::string, std::string>::const_iterator it = cookies.begin(); it != cookies.end(); ++it)
    {
        _headers += "Set-Cookie: " + it->first + "=" + it->second + "; Path=/\r\n";
    }
}

void Response::setMime(std::string path) {
	std::string mime = getMime(path);
	_headers += "Content-Type: " + mime + "\r\n";
}

int isRedirection(int statusCode) {
	return (statusCode == 301 || statusCode == 302 || statusCode == 303 || statusCode == 307 || statusCode == 308);
}

void Response::setLocation(Route &route) {
	_headers += "Location: " + route.getRedirection() + "\r\n";
}

void Response::setHeader(int statusCode, std::string path, Route &route, const std::map<std::string, std::string> &cookies)
{
    setHeader(statusCode, path, cookies);
    if (isRedirection(statusCode))
    {
        setLocation(route);
    }
}

void Response::setHeader(int statusCode, std::string path, const std::map<std::string, std::string> &cookies)
{
    setStatus(statusCode);
    setCurrentDate();
    setServerName();
	setMime(path);
    setContentLen();
    setConnection();
    setCookies(cookies);
}


void Response::setBody(const std::string &body)
{
    _body = body;
}

std::string Response::toString() const {
    return _headers + "\r\n" + _body;
}
