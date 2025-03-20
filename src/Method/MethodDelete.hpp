/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodDelete.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:38:09 by achaisne          #+#    #+#             */
/*   Updated: 2025/03/20 18:39:47 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef METHODDELETE_HPP
#define METHODDELETE_HPP

#include "IMethod.hpp"


class MethodDelete : public IMethod
{
	private:

	public:
		MethodDelete(Request &request);
		~MethodDelete();

		void handle();
};

#endif // METHODDELETE_HPP
