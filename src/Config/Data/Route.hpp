/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperthui <lperthui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:45:34 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/17 15:39:36 by lperthui         ###   ########.fr       */
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
		bool									_internal;
		bool									_autoIndex;
		std::string								_fastcgiPass;
		std::string								_fastcgiIndex;
		std::map<std::string, std::string>		_fastcgiParam;
		std::vector<std::string>				_include;
		std::string								_clientBodyTempPath;
		std::string								_uploadMaxFilesize;
		std::string								_clientMaxBodysize;
		
		public :
		Route();
		Route(const Route &route);
		Route(std::map<std::string, std::vector<std::string> > data, std::map<std::string, std::string> fastcgiParam, std::string location, Methods method, std::map<int, File> errorFiles);
		~Route();
		
		// methods
		void init(std::map<std::string, std::vector<std::string> > data, std::map<std::string, std::string> fastcgiParam, std::string location, Methods method, std::map<int, File> errorFiles);

		// getters
		const std::map<std::string, File>&			getFiles();
		const std::map<int, File>&					getErrorFiles();
		Methods										getMethods();
		const std::vector<std::string>&				getAcceptedExtensions();
		File										getDefaultFile();
		std::string									getLocation();
		std::string									getRoot();
		std::string									getRedirection();
		int											getRedirectionCode();
		bool										getInternal();
		bool										getAutoIndex();
		std::string									getFastcgiPass();
		std::string									getFastcgiIndex();
		const std::map<std::string, std::string>&	getFastcgiParam();
		const std::vector<std::string>&				getInclude();
		std::string									getClientBodyTempPath();
		std::string									getUploadMaxFilesize();
		std::string									getClientMaxBodysize();

};

#endif