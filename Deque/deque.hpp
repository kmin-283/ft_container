/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 12:28:58 by kmin              #+#    #+#             */
/*   Updated: 2020/11/26 21:37:03 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "../Iterator/DequeIterator.hpp"
#include <iostream>

namespace ft
{
    template <typename _Tp, typename _Alloc>
    class deque_base
    {
    public:
        typedef _Alloc allocator_type;

        typedef DequeIterator<_Tp, _Tp &, _Tp *> iterator;
        typedef DequeIterator<_Tp, const _Tp &, const _Tp *> const_iterator;
        typedef typename iterator::size_type size_type;
        typedef typename iterator::difference_type difference_type;

        deque_base()
            : mImpl()
        {
            mInitializeMap(0);
        }
        deque_base(const allocator_type &__a, size_type __num_elements)
            : mImpl(__a)
        {
            mInitializeMap(__num_elements);
        }
        deque_base(const allocator_type &__a)
            : mImpl(__a)
        {
        }
        ~deque_base()
        {
        }

    protected:
        typedef typename ft::vector<_Tp> vector_type;
        typedef typename ft::vector<_Tp> *MapPointer;
        typedef typename _Alloc::template rebind<_Tp *>::other MapAllocType;
        typedef typename _Alloc::template rebind<_Tp>::other TpAllocType;
        struct deque_impl
        {
            vector_type v;
            ft::vector<vector_type> mMap;
            size_type mMapSize;
            iterator mStart;
            iterator mFinish;

            deque_impl()
                : mMapSize(0), mStart(), mFinish()
            {
            }
            deque_impl(const TpAllocType &__a)
                : mMapSize(0), mStart(), mFinish()
            {
            }
        };
        enum
        {
            sInitialMapSize = 8
        };

        deque_impl mImpl;

        // TpAllocType &mGetTpAllocator() const
        // {
        //     return (this->mImpl.v.getAllocator());
        // }
        // MapAllocType mGetMapAllocator() const
        // {
        //     return (MapAllocType(mGetTpAllocator()));
        // }
        allocator_type getAllocator() const
        {
            return (this->mImpl.v.getAllocator());
        }
        void mAllocateMap(size_type __n)
        {
            mImpl.mMap.reserve(__n);
        }
        void mInitializeMap(size_type __num_elements)
        {
            const size_type __num_nodes = (__num_elements / DequeBufSize(sizeof(_Tp)) + 1);

            this->mImpl.mMapSize = std::max((size_type)sInitialMapSize, size_type(__num_nodes + 2));
            mAllocateMap(this->mImpl.mMapSize);

            MapPointer __nStart = (&this->mImpl.mMap[0]) + (this->mImpl.mMapSize - __num_nodes) / 2;
            MapPointer __nFinish = __nStart + __num_nodes;

            for (MapPointer i = __nStart; i < __nFinish; ++i)
                i->reserve(DequeBufSize(sizeof(_Tp)));
            this->mImpl.mStart.mSetNode(__nStart);
            this->mImpl.mFinish.mSetNode(__nFinish - 1);
            this->mImpl.mStart.mCur = mImpl.mStart.mFirst;
            this->mImpl.mFinish.mCur = (this->mImpl.mFinish.mFirst + __num_elements % DequeBufSize(sizeof(_Tp)));
        }
    };

    template <typename _Tp, typename _Alloc = std::allocator<_Tp> >
    class deque : public deque_base<_Tp, _Alloc>
    {
        typedef deque_base<_Tp, _Alloc> _Base;
        typedef typename _Base::TpAllocType TpAllocType;

    public:
        typedef _Tp value_type;
        typedef typename TpAllocType::pointer pointer;
        typedef typename TpAllocType::const_pointer const_pointer;
        typedef typename TpAllocType::reference reference;
        typedef typename TpAllocType::const_reference const_reference;
        typedef typename _Base::iterator iterator;
        typedef typename _Base::const_iterator const_iterator;
        // typedef typename _Base::reverse_iterator            reverse_iterator;
        // typedef typename _Base::const_reverse_iterator      const_reverse_iterator;
        typedef typename _Base::size_type size_type;
        typedef typename _Base::difference_type difference_type;
        typedef _Alloc allocator_type;

    protected:
        typedef pointer *Map_pointer;

        static size_type sBufferSize()
        {
            return (DequeBufSize(sizeof(_Tp)));
        }

        using _Base::mImpl;

    public:
        deque()
            : _Base()
        {
        }
        explicit deque(const allocator_type &__a)
            : _Base(__a)
        {
        }
        explicit deque(size_type __n, const value_type &__value = value_type(), const allocator_type &__a = allocator_type())
            : _Base(__a, __n)
        {
            mFillInitialize(__value);
        }
        template <typename _InputIterator>
        deque(_InputIterator __first, _InputIterator __last, const allocator_type &__a = allocator_type())
            : _Base(__a)
        {
            typedef typename my_is_integral<_InputIterator>::true_or_false_type tf_type;
            mInitializeDispatch(__first, __last, tf_type());
        }
        deque(const deque &__x)
            : _Base(__x.mGetTpAllocator(), __x.size())
        {
            std::uninitialized_copy(__x.begin(), __x.end(), this->mImpl.mStart);
        }
        ~deque()
        {
        }
        deque &operator=(const deque &__x)
        {
        }
        void assign(size_type __n, const value_type &__val)
        {
            mFillassign(__n, __val);
        }
        template <typename _InputIterator>
        void assign(_InputIterator __first, _InputIterator __last)
        {
            typedef typename my_is_integral<_InputIterator>::true_or_false_type tf_type;
            mAssignDispatch(__first, __last, tf_type());
        }
        allocator_type getAllocator() const
        {
            return _Base::getAllocator();
        }
        iterator begin()
        {
            return (this->mImpl.mStart);
        }
        const_iterator begin() const
        {
            return (this->mImpl.mStart);
        }
        iterator end()
        {
            return (this->mImpl.mFinish);
        }
        const_iterator end() const
        {
            return (this->mImpl.mFinish);
        }
        // reverse_iterator rbegin()
        // {
        //     return (reverse_iterator(this->mImpl.mFinish));
        // }
        // const_reverse_iterator rbegin() const
        // {
        //     return (reverse_iterator(this->mImpl.mFinish));
        // }
        // reverse_iterator rend()
        // {
        //     return (reverse_iterator(this->mImpl.mStart));
        // }
        // const_reverse_iterator rend() const
        // {
        //     return (reverse_iterator(this->mImpl.mStart));
        // }
        size_type size() const
        {
            return (this->mImpl.mFinish - this->mImpl.mStart);
        }
        size_type max_size() const
        {
            return (this->mImpl.v.max_size());
        }
        void resize(size_type __new_size, value_type __x = value_type())
        {
            const size_type __len = size();
            if (__new_size < __len)
                mEraseAtEnd(this->mImpl.mStart + difference_type(__new_size));
            else
                insert(this->mImpl.mFinish, __new_size - __len, __x);
        }
        bool empty() const
        {
            return (this->mImpl.mFinish == this->mImpl.mStart);
        }
        reference operator[](size_type __n)
        {
            return (this->mImpl.mStart[difference_type(__n)]);
        }

    protected:
        void mRangeCheck(size_type __n) const
        {
            if (__n >= this->size())
                std::__throw_out_of_range("deque::mRangeCheck");
        }

    public:
        reference at(size_type __n)
        {
            mRangeCheck(__n);
            return (*this)[__n];
        }
        const_reference at(size_type __n) const
        {
            mRangeCheck(__n);
            return (*this)[__n];
        }
        reference front()
        {
            return *(begin());
        }
        const_reference front() const
        {
            return *(begin());
        }
        reference back()
        {
            iterator __tmp = end();
            return *(__tmp);
        }
        const_reference back() const
        {
            const_iterator __tmp = end();
            return *(__tmp);
        }
        void push_front(const value_type &__x)
        {
            if (this->mImpl.mStart.mCur != this->mImpl.mStart.mFinish)
            {
                this->mImpl.v.getAllocator().construct(this->mImpl.mStart.mCur - 1, __x);
                --this->mImpl.mStart.mCur;
            }
            else
                mPushFrontAux(__x);
        }
        void push_back(const value_type &__x)
        {
            if (this->mImpl.mFinish.mCur != this->mImpl.mFinish.mLast - 1)
            {
                this->mImpl.v.getAllocator().construct(this->mImpl.mFinish.mCur, __x);
                ++this->mImpl.mFinish.mCur;
            }
            else
                mPushBackAux(__x);
        }
        void pop_front()
        {
            if (this->mImpl.mStart.mCur != this->mImpl.mStart.mLast - 1)
            {
                this->mImpl.v.getAllocator().destroy(this->mImpl.mStart.mCur);
                ++this->mImpl.mStart.mCur;
            }
            else
                mPopFrontAux();
        }
        void pop_back()
        {
            if (this->mImpl.mFinish.mCur != this->mImpl.mFinish.mLast - 1)
            {
                --this->mImpl.mFinish.mCur;
                this->mImpl.v.getAllocator().destroy(this->mImpl.mFinish.mCur);
            }
            else
                mPopBackAux();
        }
        iterator insert(iterator __position, const value_type &__x)
        {
            mFillInsert(__position, 1, __x);
        }
        void insert(iterator __position, size_type __n, const value_type &__x)
        {
            mFillInsert(__position, __n, __x);
        }
        template <class _InputIterator>
        void insert(iterator __position, _InputIterator __first, _InputIterator __last)
        {
            typedef typename my_is_integral<_InputIterator>::true_or_false_type tf_type;
            mInsertDispatch(__position, __first, __last, tf_type());
        }
        iterator erase(iterator __position)
        {
        }
        iterator erase(iterator __first, iterator __last)
        {
        }
        void swap(deque &__x)
        {
            std::swap(this->mImpl.mStart, __x.mImpl.mStart);
            std::swap(this->mImpl.mFinish, __x.mImpl.mFinish);
            std::swap(this->mImpl.mMap, __x.mImpl.mMap);
            std::swap(this->mImpl.mMapSize, __x.mImpl.mMapSize);
            std::__alloc_swap<TpAllocType>::_S_do_it(getAllocator(), __x.getAllocator());
        }
        void clear()
        {
            mEraseAtEnd(begin());
        }

    protected:
        template <typename _Integer>
        void mInitializeDispatch(_Integer __n, _Integer __x, my_true_type)
        {
            mInitializeMap(static_cast<size_type>(__n));
            mFillInitialize(__x);
        }
        template <typename _InputIterator>
        void mInitializeDispatch(_InputIterator __first, _InputIterator __last, my_false_type)
        {
            mRangeInitialize(__first, __last);
        }
        void mRangeInitialize(const_iterator __first, const_iterator __last)
        {
        }
        void mRangeInitialize(pointer __first, const pointer __last)
        {
        }
        void mFillInitialize(const value_type &__x)
        {
        }
        template <typename _Integer>
        void mAssignDispatch(_Integer __n, _Integer __val, my_true_type)
        {
            mFillAssign(__n, __val);
        }

        template <typename _InputIterator>
        void
        mAssignDispatch(_InputIterator __first, _InputIterator __last,
                           my_false_type)
        {
            typedef typename std::iterator_traits<_InputIterator>::
                iterator_category _IterCategory;
            mAssignAux(__first, __last, _IterCategory());
        }
        template <typename _InputIterator>
        void mAssignAux(_InputIterator __first, _InputIterator __last, std::input_iterator_tag);
        template <typename _ForwardIterator>
        void mAssignAux(_ForwardIterator __first, _ForwardIterator __last, std::forward_iterator_tag)
        {
            const size_type __len = std::distance(__first, __last);
            if (__len > size())
            {
                _ForwardIterator __mid = __first;
                std::advance(__mid, size());
                std::copy(__first, __mid, begin());
                insert(end(), __mid, __last);
            }
            else
                mEraseAtEnd(std::copy(__first, __last, begin()));
        }
        void mFillAssign(size_type __n, const value_type &__val)
        {
            if (__n > size())
            {
                std::fill(begin(), end(), __val);
                insert(end(), __n - size(), __val);
            }
            else
            {
                mEraseAtEnd(begin() + difference_type(__n));
                std::fill(begin(), end(), __val);
            }
        }
        void mPushFrontAux(const value_type &__x)
        {}
        void mPushBackAux(const value_type &__x)
        {}
        void mPopBackAux()
        {}
        void mPopFrontAux()
        {}
        template <typename _Integer>
        void
        mInsertDispatch(iterator __pos,
                           _Integer __n, _Integer __x, my_true_type)
        {
            mFillInsert(__pos, __n, __x);
        }

        // called by the range insert to implement [23.1.1]/9
        template <typename _InputIterator>
        void mInsertDispatch(iterator __pos, _InputIterator __first, _InputIterator __last, my_false_type)
        {
            mRangeInsertAux(__pos, __first, __last);
        }

        template <typename _InputIterator>
        void mRangeInsertAux(iterator __pos, _InputIterator __first, _InputIterator __last)
        {}
        
        void
        mFillInsert(iterator __pos, size_type __n, const value_type &__x)
        {}

        void mInsertAux(iterator __pos, size_type __n, const value_type &__x)
        {}
        template <typename _ForwardIterator>
        void mInsertAux(iterator __pos, _ForwardIterator __first, _ForwardIterator __last, size_type __n)
        {}
        void mEraseAtBegin(iterator __pos)
        {
            for (iterator it = begin(); it != __pos;)
                this->getAllocator().destroy(it);
            this->mImpl.mStart = __pos;
        }
        void mEraseAtEnd(iterator __pos)
        {
            iterator mover = __pos;
            for (; mover != this->mImpl.mFinish;)
            {
                this->getAllocator().destroy(mover);
                ++mover;
            }
            this->mImpl.mFinish = __pos;
        }
    };
} // namespace ft