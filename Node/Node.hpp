/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 13:31:13 by kmin              #+#    #+#             */
/*   Updated: 2020/10/23 14:07:24 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

#define BEGIN 1
#define END 2
#define ELSE 3

namespace ft
{
    struct NodeBase
    {
        NodeBase *mNext;
        NodeBase *mPrev;

        void hook(NodeBase * const __position, int type)
        {
            if (type == BEGIN) // begin()
            {
                this->mPrev = __position->mPrev;
                __position->mPrev = this;
                this->mNext = __position;
            }
            else if (type == END) // end()
            {
                __position->mPrev->mNext = this;
                this->mNext = __position;
                this->mPrev = __position->mPrev;
                __position->mPrev = this;
            }
            else
            {
                this->mPrev = __position->mPrev;
                __position->mPrev = this;
                this->mNext = __position;
            }
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
            if (__first != __last->mPrev) // last는 next 또는 prev의 비교대상이 될 수 없음 Node가 될 수 있기 때문에 end()인 경우
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
