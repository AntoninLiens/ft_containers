/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_compare.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliens <aliens@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 18:29:32 by aliens            #+#    #+#             */
/*   Updated: 2022/08/31 17:56:33 by aliens           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_COMPARE_HPP
# define ITERATOR_COMPARE_HPP

namespace ft {
	
	template <class InputIterator1, class InputIterator2>
	bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
		while (first1 != last1) {
			if (first2 == last2 || *first2 < *first1)
				return (false);
			else if (*first1 < *first2)
				return (true);
			++first1; 
			++first2;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
		while (first1 != last1) {
			if (!(*first1 == *first2))
				return (false);
			++first1;
			++first2;
		}
		return true;
	}

}

#endif