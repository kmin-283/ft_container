/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 14:41:12 by kmin              #+#    #+#             */
/*   Updated: 2020/10/12 16:24:18 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include "../Node/Node.hpp"

namespace ft
{
    template <typename T>
    class Iterator
    {
    private:
        Node<T> *mNode;
        std::string mIteratorCategory;
    public:
        
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;

        typedef Iterator<value_type> _Self;
        typedef Node<value_type> _Node;

        typedef ptrdiff_t difference_type;

        Iterator()
            : mNode(), mIteratorCategory("bidiretion")
        {
        }
        Iterator(_Node *other)
            : mNode(other), mIteratorCategory("bidirection")
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
        bool operator>(const _Self &rhs) const
        {
            return (this->mNode > rhs.mNode);
        }
        bool operator>=(const _Self &rhs) const
        {
            return (this->mNode >= rhs.mNode);
        }
        bool operator<(const _Self &rhs) const
        {
            return (this->mNode < rhs.mNode);
        }
        bool operator<=(const _Self &rhs) const
        {
            return (this->mNode <= rhs.mNode);
        }
        virtual ~Iterator() {}
    };
} // namespace ft
