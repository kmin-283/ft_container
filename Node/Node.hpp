/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 13:31:13 by kmin              #+#    #+#             */
/*   Updated: 2020/10/12 17:22:20 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
    template <typename T>
    class Node
    {
    private:
        Node<T> *mPrevious;
        Node<T> *mNext;
        T mValue;

    public:
        typedef Node<T> _Self;
        Node();
        Node(const T &value);
        Node(const Node &other);
        _Self &operator=(const Node &rhs);
        void setPrevious(const Node<T> &previous);
        void setNext(const Node<T> &next);
        void setValue(const T &value);
        T &getValue();
        const T &getValue() const;
        _Self *getSelf();
        const _Self *getSelf() const;
        virtual ~Node();
    };
} // namespace ft

template <typename T>
ft::Node<T>::Node()
    : mPrevious(nullptr), mNext(nullptr), mValue()
{
}

template <typename T>
ft::Node<T>::Node(const T &value)
    : mPrevious(nullptr), mNext(nullptr), mValue(value)
{
}

template <typename T>
ft::Node<T>::Node(const Node &other)
    : mPrevious(other.mPrevious), mNext(other.mNext), mValue(other.mValue)
{
}

template <typename T>
ft::Node<T> &ft::Node<T>::operator=(const Node &rhs)
{
    this->mPrevious = rhs.mPrevious;
    this->mNext = rhs.mNext;
    this->mValue = rhs.mValue;

    return (*this);
}

template <typename T>
void ft::Node<T>::setPrevious(const Node<T> &previous)
{
    this->mPrevious = &previous;
}

template <typename T>
void ft::Node<T>::setNext(const Node<T> &next)
{
    this->mNext = &next;
}

template <typename T>
void ft::Node<T>::setValue(const T &value)
{
    this->mValue = value;
}

template <typename T>
T &ft::Node<T>::getValue()
{
    return (this->mValue);
}

template <typename T>
const T &ft::Node<T>::getValue() const
{
    return (this->mValue);
}

template <typename T>
ft::Node<T> *ft::Node<T>::getSelf()
{
    return (this);
}
template <typename T>
const ft::Node<T> *ft::Node<T>::getSelf() const
{
    return (this);
}

template <typename T>
ft::Node<T>::~Node()
{
}