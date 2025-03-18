#include "Socket/WebservSocket.hpp"
#include "Config/Data/Data.hpp"
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
            int pid = fork();
            if (!pid)
            {
                servers[i].setId(i);
                servers[i].setupSocket();
                servers[i].setupPoll();
                servers[i].run();
            }
            else
                i++;
        }
        while (i--)
            waitpid(-1, NULL, 0);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
