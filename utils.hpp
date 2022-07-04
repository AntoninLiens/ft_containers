/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliens <aliens@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:29:02 by aliens            #+#    #+#             */
/*   Updated: 2022/06/22 11:44:59 by aliens           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft {

	/*************************************************************************************************
												INTEGRAL_CONSTANT
	**************************************************************************************************/

	template <class T, T v>
	struct integral_constant {
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T,v> type;
		operator	T() const {
			return (v);
		}
	};

	/*************************************************************************************************
												IS_INTEGRAL
	**************************************************************************************************/

	typedef ft::integral_constant<bool, true>	true_type;
	typedef ft::integral_constant<bool, false>	false_type;

	/******************************************_GENERAL_TEMPLATE_******************************************/

	template<class T>
	struct is_integral : public false_type {};
	
	/******************************************_SPECIALIZATIONS_******************************************/

	template<>
	struct is_integral<bool> : public true_type {};

	template<>
	struct is_integral<char> : public true_type {};

	template<>
	struct is_integral<wchar_t> : public true_type {};

	template<>
	struct is_integral<signed char> : public true_type {};
	
	template<>
	struct is_integral<short int> : public true_type {};

	template<>
	struct is_integral<int> : public true_type {};

	template<>
	struct is_integral<long int> : public true_type {};
	
	template<>
	struct is_integral<long long int> : public true_type {};

	template<>
	struct is_integral<unsigned char> : public true_type {};

	template<>
	struct is_integral<unsigned short int> : public true_type {};
	
	template<>
	struct is_integral<unsigned int> : public true_type {};

	template<>
	struct is_integral<unsigned long int> : public true_type {};

	template<>
	struct is_integral<unsigned long long int> : public true_type {};

	/*************************************************************************************************
												ENABLE_IF
	**************************************************************************************************/

	template<bool b2o, class T = void>
	struct enable_if {};
	
	template<class T>
	struct enable_if<true, T> {
		typedef T type;
	};

}

#endif
