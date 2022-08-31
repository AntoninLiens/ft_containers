/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliens <aliens@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 18:22:43 by aliens            #+#    #+#             */
/*   Updated: 2022/08/31 18:22:20 by aliens           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft {
	
	/*************************************************************************************************
													PAIR
	**************************************************************************************************/

	template <class T1, class T2>
	class pair {
	public:
		typedef T1	first_type;
		typedef T2	second_type;

		first_type	first;
		second_type	second;

	/******************************************_CONSTRUCTORS_******************************************/

	pair(void) : first(first_type()), second(second_type()) {}
	
	template<class U, class V> 
	pair (const pair<U,V>& pair) : first(pair.first), second(pair.second) {}
	
	pair (const first_type& a, const second_type& b) : first(a), second(b) {}

	/******************************************_ASSIGN_OPERATOR_******************************************/

	pair& operator= (const pair& pair) {
		this->first = pair.first;
		this->second = pair.second;
		return (*this);
	}

	};

	/******************************************_NON_MEMBER_FUNCTIONS_OVERLOAD_******************************************/

	template <class T1, class T2>
  	bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}
	
	template <class T1, class T2>
	bool operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return (!(lhs == rhs));
	}

	template <class T1, class T2>
	bool operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	}
	
	template <class T1, class T2>
  	bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return (!(rhs < lhs));
	}
	
	template <class T1, class T2>
  	bool operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return (rhs < lhs);
	}

	template <class T1, class T2>
  	bool operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return (!(lhs < rhs));
	}

	template <class T1, class T2>
	pair<const T1,T2> make_pair(T1 a, T2 b) {
		return (pair<const T1, T2>(a, b));
	}

}

#endif