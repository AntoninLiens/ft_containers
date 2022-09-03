/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliens <aliens@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:17:22 by aliens            #+#    #+#             */
/*   Updated: 2022/09/03 18:43:20 by aliens           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP

#include "node.h"
#include <memory>
#include <iostream>

namespace ft {

	/*************************************************************************************************
												RED_BLACK_TREE
	**************************************************************************************************/

	template <class Key, class T, class Compare = std::less<Key> >
	class RBTree {
	public:
		typedef Key													key_type;
		typedef T													mapped_type;
		typedef ft::Node<Key, T>									node_type;
		typedef ft::pair<const Key, T>								value_type;
		typedef Compare												key_compare;
		typedef std::allocator<ft::pair<const Key,T> >				allocator_type;
		typedef std::allocator<ft::Node<Key,T> >					node_allocator_type;
		typedef int													difference_type;
		typedef size_t												size_type;

	/******************************************_CONSTRUCTORS_******************************************/

		RBTree(const key_compare& cmp = key_compare(), const allocator_type& alloc = allocator_type(), const node_allocator_type& node_alloc = node_allocator_type())
		: _cmp(cmp), _alloc(alloc), _node_alloc(node_alloc), _size(0) {
			this->_leaf = this->_node_alloc.allocate(1);
			this->_alloc.construct(&this->_leaf->data_, value_type());
			this->_leaf->left_ = NULL;
			this->_leaf->right_ = NULL;
			this->_leaf->parent_ = NULL;
			this->_root = this->_leaf;
		}

	/******************************************_DESTRUCTOR_******************************************/

		~RBTree(void) {
			this->destroyRBTree(this->_root);
			this->_alloc.destroy(&this->_leaf->data_);
			this->_node_alloc.deallocate(this->_leaf, 1);
		}

	/******************************************_GETTERS_******************************************/

		node_type	*get_root(void) const {
			return (this->_root);
		}

		node_type	*get_leaf(void) const {
			return (this->_leaf);
		}

		key_compare	get_compare(void) const {
			return (this->_cmp);
		}

		allocator_type	get_allocator(void) const {
			return (this->_alloc);
		}

		node_allocator_type	get_node_alloc(void) const {
			return (this->_node_alloc);
		}

		size_t	get_size(void) const {
			return (this->_size);
		}
		
	/******************************************_SETTERS_******************************************/

		void	set_root(node_type *node) {
			this->_root = node;
		}

		void	set_leaf(node_type *node) {
			this->_leaf = node;
		}

		void	set_size(size_t size) {
			this->_size = size;
		}

	/******************************************_MODIFIERS_******************************************/

		node_type	*insertNode(node_type *node, value_type data) {
			if (this->_root == this->_leaf) {
				this->_size = 1;
				return (this->_root = newNode(data, false, false));
			}
			node_type	*parent = this->findParentNode(this->_root, data.first);
			if (this->_cmp(data.first, parent->data_.first)) {
				node = this->newNode(data, true, false);
				node->parent_ = parent;
				parent->left_ = node;
			}
			else if (this->_cmp(parent->data_.first, data.first)) {
				node = this->newNode(data, true, false);
				node->parent_ = parent;
				parent->right_ = node;
			}
			else {
				parent->temp_ = true;
				return (parent);
			}
			this->_size++;
			return (this->balanceInsertRB(node));
		}

		node_type	*deleteNode(node_type *node, key_type key) {
			node = this->findNode(this->_root, key);
			if (node == this->_leaf)
				return (node);
			this->_size--;
			if (node->left_ == this->_leaf && node->right_ == this->_leaf) {
				if (node == this->_root) {
					this->_alloc.destroy(&node->data_);
					this->_node_alloc.deallocate(node, 1);
					this->_root = this->_leaf;
				}
				else if (node->color_) {
					node->parent_->left_ == node ? node->parent_->left_ = this->_leaf : node->parent_->right_ = this->_leaf;
					this->_alloc.destroy(&node->data_);
					this->_node_alloc.deallocate(node, 1);
				}
				else if (!node->color_) {
					node_type	*db_node = newNode(value_type(), false, true);
					db_node->parent_ = node->parent_;
					node->parent_->left_ == node ? node->parent_->left_ = db_node : node->parent_->right_ = db_node;
					this->_alloc.destroy(&node->data_);
					this->_node_alloc.deallocate(node, 1);
					this->balanceDelRB(db_node);
				}
			}
			else {
				node_type	*tmp = node->left_ == this->_leaf ? this->minValNode(node->right_) : this->maxValNode(node->left_);
				if (tmp->left_ != this->_leaf || tmp->right_ != this->_leaf) {
					if (tmp->left_ != this->_leaf) {
						tmp->left_->color_ = false;
						tmp->left_->parent_ = tmp->parent_;
						tmp->parent_->left_ == tmp ? tmp->parent_->left_ = tmp->left_ : tmp->parent_->right_ = tmp->left_;
					}
					else {
						tmp->right_->color_ = false;
						tmp->right_->parent_ = tmp->parent_;
						tmp->parent_->left_ == tmp ? tmp->parent_->left_ = tmp->right_ : tmp->parent_->right_ = tmp->right_;
					}
					node = this->replaceNode(node, tmp);
				}
				else {
					if (tmp->color_) {
						tmp->parent_->left_ == tmp ? tmp->parent_->left_ = this->_leaf : tmp->parent_->right_ = this->_leaf;
						node = this->replaceNode(node, tmp);
					}
					else {
						node_type	*db_node = newNode(value_type(), false, true);
						db_node->parent_ = tmp->parent_;
						tmp->parent_->left_ == tmp ? tmp->parent_->left_ = db_node : tmp->parent_->right_ = db_node;
						node = this->replaceNode(node, tmp);
						this->balanceDelRB(db_node);
					}
				}
			}
			return (node);
		}

	/******************************************_OPERATIONS_******************************************/

		node_type	*searchNode(node_type *node, key_type key) const {
			if (node == this->_leaf)
				return (node);
			else if (this->_cmp(key, node->data_.first))
				node = this->searchNode(node->left_, key);
			else if (this->_cmp(node->data_.first, key))
				node = this->searchNode(node->right_, key);
			return (node);
		}

		node_type	*findNode(node_type *node, key_type key) const {
			while (node != this->_leaf) {
				if (this->_cmp(key, node->data_.first)) {
					node = node->left_;
					continue ;
				}
				else if (this->_cmp(node->data_.first, key)) {
					node = node->right_;
					continue ;
				}
				else
					return (node);
			}
			return (this->_leaf);
		}

		node_type	*findParentNode(node_type *node, key_type key) const {
			node_type	*parent;
			while (node != this->_leaf) {
				parent = node;
				if (this->_cmp(key, node->data_.first)) {
					node = node->left_;
					continue ;
				}
				else if (this->_cmp(node->data_.first, key)) {
					node = node->right_;
					continue ;
				}
				else
					return (node);
			}
			return (parent);
		}

		void	swap(RBTree &tree) {
			node_type	*tmp_root = this->_root;
			node_type	*tmp_leaf = this->_leaf;
			size_t		tmp_size = this->_size;

			this->_root = tree.get_root();
			this->_leaf = tree.get_leaf();
			this->_size = tree.get_size();

			tree.set_root(tmp_root);
			tree.set_leaf(tmp_leaf);
			tree.set_size(tmp_size);
		}

		node_type	*size_node(void) {
			if (this->_size_node) {
				this->_alloc.destroy(&this->_size_node->data_);
				this->_node_alloc.deallocate(this->_size_node, 1);
			}
			return (this->_size_node = this->newNode(ft::make_pair(this->_size, mapped_type()), false, false));
		}

	/******************************************_BALANCE_******************************************/

		node_type	*balanceInsertRB(node_type *node) {
			if (node == this->_leaf || node->parent_ == this->_root)
				return (node);
			if (!node->parent_->color_)
				return (node);
			node_type	*uncle = node->parent_->parent_->left_ == node->parent_ ? node->parent_->parent_->right_ : node->parent_->parent_->left_;
			if (uncle->color_) {
				node->parent_->color_ = false;
				uncle->color_ = false;
				if (node->parent_->parent_ != this->_root) {
					node->parent_->parent_->color_ = true;
					this->balanceInsertRB(node->parent_->parent_);
				}
			}
			else {
				node_type	*parent = node->parent_;
				node_type	*grand_parent = parent->parent_;
				if (!((node == parent->left_ && parent == grand_parent->left_) || (node == parent->right_ && parent == grand_parent->right_)))
					parent->left_ == node ? this->rotateRight(parent) : this->rotateLeft(parent);
				if (grand_parent->left_ == parent || grand_parent->left_ == node) {
					grand_parent->left_->color_ = false;
					grand_parent->color_ = true;
					this->rotateRight(grand_parent);
				}
				else {
					grand_parent->right_->color_ = false;
					grand_parent->color_ = true;
					this->rotateLeft(grand_parent);
				}
			}
			return (node);
		}

		node_type	*balanceDelRB(node_type	*db_node) {
			if (db_node == this->_root) {
				db_node->color_ = false;
				return (db_node);
			}
			node_type	*sibling = db_node->parent_->right_ == db_node ? db_node->parent_->left_ : db_node->parent_->right_;
			if (sibling->color_) {
				if (sibling->color_ != db_node->parent_->color_) {
					bool	tmp_color = db_node->parent_->color_;
					db_node->parent_->color_ = sibling->color_;
					sibling->color_ = tmp_color;
				}
				db_node->parent_->left_ == db_node ? this->rotateLeft(db_node->parent_) : this->rotateRight(db_node->parent_);
				this->balanceDelRB(db_node);
			}
			else {
				node_type	*far_child_of_sibling = db_node->parent_->left_ == db_node ? sibling->right_ : sibling->left_;
				node_type	*near_child_of_sibling = db_node->parent_->left_ == db_node ? sibling->left_ : sibling->right_;
				if (far_child_of_sibling != this->_leaf && far_child_of_sibling->color_) {
					if (sibling->color_ != db_node->parent_->color_) {
						bool	tmp_color = db_node->parent_->color_;
						db_node->parent_->color_ = sibling->color_;
						sibling->color_ = tmp_color;
					}
					db_node->parent_->left_ == db_node ? this->rotateLeft(db_node->parent_) : this->rotateRight(db_node->parent_);
					far_child_of_sibling->color_ = false;
					if (db_node->temp_) {
						db_node->parent_->left_ == db_node ? db_node->parent_->left_ = this->_leaf : db_node->parent_->right_ = this->_leaf;
						this->_alloc.destroy(&db_node->data_);
						this->_node_alloc.deallocate(db_node, 1);
					}
				}
				else if (near_child_of_sibling != this->_leaf && near_child_of_sibling->color_) {
					sibling->color_ = true;
					near_child_of_sibling->color_ = false;
					db_node->parent_->left_ == db_node ? this->rotateRight(sibling) : this->rotateLeft(sibling);
					this->balanceDelRB(db_node);
				}
				else {
					node_type	*tmparent = db_node->parent_;
					sibling->color_ = true;
					if (db_node->temp_) {
						db_node->parent_->left_ == db_node ? db_node->parent_->left_ = this->_leaf : db_node->parent_->right_ = this->_leaf;
						this->_alloc.destroy(&db_node->data_);
						this->_node_alloc.deallocate(db_node, 1);
					}
					if (tmparent->color_)
						tmparent->color_ = false;
					else
						this->balanceDelRB(tmparent);
				}
			}
			return (db_node);
		}

		void	rotateLeft(node_type *node) {
			node_type	*tmp_a = node;
			node_type	*tmp_b = node->right_->left_;
			
			node = node->right_;
			node->left_ = tmp_a;
			tmp_a->right_ = tmp_b;
			node->parent_ = tmp_a->parent_;
			if (tmp_b)
				tmp_b->parent_ = tmp_a;
			if (node->parent_)
				tmp_a == tmp_a->parent_->right_ ? node->parent_->right_ = node : node->parent_->left_ = node;
			else
				this->_root = node;
			tmp_a->parent_ = node;
		}

		void	rotateRight(node_type *node) {
			node_type	*tmp_a = node;
			node_type	*tmp_b = node->left_->right_;
			
			node = node->left_;
			node->right_ = tmp_a;
			tmp_a->left_ = tmp_b;
			node->parent_ = tmp_a->parent_;
			if (tmp_b)
				tmp_b->parent_ = tmp_a;
			if (node->parent_)
				tmp_a == tmp_a->parent_->right_ ? node->parent_->right_ = node : node->parent_->left_ = node;
			else
				this->_root = node;
			tmp_a->parent_ = node;
		}

	/******************************************_PRINT_TREE_******************************************/

		void	aff_node(node_type *node) const {
			if (!node) {
				std::cout << "NULL" << std::endl;
				return ;
			}
			std::string	color;
			node->color_ ? color = "red" : color = "black";			
			std::cout << node->data_.first << " | " << node->data_.second << " | " << color << std::endl;
		}

		void	aff_tree(node_type *node, int space) const {
			int i;
			if (this->_root == this->_leaf) {
				std::cout << std::endl;
				this->aff_node(this->_leaf);
				std::cout << std::endl;
			}
        	if (node != this->_leaf) {
        	    space = space + 10;
        	    this->aff_tree(node->right_, space);
        	    std::cout << std::endl;
        	    for (i = 10; i < space; i++)
        	        std::cout << " ";
        	    this->aff_node(node);
        	    std::cout << std::endl;
        	    this->aff_tree(node->left_, space);
        	}
		}

	/******************************************_NODE_OPERATIONS_******************************************/

		node_type	*newNode(value_type data, bool color, bool temp) {
			node_type	*tmp = this->_node_alloc.allocate(1);
			this->_alloc.construct(&tmp->data_, data);
			tmp->left_ = this->_leaf;
			tmp->right_ = this->_leaf;
			tmp->parent_ = NULL;
			tmp->color_ = color;
			tmp->temp_ = temp;
			return (tmp);
		}

		node_type	*destroyRBTree(node_type *node) {
			if (node != this->_leaf) {
				this->destroyRBTree(node->left_);
				this->destroyRBTree(node->right_);
				this->_alloc.destroy(&node->data_);
				this->_node_alloc.deallocate(node, 1);
			}
			this->_size = 0;
			return (this->_leaf);
		}
		
		node_type	*replaceNode(node_type *to_replace, node_type *replace) {
			if (to_replace == this->_root)
				this->_root = replace;
			if (replace != this->_root)
				to_replace->parent_->left_ == to_replace ? to_replace->parent_->left_ = replace : to_replace->parent_->right_ = replace;
			if (to_replace->left_ != this->_leaf)
				to_replace->left_->parent_ = replace;
			if (to_replace->right_ != this->_leaf)
				to_replace->right_->parent_ = replace;
			replace->parent_ = to_replace->parent_;
			replace->left_ = to_replace->left_;
			replace->right_ = to_replace->right_;
			replace->color_ = to_replace->color_;
			this->_alloc.destroy(&to_replace->data_);
			this->_node_alloc.deallocate(to_replace, 1);
			return (replace);
		}

		node_type	*next(node_type *node) const {
			node_type	*tmp;

			if (node->right_ == this->_leaf) {
				tmp = node;
				while (tmp->parent_ != this->_leaf && tmp == tmp->parent_->right_)
					tmp = tmp->parent_;
				tmp = tmp->parent_;
				return (tmp);
			}
			tmp = node->right_;
			while (tmp->left_ != this->_leaf)
				tmp = tmp->left_;
			return (tmp);
		}

		node_type	*prev(node_type *node) const{
			if (node == this->_leaf)
				return (this->maxValNode(this->_root));
			
			node_type	*tmp;
			if (node->left_ == this->_leaf) {
				tmp = node;
				while (tmp->parent_ != this->_leaf && tmp == tmp->parent_->left_)
					tmp = tmp->parent_;
				tmp = tmp->parent_;
				return (tmp);
			}
			tmp = node->left_;
			while (tmp->right_ != this->_leaf)
				tmp = tmp->right_;
			return (tmp);
		}
		node_type	*maxValNode(node_type *node) const {
			if (node != this->_leaf && node->right_ != this->_leaf)
				node = this->maxValNode(node->right_);
			return (node);
		}

		node_type	*minValNode(node_type *node) const {
			if (node != this->_leaf && node->left_ != this->_leaf)
				node = this->minValNode(node->left_);
			return (node);
		}

	/******************************************_SIZE_******************************************/

		size_type	height(node_type *node) {
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

		size_type nodeCount(node_type *node) const {
		    if (node == this->_leaf)
		        return (0);
		    else
		        return (this->nodeCount(node->left_) + this->nodeCount(node->right_) + 1);
		}

	private:
		node_type			*_root;
		node_type			*_leaf;
		key_compare			_cmp;
		allocator_type		_alloc;
		node_allocator_type	_node_alloc;
		size_t				_size;

	};
}

#endif
