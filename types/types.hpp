/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 01:51:17 by kmin              #+#    #+#             */
/*   Updated: 2020/11/25 01:56:07 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <limits>

namespace ft
{
    template <bool>
    struct my_tf_type
    {};

    typedef my_tf_type<true>     my_true_type;
    typedef my_tf_type<false>    my_false_type;

    template <typename T>
    struct my_is_integral
    {
        typedef my_tf_type<std::numeric_limits<T>::is_integer> true_or_false_type;
    };
} // namespace ft