/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperthui <lperthui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:01:14 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/25 04:06:09 by lperthui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP
# include <string>
# include <vector>
# include "Route.hpp"

class Server {
	private :
		std::vector<Route>			_routes;
		std::vector<std::string>	_serverNames;
		unsigned int				_listen;
		long long					_clientMaxBodysize;
		std::string					_root;
		std::vector<File>			_index;
		std::map<int, File>			_errorFiles;
	
	public :
		Server();
		Server(std::map<std::string, std::vector<std::string> > data, std::vector<Route> routes, std::map<int, File> errorFiles);
		~Server();

		// methods
		void		init(std::map<std::string, std::vector<std::string> > data, std::vector<Route> routes, std::map<int, File> errorFiles);
		
		//getters
		std::vector<Route>			&getRoutes();
		std::vector<std::string>	&getServerNames();
		unsigned int				&getListen();
		long long					&getClientMaxBodysize();
		std::string					&getRoot();
		std::vector<File>			&getIndex();
		const std::map<int, File>&	getErrorFiles();

};

#endif