/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 13:31:13 by kmin              #+#    #+#             */
/*   Updated: 2020/11/24 19:46:24 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
    struct NodeBase
    {
        NodeBase *mNext;
        NodeBase *mPrev;

        void hooking(NodeBase *const __position)
        {
            __position->mPrev->mNext = this;
            this->mPrev = __position->mPrev;
            __position->mPrev = this;
            this->mNext = __position;
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

        static void swap(NodeBase &__x, NodeBase &__y)
        {
            NodeBase tmp;

            __x.mNext->mPrev = &__y;
            __y.mNext->mPrev = &__x;
            __x.mPrev->mNext = &__y;
            __y.mPrev->mNext = &__x;

            tmp.mNext = __x.mNext;
            tmp.mPrev = __x.mPrev;

            __x.mNext = __y.mNext;
            __y.mNext = tmp.mNext;

            __y.mPrev = &__x;
            __x.mPrev = &__y;
        }
    };

    template <typename T>
    struct Node : public NodeBase
    {
        T mData;
    };
} // namespace ft
