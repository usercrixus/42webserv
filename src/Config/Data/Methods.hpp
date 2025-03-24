/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Methods.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperthui <lperthui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:11:13 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/24 16:02:58 by lperthui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef METHODS_HPP
# define METHODS_HPP
# include "File.hpp"

class Methods {

	private :
		std::vector<std::string>	_allowedMethods; // methods autorisees
		std::vector<std::string>	_allowedClients; // clients qui peuvent utiliser toutes les methods
		bool						_deny;

	public :
		Methods();
		Methods(std::vector<std::string> allowedMethods, std::vector<std::string> allowedClients, bool _deny);
		~Methods();

		//getters
		const std::vector<std::string>& getAllowedMethods();
		const std::vector<std::string>& getAllowedClients();
		bool							&getDeny();

};

#endif