/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListIterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 14:41:12 by kmin              #+#    #+#             */
/*   Updated: 2020/10/24 16:39:59 by kmin             ###   ########.fr       */
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
    class ListIterator
    {
    public:
        NodeBase *mNode;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;

        typedef ListIterator<T> _Self;
        typedef Node<T> _Node;
#ifdef __MAC__
        typedef ptrdiff_t difference_type; //mac에서 사용할 때
#endif
#ifdef __linux__
        typedef __gnu_cxx::ptrdiff_t difference_type;
#endif
        ListIterator()
            : mNode()
        {
        }
        ListIterator(NodeBase *other)
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
        virtual ~ListIterator() {}
    };

    template <typename T, typename Category = bidirectional_iterator_tag>    
    class ConstListIterator
    {
    public:
        const NodeBase *mNode;

        typedef T value_type;
        typedef const T* pointer;
        typedef const T& reference;

        typedef ConstListIterator<T> _Self;
        typedef const Node<T> _Node;
        typedef ListIterator<T> iterator;

#ifdef __MAC__
        typedef ptrdiff_t difference_type; //mac에서 사용할 때
#endif
#ifdef __linux__
        typedef __gnu_cxx::ptrdiff_t difference_type;
#endif
        ConstListIterator()
            : mNode()
        {
        }
        ConstListIterator(const NodeBase *other)
            : mNode(other)
        {
        }
        ConstListIterator(const iterator &rhs)
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
        virtual ~ConstListIterator() {}
    };

    template <typename T, typename Category = bidirectional_iterator_tag>    
    class ReverseListIterator
    {
    public:
        NodeBase *mNode;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;

        typedef ReverseListIterator<T> _Self;
        typedef Node<T> _Node;

#ifdef __MAC__
        typedef ptrdiff_t difference_type; //mac에서 사용할 때
#endif
#ifdef __linux__
        typedef __gnu_cxx::ptrdiff_t difference_type;
#endif
        ReverseListIterator()
            : mNode()
        {
        }
        ReverseListIterator(NodeBase *other)
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
            this->mNode = this->mNode->mPrev;
            return (*this);
        }
        _Self operator++(int)
        {
            _Self temp = *this;
            this->mNode = this->mNode->mPrev;
            return (temp);
        }
        _Self &operator--()
        {
            this->mNode = this->mNode->mNext;
            return (*this);
        }
        _Self operator--(int)
        {
            _Self temp = *this;
            this->mNode = this->mNode->mNext;
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
        virtual ~ReverseListIterator() {}
    };

    template <typename T, typename Category = bidirectional_iterator_tag>    
    class ConstReverseListIterator
    {
    public:
        const NodeBase *mNode;
        typedef T value_type;
        typedef const T* pointer;
        typedef const T& reference;

        typedef ConstReverseListIterator<T> _Self;
        typedef const Node<T> _Node;

#ifdef __MAC__
        typedef ptrdiff_t difference_type; //mac에서 사용할 때
#endif
#ifdef __linux__
        typedef __gnu_cxx::ptrdiff_t difference_type;
#endif
        ConstReverseListIterator()
            : mNode()
        {
        }
        ConstReverseListIterator(NodeBase *other)
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
            this->mNode = this->mNode->mPrev;
            return (*this);
        }
        _Self operator++(int)
        {
            _Self temp = *this;
            this->mNode = this->mNode->mPrev;
            return (temp);
        }
        _Self &operator--()
        {
            this->mNode = this->mNode->mNext;
            return (*this);
        }
        _Self operator--(int)
        {
            _Self temp = *this;
            this->mNode = this->mNode->mNext;
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
        virtual ~ConstReverseListIterator() {}
    };
} // namespace ft

template <typename Val>
inline bool operator==(const ft::ListIterator<Val> &x, const ft::ConstListIterator<Val> &y)
{
    return (x.mNode == y.mNode);
}
template <typename Val>
inline bool operator!=(const ft::ListIterator<Val> &x, const ft::ConstListIterator<Val> &y)
{
    return (x.mNode != y.mNode);
}
template <typename Val>
inline bool operator>(const ft::ListIterator<Val> &x, const ft::ConstListIterator<Val> &y)
{
    return (x.mNode > y.mNode);
}
template <typename Val>
inline bool operator>=(const ft::ListIterator<Val> &x, const ft::ConstListIterator<Val> &y)
{
    return (x.mNode >= y.mNode);
}template <typename Val>
inline bool operator<(const ft::ListIterator<Val> &x, const ft::ConstListIterator<Val> &y)
{
    return (x.mNode < y.mNode);
}
template <typename Val>
inline bool operator<=(const ft::ListIterator<Val> &x, const ft::ConstListIterator<Val> &y)
{
    return (x.mNode <= y.mNode);
}
