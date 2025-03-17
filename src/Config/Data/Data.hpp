/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperthui <lperthui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:10:32 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/14 15:05:10 by lperthui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_HPP
# define DATA_HPP
# include "Http.hpp"
# include "Events.hpp"

class Data {

	private :
		Http												_http;
		Events												_events;
		unsigned int										_workerProcesses;
		std::map<std::string, std::vector<std::string> >	_data;
	
	public :
		Data();
		Data(std::string configFile);
		~Data();
		
		//methods

		void	parseData(std::string configFile);
		void	init();

		//getters

		unsigned int getWorkerProcesses();
		Http getHttp();
		Events getEvents();
	
};

#endif