/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliens <aliens@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:49:23 by aliens            #+#    #+#             */
/*   Updated: 2022/08/09 17:31:37 by aliens           ###   ########.fr       */
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
	
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T>>>
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
		typedef ft::random_access_iterator<value_type>			iterator;
		typedef ft::random_access_iterator<const value_type>	const_iterator;
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

	    iterator	begin();
		
		const_iterator	begin() const;
		
		iterator	end();

		const_iterator	end() const;

		reverse_iterator	rbegin();
		
		const_reverse_iterator	rbegin() const;

      	reverse_iterator	rend();
		
		const_reverse_iterator	rend() const;

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

		mapped_type	&operator[](const key_type& k);

	/******************************************_MODIFIERS_******************************************/

		pair<iterator,bool>	insert(const value_type& val);
		
		iterator	insert(iterator position, const value_type& val);
		
		template <class InputIterator>
		void	insert(InputIterator first, InputIterator last);

	    void	erase(iterator position);
		
		size_type	erase(const key_type& k);
	    
		void	erase(iterator first, iterator last);

		void	swap(map& x);

		void	clear();

	/******************************************_OBSERVERS_******************************************/

		key_compare	key_comp() const;

		value_compare	value_comp() const;

	/******************************************_OPERATIONS_******************************************/

	    iterator	find(const key_type& k);
		
		const_iterator	find(const key_type& k) const;

		size_type	count(const key_type& k) const;

		iterator	lower_bound(const key_type& k);
		
		const_iterator	lower_bound(const key_type& k) const;

	    iterator	upper_bound(const key_type& k);
		
		const_iterator	upper_bound(const key_type& k) const;

		pair<const_iterator,const_iterator>	equal_range(const key_type& k) const;
		
		pair<iterator,iterator>	equal_range(const key_type& k);

	private:
		allocator_type		_alloc;
		key_compare			_cmp;
		ft::RBTree<Key, T>	_tree;

	};

}

#endif
