/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 14:33:58 by kmin              #+#    #+#             */
/*   Updated: 2020/10/26 13:22:13 by kmin             ###   ########.fr       */
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
            return (allocator_type(*static_cast<const T_allocator_type *>(&this->mImpl)));
        }

        VectorBase(const allocator_type &__a)
            : mImpl(__a)
        {}
        virtual ~VectorBase()
        {
            mDeallocate(this->mImpl.mStart, this->mImpl.mEndOfStorage - this->mImpl.mStart);
        }

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
        virtual ~vector()
        {
            pointer start = this->mImpl.mStart;
            pointer finish = this->mImpl.mFinish;
            for (; start != finish;)
            {
                this->getAllocator().destroy(start);
                ++start;
            }
        }
        iterator begin()
        {
            return (iterator(this->mImpl.mStart));
        }
        const_iterator begin() const
        {
            return (const_iterator(this->mImpl.mStart));
        }
        iterator end()
        {
            return (iterator(this->mImpl.mFinish));
        }
        const_iterator end() const
        {
            return (const_iterator(this->mImpl.mFinish));
        }
        reverse_iterator rbegin()
        {
            return (reverse_iterator(end()));
        }
        const_reverse_iterator rbegin() const
        {
            return (const_reverse_iterator(end()));
        }
        reverse_iterator rend()
        {
            return (reverse_iterator(begin()));
        }
        const_reverse_iterator rend() const
        {
            return (const_reverse_iterator(begin()));
        }
        size_type size() const
        {
            return (size_type(this->mImpl.mFinish - this->mImpl.mStart));
        }
        size_type max_size() const
        {
            return (this->getAllocator().max_size());
        }
        void resize(size_type __new_size)
        {
            if (__new_size > size())
                mDefaultAppend(__new_size - size());
            else if (__new_size < size())
                mEraseAtEnd(this->mImpl.mStart + __new_size);
        }
        size_type capacity() const
        {
            return (size_type(this->mImpl.mEndOfStorage - this->mImpl.mStart));
        }
        bool empty() const
        {
            return (begin() == end());
        }
        void reverse()
        {}
        reference operator[](size_type __n)
        {
            return (*(this->mImpl.mStart + __n));
        }
        const_reference operator[](size_type __n) const
        {
            return (*(this->mImpl.mStart + __n));
        }
    protected:
        void mRangeCheck(size_type __n)
        {
            if (__n >= this->size())
                std::__throw_out_of_range("vector::mRangeCheck");
        }
    public:
        reference at(size_type __n)
        {
            mRangeCheck(__n);
            return (*this)[__n];
        }
        reference front()
        {
            return (*begin());
        }
        const_reference front() const
        {
            return (*begin());
        }
        reference back()
        {
            return (*(end() - 1));
        }
        const_reference back() const
        {
            return (*(end() - 1));
        }
        void assign(size_type __n, const value_type &__val)
        {
            mFillAssign(__n, __val);
        }
        template <typename _InputIterator>
        void assign(_InputIterator __first, _InputIterator __last)
        {
            (void)__first;
            (void)__last;
        }
        void push_back(const value_type &__x)
        {
            if (this->mImpl.mFinish != this->mImpl.endOfStorage)
            {
                this->mImpl.getAllocator().construct(this->mImpl.mFinish, __x); // 할당을 하지 않고, 값만 채움
                ++this->mImpl.mFinish; // 결국 *this->mImpl.mFinish = __x과 같은 것임.
            }
            else
                mInsertAux(end(), __x); // 새롭게 메모리를 할당해서 값을 채움
        }
        void pop_back()
        {
            --this->mImpl.mFinish;
            this->mImpl.getAllocator().destoy(this->mImpl.mFinish);
        }
        iterator insert(iterator __position, const value_type &__x)
        {
            (void)__position;
            (void)__x;
        }
        void insert(iterator __position, size_type __n, const value_type &__val)
        {
            mFillInsert(__position, __n, __val);
        }
        template <typename _InputIterator>
        void insert(iterator __position, _InputIterator __first, _InputIterator __last)
        {
            (void)__position;
            (void)__first;
            (void)__last;
        }
        iterator erase(iterator __position)
        {
            
        }
        iterator erase(iterator __first, iterator __last)
        {
            
        }
        void swap(vector &__x)
        {
            std::swap(this->mImpl.mStart, __x.mImpl.mStart);
            std::swap(this->mImpl.mFinish, __x.mImpl.mFinish);
            std::swap(this->mImpl.mEndOfStorage, __x.mImpl.mEndOfStorage);
            // alloc_swap??
        }
        void clear()
        {
            mEraseAtEnd(this->mImpl.mStart);
        }
    protected:
        template <typename _ForwardIterator>
        pointer mAllocateAndCopy(size_type __n, _ForwardIterator __first, _ForwardIterator __last)
        {
            pointer __result = this->mAllocate(__n);
            try
            {
                std::uninitialized_copy(__first, __last, __result);
                return (__result);
            }
            catch(const std::exception& e)
            {
                mDeallocate(__result, __n);
                throw;
            }
        }
    };
}