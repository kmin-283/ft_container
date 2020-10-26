/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:45:06 by kmin              #+#    #+#             */
/*   Updated: 2020/10/26 13:13:01 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
    struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag: input_iterator_tag {};
	struct bidirectional_iterator_tag: forward_iterator_tag {};
	struct random_access_iterator_tag: bidirectional_iterator_tag {};

    template <typename T, typename Category = random_access_iterator_tag>
    class VectorIterator
    {
    public:
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;

        typedef VectorIterator<T> _Self;
#ifdef __linux__
        typedef __gnu_cxx::ptrdiff_t difference_type;
#endif
#ifdef __APPLE__
        typedef ptrdiff_t difference_type;
#endif
    private:
        pointer mData;
    public:
        VectorIterator()
        {}
        VectorIterator(const VectorIterator &other)
            :mData(other.mData)
        {}
        _Self &operator=(const VectorIterator &rhs)
        {
            this->mData = rhs.mData;
            return (*this);
        }
        reference operator*() const
        {
            return (*this->mData);
        }
        pointer operator->() const
        {
            return (&this->mData);
        }
        _Self &operator++()
        {
            ++this->mData;
            return (*this);
        }
        _Self operator++(int)
        {
            _Self temp = *this;
            ++this->mData;
            return (temp);
        }
        _Self &operator--()
        {
            --this->mData;
            return (*this);
        }
        _Self operator--(int)
        {
            _Self temp = *this;
            --this->mData;
            return (temp);
        }
        bool operator==(const _Self &rhs) const
        {
            return (this->mData == rhs.mData);
        }
        bool operator!=(const _Self &rhs) const
        {
            return (this->mData != rhs.mData);
        }
        virtual ~VectorIterator() {}
    };

    template <typename T, typename Category = random_access_iterator_tag>
    class ConstVectorIterator
    {
    public:
        typedef T value_type;
        typedef const T* pointer;
        typedef const T& reference;
        typedef ConstVectorIterator<T> _Self;

#ifdef __linux__
        typedef __gnu_cxx::ptrdiff_t difference_type;
#endif
#ifdef __APPLE__
        typedef ptrdiff_t difference_type;
#endif
    private:
        pointer mData;
    public:
        ConstVectorIterator()
        {}
        ConstVectorIterator(const ConstVectorIterator &other)
            :mData(other.mData)
        {}
        _Self &operator=(const ConstVectorIterator &rhs)
        {
            this->mData = rhs.mData;
            return (*this);
        }
        reference operator*() const
        {
            return (*this->mData);
        }
        pointer operator->() const
        {
            return (&this->mData);
        }
        _Self &operator++()
        {
            ++this->mData;
            return (*this);
        }
        _Self operator++(int)
        {
            _Self temp = *this;
            ++this->mData;
            return (temp);
        }
        _Self &operator--()
        {
            --this->mData;
            return (*this);
        }
        _Self operator--(int)
        {
            _Self temp = *this;
            --this->mData;
            return (temp);
        }
        bool operator==(const _Self &rhs) const
        {
            return (this->mData == rhs.mData);
        }
        bool operator!=(const _Self &rhs) const
        {
            return (this->mData != rhs.mData);
        }
        virtual ~ConstVectorIterator() {}
    };

    template <typename T, typename Category = random_access_iterator_tag>
    class ReverseVectorIterator
    {
    public:
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef ReverseVectorIterator<T> _Self;
        
#ifdef __linux__
        typedef __gnu_cxx::ptrdiff_t difference_type;
#endif
#ifdef __APPLE__
        typedef ptrdiff_t difference_type;
#endif
    private:
        pointer mData;
    public:
        ReverseVectorIterator()
        {}
        ReverseVectorIterator(const ReverseVectorIterator &other)
            :mData(other.mData)
        {}
        _Self &operator=(const ReverseVectorIterator &rhs)
        {
            this->mData = rhs.mData;
            return (*this);
        }
        reference operator*() const
        {
            return (*this->mData);
        }
        pointer operator->() const
        {
            return (&this->mData);
        }
        _Self &operator++()
        {
            ++this->mData;
            return (*this);
        }
        _Self operator++(int)
        {
            _Self temp = *this;
            ++this->mData;
            return (temp);
        }
        _Self &operator--()
        {
            --this->mData;
            return (*this);
        }
        _Self operator--(int)
        {
            _Self temp = *this;
            --this->mData;
            return (temp);
        }
        bool operator==(const _Self &rhs) const
        {
            return (this->mData == rhs.mData);
        }
        bool operator!=(const _Self &rhs) const
        {
            return (this->mData != rhs.mData);
        }
        virtual ~ReverseVectorIterator() {}
    };

    template <typename T, typename Category = random_access_iterator_tag>
    class ConstReverseVectorIterator
    {
    public:
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;

        typedef ConstReverseVectorIterator<T> _Self;
#ifdef __linux__
        typedef __gnu_cxx::ptrdiff_t difference_type;
#endif
#ifdef __APPLE__
        typedef ptrdiff_t difference_type;
#endif
    private:
        pointer mData;
    public:
        ConstReverseVectorIterator()
        {}
        ConstReverseVectorIterator(const ConstReverseVectorIterator &other)
            :mData(other.mData)
        {}
        _Self &operator=(const ConstReverseVectorIterator &rhs)
        {
            this->mData = rhs.mData;
            return (*this);
        }
        reference operator*() const
        {
            return (*this->mData);
        }
        pointer operator->() const
        {
            return (&this->mData);
        }
        _Self &operator++()
        {
            ++this->mData;
            return (*this);
        }
        _Self operator++(int)
        {
            _Self temp = *this;
            ++this->mData;
            return (temp);
        }
        _Self &operator--()
        {
            --this->mData;
            return (*this);
        }
        _Self operator--(int)
        {
            _Self temp = *this;
            --this->mData;
            return (temp);
        }
        bool operator==(const _Self &rhs) const
        {
            return (this->mData == rhs.mData);
        }
        bool operator!=(const _Self &rhs) const
        {
            return (this->mData != rhs.mData);
        }
        virtual ~ConstReverseVectorIterator() {}
    };
}

template <typename Val>
inline bool operator==(const ft::VectorIterator<Val> &x, const ft::ConstVectorIterator<Val> &y)
{
    return (x == y);
}
template <typename Val>
inline bool operator!=(const ft::VectorIterator<Val> &x, const ft::ConstVectorIterator<Val> &y)
{
    return (x != y);
}
template <typename Val>
inline bool operator>(const ft::VectorIterator<Val> &x, const ft::ConstVectorIterator<Val> &y)
{
    return (x > y);
}
template <typename Val>
inline bool operator>=(const ft::VectorIterator<Val> &x, const ft::ConstVectorIterator<Val> &y)
{
    return (x >= y);
}template <typename Val>
inline bool operator<(const ft::VectorIterator<Val> &x, const ft::ConstVectorIterator<Val> &y)
{
    return (x < y);
}
template <typename Val>
inline bool operator<=(const ft::VectorIterator<Val> &x, const ft::ConstVectorIterator<Val> &y)
{
    return (x <= y);
}
