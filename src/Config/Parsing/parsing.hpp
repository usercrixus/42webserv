/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperthui <lperthui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:32:06 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/25 04:06:50 by lperthui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_HPP
# define PARSING_HPP
# include <vector>
# include <map>
# include <string>
// Parsing

class Http;
class Events;
class Data;

std::vector<std::string>	split(std::string s);
Http						parseHttp(std::vector<std::string> key, std::ifstream &file);
Events						parseEvents(std::vector<std::string> key, std::ifstream &file);
std::vector<std::string>	getValue(std::string key, std::map<std::string, std::vector<std::string> > data);
// void printData(Data d);

#endif