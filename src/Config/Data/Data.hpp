/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperthui <lperthui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:10:32 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/24 15:59:32 by lperthui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_HPP
# define DATA_HPP
# include "Http.hpp"
# include "Events.hpp"

# define CONFIG_PATH "webservConfig.conf"

class Data {
	private :
	    static Data* instance;

		Http												_http;
		Events												_events;
		unsigned int										_workerProcesses;
		std::map<std::string, std::vector<std::string> >	_data;

		Data();
		Data(std::string path);
		~Data();
	public :
		static Data* getInstance();
		static Data* getInstance(std::string path);
		static void destroyInstance();

		void	parseData(std::string configFile);
		void	init();

		//getters

		unsigned int &getWorkerProcesses();
		Http &getHttp();
		Events &getEvents();
	
};

#endif