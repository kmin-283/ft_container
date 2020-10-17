/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 13:31:13 by kmin              #+#    #+#             */
/*   Updated: 2020/10/17 15:15:17 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

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
            else
            {
                __position->mPrev->mNext = this;
            }
            this->mPrev = __position->mPrev;
            this->mNext = __position;
            __position->mPrev = this;
        }

        void unhook()
        {
            this->mPrev->mNext = this->mNext;
            this->mNext->mPrev = this->mPrev;
            this->mPrev = this;
            this->mNext = this;
        }
    };
    
    template <typename T>
    struct Node : public NodeBase
    {
        T mData;
    };
} // namespace ft
