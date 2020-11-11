/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 18:52:12 by kmin              #+#    #+#             */
/*   Updated: 2020/11/11 18:36:17 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functional>

namespace ft
{
    template <typename T>
    bool equal(const T &a, const T &b)
    {
        return (a == b);
    }
    template <typename T>
    bool less(const T &a, const T &b)
    {
        return (a < b);
    }
}