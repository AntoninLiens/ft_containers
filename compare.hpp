/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliens <aliens@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 17:53:49 by aliens            #+#    #+#             */
/*   Updated: 2022/09/05 16:43:12 by aliens           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPARE_HPP
# define COMPARE_HPP

#include <memory>

namespace ft {

	template <class T>
	struct less : std::binary_function<T, T, bool> {
		bool	operator()(const T& x, const T& y) const {
			return (x < y);
		}
	};

}

#endif
