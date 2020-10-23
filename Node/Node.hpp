/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 13:31:13 by kmin              #+#    #+#             */
/*   Updated: 2020/10/23 16:47:16 by kmin             ###   ########.fr       */
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
        void transfer_total(NodeBase * const __first, NodeBase * const __last)
        {
            __first->mPrev =  this->mPrev;
            this->mPrev->mNext = __first;
            this->mPrev = __last->mPrev;
            __last->mPrev->mNext = this;
            __last->mNext = __last;
            __last->mPrev = __last;
        }
        void transfer(NodeBase * const __first, NodeBase * const __last)
        {
            __last->mPrev = __first->mPrev;
            __first->mPrev->mNext = __last; // 이동 전의 노드들의 결합을 바꿔줌
            
            __first->mPrev = this->mPrev; 
            this->mPrev->mNext = __first;
            __first->mNext = this;
            this->mPrev = __first;
        }
    };
    
    template <typename T>
    struct Node : public NodeBase
    {
        T mData;
    };
} // namespace ft
