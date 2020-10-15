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
#include <iostream>

namespace ft
{
    struct NodeBase
    {
        NodeBase *mNext;
        NodeBase *mPrev;

        void hook(NodeBase * const __position)
        {
            if (__position == __position->mNext)
                __position->mNext = this;
            this->mPrev = __position;
            this->mNext = __position->mPrev;
            __position->mPrev = this;
        }
    };
    
    template <typename T>
    struct Node : public NodeBase
    {
        T mData;
    };
} // namespace ft
