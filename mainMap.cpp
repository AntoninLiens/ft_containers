/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainMap.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliens <aliens@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:38:30 by aliens            #+#    #+#             */
/*   Updated: 2022/08/09 12:36:53 by aliens           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RBTree.hpp"

int main(void) {
	ft::RBTree<const int, char>	binaryTree;
	ft::Node<const int, char>	*node = binaryTree.newNode(ft::make_pair(0, 0), false);

	for (int i = 0, j = 0; i < 10; i++, j++) {
		binaryTree.insertNode(binaryTree.get_root(), ft::make_pair(i, 65 + j));
	}

	binaryTree.aff_tree(binaryTree.get_root(), 0);

//	binaryTree.deleteNode(binaryTree.get_root(), 7);

	std::cout << std::endl << binaryTree.nodeCount(binaryTree.get_root()) << std::endl;

//	binaryTree.aff_tree(binaryTree.get_root(), 0);

	//binaryTree.insertNode(binaryTree.get_root(), ft::make_pair(5, 5));

//	std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;

	//binaryTree.aff_tree(binaryTree.get_root(), 0);

	return (0);
}
