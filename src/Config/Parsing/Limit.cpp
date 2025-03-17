/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Limit.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperthui <lperthui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:03:39 by lperthui          #+#    #+#             */
/*   Updated: 2025/03/17 16:06:38 by lperthui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Limit.hpp"

Limit::Limit() : _limited(0) {

}

Limit::Limit(int min, int max) : _limited(1), _min(min), _max(max) { }

Limit::~Limit() {}

		//getters
bool	Limit::getLimited() {
	return _limited;
}

int		Limit::getMin() {
	return _min;
}

int		Limit::getMax() {
	return _max;
}
