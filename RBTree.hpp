/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliens <aliens@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:17:22 by aliens            #+#    #+#             */
/*   Updated: 2022/07/11 17:07:31 by aliens           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP

#define RED=1
#define BLACK=2

#include "pair.hpp"
#include <memory>
#include <functional>

namespace ft {

	/*************************************************************************************************
											RED_BLACK_TREE_NODE
	**************************************************************************************************/

	template <class T>
	class Node {
	public:
		typedef T	value_type;

		value_type	data_;
		Node		*left_;
		Node		*right_;
		Node		*parent_;
		bool		color_;

	};

	/*************************************************************************************************
												RED_BLACK_TREE
	**************************************************************************************************/

	template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T>>
	class RBTree {
	public:
		typedef T							value_type;
		typedef Compare						value_compare;
		typedef	Alloc						allocator_type;
		typedef ft::Node<T>					node_type;
		typedef std::allocator<ft::Node<T>>	node_allocator_type;
		
	/******************************************_CONSTRUCTORS_******************************************/

		RBTree(void)
		: _cmp(cmp), _alloc(alloc), _node_alloc(node_allocator_type()) {
			this->_leaf = this->new_node(value_type());
			this->_root = this->_leaf;
		}

		RBTree(const RBTree& tree) {}

	/******************************************_DESTRUCTOR_******************************************/

		~RBTree(void) {}

	/******************************************_MODIFIERS_******************************************/


	/******************************************_UTILS_******************************************/

		node_type	*insert(node_type *node, value_type data) {
			if (node == this->_leaf)
				return(node = new_node(data));
			else if (_cmp(data, node->data_)) {
				node->left_ = this->insert(node->left_, data);
				node->left_->parent_ = node;
			}
			else if (_cmp(node->data_, data)) {
				node->right_ = this->insert(node->right_, data);
				node->right_->parent_ = node;
			}
			return (node);
		}

		node_type	*new_node(value_type data) {
			Node	*tmp = this->_node_alloc.allocate(1);
			this->_alloc.construct(&tmp->data_, data);
			tmp->left_ = NULL;
			tmp->right_ = NULL;
			tmp->parent_ = NULL;
			tmp->color_ = true;
			return (tmp);
		}

	private:
		node_type			*_root;
		node_type			*_leaf;
		value_compare		_cmp;
		allocator_type		_alloc;
		node_allocator_type	_node_alloc;

	};
}

#endif