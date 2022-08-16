/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliens <aliens@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:49:23 by aliens            #+#    #+#             */
/*   Updated: 2022/08/16 18:13:30 by aliens           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include "iterator.hpp"
#include "pair.hpp"
#include "RBTree.hpp"

namespace ft {

	/*************************************************************************************************
													MAP
	**************************************************************************************************/
	
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T>>>
	class map {
	public:
		typedef Key												key_type;
		typedef T												mapped_type;
		typedef	ft::pair<const key_type, mapped_type>			value_type;
		typedef Compare											key_compare;
		typedef Alloc											allocator_type;
		typedef allocator_type::reference						reference;
		typedef allocator_type::const_reference					const_reference;
		typedef allocator_type::pointer							pointer;
		typedef allocator_type::const_pointer					const_pointer;
		typedef ft::tree_iterator<ft::RBTree::node_type>		iterator;
		typedef ft::tree_iterator<const ft::RBTree::node_type>	const_iterator;
		typedef	ft::reverse_iterator<iterator>					reverse_iterator;
		typedef	ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef ft::iterator_traits::difference_type			difference_type;
		typedef std::size_t										size_type;

	/******************************************_CONSTRUCTORS_******************************************/

		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _cmp(comp), _tree(ft::RBtree()) {}

		template <class InputIterator>
  		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());

		map(const map& x);

	/******************************************_DESTRUCTOR_******************************************/

		~map(void);

	/******************************************_ASSIGN_OPERATOR_******************************************/

		map	&operator=(const map& x);

	/******************************************_GET_ALLOCATOR_******************************************/

		allocator_type	get_allocator() const {
			return (this->_alloc);
		}

	/******************************************_ITERATORS_******************************************/

	    iterator	begin(void) {
			return (this->_tree.begin());
		}
		
		const_iterator	begin(void) const {
			return (this->_tree.begin());
		}
		
		iterator	end(void) {
			return (this->_tree.end());
		}

		const_iterator	end(void) const {
			return (this->_tree.end());
		}

		reverse_iterator	rbegin(void) {
			return (this->_tree.rbegin());
		}
		
		const_reverse_iterator	rbegin(void) const {
			return (this->_tree.rbegin());
		}

      	reverse_iterator	rend(void) {
			  return (this->_tree.rend());
		}
		
		const_reverse_iterator	rend(void) const {
			return (this->_tree.rend());
		}

	/******************************************_CAPACITY_******************************************/

		bool	empty(void) const {
			return (this->_tree.get_root() == this->_tree.get_leaf() ? true : false);
		}

		size_type	size(void) const {
			return (this->_tree.nodeCount(this->_tree.get_root()));
		}

		size_type	max_size(void) const {
			return (this->_tree.get_node_alloc().max_size());
		}

	/******************************************_ELEMENT_ACCES_******************************************/

		mapped_type	&operator[](const key_type& k) {
			return (this->_tree.findNode(this->_tree.get_root(), k))
		}

	/******************************************_MODIFIERS_******************************************/

		pair<iterator,bool>	insert(const value_type& val) {
			iterator	inserted(this->_tree.insertNode(this->_tree.get_root(), val));
			bool	b2o = inserted.get_node()->temp_ ? true : false;
			inserted.get_node()->temp_ = false;
			return (ft::make_pair(inserted, b2o));
		}
		
		iterator	insert(iterator position, const value_type& val) {
			iterator	inserted(this->_tree.insertNode(position.get_node(), val));
			if (inserted.get_node()->temp_)
				inserted.get_node()->temp_ = false;
			return (inserted);
		}
		
		template <class InputIterator>
		void	insert(InputIterator first, InputIterator last);

	    void	erase(iterator position) {
			this->_tree.deleteNode(this->_tree.get_root(), position.get_node().first);
		}
		
		size_type	erase(const key_type& k) {
			this->_tree.deleteNode(this->_tree.get_root(), k);
			return (1);
		}
	    
		void	erase(iterator first, iterator last) {
			for (; first != last; first++)
				this->_tree.deleteNode(this->_tree.get_root(), first.get_node().first);
		}

		void	swap(map& x);

		void	clear();

	/******************************************_OBSERVERS_******************************************/

		key_compare	key_comp(void) const {
			return (this->_cmp);
		}

		value_compare	value_comp() const;

	/******************************************_OPERATIONS_******************************************/

	    iterator	find(const key_type& k) {
			return (iterator(this->_tree.findNode(this->_tree.get_root(), k)));
		}
		
		const_iterator	find(const key_type& k) const {
			return (const_iterator(this->_tree.findNode(this->_tree.get_root(), k)));
		}

		size_type	count(const key_type& k) const {
			if (this->_tree.findNode(this->_tree.get_root(), k) == this->_tree.get_leaf())
				return (0);
			return (1);
		}

		iterator	lower_bound(const key_type& k) {
			RBTree<Key, T>::node_type	*node = this->_tree.findNode(this->_tree.get_root(), k);
			return (iterator(this->_tree.minValNode(node)));
		}
		
		const_iterator	lower_bound(const key_type& k) const {
			RBTree<Key, T>::node_type	*node = this->_tree.findNode(this->_tree.get_root(), k);
			return (const_iterator(this->_tree.minValNode(node)));
		}

	    iterator	upper_bound(const key_type& k) {
			RBTree<Key, T>::node_type	*node = this->_tree.findNode(this->_tree.get_root(), k);
			return (iterator(this->_tree.maxValNode(node)));
		}
		
		const_iterator	upper_bound(const key_type& k) const {
			RBTree<Key, T>::node_type	*node = this->_tree.findNode(this->_tree.get_root(), k);
			return (const_iterator(this->_tree.maxValNode(node)));
		}

		pair<const_iterator,const_iterator>	equal_range(const key_type& k) const;
		
		pair<iterator,iterator>	equal_range(const key_type& k);

	private:
		allocator_type		_alloc;
		key_compare			_cmp;
		ft::RBTree<Key, T>	_tree;

	};

}

#endif
