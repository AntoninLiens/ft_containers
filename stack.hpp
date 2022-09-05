/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliens <aliens@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 13:55:18 by aliens            #+#    #+#             */
/*   Updated: 2022/09/05 16:35:05 by aliens           ###   ########.fr       */
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

	explicit stack(const container_type& container = container_type()) : c(container) {}

	/******************************************_CAPACITY_******************************************/

	bool empty(void) const {
		return (this->c.empty());
	}


	size_type size(void) const {
		return (this->c.size());
	}

	/******************************************_ELEMENT_ACCES_******************************************/

	value_type& top(void) {
		return (this->c.back());
	}

	const value_type& top(void) const {
		return (this->c.back());
	}

	/******************************************_MODIFIERS_******************************************/

	void push (const value_type& val) {
		this->c.push_back(val);
	}


	void pop(void) {
		this->c.pop_back();
	}

	protected:
		container_type	c;

		template <class Type, class C>
		friend bool operator==(const stack<Type, C>& lhs, const stack<Type, C>& rhs);

		template <class Type, class C>
		friend bool operator!=(const stack<Type, C>& lhs, const stack<Type, C>& rhs);

		template <class Type, class C>
		friend bool operator<(const stack<Type, C>& lhs, const stack<Type, C>& rhs);

		template <class Type, class C>
		friend bool operator<=(const stack<Type, C>& lhs, const stack<Type, C>& rhs);

		template <class Type, class C>
		friend bool operator>(const stack<Type, C>& lhs, const stack<Type, C>& rhs);

		template <class Type, class C>
		friend bool operator>=(const stack<Type, C>& lhs, const stack<Type, C>& rhs);
	};

	/******************************************_NON_MEMBER_FUNCTIONS_OVERLOAD_******************************************/
	
	template <class T, class Container>
  	bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (lhs.c == rhs.c);
	}

	template <class T, class Container>
  	bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (lhs.c != rhs.c);
	}
	
	template <class T, class Container>
  	bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (lhs.c < rhs.c);
	}

	template <class T, class Container>
  	bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (lhs.c <= rhs.c);
	}

	template <class T, class Container>
  	bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (lhs.c > rhs.c);
	}

	template <class T, class Container>
  	bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return (lhs.c >= rhs.c);
	}

}

#endif
