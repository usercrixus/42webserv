/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Limit.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperthui <lperthui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:00:35 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/17 16:03:29 by lperthui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIMIT_HPP
# define LIMIT_HPP

class Limit {
	
	private :
		bool	_limited;
		int		_min;
		int		_max;
	
	public :
		Limit();
		Limit(int min, int max);
		~Limit();

		//getters
		bool	getLimited();
		int		getMin();
		int		getMax();

};

#endif