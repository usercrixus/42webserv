#include <poll.h>
#include <map>
#include "WebservSocket.hpp"
#include "../Method/MethodDelete.hpp"
#include "../Method/MethodGet.hpp"
#include "../Method/MethodPost.hpp"

class WebServSocketRunner
{
private:
	static WebServSocketRunner* instance;
	struct pollfd *_fds;
	std::map<int, WebservSocket*> _webServerSockets;
	int _serversSize;
	WebServSocketRunner(int size, WebservSocket *webservSocket);
	~WebServSocketRunner();

public:

	static WebServSocketRunner* getInstance(int size, WebservSocket *webservSocket);
	static void destroyInstance();
	void setupPoll();
	WebservSocket &waitConnection();
	void handleIncomingConnection(WebservSocket &buffer);
	void run();
};

