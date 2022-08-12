/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliens <aliens@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:20:53 by aliens            #+#    #+#             */
/*   Updated: 2022/08/12 15:59:45 by aliens           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
#include "RBTree.hpp"
#include <iostream>

namespace ft {
	
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	/*************************************************************************************************
											RANDOM_ACCES_ITERATOR
	**************************************************************************************************/

	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator {
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
	};

	template <class Iterator>
	class iterator_traits {
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};
	
	template <class T>
	class iterator_traits<T*> {
		typedef T							value_type;
		typedef ptrdiff_t					difference_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;
	};
	
	template <class T>
	class iterator_traits<const T*> {
		typedef T							value_type;
		typedef ptrdiff_t					difference_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	template <class T>
	class random_access_iterator : public ft::iterator<random_access_iterator_tag, T> {
	public:
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type		value_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer			pointer;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference			reference;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;

	/******************************************_CONST_OPERATOR_******************************************/

		operator random_access_iterator<const T>() const {
			return (this->_ptr);
		}

	/******************************************_CONSTRUCTORS_******************************************/

		random_access_iterator(void) : _ptr(NULL) {}

		random_access_iterator(pointer ptr) : _ptr(ptr) {}

		random_access_iterator(const random_access_iterator& it) : _ptr(it.base()) {}

	/******************************************_DESTRUCTOR_******************************************/

		~random_access_iterator(void) {}

	/******************************************_ASSIGN_OPERATOR_******************************************/

		random_access_iterator&	operator=(const random_access_iterator& it) {
			if (it.base() != this->_ptr)
				this->_ptr = it.base();
			return (*this);
		}

	/******************************************_GET_PTR_******************************************/

		pointer	base(void) const {
			return (this->_ptr);
		}

	/******************************************_DEREFERENCED_OPERATORS_******************************************/

		reference	operator*(void) const {
			return (*this->_ptr);
		}

		pointer	operator->(void) const {
			return (this->_ptr);
		}

	/******************************************_INCREMENT/DECREMENT_OPERATORS_******************************************/

		random_access_iterator&	operator++(void) {
			this->_ptr++;
			return (*this);
		}

		random_access_iterator	operator++(int n) {
			static_cast<void>(n);
			random_access_iterator	tmp(*this);
			this->_ptr++;
			return (tmp);
		}

		random_access_iterator&	operator--(void) {
			this->_ptr--;
			return (*this);
		}

		random_access_iterator	operator--(int n) {
			static_cast<void>(n);
			random_access_iterator	tmp(*this);
			this->_ptr--;
			return (tmp);
		}

	/******************************************_ARITHMETIC_OPERATORS_******************************************/

		random_access_iterator	operator+(difference_type n) const {
			return (random_access_iterator(this->base() + n));
		}

		random_access_iterator&	operator+=(difference_type n) {
			this->_ptr += n;
			return (*this);
		}
		
		random_access_iterator	operator-(difference_type n) const {
			return (random_access_iterator(this->base() - n));
		}

		random_access_iterator&	operator-=(difference_type n) {
			this->_ptr -= n;
			return (*this);
		}

	/******************************************_OFFSET_DEREFERENCE_OPERATORS_******************************************/

		reference	operator[](difference_type n) const {
			random_access_iterator	tmp(*this + n);
			return (*tmp.base());
		}

	private:
		pointer	_ptr;

	};

	/******************************************_NON_MEMBER_FUNCTIONS_OVERLOAD_******************************************/

	template<class It1, class It2>
	bool	operator==(const random_access_iterator<It1>& lhs, const random_access_iterator<It2>& rhs) {
		return (lhs.base() == rhs.base());
	}

	template<class It1, class It2>
	bool	operator!=(const random_access_iterator<It1>& lhs, const random_access_iterator<It2>& rhs) {
		return (lhs.base() != rhs.base());
	}

	template<class It1, class It2>
	bool	operator>(const random_access_iterator<It1>& lhs, const random_access_iterator<It2>& rhs) {
		return (lhs.base() > rhs.base());
	}

	template<class It1, class It2>
	bool	operator<(const random_access_iterator<It1>& lhs, const random_access_iterator<It2>& rhs) {
		return (lhs.base() < rhs.base());
	}

	template<class It1, class It2>
	bool	operator>=(const random_access_iterator<It1>& lhs, const random_access_iterator<It2>& rhs) {
		return (lhs.base() >= rhs.base());
	}

	template<class It1, class It2>
	bool	operator<=(const random_access_iterator<It1>& lhs, const random_access_iterator<It2>& rhs) {
		return (lhs.base() <= rhs.base());
	}

	template<class It>
	random_access_iterator<It>	operator+(typename random_access_iterator<It>::difference_type n, const random_access_iterator<It>& it) {
		return (random_access_iterator<It>(it.base() + n));
	}

	template<class It>
	random_access_iterator<It>	operator-(typename random_access_iterator<It>::difference_type n, const random_access_iterator<It>& it) {
		return (random_access_iterator<It>(it.base() - n));
	}

	template <typename L_T, typename R_T>
	typename random_access_iterator<L_T>::difference_type	operator-(const random_access_iterator<L_T> &lhs, const random_access_iterator<R_T> &rhs) {
		return (lhs.base() - rhs.base());
	}

	/*************************************************************************************************
												REVERSE_ITERATOR
	**************************************************************************************************/

	template<typename Iterator>
	class reverse_iterator {
	public:
		typedef Iterator							iterator_type;
		typedef typename Iterator::difference_type	difference_type;
		typedef typename Iterator::pointer			pointer;
		typedef typename Iterator::reference		reference;
	
	/******************************************_CONST_OPERATOR_******************************************/

		operator reverse_iterator<const iterator_type>() const {
			return (this->_it);
		}

	/******************************************_CONSTRUCTORS_******************************************/

		reverse_iterator(void) : _it() {}

		reverse_iterator(iterator_type it) : _it(it) {}

		reverse_iterator(pointer ptr) : _it(iterator_type(ptr)) {}

		template<typename It>
		reverse_iterator(const reverse_iterator<It>& it) : _it(it.base()) {}

	/******************************************_DESTRUCTOR_******************************************/

		~reverse_iterator(void) {}


	/******************************************_GET_PTR_******************************************/

		iterator_type	base(void) const {
			return (this->_it);
		}

	/******************************************_DEREFERENCED_OPERATORS_******************************************/

		reference	operator*(void) const {
			iterator_type	tmp = this->_it;
			tmp--;
			return (*tmp);
		}

		pointer	operator->(void) const {
			return (&this->operator*());
		}

	/******************************************_INCREMENT/DECREMENT_OPERATORS_******************************************/

		reverse_iterator&	operator++(void) {
			this->_it--;
			return (*this);
		}

		reverse_iterator	operator++(int n) {
			static_cast<void>(n);
			reverse_iterator	tmp = *this;
			this->_it--;
			return (tmp);
		}

		reverse_iterator&	operator--(void) {
			this->_it++;
			return (*this);
		}

		reverse_iterator	operator--(int n) {
			static_cast<void>(n);
			reverse_iterator	tmp = *this;
			this->_it++;
			return (tmp);
		}

	/******************************************_ARITHMETIC_OPERATORS_******************************************/

		reverse_iterator	operator+(difference_type n) const {
			return (reverse_iterator(this->_it - n));
		}

		reverse_iterator	operator+=(difference_type n) {
			this->_it -= n;
			return (*this);
		}

		reverse_iterator	operator-(difference_type n) const {
			return (reverse_iterator(this->_it + n));
		}

		reverse_iterator	operator-=(difference_type n) {
			this->_it += n;
			return (*this);
		}

	/******************************************_OFFSET_DEREFERENCE_OPERATORS_******************************************/

		reference	operator[](difference_type n) const {
			return (*(*this + n));
		}

	private:
		iterator_type	_it;

	};

	/******************************************_NON_MEMBER_FUNCTIONS_OVERLOAD_******************************************/

	template<class It1, class It2>
	bool operator==(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs) {
		return (lhs.base() == rhs.base());
	}

	template<class It1, class It2>
	bool operator!=(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs) {
		return (lhs.base() != rhs.base());
	}

	template<class It1, class It2>
	bool operator<(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs) {
		return (lhs.base() > rhs.base());
	}
	
	template<class It1, class It2>
	bool operator<=(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs) {
		return (lhs.base() >= rhs.base());
	}

	template<class It1, class It2>
	bool operator>(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs) {
		return (lhs.base() < rhs.base());
	}

	template <class It1, class It2>
	bool operator>=(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs) {
		return (lhs.base() <= rhs.base());
	}

	template<class It>
	reverse_iterator<It>	operator+(typename reverse_iterator<It>::difference_type n, const reverse_iterator<It>& it) {
		return (reverse_iterator<It>(it.base()- n));
	}

	template <typename It1, typename It2>
	typename reverse_iterator<It1>::difference_type	operator-(const reverse_iterator<It1> &lhs, const reverse_iterator<It2> &rhs) {
		return (rhs.base() - lhs.base());
	}

	template<class It>
	reverse_iterator<It>	operator-(typename reverse_iterator<It>::difference_type n, const reverse_iterator<It>& it) {
		return (reverse_iterator<It>(it.base() + n));
	}

	/*************************************************************************************************
												MAP_ITERATOR
	**************************************************************************************************/

	template<class Node, class Pointer = Node *, class Reference = Node &>
	class map_iterator {
	public:
		typedef	Node		node_type;
		typedef Pointer		pointer;
		typedef	Reference	reference;

	/******************************************_CONST_OPERATOR_******************************************/

		operator map_iterator<const pointer>(void) const {
			return (this->_node);
		}

	/******************************************_CONSTRUCTORS_******************************************/

		map_iterator(void) {
			this->_node = NULL;
			this->_node->left_ = NULL;
			this->_node->right_ = NULL;
			this->_node->parent_ = NULL;
		}

		map_iterator(pointer node, pointer leaf) : _node(node), _leaf(leaf) {}

		map_iterator(const map_iterator<node_type>& it) : _node(it.get_node()), _leaf(it.get_leaf()) {}

	/******************************************_DESTRUCTOR_******************************************/

		~map_iterator(void) {}

	/******************************************_GET_NODE_******************************************/

		pointer	get_node(void) const {
			return (this->_node);
		}

		pointer	get_leaf(void) const {
			return (this->_leaf);
		}

	/******************************************_DEREFERENCED_OPERATORS_******************************************/
	
		reference	operator*(void) const {
			return (*this->_node);
		}

		pointer	operator->(void) const {
			return (this->_node);
		}

	/******************************************_INCREMENT/DECREMENT_OPERATORS_******************************************/

		map_iterator&	operator++(void) {
			this->_node = this->next(this->_node);
			return (*this);
		}

		map_iterator	operator++(int n) {
			static_cast<void>(n);
			pointer	tmp = this->_node;
			std::cout << "**-----**" << std::endl;
			this->aff_node(this->_node);
			std::cout << "**-----**" << std::endl;
			this->_node = this->next(this->_node);
			std::cout << "**-----**" << std::endl;
			this->aff_node(this->_node);
			std::cout << "**-----**" << std::endl;
			return (map_iterator(tmp, this->_leaf));
		}

		map_iterator&	operator--(void) {
			this->_node = this->prev(this->_node);
			return (*this);
		}

		map_iterator	operator--(int n) {
			static_cast<void>(n);
			pointer	tmp = this->_node;
			std::cout << "**-----**" << std::endl;
			this->aff_node(this->_node);
			std::cout << "**-----**" << std::endl;
			this->_node = this->prev(this->_node);
			std::cout << "**-----**" << std::endl;
			this->aff_node(this->_node);
			std::cout << "**-----**" << std::endl;
			return (map_iterator(tmp, this->_leaf));
		}

		/******************************************_UTILS_******************************************/

		void	aff_node(node_type *node) const {
			std::string	color;
			node->color_ ? color = "red" : color = "black";			
			std::cout << node->data_.first << " | " << node->data_.second << " | " << color << std::endl;
		}

		node_type	*next(node_type *node) {
			node_type	*tmp;

			// aff_node(node);
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

			// aff_node(node);
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

		pointer	maxValNode(pointer node) {
			if (node && node->right_ != this->_leaf)
				this->maxValNode(node->right_);
			return (node);
		}

		pointer	minValNode(pointer node) {
			if (node && node->left_ != this->_leaf)
				this->minValNode(node->left_);
			return (node);
		}

	private:
		pointer	_node;
		pointer	_leaf;

	};

}

#endif
