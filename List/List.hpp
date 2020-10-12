/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 13:19:12 by kmin              #+#    #+#             */
/*   Updated: 2020/10/12 18:50:51 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <memory>
#include "../Node/Node.hpp"

namespace ft
{
    template <typename T, typename _Alloc>
    class ListBase
    {
    protected:
        typedef typename _Alloc::template rebind<ft::Node<T>>::other _Node_Alloc_type;
        class ListImpl : public _Node_Alloc_type
        {
            public:
            Node<T> mNode;
            ListImpl(const _Node_Alloc_type &__a)
                : _Node_Alloc_type(__a)
            {
            }
        };
        ListImpl mImpl;
        Node<T> *mGetNode()
        {
            return mImpl._Node_Alloc_type::allocate(1);
        }

        void mPutNode(Node<T> *__p)
        {
            mImpl._Node_Alloc_type::deallocate(__p, 1);
        }

    public:
        ListBase()
        {
        }
        ListBase(const List<T> &other)
        {
        }
        ListBase &operator=(const List<T> &rhs)
        {
        }
        virtual ~ListBase() {}
    };

    template <typename T, typename _Alloc = std::allocator<T>>
    class List : protected ListBase<T, _Alloc>
    {
    private:
        /* data */
    public:
        List(/* args */);
        ~List();
    };
} // namespace ft
