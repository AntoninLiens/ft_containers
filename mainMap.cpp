/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainMap.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliens <aliens@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:38:30 by aliens            #+#    #+#             */
/*   Updated: 2022/07/29 15:50:54 by aliens           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RBTree.hpp"

int main(void) {
	ft::RBTree<const int, int>	binaryTree;
	ft::Node<const int, int>	node;

	for (int i = 0, j = 0; i < 10; i++, j++) {
		std::cout << i << std::endl;
		binaryTree.insertNode(&node, ft::make_pair(i, j));
	}

	return (0);
}