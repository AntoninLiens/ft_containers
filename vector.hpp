/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliens <aliens@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:51:46 by aliens            #+#    #+#             */
/*   Updated: 2022/09/05 13:45:03 by aliens           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "iterator.hpp"
#include "iterator_check.hpp"
#include <memory>
#include <stdexcept>
#include <cstddef>

namespace ft {

	/*************************************************************************************************
													VECTOR
	**************************************************************************************************/

	template< class T, class Allocator = std::allocator<T> >
	class vector {
	public:
		typedef T 											value_type;
		typedef	Allocator									allocator_type;
		typedef	std::size_t									size_type;
		typedef	std::ptrdiff_t								difference_type;
		typedef	T&											reference;
		typedef	const T&									const_reference;
		typedef T*											pointer;
		typedef	const T*									const_pointer;
		typedef ft::random_access_iterator<T>				iterator;
		typedef ft::random_access_iterator<const T>			const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

	/******************************************_CONSTRUCTORS_******************************************/

		explicit vector(const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _start(NULL), _end(NULL), _capacity(NULL) {
			this->_start = this->_alloc.allocate(0);
			this->_end = this->_start;
			this->_capacity = this->_start;
		}

		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
		: _alloc(alloc) ,_start(NULL), _end(NULL), _capacity(NULL) {
			this->_start = this->_alloc.allocate(n);
			this->_end = this->_start;
			this->_capacity = this->_start + n;
			while (n--)
				this->_alloc.construct(this->_end++, val);
		}

		template <class InputIterator>
        vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
		: _alloc(alloc), _start(NULL), _end(NULL), _capacity(NULL) {
			int	size = 0;
			InputIterator	tmp(first);
			while (tmp++ != last)
				size++;
			this->_start = this->_alloc.allocate(size);
			this->_end = this->_start;
			this->_capacity = this->_start + size;
			while (size--)
				this->_alloc.construct(this->_end++, *first++);
		}

		vector(const vector& vector)
		: _alloc(vector._alloc), _start(NULL), _end(NULL), _capacity(NULL) {
			this->_start = this->_alloc.allocate(vector.capacity());
			this->_capacity = this->_start + vector.capacity();
			this->_end = this->_start;
			for (size_type i = 0; i < vector.size(); i++)
				this->_alloc.construct(this->_end++, vector[i]);
		}

	/******************************************_DESTRUCTOR_******************************************/

		~vector(void) {
			while (this->_end-- != this->_start)
				this->_alloc.destroy(this->_end);
			this->_alloc.destroy(this->_start);
			this->_alloc.deallocate(this->_start, this->capacity());
			this->_start = NULL;
			this->_end = NULL;
			this->_capacity = NULL;
		}

	/******************************************_ASSIGN_OPERATOR_******************************************/

		vector& operator=(const vector& vector) {
			this->clear();
			this->_start = this->_alloc.allocate(vector.capacity());
			this->_capacity = this->_start + vector.capacity();
			this->_end = this->_start;
			for (size_type i = 0; i < vector.size(); i++)
				this->_alloc.construct(this->_end++, vector[i]);
			return (*this);
		}

	/******************************************_ITERATORS_******************************************/

		iterator	begin(void) {
			return (iterator(this->_start));
		}

		const_iterator	begin(void) const {
			return (const_iterator(this->_start));
		}

		iterator	end(void) {
			return (iterator(this->_end));
		}

		const_iterator	end(void) const {
			return (const_iterator(this->_end));
		}

		reverse_iterator	rbegin(void) {
			return (reverse_iterator(this->_end));
		}
		
		const_reverse_iterator	rbegin(void) const {
			return (const_reverse_iterator(this->_end));
		}

		const_reverse_iterator	rend(void) const {
			return (const_reverse_iterator(this->_start));
		}

		reverse_iterator	rend(void) {
			return (reverse_iterator(this->_start));
		}

	/******************************************_CAPACITY_******************************************/

		size_type	size(void) const {
			return (this->_end - this->_start);
		}

		size_type	max_size(void) const {
			return (this->_alloc.max_size());
		}

		void	resize(size_type n, value_type val = value_type()) {
			if (n > this->max_size())
				throw(std::length_error("error: vector: resize"));
			if (n < this->size())
				while (n < this->size())
					this->_alloc.destroy(this->_end--);
			else if (n > this->size() && n > this->capacity())
				this->reserve(n);
			if (n > this->size())
				while (this->size() < n)
					this->_alloc.construct(this->_end++, val);
		}

		size_type	capacity(void) const {
			return (this->_capacity - this->_start);
		}

		bool	empty(void) const {
			return (this->size() == 0 ? true : false);
		}

		void	reserve(size_type n) {
			if (n > this->max_size())
				throw (std::length_error("error: vector: reserve"));
			if (this->capacity() > n)
				return ;
			pointer	prev_ptr[2] = {this->_start, this->_end};
			size_type	prev_size[2] = {this->size(), this->capacity()};
			this->_start = this->_alloc.allocate(n);
			this->_end = this->_start;
			this->_capacity = this->_start + n;
			while (prev_ptr[0] != prev_ptr[1]) {
				this->_alloc.construct(this->_end++, *prev_ptr[0]);
				this->_alloc.destroy(prev_ptr[0]++);
			}
			this->_alloc.deallocate(prev_ptr[0] - prev_size[0], prev_size[1]);
		}

	/******************************************_ELEMENT_ACCES_******************************************/

		reference	operator[](size_type n) {
			if (n >= this->size())
				throw (std::out_of_range("error: vector"));
			return (*(this->_start + n));
		}

		const_reference	operator[](size_type n) const {
			if (n >= this->size())
				throw (std::out_of_range("error: vector"));
			return (*(this->_start + n));
		}

		reference	at(size_type n) {
			if (n >= this->size())
				throw (std::out_of_range("error: vector"));
			return (*(this->_start + n));
		}
		
		const_reference	at(size_type n) const {
			if (n >= this->size())
				throw (std::out_of_range("error: vector"));
			return (*(this->_start + n));
		}

		reference	front(void) {
			if (!this->size())
				throw (std::out_of_range("error: vector"));
			return (*(this->_start));
		}
		
		const_reference	front(void) const {
			if (!this->size())
				throw (std::out_of_range("error: vector"));
			return (*(this->_start));
		}

		reference	back(void) {
			if (!this->size())
				throw (std::out_of_range("error: vector"));
			return (*(this->_end - 1));
		}
		
		const_reference	back(void) const {
			if (!this->size())
				throw (std::out_of_range("error: vector"));
			return (*(this->_end - 1));
		}

	/******************************************_MODIFIERS_******************************************/

		template <class InputIterator>
		void	assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL) {
			size_type	size = 0;
			for (InputIterator tmp(first); tmp != last; tmp++)
				size++;
			this->resize(0);
			this->reserve(size);
			while (size--)
				this->_alloc.construct(this->_end++, *first++);
		}

		void	assign(size_type n, const value_type& val) {
			this->resize(0);
			this->reserve(n);
			while (n--)
				this->_alloc.construct(this->_end++, val);
		}

		void	push_back(const value_type& val) {
			if (this->_end == this->_capacity) {
				size_type	size = this->size() <= 0 ? 1 : this->size() * 2;
				this->reserve(size);
			}
			this->_alloc.construct(this->_end, val);
			this->_end++;
		}

		void	pop_back(void) {
			this->_alloc.destroy(this->_end);
			this->_end--;
		}

		iterator	insert(iterator position, const_reference val) {
			size_type	pos = 0;
			size_type	end = this->size();

			for (; pos <= this->size(); pos++)
				if (position.base() == this->_start + pos)
					break ;
			if (pos == this->size() && position.base() != this->_end)
				return (iterator());
			this->_end++;
			this->reserve(this->size());
			while (pos < end) {
				*(this->_start + end) = *(this->_start + end - 1);
				end--;
			}
			this->_alloc.construct(this->_start + end, val);
			return (iterator(this->_start + pos));
		}

		void	insert(iterator position, size_type n, const_reference val) {
			size_type	pos = 0;
			for (; pos <= this->size(); pos++) {
				if (position.base() == this->_start + pos)
					break ;
			}
			if (pos == this->size() && position.base() != this->_end)
				return ;
			this->_end += n;
			this->reserve(this->size());
			for (size_type i = 0; i < this->size() - n - pos; i++)
				*(this->_end - i - 1) = *(this->_end - n - i - 1);
			for (size_type i = 0; i < n; i++)
				this->_alloc.construct(this->_start + pos + i, val);
		}
		
		template <class InputIterator>
		void	insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) {
			size_type	n = 0;
			InputIterator tmp = first;
			while (tmp++ != last)
				n++;
			size_type pos = 0;
			for (; pos <= this->size(); pos++)
				if (position.base() == this->_start + pos)
					break ;
			if (pos == this->size() && position.base() != this->_end)
				return ;
			this->_end += n;
			this->reserve(this->size());
			for (size_type i = 0; i < this->size() - n - pos; i++)
				*(this->_end - i - 1) = *(this->_end - n - i - 1);
			for (size_type i = 0; i < n; i++)
				this->_alloc.construct(this->_start + pos + i, *first++);
		}

		iterator	erase(iterator position) {
			size_type	pos = 0;
			for (; pos < this->size(); pos++) {
				if (position.base() == this->_start + pos)
					break ;
			}
			if (pos == this->size())
				this->_alloc.destroy(this->_end);
			else {
				this->_alloc.destroy(this->_start + pos);
				for (size_type i = pos; i < this->size(); i++) {
					if (i < this->size() - 1)
						*(this->_start + i) = *(this->_start + i + 1);
				}
			}
			this->_end--;
			return (iterator(this->_start + pos));
		}
		
		iterator	erase(iterator first, iterator last) {
			size_type	pos = 0, len = 0;
			for (; pos < this->size(); pos++) {
				if (first.base() == this->_start + pos)
					break ;
			}
			if (pos == this->size())
				return (iterator());
			iterator	tmp = first;
			while (tmp++ != last)
				len++;
			for (size_type i = 0; i < this->size() - len - pos; i++) {
				this->_alloc.destroy(this->_start + pos + i);
				*(this->_start + pos + i) = *(this->_start + pos + i + len);
			}
			this->_end -= len;
			return (first);
		}

		void	swap(vector& vector) {
			pointer	ptrTmp[3] = {this->_start, this->_end, this->_capacity};
			this->_start = vector._start;
			this->_end = vector._end;
			this->_capacity = vector._capacity;
			vector._start = ptrTmp[0];
			vector._end = ptrTmp[1];
			vector._capacity = ptrTmp[2];
		}

		void	clear(void) {
			while (this->_end != this->_start)
				this->_alloc.destroy(this->_end--);
			this->_start = NULL;
			this->_end = NULL;
		}

	private:
		allocator_type	_alloc;
		pointer			_start;
		pointer			_end;
		pointer			_capacity;

	};

	/******************************************_NON_MEMBER_FUNCTIONS_OVERLOAD_******************************************/

	template <class T, class Alloc>
	bool	operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return (false);
		for (typename vector<T, Alloc>::size_type i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return (false);
		return (true);

	}

	template <class T, class Alloc>
	bool	operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return (true);
		for (typename vector<T, Alloc>::size_type i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return (true);
		return (false);
	}
	
	template <class T, class Alloc>
	bool	operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		for (typename vector<T, Alloc>::size_type i = 0; i < lhs.size() && i < rhs.size(); i++) {
			if (lhs[i] > rhs[i])
				return (false);
			else if (lhs[i] < rhs[i])
				return (true);
		}
		if (lhs.size() < rhs.size())
			return (true);
		return (false);
	}

	template <class T, class Alloc>
	bool	operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		if (lhs == rhs || lhs < rhs)
			return (true);
		return (false);
	}
	
	template <class T, class Alloc>
	bool	operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		for (typename vector<T, Alloc>::size_type i = 0; i < lhs.size() && i < rhs.size(); i++) {
			if (lhs[i] < rhs[i])
				return (false);
			else if (lhs[i] > rhs[i])
				return (true);
		}
		if (lhs.size() > rhs.size())
			return (true);
		return (false);
	}

	template <class T, class Alloc>
	bool	operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		if (lhs == rhs || lhs > rhs)
			return (true);
		return (false);
	}

}

#endif
