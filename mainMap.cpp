/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainMap.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliens <aliens@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:38:30 by aliens            #+#    #+#             */
/*   Updated: 2022/08/20 20:10:34 by aliens           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"
#include <sys/wait.h>

int main(void) {
	ft::map<const int, char>	map;

	map.insert(ft::make_pair(5, 65));
	map.insert(ft::make_pair(6, 65));
	map.insert(ft::make_pair(7, 65));
	map.insert(ft::make_pair(8, 65));
	map.insert(ft::make_pair(18, 65));
	map.insert(ft::make_pair(1, 65));
	map.insert(ft::make_pair(-4, 65));
	map.insert(ft::make_pair(1000, 65));
	map.insert(ft::make_pair(2, 65));
	map.insert(ft::make_pair(84, 65));
	map.insert(ft::make_pair(69, 65));
	map.insert(ft::make_pair(420, 65));
	map.insert(ft::make_pair(42, 65));
	map.insert(ft::make_pair(19, 65));
	map.insert(ft::make_pair(101, 65));

	std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;
	
	map.aff_tree();

	std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;

	ft::map<const int, char>::iterator	it = map.begin();
	ft::map<const int, char>::iterator	it2 = map.end();
	for (;it != it2; it++)
		std::cout << it->first << " | " << it->second << std::endl;

	std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;

	map.erase(6);
	map.erase(5);
	map.erase(84);
	map.erase(19);
	map.erase(101);
	map.erase(1000);
	map.erase(420);

	map.aff_tree();

	std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;
	// ft::RBTree<const int, char>	binaryTree;

	// binaryTree.insertNode(binaryTree.get_root(), ft::make_pair(50, 65));
	// binaryTree.insertNode(binaryTree.get_root(), ft::make_pair(55, 65));
	// binaryTree.insertNode(binaryTree.get_root(), ft::make_pair(35, 65));
	// binaryTree.insertNode(binaryTree.get_root(), ft::make_pair(40, 65));
	// binaryTree.insertNode(binaryTree.get_root(), ft::make_pair(20, 65));
	// binaryTree.insertNode(binaryTree.get_root(), ft::make_pair(10, 65));
	// binaryTree.insertNode(binaryTree.get_root(), ft::make_pair(5, 65));
	// binaryTree.insertNode(binaryTree.get_root(), ft::make_pair(25, 65));
	// binaryTree.insertNode(binaryTree.get_root(), ft::make_pair(17, 65));

	// binaryTree.aff_tree(binaryTree.get_root(), 0);


	// std::cout << "size, height :" << std::endl;
	// std::cout << std::endl << binaryTree.nodeCount(binaryTree.get_root()) << std::endl;
	// std::cout << binaryTree.height(binaryTree.get_root()) << std::endl;

	// std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;

	// ft::RBTree<const int, char>::iterator	it = binaryTree.begin();
	// // ft::RBTree<const int, char>::iterator	itbis = binaryTree.begin();
	// // ft::RBTree<const int, char>::const_iterator	cit = binaryTree.begin();
	// binaryTree.aff_node(it.get_node());
	// // if (it != itbis)
	// // 	binaryTree.aff_node(itbis.get_node());
	// // binaryTree.aff_node(cit.get_node());
	// it--;
	// // cit++;
	// binaryTree.aff_node(it.get_node());
	// // binaryTree.aff_node(cit.get_node());
	// it++;
	// // cit--;
	// binaryTree.aff_node(it.get_node());
	// it--;
	// binaryTree.aff_node(it.get_node());
	// // binaryTree.aff_node(cit.get_node());

	// std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;

	// binaryTree.deleteNode(binaryTree.get_root(), 20);
	// binaryTree.deleteNode(binaryTree.get_root(), 35);
	
	// binaryTree.aff_tree(binaryTree.get_root(), 0);

	// std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;
	
	// std::cout << "size, height :" << std::endl;
	// std::cout << std::endl << binaryTree.nodeCount(binaryTree.get_root()) << std::endl;
	// std::cout << binaryTree.height(binaryTree.get_root()) << std::endl;

	// std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;

	// ft::RBTree<const int, char>::iterator	it2 = binaryTree.begin();
	// // ft::RBTree<const int, char>::const_iterator	cit = binaryTree.begin();
	// binaryTree.aff_node(it2.get_node());
	// // binaryTree.aff_node(cit.get_node());
	// it2++;
	// // cit++;
	// binaryTree.aff_node(it2.get_node());
	// // binaryTree.aff_node(cit.get_node());
	// it2--;
	// // cit--;
	// binaryTree.aff_node(it2.get_node());
	// it2++;
	// binaryTree.aff_node(it2.get_node());
	// // binaryTree.aff_node(cit.get_node());

	return (0);
}
