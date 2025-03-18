#include "Socket/WebservSocket.hpp"
#include "Config/Data/Data.hpp"

int main() {
    try
    {
        WebservSocket servers[Data::getInstance()->getHttp().getServers().size()];
        
        for (size_t i = 0; i < Data::getInstance()->getHttp().getServers().size(); i++)
        {
            servers[i].setPort(Data::getInstance()->getHttp().getServers()[i].getListen());
            servers[i].setupSocket();
            servers[i].setupPoll();
            servers[i].run();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
