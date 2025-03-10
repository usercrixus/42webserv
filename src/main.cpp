#include "Socket/WebservSocket.hpp"

#define PORT 4580

int main() {
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
