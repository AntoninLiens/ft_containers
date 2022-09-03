/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliens <aliens@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:08:43 by aliens            #+#    #+#             */
/*   Updated: 2022/09/03 18:14:54 by aliens           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include <algorithm>
#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"
#include <iostream>

int main ()
{
	{
		std::cout << "MAP :" << std::endl << std::endl;

		ft::map<int, std::string>	map2;
		for (size_t i = 0; i < 5; i++)
			map2[i] = "some string";

		ft::map<int, std::string>::iterator	itmodif = map2.begin();
		++itmodif;
		(*itmodif).second = "yop";
		
		std::cout << "constructors" << std::endl;
		ft::map<int, std::string>	map_default;
		ft::map<int, std::string>	map_range(map2.begin(), map2.end());
		ft::map<int, std::string>	map_copy(map_range);
		ft::map<int, std::string>	map_assigned;
		map_assigned = map_copy;

		std::cout << "map_default :" << std::endl << std::endl << "size : " << map_default.size() << std::endl << "max_size : " << map_default.max_size() << std::endl;
		std::cout << "content of map_default : " << std::endl;
		for (ft::map<int, std::string>::const_iterator	it = map_assigned.begin(); it != map_assigned.end(); it++)
			std::cout << "[ " << (*it).first << " ][ " << (*it).second << " ]" << std::endl;

		std::cout << std::endl << "map_range :" << std::endl << std::endl << "size : " << map_range.size() << std::endl << "max_size : " << map_range.max_size() << std::endl;
		std::cout << "content of map_range : " << std::endl;
		std::cout << "reverse content of map_range :" <<std::endl;
		for (ft::map<int, std::string>::const_reverse_iterator it = map_range.rbegin(); it != map_range.rend(); it++)
			std::cout << "[ " << (*it).first << " ][ " << (*it).second << " ]" << std::endl;

		std::cout << std::endl << "map_default.empty() : " << map_default.empty() << std::endl;
		std::cout << "map_range.empty() : " << map_range.empty() << std::endl;
		std::cout << "map_copy.empty() : " << map_copy.empty() << std::endl << std::endl;
	}
		//////////////////////////////////////////////
	{
		std::cout << "element access :" << std::endl << std::endl;

		ft::map<int, char>	map2;
		map2[-55] = 's';
		map2[-44] = 'a';
		map2[-33] = 'l';
		map2[-22] = 'u';
		map2[-11] = 't';

		ft::map<int, char>	map;
		for (size_t i = 0; i < 10; i++)
			map[i] = i + 65;

		std::cout << "map.count(33) = " << map.count(33) << std::endl;
		std::cout << "map[33] = 'y'" << std::endl;
		map[33] = 'y';
		std::cout << "map.count(33) = " << map.count(33) << std::endl << std::endl;

		std::cout << "map.insert(map2.begin(), map2.end())" << std::endl;
		map.insert(map2.begin(), map2.end());

		std::cout << "erase map.begin()" << std::endl;
		map.erase(map.begin());
		std::cout << "erase key -100 : " << map.erase(-100) << std::endl;
		std::cout << "erase key 66 : " << map.erase(66) << std::endl;
		std::cout << "erase key 0 : " << map.erase(0) << std::endl;

		ft::map<int, char>::iterator	it = map.find(12), ite = map.find(15);

		std::cout << "map.erase(find(12), find(15))" << std::endl;
		map.erase(it, ite);

		std::cout << std::endl << "swap map && map2" << std::endl;
		map2.swap(map);
		std::cout << "clear map" <<std::endl;
		map.clear();
		std::cout << "size of map : " << map.size() << std::endl;
		std::cout << "swap map && map2" << std::endl;
		map2.swap(map);
		std::cout << "size of map2 : " << map2.size() << std::endl;

		std::cout << "lower_bound key -1000 : [ " << (*(it = map.lower_bound(-1000))).first << " ][ " << (*it).second << " ]" << std::endl << std::endl;
		std::cout << "upper_bound key 70 : [ " << (*(it = map.upper_bound(70))).first << " ][ " << (*it).second << " ]" << std::endl << std::endl;
		ft::pair<ft::map<int, char>::iterator, ft::map<int, char>::iterator>	eqrange = map.equal_range(34);
		std::cout << "equal_range with 34 : [ " << (*(eqrange.first)).first << " ][ " << (*(eqrange.first)).second << " ] to [ " << (*(eqrange.second)).first << " ][ " << (*(eqrange.second)).second << " ]" << std::endl << std::endl;

		std::cout << "contents of map" << std::endl;
		for (ft::map<int, char>::const_iterator	it = map.begin(); it != map.end(); it++)
			std::cout << "[ " << (*it).first << " ][ " << (*it).second << " ]" << std::endl;

		map2[5] = 'j';

		std::cout << "map == map2 ? " << (map == map2) << std::endl;
		std::cout << "map != map2 ? " << (map != map2) << std::endl;
		std::cout << "map > map2 ? " << (map > map2) << std::endl;
		std::cout << "map < map2 ? " << (map < map2) << std::endl;

		std::cout << "map == map ? " << (map == map) << std::endl;
		std::cout << "map != map ? " << (map != map) << std::endl;
		std::cout << "map <= map ? " << (map <= map) << std::endl;
		std::cout << "map >= map ? " << (map >= map) << std::endl;
		std::cout << "map < map ? " << (map < map) << std::endl;
		std::cout << "map > map ? " << (map > map) << std::endl;
	}
	return 0;
}
