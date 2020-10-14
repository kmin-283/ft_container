/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConstIterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 14:41:12 by kmin              #+#    #+#             */
/*   Updated: 2020/10/14 13:54:20 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include "../Node/Node.hpp"
#include "Iterator.hpp"

namespace ft
{
    template <typename T>
    class ConstIterator
    {
    private:
        const Node<T> *mNode;
        std::string mIteratorCategory;
    public:

        typedef T value_type;
        typedef const T* pointer;
        typedef const T& reference;

        typedef ConstIterator<value_type> _Self;
        typedef const Node<value_type> _Node;
        typedef Iterator<value_type> iterator;

        typedef ptrdiff_t difference_type;

        ConstIterator()
            : mNode(), mIteratorCategory("bidiretion")
        {
        }
        ConstIterator(const _Node *other)
            : mNode(other), mIteratorCategory("bidirection")
        {
        }
        ConstIterator(const iterator &rhs)
            : mNode(rhs.mNode)
        {
        }
        _Self &operator=(const _Self &rhs)
        {
            this->mNode = rhs.mNode;
            this->mIteratorCategory = rhs.mIteratorCategory;
            return (*this);
        }
        reference operator*() const
        {
            return (this->mNode->getValue());
        }
        pointer operator->() const
        {
            return (&this->mNode->getValue());
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
            this->mNode = this->mNode->mPrevious;
            return (*this);
        }
        _Self operator--(int)
        {
            _Self temp = *this;
            this->mNode = this->mNode->mPrevious;
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