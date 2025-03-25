#include "Socket/WebservSocket.hpp"
#include "Config/Data/Data.hpp"
#include "Socket/WebServSocketRunner.hpp"
#include "Response/Response.hpp"
#include <unistd.h>
#include <sys/wait.h>
#include <csignal>

void exitClean (int signal) {
	
	std::cout << "\n\nBye!" << std::endl;
	Data::destroyInstance();
	WebServSocketRunner::destroyInstance();
	exit(signal);
}


int main(int argc, char **argv) {
	signal(SIGINT, exitClean);
	if (argc > 2) {
		std::cout << "Usage: ./webserv [configuration file]" << std::endl;
	}
	Data* data;
    try
    {
		if (argc == 2) {
			data = Data::getInstance(argv[1]);
		}
		else {
			data = Data::getInstance();
		}
        WebservSocket servers[data->getHttp().getServers().size()];
        size_t i;
        
        i = 0;
        while (i < Data::getInstance()->getHttp().getServers().size())
        {
            servers[i].setId(i);
            servers[i].setupSocket();
            i++;
        }

        // WebServSocketRunner runner(Data::getInstance()->getHttp().getServers().size(), servers);
        WebServSocketRunner::getInstance(Data::getInstance()->getHttp().getServers().size(), servers)->setupPoll();
        WebServSocketRunner::getInstance(Data::getInstance()->getHttp().getServers().size(), servers)->run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
	std::cout << "test" << std::endl;
    return 0;
}

// Check aussi comment faire les redirections
// Faire pleins de tests (avec les curl en exemple etc, bien comprendre comment tout marche)
