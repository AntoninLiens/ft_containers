/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainMap.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliens <aliens@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:38:30 by aliens            #+#    #+#             */
/*   Updated: 2022/08/18 18:23:02 by aliens           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"
#include <sys/wait.h>

int main(void) {
	ft::map<const int, char>	map;

	map.insert(ft::make_pair(50, 65));
	map.insert(ft::make_pair(55, 65));
	map.insert(ft::make_pair(35, 65));
	map.insert(ft::make_pair(40, 65));
	map.insert(ft::make_pair(20, 65));
	map.insert(ft::make_pair(10, 65));
	map.insert(ft::make_pair(5, 65));
	map.insert(ft::make_pair(25, 65));
	map.insert(ft::make_pair(17, 65));

	std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;
	
	map.aff_tree();

	std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;

	ft::map<const int, char>::iterator	it = map.begin();
	ft::map<const int, char>::iterator	it2 = map.end();
	it++;
	std::cout << it->first << " || " << it->second << std::endl;
	std::cout << (++it)->first << std::endl;
	std::cout << it2->first << " || " << it2->second << std::endl;

	std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;

	map.clear();

	map.aff_tree();

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
