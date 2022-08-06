/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainMap.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliens <aliens@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:38:30 by aliens            #+#    #+#             */
/*   Updated: 2022/08/06 19:02:24 by aliens           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RBTree.hpp"

int main(void) {
	ft::RBTree<const int, int>	binaryTree;
	ft::Node<const int, int>	*node = binaryTree.newNode(ft::make_pair(0, 0), false);

	for (int i = 0, j = 0; i < 10; i++, j++) {
		binaryTree.insertNode(binaryTree.get_root(), ft::make_pair(i, j));
	}

	binaryTree.aff_tree(binaryTree.get_root(), 0);

	binaryTree.deleteNode(binaryTree.get_root(), 5);

	std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;

	binaryTree.aff_tree(binaryTree.get_root(), 0);


	return (0);
}
