/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 14:33:58 by kmin              #+#    #+#             */
/*   Updated: 2020/11/01 18:02:47 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <memory>
#include "../Iterator/VectorIterator.hpp"
#include <iostream>

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

            VectorImpl()
                : T_allocator_type(), mStart(0), mFinish(0), mEndOfStorage(0)
            {}
            VectorImpl(const T_allocator_type &__a)
                : T_allocator_type(__a), mStart(0), mFinish(0), mEndOfStorage(0)
            {}
        };
    public:
        typedef _Alloc  allocator_type;
#ifdef __APPLE__
        typedef size_t  size_type;
#endif
#ifdef __linux__
        typedef __gnu_cxx::size_t size_type;
#endif
        VectorImpl mImpl;

        allocator_type getAllocator() const
        {
            return (allocator_type(*static_cast<const T_allocator_type *>(&this->mImpl)));
        }
        VectorBase(const allocator_type &__a)
            : mImpl(__a)
        {}
        VectorBase(size_type __n)
            : mImpl()
        {
            this->mImpl.mStart = this->mAllocate(__n);
            this->mImpl.mFinish = this->mImpl.mStart;
            this->mImpl.mEndOfStorage = this->mImpl.mStart + __n;
        }
        VectorBase(size_type __n, const allocator_type &__a)
            : mImpl(__a)
        {
            this->mImpl.mStart = this->mAllocate(__n);
            this->mImpl.mFinish = this->mImpl.mStart;
            this->mImpl.mEndOfStorage = this->mImpl.mStart + __n;
        }
        virtual ~VectorBase()
        {
            mDeallocate(this->mImpl.mStart, this->mImpl.mEndOfStorage - this->mImpl.mStart);
        }

        typename T_allocator_type::pointer mAllocate(size_type __n)
        {
            return (__n != 0 ? this->mImpl.T_allocator_type::allocate(__n) : 0);
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
#ifdef __APPLE__
        typedef size_t                                      size_type;
        typedef ptrdiff_t                                   difference_type;
#endif
#ifdef __linux__
        typedef __gnu_cxx::size_t                           size_type;
        typedef __gnu_cxx::ptrdiff_t                        difference_type;
#endif
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
            : _Base(__n, __a)
        {
            mFillInitialize(__n, __val);
        }
        template <typename _InputIterator>
        vector(_InputIterator __first, _InputIterator __last, const allocator_type &__a = allocator_type()) // range constructor
            : _Base(__a)
        {
            mInitializeDispatch(__first, __last);
        }
        vector(const vector &__x) // copy constructor
            : _Base(__x.size(), __x.getAllocator())
        {
            this->mImpl.mFinish = std::uninitialized_copy(__x.begin(), __x.end(), this->mImpl.mStart);
        }
        vector &operator=(const vector &__x) // assign operator
        {
            this->mImpl.mStart = mAllocate(__x.size());
            this->mImpl.mFinish = std::uninitialized_copy(__x.begin(), __x.end(), this->mImpl.mStart);
            this->mImpl.mEndOfStroage = this->mImpl.mStart + this->size();
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
            return (reverse_iterator(end() - 1));
        }
        const_reverse_iterator rbegin() const
        {
            return (const_reverse_iterator(end() - 1));
        }
        reverse_iterator rend()
        {
            return (reverse_iterator(begin() - 1));
        }
        const_reverse_iterator rend() const
        {
            return (const_reverse_iterator(begin() - 1));
        }
        size_type size() const
        {
            return (size_type(this->mImpl.mFinish - this->mImpl.mStart));
        }
        size_type max_size() const
        {
            return (this->getAllocator().max_size());
        }
        void resize(size_type __new_size, value_type __val = value_type())
        {
            if (__new_size > size())
                insert(end(), __new_size - size(), __val);
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
        void reserve(size_type __n)
        {
            size_type current_size = size();
            
            if (this->capacity() < __n)
            {
                pointer tmp = mAllocateAndCopy(__n, begin(), end());
                mEraseAtEnd(this->mImpl.mStart);
                this->mDeallocate(this->mImpl.mStart, current_size);
                this->mImpl.mStart = tmp;
                this->mImpl.mEndOfStorage = this->mImpl.mStart + __n;
                this->mImpl.mFinish = this->mImpl.mStart + current_size;
            }
        }
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
        // template<typename _InputType>
        // bool is_integral(_InputType &val)
        // {
        //     if (typeid(_InputType) == typeid(bool) ||
        //     typeid(_InputType) == typeid(char) ||
        //     typeid(_InputType) == typeid(wchar_t) ||
        //     typeid(_InputType) == typeid(signed char) ||
        //     typeid(_InputType) == typeid(short int) ||
        //     typeid(_InputType) == typeid(int) ||
        //     typeid(_InputType) == typeid(long int) ||
        //     typeid(_InputType) == typeid(long long int) ||
        //     typeid(_InputType) == typeid(unsigned char) ||
        //     typeid(_InputType) == typeid(unsigned short int) ||
        //     typeid(_InputType) == typeid(unsigned int) ||
        //     typeid(_InputType) == typeid(unsigned long int) ||
        //     typeid(_InputType) == typeid(unsigned long long int))
        //         return (true);
        //     else
        //         return (false);
        // }
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
            mAssignDispatch(__first, __last);
        }
        void push_back(const value_type &__x)
        {
            if (this->mImpl.mFinish != this->mImpl.mEndOfStorage)
            {
                this->getAllocator().construct(this->mImpl.mFinish, __x); // 할당을 하지 않고, 값만 채움
                ++this->mImpl.mFinish; // 결국 *this->mImpl.mFinish = __x과 같은 것임.
            }
            else
                mInsertAux(end(), __x); // 새롭게 메모리를 할당해서 값을 채움
        }
        void pop_back()
        {
            --this->mImpl.mFinish;
            this->getAllocator().destroy(this->mImpl.mFinish);
        }
        iterator insert(iterator __position, const value_type &__x)
        {
            difference_type distance = __position.distance(begin());

            mFillInsert(__position, 1, __x);
            return (begin() + distance);
        }
        void insert(iterator __position, size_type __n, const value_type &__val)
        {
            mFillInsert(__position, __n, __val);
        }
        template <typename _InputIteraor>
        void insert(iterator __position, _InputIteraor __first, _InputIteraor __last)
        {
            mInsertDispatch(__position, __first, __last);
        }
        iterator erase(iterator __position)
        {
            difference_type __n = __position.distance(begin());
            pointer initial_pos = this->mImpl.mStart + __n;
            
            for (;initial_pos != this->mImpl.mFinish - 1; ++initial_pos)
                *initial_pos = *(initial_pos + 1);
            --this->mImpl.mFinish;
            return (__position);
        }
        iterator erase(iterator __first, iterator __last)
        {
            difference_type __n = __first.distance(begin());
            pointer initial_pos = this->mImpl.mStart + __n;
            iterator ret = __first;

            for (iterator finish_pos = __last; finish_pos != end(); ++finish_pos)
            {
                *initial_pos = *finish_pos;
                ++initial_pos;
            }
            for (; __first != __last; ++__first)
                --this->mImpl.mFinish;
            return (ret);
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
        void mInitializeDispatch(size_type __n, value_type __value)
        {
            this->mImpl.mStart = mAllocate(__n);
            this->mImpl.mEndOfStorage = this->mImpl.mStart + __n;
            mFillInitialize(__n, __value);
        }
        void mInitializeDispatch(const pointer __first, const pointer __last)
        {
            mRangeInitialize(__first, __last);
        }
        void mInitializeDispatch(const iterator __first, const iterator __last)
        {
            mRangeInitialize(__first, __last);
        }
        void mRangeInitialize(iterator __first, const iterator __last)
        {
            for(; __first != __last; ++__first)
                push_back(*__first);
        }
        void mRangeInitialize(const pointer __first, const pointer __last)
        {
            const size_type __n = std::distance(__first, __last);
            this->mImpl.mStart = this->mAllocate(__n);
            this->mImpl.mEndOfStorage = this->mImpl.mStart + __n;
            this->mImpl.mFinish = std::uninitialized_copy(__first, __last, this->mImpl.mStart);
        }
        void mFillInitialize(size_type __n, const value_type &__value)
        {
            std::uninitialized_fill_n(this->mImpl.mStart, __n, __value);
            this->mImpl.mFinish = this->mImpl.mEndOfStorage;
        }
        void mDefaultInitialize(size_type __n)
        {
            try
            {
                this->mAllocate(__n);
            }
            catch (std::exception &e)
            {
                this->mDeallocate(this->mImpl.mStart, __n);
                throw;
            }
            this->mImpl.mFinish = this->mImpl.mEndOfStorage;
        }
        void mFillAssign(size_type __n, const value_type &__val)
        {
            std::uninitialized_fill_n(this->mImpl.mStart, __n, __val);
            this->mImpl.mFinish = this->mImpl.mStart + __n;
        }
        void mAssignDispatch(size_type __n, value_type __val)
        {
            if (this->capacity() > __n)
                mFillAssign(__n, __val);
            else
            {
                for (size_type i = 0; i != __n; ++i)
                    push_back(__val);
            }
        }
        void mAssignDispatch(const iterator __first, const iterator __last)
        {
            mAssignAux(__first, __last);
        }
        void mAssignDispatch(const pointer __first, const pointer __last)
        {
            mAssignAux(__first, __last);
        }
        template <typename _InputIterator>
        void mAssignAux(_InputIterator __first, _InputIterator __last)
        {
            difference_type __n = __last - __first;

            if (this->capacity() > __n)
                mRangeInsert(begin(), __first, __last);
            else
            {
                for (; __first != __last;)
                {
                    push_back(*__first);
                    ++__first;
                }
            }
        }
        void mInsertDispatch(iterator __pos, size_type __n, value_type __val)
        {
            mFillInsert(__pos, __n, __val);
        }
        void mInsertDispatch(iterator __pos, const iterator __first, const iterator __last)
        {
            mRangeInsert(__pos, __first, __last);
        }
        void mInsertDispatch(iterator __pos, const pointer __first, const pointer __last)
        {
            mRangeInsert(__pos, __first, __last);
        }
        template <typename _InputIterator>
        void mRangeInsert(iterator __pos, _InputIterator __first, _InputIterator __last)
        {
            for(; __first != __last;)
            {
                __pos = this->insert(__pos, *__first);
                ++__first;
                ++__pos;
            }
        }
        void mFillInsert(iterator __pos, size_type __n, const value_type &__x)
        {
            pointer element;
            pointer startPoint;
            difference_type disToBegin = __pos.distance(begin()); // distance from __pos to begin()
            difference_type disToEnd = __pos.distance(end()) - 1; // distance from __pos to end()

            for (size_type i = 0; i < __n; ++i)
                push_back(__x); //push back에서 주소가 바뀔 수 있기 때문에 __pos를 그대로 사용할 수 없다.
            element = this->mImpl.mFinish;
            startPoint = this->mImpl.mStart + disToBegin;
            --startPoint;
            --element;
            for (size_type i = 0; startPoint != this->mImpl.mStart + disToBegin + disToEnd; --element)
            {
                *element = *(this->mImpl.mStart + disToBegin + disToEnd - i);
                ++startPoint;
                ++i;
            }
            element = this->mImpl.mStart + disToBegin;
            for (size_type i = 0; i < __n; ++i)
            {
                *element =  __x;
                ++element;
            }
        }
        void mDefaultAppend(size_type __n)
        {}
        void mInsertAux(iterator __position, const value_type &__x)
        {
            size_type default_capacity = this->size();
            size_type capacity = default_capacity == 0 ? 1 : default_capacity * 2;
            pointer tmp = mAllocateAndCopy(capacity, this->begin(), this->end());
            this->getAllocator().construct(tmp + default_capacity, __x);
            mEraseAtEnd(this->mImpl.mStart);
            this->mDeallocate(this->mImpl.mStart, default_capacity);
            this->mImpl.mStart = tmp;
            this->mImpl.mFinish = this->mImpl.mStart + default_capacity + 1;
            this->mImpl.mEndOfStorage = this->mImpl.mStart + capacity;
        }
        size_type mCheckLen(size_type __n, const char *__s) const
        {
            if (max_size() - size() < __n)
                std::__throw_length_error(__s);
            const size_type __len = size() + std::max(size(), __n);
            return (__len < size() || __len > max_size()) ? max_size() : __len;
        }
        void mEraseAtEnd(pointer __pos)
        {
            pointer mover = __pos;
            for (; mover != this->mImpl.mFinish;)
            {
                this->getAllocator().destroy(mover);
                ++mover;
            }
            this->mImpl.mFinish = __pos;
        }
    };
    template <typename _Tp, typename _Alloc>
    inline bool operator<(const vector<_Tp, _Alloc> &__x, const vector<_Tp, _Alloc> &__y)
    {
        return (std::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end()));
    }
    template <typename _Tp, typename _Alloc>
    inline bool operator!=(const vector<_Tp, _Alloc> &__x, const vector<_Tp, _Alloc> &__y)
    {
        return (!(__x == __y));
    }
    template <typename _Tp, typename _Alloc>
    inline bool operator<=(const vector<_Tp, _Alloc> &__x, const vector<_Tp, _Alloc> &__y)
    {
        return (!(__x <= __y));
    }
    template <typename _Tp, typename _Alloc>
    inline bool operator>(const vector<_Tp, _Alloc> &__x, const vector<_Tp, _Alloc> &__y)
    {
        return (!(__x > __y));
    }
    template <typename _Tp, typename _Alloc>
    inline bool operator>=(const vector<_Tp, _Alloc> &__x, const vector<_Tp, _Alloc> &__y)
    {
        return (!(__x >= __y));
    }
    template <typename _Tp, typename _Alloc>
    inline void swap(const vector<_Tp, _Alloc> &__x, const vector<_Tp, _Alloc> &__y)
    {
        __x.swap(__y);
    }
}
