/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 14:33:58 by kmin              #+#    #+#             */
/*   Updated: 2020/10/19 16:33:33 by kmin             ###   ########.fr       */
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
            typedef typename T_allocator_type::pointer mStart;
            typedef typename T_allocator_type::pointer mFinish;
            typedef typename T_allocator_type::pointer mEndOfStorage;

            VectorImpl(const T_allocator_type &__a)
                : T_allocator_type(__a), mStart(NULL), mFinish(NULL), mEndOfStorage(NULL)
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
        typedef typename VectorBase<T, _Alloc>              _Base;
    public:
        typedef T                                           value_type;
        typedef typename T_allocator_type::pointer          pointer;
        typedef typename T_allocator_type::const_pointer    const_pointer;
        typedef typename T_allocator_type::reference        reference;
        typedef typename T_allocator_type::const_reference  const_reference;
        typedef typename VectorIterator<T>                  iterator;
        typedef typename ConstVectorIterator<T>             const_iterator;
        typedef typename ReverseVectorIterator<T>           reverse_iterator;
        typedef typename ConstReverseVectorIterator<T>      const_reverse_iterator;
        typedef typename _Base::T_allocator_type            T_allocator_type;
        typedef ptrdiff_t                                   difference_type;
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
        {}
        template <typename _InputIterator>
        vector(_InputIterator __first, _InputIterator __last, const allocator_type = allocator_type()) // range constructor
            : _Base(__a)
        {}
        vector(const vector &__x) // copy constructor
        {}
    };
}