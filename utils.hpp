/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliens <aliens@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 15:47:53 by aliens            #+#    #+#             */
/*   Updated: 2022/09/03 16:03:16 by aliens           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

#include "map.hpp"
#include <map>

namespace ft {

	template<typename T1, typename T2>
	void	printMap(typename const ft::map<T1, T2> &map, std::string name) {
		std::cout << name  << " :" << std::endl << std::endl;
		std::cout << "size : " << map.size() << std::endl;
		std::cout << "max_size : " << map.max_size() << std::endl;
		std::cout << "content : " << std::endl;
		for (ft::map<T1, T2>::const_iterator it = map.begin(), ite = map.end(); it != ite; it++)
			std::cout << name << "[ " << it.first << " ][ " << it.second << " ]" << std::endl;
	};

}

#endif