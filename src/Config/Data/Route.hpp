/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperthui <lperthui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:45:34 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/24 18:04:39 by lperthui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTE_HPP
# define ROUTE_HPP
# include <map>
# include <vector>
# include <string>
# include "File.hpp"
# include "Methods.hpp"

class Route {

	private :
		std::map<std::string, File>				_files; // a init ? Si oui en parcourant le repertoire root
		std::map<int, File>						_errorFiles;
		Methods									_methods;
		std::vector<std::string>				_acceptedExtensions; // a init a partir de quoi ?
		File									_defaultFile; // a init une fois que les files seront parse, fichier charge par defaut sur la route
		std::string								_location;
		std::string								_root;
		std::string								_redirection;
		int										_redirectionCode;
		bool									_autoIndex;
		std::string								_cgi_path;
		std::string								_clientMaxBodysize;
		std::string								_index;
		
		public :
		Route();
		Route(const Route &route);
		Route(std::map<std::string, std::vector<std::string> > data, std::string location, Methods method, std::map<int, File> errorFiles);
		~Route();
		
		// methods
		void init(std::map<std::string, std::vector<std::string> > data, std::string location, Methods method, std::map<int, File> errorFiles);

		// getters
		const std::map<std::string, File>&			getFiles();
		const std::map<int, File>&					getErrorFiles();
		Methods										&getMethods();
		const std::vector<std::string>&				getAcceptedExtensions();
		File										&getDefaultFile();
		std::string									&getLocation();
		std::string									&getRoot();
		std::string									&getRedirection();
		int											&getRedirectionCode();
		bool										&getAutoIndex();
		std::string									&getCgiPath();
		std::string									&getClientMaxBodysize();
		std::string									&getIndex();

};

#endif