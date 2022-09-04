/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliens <aliens@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 17:53:49 by aliens            #+#    #+#             */
/*   Updated: 2022/09/04 17:56:33 by aliens           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPARE_HPP
# define COMPARE_HPP

namespace ft {

	template <class T>
	struct less : std::binary_function<T, T, bool> {
		bool	operator()(const T& x, const T& y) const {
			return (x < y);
		}
	};

}

#endif