/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliens <aliens@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:49:23 by aliens            #+#    #+#             */
/*   Updated: 2022/06/28 21:24:23 by aliens           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include "pair.hpp"
#include "iterator.hpp"
#include <functional>
#include <memory>

namespace ft {

	/*************************************************************************************************
													VECTOR
	**************************************************************************************************/
	
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
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
		typedef ft::iterator_traits::size_type					size_type;

	/******************************************_CONSTRUCTORS_******************************************/

		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		: {}

	private:

	};

}

#endif
