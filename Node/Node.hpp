/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 13:31:13 by kmin              #+#    #+#             */
/*   Updated: 2020/10/14 13:59:13 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
    struct Node_base
    {
        Node_base *mPrev;
        Node_base *mNext;
    };

	template <typename T>
	struct Node : public Node_base
	{
		T mData;
	};
} // namespace ft
