/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainMap.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliens <aliens@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:38:30 by aliens            #+#    #+#             */
/*   Updated: 2022/08/17 15:37:13 by aliens           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RBTree.hpp"

int main(void) {
	ft::RBTree<const int, char>	binaryTree;
	ft::Node<const int, char>	*node = binaryTree.newNode(ft::make_pair(0, 0), false, false);

	binaryTree.insertNode(binaryTree.get_root(), ft::make_pair(50, 65));
	binaryTree.insertNode(binaryTree.get_root(), ft::make_pair(55, 65));
	binaryTree.insertNode(binaryTree.get_root(), ft::make_pair(35, 65));
	binaryTree.insertNode(binaryTree.get_root(), ft::make_pair(40, 65));
	binaryTree.insertNode(binaryTree.get_root(), ft::make_pair(20, 65));
	binaryTree.insertNode(binaryTree.get_root(), ft::make_pair(10, 65));
	binaryTree.insertNode(binaryTree.get_root(), ft::make_pair(5, 65));
	binaryTree.insertNode(binaryTree.get_root(), ft::make_pair(25, 65));
	binaryTree.insertNode(binaryTree.get_root(), ft::make_pair(17, 65));

	binaryTree.aff_tree(binaryTree.get_root(), 0);

	std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;

	std::cout << "size, height :" << std::endl;
	std::cout << std::endl << binaryTree.nodeCount(binaryTree.get_root()) << std::endl;
	std::cout << binaryTree.height(binaryTree.get_root()) << std::endl;

	std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;

	ft::RBTree<const int, char>::iterator	it = binaryTree.begin();
	// ft::RBTree<const int, char>::iterator	itbis = binaryTree.begin();
	// ft::RBTree<const int, char>::const_iterator	cit = binaryTree.begin();
	// binaryTree.aff_node(it.get_node());
	// if (it != itbis)
	// 	binaryTree.aff_node(itbis.get_node());
	// binaryTree.aff_node(cit.get_node());
	it--;
	// cit++;
	binaryTree.aff_node(it.get_node());
	// binaryTree.aff_node(cit.get_node());
	it++;
	// cit--;
	binaryTree.aff_node(it.get_node());
	it--;
	binaryTree.aff_node(it.get_node());
	// binaryTree.aff_node(cit.get_node());

	std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;

	binaryTree.deleteNode(binaryTree.get_root(), 20);
	binaryTree.deleteNode(binaryTree.get_root(), 35);
	
	binaryTree.aff_tree(binaryTree.get_root(), 0);

	std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;
	
	std::cout << "size, height :" << std::endl;
	std::cout << std::endl << binaryTree.nodeCount(binaryTree.get_root()) << std::endl;
	std::cout << binaryTree.height(binaryTree.get_root()) << std::endl;

	std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;

	ft::RBTree<const int, char>::iterator	it2 = binaryTree.begin();
	// ft::RBTree<const int, char>::const_iterator	cit = binaryTree.begin();
	binaryTree.aff_node(it2.get_node());
	// binaryTree.aff_node(cit.get_node());
	it2++;
	// cit++;
	binaryTree.aff_node(it2.get_node());
	// binaryTree.aff_node(cit.get_node());
	it2--;
	// cit--;
	binaryTree.aff_node(it2.get_node());
	it2++;
	binaryTree.aff_node(it2.get_node());
	// binaryTree.aff_node(cit.get_node());

	return (0);
}
