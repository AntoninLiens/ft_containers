/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliens <aliens@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:05:02 by aliens            #+#    #+#             */
/*   Updated: 2022/07/20 22:11:10 by aliens           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "vector.hpp"
#include <iostream>
// #include <vector>
#include "RBTree.hpp"

// #define NAMESPACE ft // change to STD if you want to compare with the STL

// int main()
// {
// 	std::cout << "~~~~TEST WITH INT~~~~~" << std::endl;
// 	NAMESPACE::vector<int> a;
// 	std::cout << "----MAX_SIZE----" << std::endl;
// 	std::cout << a.max_size() << " (is constant, no need to retest)" << std::endl;
// 	std::cout << "----SIZE----" << std::endl;
// 	std::cout << a.size() << std::endl;
// 	std::cout << "----CAPACITY----" << std::endl;
// 	std::cout << a.capacity() << std::endl;
// 	std::cout << "----EMPTY----" << std::endl;
// 	std::cout << a.empty() << std::endl;
// 	std::cout << "----PUSH_BACK + operator[] + RESERVE----" << std::endl;
// 	int j = 1;
// 	for (int i = 0; i < 30; i++)
// 	{
// 		a.push_back((j += 3) % 2 ? j : -j);
// 		std::cout << "Index " << i << " : value = " << a[i] << std::endl;
// 	}
// 	std::cout << "----SIZE----" << std::endl;
// 	std::cout << a.size() << std::endl;
// 	std::cout << "----CAPACITY----" << std::endl;
// 	std::cout << a.capacity() << std::endl;
// 	std::cout << "----EMPTY----" << std::endl;
// 	std::cout << a.empty() << std::endl;
// 	std::cout << "----RESERVE----" << std::endl;
// 	a.reserve(50);
// 	std::cout << "----SIZE----" << std::endl;
// 	std::cout << a.size() << std::endl;
// 	std::cout << "----CAPACITY----" << std::endl;
// 	std::cout << a.capacity() << std::endl;
// 	std::cout << "----AT----" << std::endl;
// 	std::cout << a.at(5) << std::endl;
// 	std::cout << a.at(15) << std::endl;
// 	try
// 	{
// 		std::cout << a.at(60) << std::endl;
// 		std::cerr << "it should throw an exception" << std::endl;
// 	}
// 	catch (std::out_of_range a)
// 	{
// 		std::cout << "An exception has been throw (and that's normal :p)" << std::endl;
// 	}
// 	std::cout << "----FRONT----" << std::endl;
// 	std::cout << a.front() << std::endl;
// 	std::cout << "----BACK----" << std::endl;
// 	std::cout << a.back() << std::endl;
// 	std::cout << "----COPY_CONSTRUCTOR----" << std::endl;
// 	NAMESPACE::vector<int> b(a);
// 	std::cout << b.size() << std::endl;
// 	for (int i = 0; i < b.size(); i++) {
// 		std::cout << "Index " << i << " : value = " << b[i] << std::endl;
// 	}
// 	std::cout << "----ASSIGN----" << std::endl;
// 	std::cout << "before : size = " << a.size() << " && capacity = " << a.capacity() << std::endl;
// 	a.assign(10, 400);
// 	for (int i = 0; i < a.size(); i++) {
// 		std::cout << "Index " << i << " : value = " << a[i] << std::endl;
// 	}
// 	std::cout << "after : size = " << a.size() << " && capacity = " << a.capacity() << std::endl;
// 	std::cout << "----CLEAR----" << std::endl;
// 	a.clear();
// 	std::cout << "----SIZE----" << std::endl;
// 	std::cout << a.size() << std::endl;
// 	std::cout << "----OPERATOR=----" << std::endl;
// 	a = b;
// 	for (int i = 0; i < a.size(); i++) {
// 		std::cout << "Index " << i << " : value = " << a[i] << std::endl;
// 	}
// 		for (int i = 0; i < b.size(); i++) {
// 		std::cout << "Index " << i << " : value = " << b[i] << std::endl;
// 	}
// 	std::cout << "----SIZE----" << std::endl;
// 	std::cout << a.size() << std::endl;
// 	std::cout << "----POP_BACK + RESIZE----" << std::endl;
// 	for (int i = 0; i < 20; i++)
// 	{
// 		a.pop_back();
// 	}
// 	for (unsigned int i = 0; i < a.size(); i++)
// 	{
// 		std::cout << "Index " << i << " : value = " << a.at(i) << std::endl;
// 	}
//  	std::cout << "----INSERT + BEGIN + END----" << std::endl;
// 	std::cout << "lets remplace the value of the index 0 by 900" << std::endl;
// 	std::cout << a.size() << std::endl;
// 	for (unsigned int i = 0; i < a.size(); i++)
// 	{
// 		std::cout << "Index " << i << " : value = " << a[i] << std::endl;
// 	}
// 	a.insert(a.begin(), 900);
// 	std::cout << a.size() << std::endl;
// 	for (unsigned int i = 0; i < a.size(); i++)
// 	{
// 		std::cout << "Index " << i << " : value = " << a[i] << std::endl;
// 	}
// 	std::cout << "Index " << 0 << " : value = " << a[0] << std::endl;
// 	std::cout << "lets add 5 x 200 to the result" << std::endl;
// 	a.insert(a.end(), 5, 200);
// 	for (unsigned int i = 0; i < a.size(); i++)
// 	{
// 		std::cout << "Index " << i << " : value = " << a[i] << std::endl;
// 	}
// 	std::cout << "lets copy b in the end of a by using insert" << std::endl;
// 	a.insert(a.end(), b.begin(), b.end());
// 	for (unsigned int i = 0; i < a.size(); i++)
// 	{
// 		std::cout << "Index " << i << " : value = " << a[i] << std::endl;
// 	}
// 	std::cout << "----ERASE + BEGIN + END----" << std::endl;
// 	std::cout << "lets remove the end element" << std::endl;
// 	a.erase(a.end() - 1);
// 	std::cout << "lets remove the two first elements" << std::endl;
// 	NAMESPACE::vector<int>::iterator it = a.begin();
// 	it = it + 2;
// 	a.erase(a.begin(), it);
// 	for (unsigned int i = 0; i < a.size(); i++)
// 	{
// 		std::cout << "Index " << i << " : value = " << a.at(i) << std::endl;
// 	}
// 	std::cout << "----SWAP----" << std::endl;
// 	a.swap(b);
// 	for (unsigned int i = 0; i < a.size(); i++)
// 	{
// 		std::cout << "Index " << i << " : value = " << a.at(i) << std::endl;
// 	}
// 	std::cout << "----OPERATORS----" << std::endl;
// 	std::cout << "a == b : "<< (a == b) << std::endl;
// 	std::cout << "a != b : "<< (a != b) << std::endl;
// 	std::cout << "a > b : "<< (a > b) << std::endl;
// 	std::cout << "a < b : "<< (a < b) << std::endl;
// 	std::cout << "~~~~MINI TEST WITH CONST CHAR *~~~~" << std::endl;
// 	std::cout << "----CONSTRUCTOR WITH VALUE----" << std::endl;
// 	NAMESPACE::vector<const char *> c(4, "coucou");
// 	std::cout << "----CONSTRUCTOR WITH ITERATORS----" << std::endl;
// 	NAMESPACE::vector<const char *> d(c.begin(), c.end());
// 	for (unsigned int i = 0; i < d.size(); i++)
// 	{
// 		std::cout << "Index " << i << " : value = " << d[i] << std::endl;
// 	}
// }