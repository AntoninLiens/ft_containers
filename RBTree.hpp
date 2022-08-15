/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliens <aliens@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:17:22 by aliens            #+#    #+#             */
/*   Updated: 2022/08/15 13:52:24 by aliens           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP

#include "iterator.hpp"
#include "pair.hpp"
#include <memory>
#include <iostream>

namespace ft {

	/*************************************************************************************************
											RED_BLACK_TREE_NODE
	**************************************************************************************************/

	template <class Key, class T>
	struct Node {
		ft::pair<const Key, T>	data_;
		Node					*left_;
		Node					*right_;
		Node					*parent_;
		bool					color_;
		bool					temp_;

	};

	/*************************************************************************************************
												RED_BLACK_TREE
	**************************************************************************************************/

	template <class Key, class T, class Compare = std::less<Key> >
	class RBTree {
	public:
		typedef Key													key_type;
		typedef T													mapped_type;
		typedef ft::Node<const Key, T>								node_type;
		typedef ft::pair<const Key, T>								value_type;
		typedef Compare												key_compare;
		typedef std::allocator<ft::pair<const Key,T> >				allocator_type;
		typedef std::allocator<ft::Node<const Key,T> >				node_allocator_type;
		typedef int													difference_type;
		typedef size_t												size_type;
		typedef ft::tree_iterator<node_type>							iterator;
		typedef ft::tree_iterator<const node_type>					const_iterator;
		
	/******************************************_CONSTRUCTORS_******************************************/

		RBTree(const key_compare& cmp = key_compare(), const allocator_type& alloc = allocator_type(), const node_allocator_type& node_alloc = node_allocator_type())
		: _cmp(cmp), _alloc(alloc), _node_alloc(node_alloc), _ll(false), _rl(false), _rr(false), _lr(false), _f(false) {
			this->_leaf = this->_node_alloc.allocate(1);
			this->_alloc.construct(&this->_leaf->data_, value_type());
			this->_leaf->left_ = NULL;
			this->_leaf->right_ = NULL;
			this->_leaf->parent_ = NULL;
			this->_root = this->_leaf;
		}

		RBTree(const RBTree& tree)
		: _cmp(tree.get_compare()), _alloc(tree.get_allocator()), _node_alloc(tree.get_node_alloc()), _ll(false), _rl(false), _rr(false), _lr(false), _f(false) {}

	/******************************************_DESTRUCTOR_******************************************/

		~RBTree(void) {}

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

	/******************************************_ITERATORS_******************************************/

		iterator	begin(void) {
			return (iterator(this->_root, this->_leaf));
		}

		const_iterator	begin(void) const {
			return (const_iterator(this->_root, this->_leaf));
		}

		iterator	end(void) {
			return (iterator(this->_leaf, this->_leaf));
		}

		const_iterator	end(void) const {
			return (const_iterator(this->_leaf, this->_leaf));
		}

	/******************************************_MODIFIERS_******************************************/

		node_type	*insertNode(node_type *node, value_type data) {
			if (this->_root == this->_leaf)
				return (this->_root = newNode(data, false, false));
			else if (node == this->_leaf)
				return (node = newNode(data, true, false));
			else if (this->_cmp(data.first, node->data_.first)) {
				node->left_ = this->insertNode(node->left_, data);
				node->left_->parent_ = node;
				if (node != this->_root)
					if (node->color_ && node->left_->color_)
						this->_f = true;
			}
			else if (this->_cmp(node->data_.first, data.first)) {
				node->right_ = this->insertNode(node->right_, data);
				node->right_->parent_ = node;
				if (node != this->_root) {
					if (node->color_ && node->right_->color_)
						this->_f = true;
				}
			}
			return (node = this->balanceInsertRB(node));
		}

		node_type	*deleteNode(node_type *node, key_type key) {
			node = this->findNode(this->_root, key);
			if (node == this->_leaf)
				return (node);
			if (node->left_ == this->_leaf && node->right_ == this->_leaf) {
				if (node->color_ || node == this->_root) {
					this->_alloc.destroy(&node->data_);
					this->_node_alloc.deallocate(node, 1);
				}
				else if (!node->color_) {
					node_type	*db_node = newNode(value_type(), false, true);
					db_node->parent_ = node->parent_;
					node->parent_->left_ == node ? node->parent_->left_ = db_node : node->parent_->right_ = db_node;
					this->balanceDelRB(db_node);
				}
			}
			else {
				node_type	*tmp = this->minValNode(node);
				if (tmp->left_ != this->_leaf || tmp->right_ != this->_leaf) {
					if (tmp->left_ != this->_leaf) {
						tmp->color_ = false;
						tmp->left_->parent_ = tmp->parent_;
						tmp->parent_->left_ == tmp ? tmp->parent_->left_ = tmp->left_ : tmp->parent_->right_ = tmp->left_;
					}
					else {
						tmp->color_ = false;
						tmp->right_->parent_ = tmp->parent_;
						tmp->parent_->left_ == tmp ? tmp->parent_->left_ = tmp->right_ : tmp->parent_->right_ = tmp->right_;
					}
					node = this->swapNode(node, tmp);
				}
				else {
					if (tmp->color_) {
						tmp->parent_->left_ == tmp ? tmp->parent_->left_ = this->_leaf : tmp->parent_->right_ = this->_leaf;
						node = this->swapNode(node, tmp);
					}
					else {
						node_type	*db_node = newNode(value_type(), false, true);
						db_node->parent_ = tmp->parent_;
						tmp->parent_->left_ == tmp ? tmp->parent_->left_ = db_node : tmp->parent_->right_ = db_node;
						node = this->swapNode(node, tmp);
						this->balanceDelRB(db_node);
					}
				}
			}
			return (node);
		}

	/******************************************_OPERATIONS_******************************************/

		node_type	*searchNode(node_type *node, key_type key) {
			if (node == this->_leaf)
				return (node);
			else if (this->_cmp(key, node->data_.first))
				node = this->searchNode(node->left_, key);
			else if (this->_cmp(node->data_.first, key))
				node = this->searchNode(node->right_, key);
			return (node);
		}

		node_type	*findNode(node_type *node, key_type key) {
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

	/******************************************_BALANCE_******************************************/

		node_type	*balanceInsertRB(node_type *node) {
			if (this->_ll) {
				node = this->rotateLeft(node);
				node->color_ = false;
				node->left_->color_ = true;
				this->_ll = false;
			}
			else if (this->_rr) {
				node = this->rotateRight(node);
				node->color_ = false;
				node->right_->color_ = true;
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

		node_type	*balanceDelRB(node_type	*db_node) {
			if (db_node->parent_ == NULL) {
				db_node->color_ = false;
				return (db_node);
			}
			node_type	*sibling;
			db_node->parent_->right_ == db_node ? sibling = db_node->parent_->left_ : sibling = db_node->parent_->right_;
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
				node_type	*far_child_of_sibling;
				db_node->parent_->left_ == db_node ? far_child_of_sibling = sibling->right_ : far_child_of_sibling = sibling->left_;
				node_type	*near_child_of_sibling;
				db_node->parent_->left_ == db_node ? near_child_of_sibling = sibling->left_ : near_child_of_sibling = sibling->right_;
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
					if (sibling != this->_leaf)
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

		node_type	*rotateLeft(node_type *node) {
			node_type	*tmpA = node->right_;
			node_type	*tmpB = tmpA->left_;
			node_type	*tmparent = node->parent_;

			tmpA->left_ = node;
			node->right_ = tmpB;
			node->parent_ = tmpA;
			tmpA->parent_ = tmparent;
			if (tmpB != this->_leaf)
				tmpB->parent_ = node;
			if (tmpA->parent_ == NULL)
				this->_root = tmpA;
			else
				tmpA->parent_->right_ = tmpA;
			return (tmpA);
		}

		node_type	*rotateRight(node_type *node) {
			node_type	*tmpA = node->left_;
			node_type	*tmpB = tmpA->right_;
			node_type	*tmparent = node->parent_;

			tmpA->right_ = node;
			node->left_ = tmpB;
			node->parent_ = tmpA;
			tmpA->parent_ = tmparent;
			if (tmpB != this->_leaf)
				tmpB->parent_ = node;
			if (tmpA->parent_ == NULL)
				this->_root = tmpA;
			else
				tmpA->parent_->left_ = tmpA;
			return (tmpA);
		}

	/******************************************_PRINT_TREE_******************************************/

		void	aff_node(node_type *node) const {
			std::string	color;
			node->color_ ? color = "red" : color = "black";			
			std::cout << node->data_.first << " | " << node->data_.second << " | " << color << std::endl;
		}

		void	aff_tree(node_type *node, int space) const {
			int i;
        	if(node != this->_leaf) {
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

	/******************************************_UTILS_******************************************/

		node_type	*next(node_type *node) {
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

		node_type	*prev(node_type *node) {
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

		node_type	*swapNode(node_type *to_replace, node_type *replace) {
			if (to_replace->parent_ == NULL)
				this->_root = replace;
			to_replace->parent_->left_ == to_replace ? to_replace->parent_->left_ = replace : to_replace->parent_->right_ = replace;
			if (to_replace->left_)
				to_replace->left_->parent_ = replace;
			if (to_replace->right_)
				to_replace->right_->parent_ = replace;
			replace->parent_ = to_replace->parent_;
			replace->left_ = to_replace->left_;
			replace->right_ = to_replace->right_;
			replace->color_ = to_replace->color_;
			return (replace);
		}

		node_type	*maxValNode(node_type *node) {
			this->aff_node(node);
			if (node != this->_leaf && node->right_ != this->_leaf)
				this->maxValNode(node->right_);
			return (node->right_);
		}

		node_type	*minValNode(node_type *node) {
			if (node != this->_leaf && node->left_ != this->_leaf)
				this->minValNode(node->left_);
			return (node->left_);
		}

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

		size_type nodeCount(node_type *node) {
		    if (node == this->_leaf)
		        return (0);
		    else
		        return (this->nodeCount(node->left_) + this->nodeCount(node->right_) + 1);
		}

	private:
		node_type				*_root;
		node_type				*_leaf;
		key_compare			_cmp;
		bool				_ll;
		bool				_rl;
		bool				_rr;
		bool				_lr;
		bool				_f;
		allocator_type		_alloc;
		node_allocator_type	_node_alloc;

	};
}

#endif
