/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:45:06 by kmin              #+#    #+#             */
/*   Updated: 2020/11/05 16:09:24 by kmin             ###   ########.fr       */
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
        typedef Category iterator_category;
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
    public:
        pointer mData;

        VectorIterator()
        {}
        VectorIterator(pointer ptr)
            :mData(ptr)
        {}
        VectorIterator(const VectorIterator<T> &other)
            :mData(other.mData)
        {}
        _Self &operator=(const VectorIterator<T> &rhs)
        {
            this->mData = rhs.mData;
            return (*this);
        }
        difference_type distance(const VectorIterator<T> &other)
        {
            return (other.mData - this->mData > 0 ? other.mData - this->mData : this->mData - other.mData);
        }
        reference operator*() const
        {
            return (*this->mData);
        }
        pointer operator->() const
        {
            return (&this->mData);
        }
        _Self &operator+(int cnt)
        {
            for (int i = 0; i < cnt; ++i)
                ++this->mData;
            return (*this);
        }
        _Self &operator-(int cnt)
        {
            for (int i = 0; i < cnt; ++i)
                --this->mData;
            return (*this);
        }
        difference_type operator-(VectorIterator<T> &other)
        {
            difference_type distance = this->mData - other.mData;
            return (distance);
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
        typedef Category iterator_category;
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
    public:
        pointer mData;

        ConstVectorIterator()
        {}
        ConstVectorIterator(pointer ptr)
            :mData(ptr)
        {}
        ConstVectorIterator(const ConstVectorIterator<T> &other)
            :mData(other.mData)
        {}
        _Self &operator=(const ConstVectorIterator<T> &rhs)
        {
            this->mData = rhs.mData;
            return (*this);
        }
        difference_type distance(const ConstVectorIterator<T> &other)
        {
            return (other.mData - this->mData > 0 ? other.mData - this->mData : this->mData - other.mData);
        }
        reference operator*() const
        {
            return (*this->mData);
        }
        pointer operator->() const
        {
            return (&this->mData);
        }
        _Self &operator+(int cnt)
        {
            for (int i = 0; i < cnt; ++i)
                ++this->mData;
            return (*this);
        }
        _Self &operator-(int cnt)
        {
            for (int i = 0; i < cnt; ++i)
                --this->mData;
            return (*this);
        }
        difference_type operator-(ConstVectorIterator<T> &other)
        {
            difference_type distance = this->mData - other.mData;
            return (distance);
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
        typedef Category iterator_category;
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
    public:
        pointer mData;

        ReverseVectorIterator()
        {}
        ReverseVectorIterator(pointer ptr)
            :mData(ptr)
        {}
        ReverseVectorIterator(const ReverseVectorIterator<T> &other)
            :mData(other.mData)
        {}
        ReverseVectorIterator(const VectorIterator<T> &other)
            :mData(other.mData)
        {}
        _Self &operator=(const ReverseVectorIterator<T> &rhs)
        {
            this->mData = rhs.mData;
            return (*this);
        }
        difference_type distance(const ReverseVectorIterator<T> &other)
        {
            return (other.mData - this->mData > 0 ? other.mData - this->mData : this->mData - other.mData);
        }
        reference operator*() const
        {
            return (*this->mData);
        }
        pointer operator->() const
        {
            return (&this->mData);
        }
        _Self &operator+(int cnt)
        {
            for (int i = 0; i < cnt; ++i)
                --this->mData;
            return (*this);
        }
        _Self &operator-(int cnt)
        {
            for (int i = 0; i < cnt; ++i)
                ++this->mData;
            return (*this);
        }
        difference_type operator-(ReverseVectorIterator<T> &other)
        {
            difference_type distance = other.mData - this->mData;
            return (distance);
        }
        _Self &operator++()
        {
            --this->mData;
            return (*this);
        }
        _Self operator++(int)
        {
            _Self temp = *this;
            --this->mData;
            return (temp);
        }
        _Self &operator--()
        {
            ++this->mData;
            return (*this);
        }
        _Self operator--(int)
        {
            _Self temp = *this;
            ++this->mData;
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
        typedef Category iterator_category;
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
    public:
        pointer mData;

        ConstReverseVectorIterator()
        {}
        ConstReverseVectorIterator(pointer ptr)
            :mData(ptr)
        {}
        ConstReverseVectorIterator(const ConstReverseVectorIterator<T> &other)
            :mData(other.mData)
        {}
        ConstReverseVectorIterator(const VectorIterator<T> &other)
            :mData(other.mData)
        {}
        _Self &operator=(const ConstReverseVectorIterator<T> &rhs)
        {
            this->mData = rhs.mData;
            return (*this);
        }
        difference_type distance(const ConstReverseVectorIterator<T> &other)
        {
            return (other.mData - this->mData > 0 ? other.mData - this->mData : this->mData - other.mData);
        }
        reference operator*() const
        {
            return (*this->mData);
        }
        pointer operator->() const
        {
            return (&this->mData);
        }
        _Self &operator+(int cnt)
        {
            for (int i = 0; i < cnt; ++i)
                --this->mData;
            return (*this);
        }
        _Self &operator-(int cnt)
        {
            for (int i = 0; i < cnt; ++i)
                ++this->mData;
            return (*this);
        }
        difference_type operator-(ConstReverseVectorIterator<T> &other)
        {
            difference_type distance = other.mData - this->mData;
            return (distance);
        }
        _Self &operator++()
        {
            --this->mData;
            return (*this);
        }
        _Self operator++(int)
        {
            _Self temp = *this;
            --this->mData;
            return (temp);
        }
        _Self &operator--()
        {
            ++this->mData;
            return (*this);
        }
        _Self operator--(int)
        {
            _Self temp = *this;
            ++this->mData;
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
