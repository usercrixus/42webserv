/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:39:16 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/20 23:47:41 by achaisne         ###   ########.fr       */
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
		std::string _absolutePath;
		std::string _extension;
		
	public:
		File();
		File(std::string absolutePath);
		File(std::string name, std::string root);
		~File();

		// methods
		void buildAbsolutePath();
		void buildExtension();
		void buildName();
		void buildRoot();

		// getters
		std::string getName();
		std::string getRoot();
		std::string getAbsolutePath() const;
		std::string getExtension();
		
};

void printVector(std::vector<std::string> v);

#endif
