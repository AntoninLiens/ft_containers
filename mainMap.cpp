/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainMap.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliens <aliens@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:38:30 by aliens            #+#    #+#             */
/*   Updated: 2022/08/10 14:24:07 by aliens           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RBTree.hpp"

int main(void) {
	ft::RBTree<const int, char>	binaryTree;
	ft::Node<const int, char>	*node = binaryTree.newNode(ft::make_pair(0, 0), false);

	for (int i = 0, j = 0; i < 8; i++, j++) {
		binaryTree.insertNode(binaryTree.get_root(), ft::make_pair(i, 65 + j));
	}

	binaryTree.aff_tree(binaryTree.get_root(), 0);

	std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;

	binaryTree.aff_node(binaryTree.searchNode(binaryTree.get_root(), 0));
	binaryTree.aff_node(binaryTree.searchNode(binaryTree.get_root(), 5));
	binaryTree.aff_node(binaryTree.searchNode(binaryTree.get_root(), 7));
	binaryTree.aff_node(binaryTree.searchNode(binaryTree.get_root(), 3));

	std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;

	binaryTree.aff_node(binaryTree.next(binaryTree.get_root()));

	std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;

	std::cout << "size, height :" << std::endl;
	std::cout << std::endl << binaryTree.nodeCount(binaryTree.get_root()) << std::endl;
	std::cout << binaryTree.height(binaryTree.get_root()) << std::endl;

	std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;

	binaryTree.deleteNode(binaryTree.get_root(), 7);
	
	binaryTree.aff_tree(binaryTree.get_root(), 0);

	std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;
	std::cout << "size, height :" << std::endl;
	std::cout << std::endl << binaryTree.nodeCount(binaryTree.get_root()) << std::endl;
	std::cout << binaryTree.height(binaryTree.get_root()) << std::endl;

	//binaryTree.insertNode(binaryTree.get_root(), ft::make_pair(5, 5));

	//binaryTree.aff_tree(binaryTree.get_root(), 0);




	return (0);
}
