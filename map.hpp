/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliens <aliens@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:49:23 by aliens            #+#    #+#             */
/*   Updated: 2022/09/05 16:25:39 by aliens           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include "RBTree.hpp"
#include "iterator.hpp"
#include "iterator_check.hpp"

namespace ft {

	/*************************************************************************************************
													MAP
	**************************************************************************************************/
	
	template <class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map {
	public:
		typedef	ft::Node<Key, T>										node_type;
		typedef Key														key_type;
		typedef T														mapped_type;
		typedef	ft::pair<const key_type, mapped_type>					value_type;
		typedef Compare													key_compare;
		typedef Alloc													allocator_type;
		typedef typename allocator_type::reference						reference;
		typedef typename allocator_type::const_reference				const_reference;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;
		typedef ft::map_iterator<value_type, ft::Node<Key, T> >			iterator;
		typedef ft::map_iterator<const value_type, ft::Node<Key, T> >	const_iterator;
		typedef	ft::reverse_iterator<iterator>							reverse_iterator;
		typedef	ft::reverse_iterator<const_iterator>					const_reverse_iterator;
		typedef ptrdiff_t												difference_type;
		typedef size_t													size_type;

	private:
		class value_compare : public std::binary_function<value_type, value_type, bool> {
			friend class map;
		protected:
			key_compare _cmp;
			value_compare(key_compare c) : _cmp(c) {}

		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator() (const value_type& x, const value_type& y) const {
				return this->_cmp(x.first, y.first);
			}
	
		};
		
		allocator_type					_alloc;
		key_compare						_cmp;
		ft::RBTree<Key, T, key_compare>	_tree;

		void	aff_node(node_type *node) const {
			this->_tree.aff_node(node);
		}

		void	aff_tree(void) const {
			this->_tree.aff_tree(this->_tree.get_root(), 0);
		}
		
	public:
	/******************************************_CONSTRUCTORS_******************************************/

		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _cmp(comp), _tree(ft::RBTree<Key, T, key_compare>()) {}

		template <class InputIterator>
  		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
		: _alloc(alloc), _cmp(comp), _tree(ft::RBTree<Key, T, key_compare>()) {
			this->insert(first, last);
		}

		map(const map& x)
		: _alloc(x.get_allocator()), _cmp(x.key_comp()), _tree(ft::RBTree<Key, T, key_compare>()) {
			for (const_iterator begin = x.begin(), end = x.end(); begin != end; begin++)
				this->_tree.insertNode(this->_tree.get_root(), *begin);
		}

	/******************************************_DESTRUCTOR_******************************************/

		~map(void) {}

	/******************************************_ASSIGN_OPERATOR_******************************************/

		map	&operator=(const map& x) {
			this->clear();
			this->_alloc = x.get_allocator();
			this->_cmp = this->key_comp();
			for (const_iterator begin = x.begin(), end = x.end(); begin != end; begin++)
				this->_tree.insertNode(this->_tree.get_root(), *begin);
			return (*this);
		}

	/******************************************_GET_ALLOCATOR_******************************************/

		allocator_type	get_allocator() const {
			return (this->_alloc);
		}

	/******************************************_ITERATORS_******************************************/

	    iterator	begin(void) {
			return (iterator(this->_tree.minValNode(this->_tree.get_root()), this->_tree.get_leaf()));
		}
		
		const_iterator	begin(void) const {
			return (const_iterator(this->_tree.minValNode(this->_tree.get_root()), this->_tree.get_leaf()));
		}
		
		iterator	end(void) {
			return (iterator(this->_tree.get_leaf(), this->_tree.get_leaf()));
		}

		const_iterator	end(void) const {
			return (const_iterator(this->_tree.get_leaf(), this->_tree.get_leaf()));
		}

		reverse_iterator	rbegin(void) {
			return (reverse_iterator(this->end()));
		}
		
		const_reverse_iterator	rbegin(void) const {
			return (const_reverse_iterator(this->end()));
		}

      	reverse_iterator	rend(void) {
			  return (reverse_iterator(this->begin()));
		}
		
		const_reverse_iterator	rend(void) const {
			return (const_reverse_iterator(this->begin()));
		}

	/******************************************_CAPACITY_******************************************/

		bool	empty(void) const {
			return (this->_tree.get_size() ? false : true);
		}

		size_type	size(void) const {
			return (this->_tree.get_size());
		}

		size_type	max_size(void) const {
			return (this->_tree.get_node_alloc().max_size());
		}

	/******************************************_ELEMENT_ACCES_******************************************/

		mapped_type	&operator[](const key_type& k) {
			return (this->insert(ft::make_pair(k, mapped_type())).first->second);
		}

	/******************************************_MODIFIERS_******************************************/

		pair<iterator,bool>	insert(const value_type& val) {
			iterator	inserted(this->_tree.insertNode(this->_tree.get_root(), val), this->_tree.get_leaf());
			bool	b2o = inserted.get_node()->temp_ ? false : true;
			inserted.get_node()->temp_ = false;
			return (ft::make_pair(inserted, b2o));
		}
		
		iterator	insert(iterator position, const value_type& val) {
			static_cast<void>(position);
			iterator	inserted(this->_tree.insertNode(this->_tree.get_root(), val), this->_tree.get_leaf());
			inserted.get_node()->temp_ = false;
			return (inserted);
		}
		
		template <class InputIterator>
		void	insert(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) {
			for (; first != last; first++) {
				iterator	inserted(this->_tree.insertNode(this->_tree.get_root(), *first), this->_tree.get_leaf());
				inserted.get_node()->temp_ = false;
			}
		}

	    void	erase(iterator position) {
			this->erase(position->first);
		}
		
		size_type	erase(const key_type& k) {
			if (this->_tree.deleteNode(this->_tree.get_root(), k) == this->_tree.get_leaf())
				return (0);
			return (1);
		}
	    
		void	erase(iterator first, iterator last) {
			while (first != last)
				this->erase(first++);
		}

		void	swap(map& x) {
			this->_tree.swap(x._tree);
		}

		void	clear(void) {
			this->_tree.set_root(this->_tree.destroyRBTree(this->_tree.get_root()));
		}

	/******************************************_OBSERVERS_******************************************/

		key_compare	key_comp(void) const {
			return (this->_cmp);
		}

		value_compare	value_comp(void) const {
			return (value_compare(this->_cmp));
		}

	/******************************************_OPERATIONS_******************************************/

	    iterator	find(const key_type& k) {
			return (iterator(this->_tree.findNode(this->_tree.get_root(), k), this->_tree.get_leaf()));
		}
		
		const_iterator	find(const key_type& k) const {
			return (const_iterator(this->_tree.findNode(this->_tree.get_root(), k), this->_tree.get_leaf()));
		}

		size_type	count(const key_type& k) const {
			if (this->_tree.findNode(this->_tree.get_root(), k) == this->_tree.get_leaf())
				return (0);
			return (1);
		}

		iterator	lower_bound(const key_type& k) {
			node_type	*parent = this->_tree.findParentNode(this->_tree.get_root(), k);
			node_type	*node = this->_tree.findNode(this->_tree.get_root(), k);
			if (node == this->_tree.get_leaf()) {
				if (this->_cmp(k, this->_tree.minValNode(this->_tree.get_root())->data_.first))
					node = this->_tree.minValNode(this->_tree.get_root());
				else if (this->_cmp(this->_tree.maxValNode(this->_tree.get_root())->data_.first, k))
					node = this->_tree.get_leaf();
				else
					node = this->_cmp(parent->data_.first, k) ? this->_tree.next(parent) : parent;
				return (iterator(node, this->_tree.get_leaf()));
			}
			return (iterator(node, this->_tree.get_leaf()));
		}
		
		const_iterator	lower_bound(const key_type& k) const {
			node_type	*parent = this->_tree.findParentNode(this->_tree.get_root(), k);
			node_type	*node = this->_tree.findNode(this->_tree.get_root(), k);
			if (node == this->_tree.get_leaf()) {
				if (this->_cmp(k, this->_tree.minValNode(this->_tree.get_root())->data_.first))
					node = this->_tree.minValNode(this->_tree.get_root());
				else if (this->_cmp(this->_tree.maxValNode(this->_tree.get_root())->data_.first, k))
					node = this->_tree.get_leaf();
				else
					node = this->_cmp(parent->data_.first, k) ? this->_tree.next(parent) : parent;
				return (const_iterator(node, this->_tree.get_leaf()));
			}
			return (const_iterator(node, this->_tree.get_leaf()));
		}

	    iterator	upper_bound(const key_type& k) {
			node_type	*parent = this->_tree.findParentNode(this->_tree.get_root(), k);
			node_type	*node = this->_tree.findNode(this->_tree.get_root(), k);
			if (node == this->_tree.get_leaf()) {
				if (this->_cmp(k, this->_tree.minValNode(this->_tree.get_root())->data_.first))
					node = this->_tree.minValNode(this->_tree.get_root());
				else if (this->_cmp(this->_tree.maxValNode(this->_tree.get_root())->data_.first, k))
					node = this->_tree.get_leaf();
				else
					node = this->_cmp(parent->data_.first, k) ? this->_tree.next(parent) : parent;
				return (iterator(node, this->_tree.get_leaf()));
			}
			node = node == this->_tree.maxValNode(this->_tree.get_root()) ? this->_tree.get_leaf() : this->_tree.next(node);
			return (iterator(node, this->_tree.get_leaf()));
		}
		
		const_iterator	upper_bound(const key_type& k) const {
			node_type	*parent = this->_tree.findParentNode(this->_tree.get_root(), k);
			node_type	*node = this->_tree.findNode(this->_tree.get_root(), k);
			if (node == this->_tree.get_leaf()) {
				if (this->_cmp(k, this->_tree.minValNode(this->_tree.get_root())->data_.first))
					node = this->_tree.minValNode(this->_tree.get_root());
				else if (this->_cmp(this->_tree.maxValNode(this->_tree.get_root())->data_.first, k))
					node = this->_tree.get_leaf();
				else
					node = this->_cmp(parent->data_.first, k) ? this->_tree.next(parent) : parent;
				return (const_iterator(node, this->_tree.get_leaf()));
			}
			node = node == this->_tree.maxValNode(this->_tree.get_root()) ? this->_tree.get_leaf() : this->_tree.next(node);
			return (const_iterator(node, this->_tree.get_leaf()));
		}

		pair<const_iterator,const_iterator>	equal_range(const key_type& k) const {
			const_iterator	end = this->upper_bound(k);
			const_iterator	begin = this->lower_bound(k) != this->end() ? this->lower_bound(k) : this->upper_bound(k);
			return (ft::make_pair(begin, end));
		}
		
		pair<iterator,iterator>	equal_range(const key_type& k) {
			iterator	end = this->upper_bound(k);
			iterator	begin = this->lower_bound(k) != this->end() ? this->lower_bound(k) : this->upper_bound(k);
			return (ft::make_pair(begin, end));
		}
		
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return (false);
		if (!ft::equal(lhs.begin(), lhs.end(), rhs.begin()))
			return (false);
		return (true);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
		return (!(lhs == rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator<(const map<Key, T, Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
		return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator<=(const map<Key, T, Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
		return (!(rhs < lhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator>(const map<Key, T, Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator>=(const map<Key, T, Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
		return (!(lhs < rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	void	swap(map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y) {
		x.swap(y);
	}

}

#endif
