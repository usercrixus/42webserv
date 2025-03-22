#include "Socket/WebservSocket.hpp"
#include "Config/Data/Data.hpp"
#include "Socket/WebServSocketRunner.hpp"
#include "Response/Response.hpp"
#include <unistd.h>
#include <sys/wait.h>

int main() {
    try
    {
        WebservSocket servers[Data::getInstance()->getHttp().getServers().size()];
        size_t i;
        
        i = 0;
        while (i < Data::getInstance()->getHttp().getServers().size())
        {
            servers[i].setId(i);
            servers[i].setupSocket();
            i++;
        }

        WebServSocketRunner runner(Data::getInstance()->getHttp().getServers().size(), servers);
        runner.setupPoll();
        runner.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}

// Check aussi comment faire les redirections
// Faire pleins de tests (avec les curl en exemple etc, bien comprendre comment tout marche)
