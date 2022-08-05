/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainMap.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliens <aliens@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:38:30 by aliens            #+#    #+#             */
/*   Updated: 2022/08/06 01:21:48 by aliens           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RBTree.hpp"

int main(void) {
	ft::RBTree<const int, int>	binaryTree;
	ft::Node<const int, int>	*node = binaryTree.newNode(ft::make_pair(0, 0), false);

	for (int i = 0, j = 0; i < 10; i++, j++) {
		binaryTree.insertNode(binaryTree.get_root(), ft::make_pair(i, j));
	}

	binaryTree.aff_node(binaryTree.get_root());
	binaryTree.aff_tree(binaryTree.get_root());

	return (0);
}
