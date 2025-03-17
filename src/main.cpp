#include "Socket/WebservSocket.hpp"
#include "Config/Data/Data.hpp"

#define PORT 4580

int main() {
	// try {
	// 	// Si probleme aparait: viennent surement de static cast.
	// 	Data d("webservConfig.conf");
	// }
	// catch (std::exception & e) {
	// 	std::cout << e.what() << std::endl;
	// 	return 1;
	// }
    try
    {
        WebservSocket server(PORT);
        server.setupSocket();
        server.setupPoll();
        server.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
