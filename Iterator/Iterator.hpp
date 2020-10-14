/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 14:41:12 by kmin              #+#    #+#             */
/*   Updated: 2020/10/14 13:54:18 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "../Node/Node.hpp"

namespace ft
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag: input_iterator_tag {};
	struct bidirectional_iterator_tag: forward_iterator_tag {};
	struct random_access_iterator_tag: bidirectional_iterator_tag {};

    template <typename T, typename Category = bidirectional_iterator_tag>
    class Iterator
    {
    public:
        Node_base *mNode;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;

        typedef Iterator<T> _Self;
        typedef Node<T> _Node;

        typedef ptrdiff_t difference_type;

        Iterator()
            : mNode()
        {
        }
        Iterator(_Node *other)
            : mNode(other)
        {
        }
        _Self &operator=(const _Self &rhs)
        {
            this->mNode = rhs.mNode;
            return (*this);
        }
        reference operator*() const
        {
            return (static_cast<_Node *>(mNode)->mData);
        }
        pointer operator->() const
        {
            return (&static_cast<_Node *>(mNode)->mData);
        }
        _Self &operator++()
        {
            this->mNode = this->mNode->mNext;
            return (*this);
        }
        _Self operator++(int)
        {
            _Self temp = *this;
            this->mNode = this->mNode->mNext;
            return (temp);
        }
        _Self &operator--()
        {
            this->mNode = this->mNode->mPrev;
            return (*this);
        }
        _Self operator--(int)
        {
            _Self temp = *this;
            this->mNode = this->mNode->mPrev;
            return (temp);
        }
        bool operator==(const _Self &rhs) const
        {
            return (this->mNode == rhs.mNode);
        }
        bool operator!=(const _Self &rhs) const
        {
            return (this->mNode != rhs.mNode);
        }
        virtual ~Iterator() {}
    };

    template <typename T, typename Category = bidirectional_iterator_tag>
    class ConstIterator
    {
    public:
        const Node_base *mNode;

        typedef T value_type;
        typedef const T* pointer;
        typedef const T& reference;

        typedef ConstIterator<T> _Self;
        typedef const Node<T> _Node;
        typedef Iterator<T> iterator;

        typedef ptrdiff_t difference_type;

        ConstIterator()
            : mNode()
        {
        }
        ConstIterator(const _Node *other)
            : mNode(other)
        {
        }
        ConstIterator(const iterator &rhs)
            : mNode(rhs.mNode)
        {
        }
        _Self &operator=(const _Self &rhs)
        {
            this->mNode = rhs.mNode;
            return (*this);
        }
        reference operator*() const
        {
            return (static_cast<_Node *>(mNode)->mData);
        }
        pointer operator->() const
        {
            return (&static_cast<_Node *>(mNode)->mData);
        }
        _Self &operator++()
        {
            this->mNode = this->mNode->mNext;
            return (*this);
        }
        _Self operator++(int)
        {
            _Self temp = *this;
            this->mNode = this->mNode->mNext;
            return (temp);
        }
        _Self &operator--()
        {
            this->mNode = this->mNode->mPrev;
            return (*this);
        }
        _Self operator--(int)
        {
            _Self temp = *this;
            this->mNode = this->mNode->mPrev;
            return (temp);
        }
        bool operator==(const _Self &rhs) const
        {
            return (this->mNode == rhs.mNode);
        }
        bool operator!=(const _Self &rhs) const
        {
            return (this->mNode != rhs.mNode);
        }
        virtual ~ConstIterator() {}
    };
} // namespace ft

template <typename Val>
inline bool operator==(const ft::Iterator<Val> &x, const ft::ConstIterator<Val> &y)
{
    return (x.mNode->getSelf() == y.mNode->getSelf());
}
template <typename Val>
inline bool operator!=(const ft::Iterator<Val> &x, const ft::ConstIterator<Val> &y)
{
    return (x.mNode->getSelf() != y.mNode->getSelf());
}
template <typename Val>
inline bool operator>(const ft::Iterator<Val> &x, const ft::ConstIterator<Val> &y)
{
    return (x.mNode->getSelf() > y.mNode->getSelf());
}
template <typename Val>
inline bool operator>=(const ft::Iterator<Val> &x, const ft::ConstIterator<Val> &y)
{
    return (x.mNode->getSelf() >= y.mNode->getSelf());
}template <typename Val>
inline bool operator<(const ft::Iterator<Val> &x, const ft::ConstIterator<Val> &y)
{
    return (x.mNode->getSelf() < y.mNode->getSelf());
}
template <typename Val>
inline bool operator<=(const ft::Iterator<Val> &x, const ft::ConstIterator<Val> &y)
{
    return (x.mNode->getSelf() <= y.mNode->getSelf());
}