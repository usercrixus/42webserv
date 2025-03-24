/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperthui <lperthui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:39:16 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/24 16:00:59 by lperthui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_HPP
# define FILE_HPP
# include <string>
# include <map>
# include <vector>
# include <set>
# include <string>
# include <fstream>
# include <sstream>
# include <iostream>
# include <exception>
# include <cstdlib>
# include "../Parsing/parsing.hpp"
# include "../Parsing/Limit.hpp"

class File {
	
	private:
		std::string _name;
		std::string _root;
		std::string _relativePath;
		std::string _extension;
		
	public:
		File();
		File(std::string relativePath);
		File(std::string name, std::string root);
		~File();

		// methods
		void buildRelativePath();
		void buildExtension();
		void buildName();
		void buildRoot();

		// getters
		std::string &getName();
		std::string &getRoot();
		const std::string &getRelativePath() const;
		std::string &getExtension();
		
};

void printVector(std::vector<std::string> v);

#endif
