/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 13:31:13 by kmin              #+#    #+#             */
/*   Updated: 2020/10/22 15:56:59 by kmin             ###   ########.fr       */
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

        void transfer(NodeBase * const __first, NodeBase * const __last)
        {
            __last->mPrev->mNext = this;
            if (__first != __last->mPrev) // last는 next 또는 prev의 비교대상이 될 수 없음 Node이기 때문에
            {
                __last->mNext = __last; // end()의 경우 맨 처음 상태인 self->next = self;
                __last->mPrev = __last; // self->prev = self로 만들어줌
            }
            else if (__first == __last->mPrev)
            {
                __first->mPrev->mNext = __last;
                __last->mPrev = __first->mPrev;
            }
            __first->mPrev = this->mPrev;
            this->mPrev->mNext = __first;
            this->mPrev = __last->mPrev;
        } 
    };
    
    template <typename T>
    struct Node : public NodeBase
    {
        T mData;
    };
} // namespace ft
