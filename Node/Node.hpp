/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 13:31:13 by kmin              #+#    #+#             */
/*   Updated: 2020/10/26 14:49:20 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
    struct NodeBase
    {
        NodeBase *mNext;
        NodeBase *mPrev;

        void hook_front(NodeBase *const __position)
        {
            this->mPrev = __position->mPrev;
            __position->mPrev = this;
            this->mNext = __position;
        }
        void hook_end(NodeBase *const __position)
        {
            __position->mPrev->mNext = this;
            this->mNext = __position;
            this->mPrev = __position->mPrev;
            __position->mPrev = this;
        }
        void unhook()
        {
            this->mPrev->mNext = this->mNext;
            this->mNext->mPrev = this->mPrev;
            this->mPrev = this;
            this->mNext = this;
        }
        // void transfer_start_to_end(NodeBase *const __first, NodeBase *const __last)
        // {
        //     __first->mPrev = this->mPrev;
        //     this->mPrev->mNext = __first;
        //     this->mPrev = __last->mPrev;
        //     __last->mPrev->mNext = this;
        //     __last->mNext = __last;
        //     __last->mPrev = __last;
        // }
        void transfer_range(NodeBase *const __first, NodeBase *const __last)
        {
            __first->mPrev->mNext = __last->mNext;
            __last->mNext->mPrev = __first->mPrev; // 이동 전의 노드들의 결합을 바꿔줌

            __first->mPrev = this->mPrev;
            this->mPrev->mNext = __first;
            __last->mNext = this;
            this->mPrev = __last;
        }
        void transfer(NodeBase *const __first, NodeBase *const __last)
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
