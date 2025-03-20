#include <poll.h>
#include <map>
#include "WebservSocket.hpp"
#include "../Method/MethodDelete.hpp"
#include "../Method/MethodGet.hpp"
#include "../Method/MethodPost.hpp"

class WebServSocketRunner
{
private:
	struct pollfd *_fds;
	std::map<int, WebservSocket*> _webServerSockets;
	int _serversSize;

public:
	WebServSocketRunner(int size, WebservSocket *webservSocket);
	~WebServSocketRunner();

	void setupPoll();
	WebservSocket &waitConnection();
	void handleIncomingConnection(WebservSocket &buffer);
	void run();
};

