/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Events.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperthui <lperthui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 01:27:57 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/14 15:07:56 by lperthui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_HPP
# define EVENTS_HPP
# include "File.hpp"

class Events {
	
	private:
		unsigned int _workerConnections;
		
	public:
		Events();
		Events(std::map<std::string, std::vector<std::string> > data);
		~Events();

		// methods
		void	init(std::map<std::string, std::vector<std::string> > data);

		// getters
		unsigned int getWorkerConnections();
};

#endif