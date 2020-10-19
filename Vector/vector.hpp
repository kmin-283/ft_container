/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 14:33:58 by kmin              #+#    #+#             */
/*   Updated: 2020/10/19 17:03:24 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <memory>
#include "../Iterator/VectorIterator.hpp"

namespace ft
{
    template <typename T, typename _Alloc>
    struct VectorBase
    {
        typedef typename _Alloc::template rebind<T>::other T_allocator_type;

        struct VectorImpl : public T_allocator_type
        {
            typename T_allocator_type::pointer mStart;
            typename T_allocator_type::pointer mFinish;
            typename T_allocator_type::pointer mEndOfStorage;

            VectorImpl(const T_allocator_type &__a)
                : T_allocator_type(__a), mStart(0), mFinish(0), mEndOfStorage(0)
            {}
        };
    public:
        typedef _Alloc  allocator_type;
        typedef size_t  size_type;

        VectorImpl mImpl;

        allocator_type getAllocator() const
        {
            return (allocator_type(*static_cast<T_allocator_type *>(&this->mImpl)));
        }

        VectorBase(const allocator_type &__a)
            : mImpl(__a)
        {}
        virtual ~VectorBase()
        {}

        void mAllocate(size_type __n)
        {
            return (__n != 0 ? mImpl.allocate(__n) : 0);
        }
        void mDeallocate(typename T_allocator_type::pointer __p, size_type __n)
        {
            if (__p)
                mImpl.deallocate(__p, __n);
        }
    };

    template <typename T, typename _Alloc = std::allocator<T> >
    class vector : public VectorBase<T, _Alloc>
    {
        typedef VectorBase<T, _Alloc>                       _Base;
        typedef typename _Base::T_allocator_type            T_allocator_type;
    public:
        typedef T                                           value_type;
        typedef typename T_allocator_type::pointer          pointer;
        typedef typename T_allocator_type::const_pointer    const_pointer;
        typedef typename T_allocator_type::reference        reference;
        typedef typename T_allocator_type::const_reference  const_reference;
        typedef VectorIterator<T>                  iterator;
        typedef ConstVectorIterator<T>             const_iterator;
        typedef ReverseVectorIterator<T>           reverse_iterator;
        typedef ConstReverseVectorIterator<T>      const_reverse_iterator;
        typedef size_t                                      size_type;
        typedef ptrdiff_t                                   difference_type;
        typedef _Alloc                                      allocator_type;
    protected:
        using _Base::mAllocate;
        using _Base::mDeallocate;
        using _Base::mImpl;
    public:
        explicit vector(const allocator_type &__a = allocator_type()) // default constructor
            : _Base(__a)
        {}
        explicit vector(size_type __n, const value_type &__val = value_type(), const allocator_type &__a = allocator_type()) // fill constructor
            : _Base(__a)
        {
            insert(begin(), __n, __val);
        }
        explicit vector(size_type __n) // size constructor?
            : _Base(allocator_type())
        {
            insert(begin(), __n, value_type());
        }
        template <typename _InputIterator>
        vector(_InputIterator __first, _InputIterator __last, const allocator_type &__a = allocator_type()) // range constructor
            : _Base(__a)
        {
            insert(begin(), __first, __last);
        }
        vector(const vector &__x) // copy constructor
            : _Base(__x.getAllocator())
        {
            insert(begin(), __x.begin(), __x.end());
        }
        vector &operator=(const vector &__x) // assign operator
        {
            this->insert(begin(), __x.begin(), __x.end());
            return (*this);
        }
        void begin()
        {}
        void insert()
        {}
        virtual ~vector()
        {}
    };
}