/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DequeIterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:02:36 by kmin              #+#    #+#             */
/*   Updated: 2020/11/26 19:40:28 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "../Vector/vector.hpp"

#define DEQUEBUFSIZE 512

inline __gnu_cxx::size_t DequeBufSize(__gnu_cxx::size_t __size)
{
    return (__size < DEQUEBUFSIZE ? __gnu_cxx::size_t(DEQUEBUFSIZE/__size) : __gnu_cxx::size_t(1));
}
namespace ft
{
    template <typename T, typename _Ref, typename _Ptr, typename Category = random_access_iterator_tag>
    class DequeIterator
    {
    public:
        typedef DequeIterator<T, T&, T*>            iterator;

        typedef Category                            iterator_category;
        typedef T                                   value_type;
        typedef T*                                  pointer;
        typedef T&                                  reference;

        typedef ft::vector<T>*                      MapPointer;

        typedef DequeIterator<T, T&, T*>            _Self;

#ifdef __linux__
        typedef __gnu_cxx::size_t   size_type;
        typedef __gnu_cxx::ptrdiff_t difference_type;
#endif
#ifdef __APPLE__
        typedef size_t      size_type;
        typedef ptrdiff_t difference_type;
#endif
        
        
        static size_type sBufferSize()
        {
            return (DequeBufSize(sizeof(T)));
        }
    public:
        pointer mCur;
        pointer mFirst;
        pointer mLast;
        MapPointer mNode;

        DequeIterator()
            : mCur(0), mFirst(0), mLast(0), mNode(0)
        {}
        DequeIterator(pointer __x, MapPointer __y)
            : mCur(__x), mFirst(*__y), mLast(*__y + sBufferSize()), mNode(__y)
        {}
        DequeIterator(const iterator &__x)
            : mCur(__x.mCur), mFirst(__x.mFirst), mLast(__x.mLast), mNode(__x.mNode)
        {}
        _Self &operator=(const iterator &rhs)
        {
            this->mData = rhs.mData;
            return (*this);
        }
        reference operator*() const
        {
            return *mCur;
        }
        pointer operator->() const
        {
            return mCur;
        }
        _Self &operator++()
        {
            ++mCur;
            if (mCur == mLast)
            {
                mSetNode(mNode + 1);
                mCur = mFirst;
            }
            return (*this);
        }
        _Self operator++(int)
        {
            _Self __tmp = *this;
            ++*this;
            return (__tmp);
        }
        _Self &operator--()
        {
            if (mCur == mFirst)
            {
                mSetNode(mNode - 1);
                mCur = mLast;
            }
            --mCur;
            return (*this);
        }
        _Self operator--(int)
        {
            _Self __tmp = *this;
            --*this;
            return (__tmp);
        }
        _Self operator+=(difference_type __n)
        {
            const difference_type __offset = __n + (mCur - mFirst);
            if (__offset >= 0 && __offset < difference_type(sBufferSize()))
                mCur += __n;
            else
            {
                const difference_type __node_offset = __offset > 0 ? __offset / difference_type(sBufferSize()) \
                                                        : -difference_type((-__offset - 1) / sBufferSize()) - 1;
                mSetNode(mNode + __node_offset);
                mCur = mFirst + (__offset - __node_offset * difference_type(sBufferSize()));
            }
            return (*this);
        }
        _Self operator+(difference_type __n) const{
            _Self __tmp = *this;
            return (__tmp += __n);
        }
        _Self &operator-=(difference_type __n)
        {
            return *this += -__n;
        }
        _Self operator-(difference_type __n) const
        {
            _Self __tmp = *this;
            
            return (__tmp -= __n);
        }
        reference operator[](difference_type __n) const
        {
            return (*(*this + __n));
        }
        void mSetNode(MapPointer __new_node)
        {
            mNode = __new_node;
            mFirst = &(*__new_node)[0];
            mLast = mFirst + difference_type(sBufferSize());
        }
        virtual ~DequeIterator() {}
    };

    template <typename T, typename _Ref, typename _Ptr, typename Category = random_access_iterator_tag>
    class ConstDequeIterator
    {
    public:
        typedef ConstDequeIterator<T, T&, T*>             iterator;

        typedef Category iterator_category;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;

        typedef ft::vector<T>*              MapPointer;

        typedef ConstDequeIterator<T, T&, T*> _Self;

#ifdef __linux__
        typedef __gnu_cxx::size_t   size_type;
        typedef __gnu_cxx::ptrdiff_t difference_type;
#endif
#ifdef __APPLE__
        typedef size_t      size_type;
        typedef ptrdiff_t difference_type;
#endif
    static size_type sBufferSize()
    {
        return (DequeBufSize(sizeof(T)));
    }
    public:
        pointer mCur;
        pointer mFirst;
        pointer mLast;
        MapPointer mNode;
        
        ConstDequeIterator()
            : mCur(0), mFirst(0), mLast(0), mNode(0)
        {}
        ConstDequeIterator(pointer __x, MapPointer __y)
            : mCur(__x), mFirst(*__y), mLast(*__y + sBufferSize()), mNode(__y)
        {}
        ConstDequeIterator(const iterator &__x)
            : mCur(__x.mCur), mFirst(__x.mFirst), mLast(__x.mLast), mNode(__x.mNode)
        {}
        _Self &operator=(const iterator &rhs)
        {
            this->mData = rhs.mData;
            return (*this);
        }
        reference operator*() const
        {
            return *mCur;
        }
        pointer operator->() const
        {
            return mCur;
        }
        _Self &operator++()
        {
            ++mCur;
            if (mCur == mLast)
            {
                mSetNode(mNode + 1);
                mCur = mFirst;
            }
            return (*this);
        }
        _Self operator++(int)
        {
            _Self __tmp = *this;
            ++*this;
            return (__tmp);
        }
        _Self &operator--()
        {
            if (mCur == mFirst)
            {
                mSetNode(mNode - 1);
                mCur = mLast;
            }
            --mCur;
            return (*this);
        }
        _Self operator--(int)
        {
            _Self __tmp = *this;
            --*this;
            return (__tmp);
        }
        _Self operator+=(difference_type __n)
        {
            const difference_type __offset = __n + (mCur - mFirst);
            if (__offset >= 0 && __offset < difference_type(sBufferSize()))
                mCur += __n;
            else
            {
                const difference_type __node_offset = __offset > 0 ? __offset / difference_type(sBufferSize()) \
                                                        : -difference_type((-__offset - 1) / sBufferSize()) - 1;
                mSetNode(mNode + __node_offset);
                mCur = mFirst + (__offset - __node_offset * difference_type(sBufferSize()));
            }
            return (*this);
        }
        _Self operator+(difference_type __n) const{
            _Self __tmp = *this;
            return (__tmp += __n);
        }
        _Self &operator-=(difference_type __n)
        {
            return *this += -__n;
        }
        _Self operator-(difference_type __n) const
        {
            _Self __tmp = *this;
            
            return (__tmp -= __n);
        }
        reference operator[](difference_type __n) const
        {
            return (*(*this + __n));
        }
        void mSetNode(MapPointer __new_node)
        {
            mNode = __new_node;
            mFirst = *__new_node;
            mLast = mFirst + difference_type(sBufferSize());
        }
        virtual ~ConstDequeIterator() {}
    };
    template <typename T, typename _Ref, typename _Ptr>
    inline bool operator==(const DequeIterator<T, _Ref, _Ptr> &__x, const DequeIterator<T, _Ref, _Ptr> &__y)
    {
        return (__x.mCur == __y.mCur);
    }
    template <typename T, typename _RefL, typename _PtrL, typename _RefR, typename _PtrR>
    inline bool operator==(const DequeIterator<T, _RefL, _PtrL> &__x, const DequeIterator<T, _RefR, _PtrR> &__y)
    {
        return (__x.mCur == __y.mCur);
    }
    template <typename T, typename _Ref, typename _Ptr>
    inline bool operator!=(const DequeIterator<T, _Ref, _Ptr> &__x, const DequeIterator<T, _Ref, _Ptr> &__y)
    {
        return !(__x.mCur == __y.mCur);
    }
    template <typename T, typename _RefL, typename _PtrL, typename _RefR, typename _PtrR>
    inline bool operator!=(const DequeIterator<T, _RefL, _PtrL> &__x, const DequeIterator<T, _RefR, _PtrR> &__y)
    {
        return !(__x.mCur == __y.mCur);
    }
    template <typename T, typename _Ref, typename _Ptr>
    inline bool operator<(const DequeIterator<T, _Ref, _Ptr> &__x, const DequeIterator<T, _Ref, _Ptr> &__y)
    {
        return !(__x.mNode == __y.mNode) ? (__x.mCur < __y.mCur) : (__x.mNode < __y.mNode);
    }
    template <typename T, typename _RefL, typename _PtrL, typename _RefR, typename _PtrR>
    inline bool operator<(const DequeIterator<T, _RefL, _PtrL> &__x, const DequeIterator<T, _RefR, _PtrR> &__y)
    {
        return !(__x.mNode == __y.mNode) ? (__x.mCur < __y.mCur) : (__x.mNode < __y.mNode);
    }
    template <typename T, typename _Ref, typename _Ptr>
    inline bool operator>(const DequeIterator<T, _Ref, _Ptr> &__x, const DequeIterator<T, _Ref, _Ptr> &__y)
    {
        return (__y < __x);
    }
    template <typename T, typename _RefL, typename _PtrL, typename _RefR, typename _PtrR>
    inline bool operator>(const DequeIterator<T, _RefL, _PtrL> &__x, const DequeIterator<T, _RefR, _PtrR> &__y)
    {
        return (__y < __x);
    }
    template <typename T, typename _Ref, typename _Ptr>
    inline bool operator<=(const DequeIterator<T, _Ref, _Ptr> &__x, const DequeIterator<T, _Ref, _Ptr> &__y)
    {
        return !(__y < __x);
    }
    template <typename T, typename _RefL, typename _PtrL, typename _RefR, typename _PtrR>
    inline bool operator<=(const DequeIterator<T, _RefL, _PtrL> &__x, const DequeIterator<T, _RefR, _PtrR> &__y)
    {
        return !(__y < __x);
    }
    template <typename T, typename _Ref, typename _Ptr>
    inline bool operator>=(const DequeIterator<T, _Ref, _Ptr> &__x, const DequeIterator<T, _Ref, _Ptr> &__y)
    {
        return !(__x < __y);
    }
    template <typename T, typename _RefL, typename _PtrL, typename _RefR, typename _PtrR>
    inline bool operator>=(const DequeIterator<T, _RefL, _PtrL> &__x, const DequeIterator<T, _RefR, _PtrR> &__y)
    {
        return !(__x < __y);
    }
    template <typename T, typename _Ref, typename _Ptr>
    inline typename DequeIterator<T, _Ref, _Ptr>::difference_type \
    operator-(const DequeIterator<T, _Ref, _Ptr> &__x, const DequeIterator<T, _Ref, _Ptr> &__y)
    {
        return typename DequeIterator<T, _Ref, _Ptr>::difference_type(DequeIterator<T, _Ref, _Ptr>::sBufferSize()) \
        * (__x.mNode - __y.mNode - 1) + (__x.mCur - __x.mFirst) + (__y.mLast - __y.mCur);
    }
    template <typename T, typename _RefL, typename _PtrL, typename _RefR, typename _PtrR>
    inline typename DequeIterator<T, _RefL, _PtrL>::difference_type \
    operator-(const DequeIterator<T, _RefL, _PtrL> &__x, const DequeIterator<T, _RefR, _PtrR> &__y)
    {
        return typename DequeIterator<T, _RefL, _PtrL>::difference_type(DequeIterator<T, _RefL, _PtrL>::sBufferSize()) \
        * (__x.mNode - __y.mNode - 1) + (__x.mCur - __x.mFirst) + (__y.mLast - __y.mCur);
    }
    template<typename T, typename _Ref, typename _Ptr>
    inline DequeIterator<T, _Ref, _Ptr> operator+(typename DequeIterator<T, _Ref, _Ptr>::difference_type __n, const DequeIterator<T, _Ref, _Ptr> &__x)
    {
        return __x + __n;
    }
} // namespace ft
