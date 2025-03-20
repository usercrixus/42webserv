#include <poll.h>
#include <map>
#include "WebservSocket.hpp"
#include "../Method/MethodDelete.hpp"
#include "../Method/MethodGet.hpp"
#include "../Method/MethodPost.hpp"

class WebServerSocketRunner
{
private:
	struct pollfd *_fds;
	std::map<int, WebservSocket*> _webServerSockets;
	int _serversSize;

public:
	WebServerSocketRunner(int size, WebservSocket *webservSocket);
	~WebServerSocketRunner();

	void setupPoll();
	WebservSocket &waitConnection();
	void handleIncomingConnection(WebservSocket &buffer);
	void run();
};

