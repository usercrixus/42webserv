/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Http.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperthui <lperthui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:55:45 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/25 04:02:58 by lperthui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTES_HPP
# define ROUTES_HPP
# include <map>
# include <vector>
# include <string>
# include "Server.hpp"
# include "File.hpp"

class Http {

	private :
		std::vector<Server>			_servers;
		std::vector<std::string>	_serverName;
		Server						_defaultServer;
		std::map<int, File>			_errorFiles;
		long long					_clientMaxBody;
	
	public :
		Http();
		Http(std::map<std::string, std::vector<std::string> > data, std::vector<Server> servers, std::map<int, File> errorFiles);
		~Http();

		// methods
		void init(std::map<std::string, std::vector<std::string> > data, std::vector<Server> servers, std::map<int, File> errorFiles);
		
		//getters
		std::vector<Server> &getServers();
		std::vector<std::string>			&getServerName();
		Server				&getDefaultServer();
		const std::map<int, File> &getErrorFiles();
		long long			&getClientMaxBody();
};

#endif