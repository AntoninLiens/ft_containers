/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliens <aliens@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:08:43 by aliens            #+#    #+#             */
/*   Updated: 2022/09/06 13:42:43 by aliens           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include <algorithm>
#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"
#include <iostream>
#include <math.h>

int main ()
{
	{
		{
			std::cout << "MAP :" << std::endl;

			ft::map<int, std::string>	map2;
			for (size_t i = 0; i < 5; i++)
				map2[i] = "some string";

			ft::map<int, std::string>::iterator	itmodif = map2.begin();
			++itmodif;
			(*itmodif).second = "yop";

			ft::map<int, std::string>	map_default;
			ft::map<int, std::string>	map_range(map2.begin(), map2.end());
			ft::map<int, std::string>	map_copy(map_range);
			ft::map<int, std::string>	map_assigned;
			map_assigned = map_copy;

			std::cout << "map_default :" << std::endl << "size : " << map_default.size() << std::endl << "max_size : " << map_default.max_size() << std::endl;
			std::cout << "map_default.empty() : " << map_default.empty() << std::endl;

			std::cout << std::endl << "map_assigned :" << std::endl << "size : " << map_assigned.size() << std::endl << "max_size : " << map_assigned.max_size() << std::endl;
			std::cout << "content of map_assigned : " << std::endl;
			for (ft::map<int, std::string>::const_iterator	it = map_assigned.begin(); it != map_assigned.end(); it++)
				std::cout << "[ " << (*it).first << " ][ " << (*it).second << " ]" << std::endl;
			std::cout << "map_assigned.empty() : " << map_assigned.empty() << std::endl;
			std::cout << "map_copy.empty() : " << map_copy.empty() << std::endl;

			std::cout << std::endl << "map_range :" << std::endl << "size : " << map_range.size() << std::endl << "max_size : " << map_range.max_size() << std::endl;
			std::cout << "content of map_range : " << std::endl;
			std::cout << "reverse content of map_range :" <<std::endl;
			for (ft::map<int, std::string>::const_reverse_iterator it = map_range.rbegin(); it != map_range.rend(); it++)
				std::cout << "[ " << (*it).first << " ][ " << (*it).second << " ]" << std::endl;
			std::cout << "map_range.empty() : " << map_range.empty() << std::endl << std::endl;

			// std::sort(map2.begin(), map2.end());
			// std::cout << std::endl << "sort map2 :" << std::endl;
			// std::cout << std::endl << "content of map2 :" << std::endl;
			// for (ft::map<int, std::string>::const_iterator it1 = map2.begin(), it2 = map2.end(); it1 != it2; it1++)
			// 	std::cout << "[ " << it1->first << " ][ " << it1->second << " ]" << std::endl;

		}

		{
			std::cout << "element access :" << std::endl;

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

			std::cout << std::endl;
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
			std::cout << "map > map ? " << (map > map) << std::endl << std::endl;
		}
	}

	std::cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << std::endl << std::endl;

	{
		std::cout << "Vector:" << std::endl;
		std::srand(19);

		{

			ft::vector<int>	vdefault;
			std::cout << "size of vdefault : " << vdefault.size() << std::endl;
			std::cout << "max_size of vdefault : " << vdefault.max_size() << std::endl;
			std::cout << "capacity of vdefault : " << vdefault.capacity() << std::endl;
			std::cout << "vdefault.empty() : " << vdefault.empty() << std::endl; 

			ft::vector<int>	vfill(4, -5);
			std::cout << std::endl << "size of vfill : " << vfill.size() << std::endl;
			std::cout << "max_size of vfill : " << vfill.max_size() << std::endl;
			std::cout << "vfill.empty() : " << vfill.empty() << std::endl; 
			std::cout << "capacity of vfill : " << vfill.capacity() << std::endl;
			std::cout << "content of vfill :" << std::endl;
			for (size_t i = 0; i < vfill.size(); i++)
				std::cout << vfill[i] << std::endl;

			std::list<int>	templist;
			for (size_t i = 0; i < 4; i++)
				templist.push_back(i * i);

			ft::vector<int>	vrange(templist.begin(), templist.end());
			std::cout << std::endl << "size of vrange : " << vrange.size() << std::endl;
			std::cout << "max_size of vrange : " << vrange.max_size() << std::endl;
			std::cout << "vrange.empty() : " << vrange.empty() << std::endl; 
			std::cout << "capacity of vrange : " << vrange.capacity() << std::endl;
			std::cout << "content of vrange :" << std::endl;
			for (size_t i = 0; i < vrange.size(); i++)
				std::cout << vrange[i] << std::endl;

			ft::vector<int>	vcopy(vfill);
			std::cout << std::endl << "size of vcopy : " << vcopy.size() << std::endl;
			std::cout << "max_size of vcopy : " << vcopy.max_size() << std::endl;
			std::cout << "vcopy.empty() : " << vcopy.empty() << std::endl; 
			std::cout << "capacity of vcopy : " << vcopy.capacity() << std::endl;
			std::cout << "content of vcopy :" << std::endl;
			for (size_t i = 0; i < vcopy.size(); i++)
				std::cout << vcopy[i] << std::endl;

			vdefault = vrange;
			std::cout << std::endl << "size of vdefault : " << vdefault.size() << std::endl;
			std::cout << "max_size of vdefault : " << vdefault.max_size() << std::endl;
			std::cout << "vdefault.empty() : " << vdefault.empty() << std::endl; 
			std::cout << "capacity of vdefault : " << vdefault.capacity() << std::endl;
			std::cout << "content of vdefault :" << std::endl;
			for (size_t i = 0; i < vdefault.size(); i++)
				std::cout << vdefault[i] << std::endl;
		}

		{
			ft::vector<int>	v;
			for (size_t i = 0; i < 10; i++)
				v.push_back(rand() % 1000);
			
			std::cout << std::endl << "content of v :" << std::endl;
			for (ft::vector<int>::const_iterator it1 = v.begin(), it2 = v.end(); it1 < it2; it1++)
				std::cout << *it1 << std::endl;

			std::cout << std::endl << "reverse content of v :" << std::endl;
			for (ft::vector<int>::reverse_iterator it1 = v.rbegin(), it2 = v.rend(); it1 < it2; it1++)
				std::cout << *it1 << std::endl;

			std::sort(v.begin(), v.end());
			std::cout << std::endl << "sort v :" << std::endl;
			std::cout << std::endl << "content of v :" << std::endl;
			for (ft::vector<int>::const_iterator it1 = v.begin(), it2 = v.end(); it1 < it2; it1++)
				std::cout << *it1 << std::endl;
		}

		{
			ft::vector<int>	v;
			std::cout << "capacity of v : " << v.capacity() << std::endl;
			v.reserve(10);
			std::cout << "capacity of v after reserve(10) : " << v.capacity() << std::endl;
			for (size_t i = 0; i < v.capacity(); i++)
				v.push_back(rand() % 50);

			std::cout << std::endl << "v[3] = -7" << std::endl << "v.at(8) = -7" << std::endl;
			v[3] = -7;
			v.at(8) = -7;
			std::cout << "content of v :" << std::endl;
			for (size_t i = 0; i < v.size(); i++)
				std::cout << "index " << i << " : " << v[i] << std::endl;

			std::cout << std::endl << "front : " << v.front() << " | back : " << v.back() << std::endl;
			std::cout << "index 2 : " << v[3] << " | index 7 : " << v.at(8) << std::endl;
			try
			{
				std::cout << v.at(19);
			}
			catch(const std::exception& e)
			{
				std::cout << "Exception : " << e.what() << std::endl;
			}
		}

		{
			ft::vector<int>	v;
			std::cout << std::endl << "v.assign(9, -3)" << std::endl;
			v.assign(9, -3);
			std::cout << "content of v :" << std::endl;
			for (size_t i = 0; i < v.size(); i++)
				std::cout << v[i] << std::endl;

			std::list<int>	l;
			for (size_t i = 0; i < 5; i++)
				l.push_front(i);
			std::cout << std::endl << "v.assign(list.begin(), list.end())" << std::endl;
			v.assign(l.begin(), l.end());
			std::cout << "content of v :" << std::endl;
			for (size_t i = 0; i < v.size(); i++)
				std::cout << v[i] << std::endl;

			std::cout << std::endl << "v.pop_back()" << std::endl << "v.push_back(5)" << std::endl;
			v.pop_back();
			v.push_back(-5);
			std::cout << "content of v :" << std::endl;
			for (size_t i = 0; i < v.size(); i++)
				std::cout << v[i] << std::endl;

			std::cout << "v.insert(v.begin() + 1, -2)" << std::endl;
			v.insert(v.begin() + 1, -2);
			std::cout << "v.insert(v.end() - 1, 5, -19)" << std::endl;
			v.insert(v.end() - 1, 5, -19);
			std::cout << "content of v :" << std::endl;
			for (size_t i = 0; i < v.size(); i++)
				std::cout << v[i] << std::endl;

			std::list<int>::reverse_iterator	ritl = l.rbegin();
			for (size_t i = 0; i < 3; i++)
				++ritl;
			std::cout << "v.insert(v.begin(), l.rbegin(), ritl)" << std::endl;
			v.insert(v.begin(), l.rbegin(), ritl);
			std::cout << "content of v" << std::endl;
			for (size_t i = 0; i < v.size(); i++)
				std::cout << v[i] << std::endl;

			std::cout << "v.erase(v.begin() + 4)" << std::endl << "v.erase(v.end() - 5, v.end())" << std::endl;
			v.erase(v.begin() + 4);
			v.erase(v.end() - 5, v.end());
			std::cout << "content of v :" << std::endl;
			for (size_t i = 0; i < v.size(); i++)
				std::cout << v[i] << std::endl;

			std::cout << std::endl << "swap v with vector(3, -7)" << std::endl;
			ft::vector<int>(3, -7).swap(v);
			std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
			std::cout << "content of v :" <<std::endl;
			for (size_t i = 0; i < v.size(); i++)
				std::cout << v[i] << std::endl;

			std::cout << std::endl << "v.clear()" << std::endl;
			v.clear();
			std::cout << "size : " << v.size() << " | capacity : " << v.capacity() << std::endl;
		}

		{
			ft::vector<int>	s1, s2;
			for (size_t i = 0; i < 5; i++) {
				s1.push_back(rand() % 5);
				s2.push_back(rand() % 5);
			}

			std::cout << "s1 == s2 : " << (s1 == s2) << std::endl;
			std::cout << "s1 != s2 : " << (s1 != s2) << std::endl;
			std::cout << "s1 < s2 : " << (s1 < s2) << std::endl;
			std::cout << "s1 <= s2 : " << (s1 <= s2) << std::endl;
			std::cout << "s1 > s2 : " << (s1 > s2) << std::endl;
			std::cout << "s1 >= s2 : " << (s1 >= s2) << "\n\n";

			std::cout << std::endl << "content of s1 :" << std::endl;
			for (size_t i = 0; i < s1.size(); i++)
				std::cout << s1[i] << std::endl;

			std::cout << std::endl << "content of s2 :" << std::endl;
			for (size_t i = 0; i < s2.size(); i++)
				std::cout << s2[i] << std::endl;
		}

	}

	std::cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << std::endl << std::endl;

	{
		std::cout << "Stack :" << std::endl;
		ft::stack<int, ft::vector<int> > s1, s2;

		for (size_t i = 0; i < 10; i++) {
			s1.push(pow(-1, i) * i);
			s2.push(i);
		}

		s2.pop();
		
		std::cout << "s1 == s2 : " << (s1 == s2) << std::endl;
		std::cout << "s1 != s2 : " << (s1 != s2) << std::endl;
		std::cout << "s1 < s2 : " << (s1 < s2) << std::endl;
		std::cout << "s1 <= s2 : " << (s1 <= s2) << std::endl;
		std::cout << "s1 > s2 : " << (s1 > s2) << std::endl;
		std::cout << "s1 >= s2 : " << (s1 >= s2) << std::endl << std::endl;

		std::cout << "size of s1 : " << s1.size() << std::endl;
		std::cout << "content of s1 : " << std::endl;
		while (!(s1.empty())) {
			std::cout << "[ " << s1.top() << " ]" << std::endl;
			s1.pop();
		}

		std::cout <<std::endl << "size of s2 : " << s2.size() << std::endl;
		std::cout << "content of s2 : " << std::endl;
		while (!(s2.empty())) {
			std::cout << "[ " << s2.top() << " ]" << std::endl;
			s2.pop();
		}
	}
	
	return 0;
}
