/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliens <aliens@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:17:22 by aliens            #+#    #+#             */
/*   Updated: 2022/07/29 16:00:45 by aliens           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP

#include "pair.hpp"
#include <memory>
#include <iostream>

namespace ft {

	/*************************************************************************************************
											RED_BLACK_TREE_NODE
	**************************************************************************************************/

	template <class Key, class T>
	class Node {
	public:
		ft::pair<const Key, T>	data_;
		Node					*left_;
		Node					*right_;
		Node					*parent_;
		bool					color_;

	};

	/*************************************************************************************************
												RED_BLACK_TREE
	**************************************************************************************************/

	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T>>, class Node = ft::Node<const Key, T>>
	class RBTree {
	public:
		typedef Key													key_type;
		typedef T													mapped_type;
		typedef ft::pair<const Key,T>								value_type;
		typedef Compare												key_compare;
		typedef std::allocator<ft::pair<const Key,T> >				allocator_type;
		typedef std::allocator<ft::Node<const Key,T> >				node_allocator_type;
		typedef int													difference_type;
		typedef size_t												size_type;
		
	/******************************************_CONSTRUCTORS_******************************************/

		RBTree(const key_compare& cmp = key_compare(), const allocator_type& alloc = allocator_type(), const node_allocator_type& node_alloc = node_allocator_type())
		: _cmp(cmp), _alloc(alloc), _node_alloc(node_allocator_type()) {
			this->_leaf = this->_node_alloc.allocate(1);
			this->_alloc.construct(&this->_leaf->data_, value_type());
			this->_leaf->left_ = NULL;
			this->_leaf->right_ = NULL;
			this->_leaf->parent_ = NULL;
			this->_root = this->_leaf;
		}

		RBTree(const RBTree& tree) {}

	/******************************************_DESTRUCTOR_******************************************/

		~RBTree(void) {}

	/******************************************_MODIFIERS_******************************************/


	/******************************************_UTILS_******************************************/

		Node	*balanceRB(Node *node) {
			if (this->_ll) {
				node = this->rotateLeft(node);
				node->color_ = false;
				node->left_->color_ = true;
				this->_ll = false;
			}
			else if (this->_rr) {
				node = this->rotateRight(node);
				node->color_ = false;
				node->left_->color_ = true;
				this->_rr = false;
			}
			else if (this->_rl) {
				node->right_ = this->rotateRight(node->right_);
				node->right_->parent_ = node;
				node = this->rotateLeft(node);
				node->color_ = false;
				node->left_->color_ = true;
				this->_rl = false;
			}
			else if (this->_lr) {
				node->left_ = this->rotateLeft(node->left_);
				node->left_->parent_ = node;
				node = this->rotateRight(node);
				node->color_ = false;
				node->left_->color_ = true;
				this->_lr = false;
			}
			if (this->_f) {
				if (node->parent_->right_ == node) {
					if (node->parent_->left_ == this->_leaf || node->parent_->left_->color_ == false) {
						if (node->left_ != this->_leaf && node->left_->color_ == true)
							this->_rl = true;
						else if (node->right_ != this->_leaf && node->right_->color_ == true)
							this->_ll = true;
					}
					else {
						node->parent_->left_->color_ = false;
						node->color_ = false;
						if (node->parent_ != this->_root)
							node->parent_->color_ = true;
					}
				}
				else {
					if (node->parent_->right_ == this->_leaf || node->parent_->right_->color_ == false) {
						if (node->left_ != this->_leaf && node->left_->color_ == true)
							this->_rr = true;
						else if (node->right_ != this->_leaf & node->right_->color_ == true)
							this->_lr = true;
					}
					else {
						node->parent_->right_->color_ = false;
						node->color_ = false;
						if (node->parent_ != this->_root)
							node->parent_->color_ = true;
					}
				}
				this->_f = false;
			}
			return (node);
		}

		Node	*rotateLeft(Node *node) {
			Node	*tmpA = node->right_;
			Node	*tmpB = tmpA->left_;
			Node	*tmparent = node->parent_;

			tmpA->left_ = node;
			node->right_ = tmpB;
			node->parent_ = tmpA;
			tmpA->parent_ = tmparent;
			tmpB->parent_ = node;
			if (tmpA->parent_ == NULL)
				this->_root = tmpA;
			return (tmpA);
		}

		Node	*rotateRight(Node *node) {
			Node	*tmpA = node->left_;
			Node	*tmpB = tmpA->right_;
			Node	*tmparent = node->parent_;

			tmpA->right_ = node;
			node->left_ = tmpB;
			node->parent_ = tmpA;
			tmpA->parent_ = tmparent;
			tmpB->parent_ = node;
			if (tmpA->parent_ == NULL)
				this->_root = tmpA;
			return (tmpA);
		}

		Node	*insertNode(Node *node, value_type data) {
			if (this->_root == this->_leaf) {
				std::cout << "root" << std::endl;
				return (this->_root = newNode(data, false));
			}
			else if (node == this->_leaf) {
				std::cout << "node" << std::endl;
				return(node = newNode(data, true));
			}
			else if (this->_cmp(data.first, node->data_.first)) {
				std::cout << "yo" << std::endl;
				node->left_ = this->insertNode(node->left_, data);
				node->left_->parent_ = node;
				if (node != this->_root)
					if (node->color_ && node->left_->color_)
						this->_f = true;
			}
			else if (this->_cmp(node->data_.first, data.first)) {
				std::cout << "yo2" << std::endl;
				node->right_ = this->insertNode(node->right_, data);
				node->right_->parent_ = node;
				if (node != this->_root) {
					if (node->color_ && node->right_->color_)
						this->_f = true;
				}
			}
			return (node = this->balanceRB(node));
		}

		Node	*deleteNode(Node *node, key_type key) {
			Node	*tmp;
			if (node == this->_leaf)
				return (node);
			else if (_cmp(key, node->data_))
				node->left_ = this->deleteNode(node->left_, key);
			else if (_cmp(node->data_, key))
				node->right_ = this->deleteNode(node->right_, key);
			else {
				tmp = node->left_ != this->_leaf ? node->left_ : node->right_;
				if (tmp == this->_leaf) {
					tmp = node;
					node = this->_leaf;
				}
				else {
					if (node->left_ == this->_leaf) {
						Node	*tmparent = node->parent_;
						tmp = node;
						node = node->right_;
						node->parent_ = tmparent;
					}
					else if (node->right == this->_leaf) {
						Node	*tmparent = node->parent_;
						tmp = node;
						node = node->right;
						node->parent_ = tmparent;
					}
				}
				if (tmp->parent_ == NULL && tmp->left_ == this->_leaf && tmp->right == this->_leaf) {
					this->_alloc.destroy(&tmp->data_);
					this->_node_alloc.deallocate(tmp, 1);
					this->_root = this->_leaf;
				}
				else {
					if (this->_root == tmp)
						this->_root = node;
					this->_alloc.destroy(&tmp->data);
					this->_alloc.deallocate(tmp, 1);
				}
			}
			if (node->left != this->_leaf && node->right != this->_leaf) {
				tmp = minValNode(node->right); 
				this->_alloc.destroy(&node->data); 
				this->_alloc.construct(&node->data, tmp->data);
				node->right = delete_node(node->right, node->data);
			}
			return (node);
		}

		Node	*newNode(value_type data, bool color) {
			Node	*tmp = this->_node_alloc.allocate(1);
			this->_alloc.construct(&tmp->data_, data);
			tmp->left_ = this->_leaf;
			tmp->right_ = this->_leaf;
			tmp->parent_ = NULL;
			tmp->color_ = color;
			return (tmp);
		}

		Node	*maxValNode(Node *node) {
			if (node && node->right_ != this->_leaf)
				this->maxValNode(node->right_);
			return (node);
		}

		Node	*minValNode(Node *node) {
			if (node && node->left_ != this->_leaf)
				this->minValNode(node->left_);
			return (node);
		}

		size_type	height(Node *node) {
			if (node == this->_leaf)
				return (0);
			else {
				size_type	left_depth = this->height(node->left_);
				size_type	right_depth = this->height(node->right_);
				if (left_depth > right_depth)
					return (left_depth + 1);
				else
					return (right_depth + 1);
			}
		}

		size_type nodeCount(Node *node) {
		    if (node == this->_leaf)
		        return (0);
		    else
		        return (this->nodeCount(node->left_) + this->nodeCount(node->right_) + 1);
		}

	private:
		Node				*_root;
		Node				*_leaf;
		key_compare			_cmp;
		bool				_ll = false;
		bool				_rl = false;
		bool				_rr = false;
		bool				_lr = false;
		bool				_f = false;
		allocator_type		_alloc;
		node_allocator_type	_node_alloc;

	};
}

#endif