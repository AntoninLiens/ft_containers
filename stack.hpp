/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliens <aliens@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 13:55:18 by aliens            #+#    #+#             */
/*   Updated: 2022/09/02 17:20:57 by aliens           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"
#include "iterator.hpp"
#include "iterator_check.hpp"
#include <memory>
#include <stdexcept>
#include <cstddef>

namespace ft {

	/*************************************************************************************************
													STACK
	**************************************************************************************************/

	template <class T, class Container = ft::vector<T> >
	class stack {
	public:
		typedef	T									value_type;
		typedef Container							container_type;
		typedef typename container_type::size_type	size_type;

	/******************************************_CONSTRUCTOR_******************************************/

	explicit stack(const container_type& container = container_type()) : _container(container) {}

	/******************************************_GET_CONTAINER_******************************************/

	container_type	get_container(void) const {
		return (this->_container);
	}

	/******************************************_CAPACITY_******************************************/

	bool empty(void) const {
		return (this->_container.empty());
	}


	size_type size(void) const {
		return (this->_container.size());
	}

	/******************************************_ELEMENT_ACCES_******************************************/

	value_type& top(void) {
		return (this->_container.back());
	}

	const value_type& top(void) const {
		return (this->_container.back());
	}

	/******************************************_MODIFIERS_******************************************/

	void push (const value_type& val) {
		this->_container.push_back(val);
	}


	void pop(void) {
		this->_container.pop_back();
	}

	private:
		container_type	_container;

	};

	/******************************************_NON_MEMBER_FUNCTIONS_OVERLOAD_******************************************/
	
	template <class T, class Container>
  	bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (lhs.get_container() == rhs.get_container());
	}

	template <class T, class Container>
  	bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (lhs.get_container() != rhs.get_container());
	}
	
	template <class T, class Container>
  	bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (lhs.get_container() < rhs.get_container());
	}

	template <class T, class Container>
  	bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (lhs.get_container() <= rhs.get_container());
	}

	template <class T, class Container>
  	bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (lhs.get_container() > rhs.get_container());
	}

	template <class T, class Container>
  	bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (lhs.get_container() >= rhs.get_container());
	}

}

#endif