/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 12:28:58 by kmin              #+#    #+#             */
/*   Updated: 2020/11/25 20:32:55 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "../Iterator/DequeIterator.hpp"

namespace ft
{
    template <typename _Tp, typename _Alloc>
    class deque_base
    {
    public:
        typedef _Alloc                      allocator_type;
        allocator_type getAllocator() const
        {
            return (allocator_type(mGetTpAllocator()));
        }

        typedef DequeIterator<_Tp, _Tp &, _Tp *>                iterator;
        typedef DequeIterator<_Tp, const _Tp &, const _Tp *>    const_iterator;
        typedef typename iterator::size_type                             size_type;
        typedef typename iterator::difference_type                  difference_type;

        deque_base()
            : mImpl()
        {
            mInitialize_map(0);
        }
        deque_base(const allocator_type& __a, size_type __num_elements)
            : mImpl(__a)
        {
            mInitialize_map(__num_elements);
        }
        deque_base(const allocator_type& __a)
            : mImpl(__a)
        {}
        ~deque_base()
        {}
    protected:
        typedef typename ft::vector<_Tp>                                vector_type;
        typedef typename ft::vector<_Tp>*                               MapPointer;
        typedef typename _Alloc::template rebind<_Tp *>::other          MapAllocType;
        typedef typename _Alloc::template rebind<_Tp>::other            TpAllocType;
        struct deque_impl
        {
            vector_type v;
            ft::vector<vector_type> mMap;
            size_type mMapSize;
            iterator mStart;
            iterator mFinish;

            deque_impl()
                : mMapSize(0), mStart(), mFinish()
            {}
            deque_impl(const TpAllocType &__a)
                : mMapSize(0), mStart(), mFinish()
            {}
        };
        enum {sInitialMapSize = 8};

        deque_impl mImpl;

        TpAllocType &mGetTpAllocator()
        {
            return (this->mImpl.v.getAllocator());
        }
        MapAllocType mGetMapAllocator() const
        {
            return (MapAllocType(mGetTpAllocator()));
        }
        void mAllocateMap(size_type __n)
        {
            mImpl.mMap.reserve(__n);
        }
        void mInitialize_map(size_type __num_elements)
        {
            const size_type __num_nodes = (__num_elements / DequeBufSize(sizeof(_Tp)) + 1);
            
            this->mImpl.mMapSize = std::max((size_type)sInitialMapSize, size_type(__num_nodes + 2));
            mAllocateMap(this->mImpl.mMapSize);

            MapPointer __nStart = (&this->mImpl.mMap[0]) + (this->mImpl.mMapSize - __num_nodes) / 2;
            MapPointer __nFinish = __nStart + __num_nodes;

            for (MapPointer i =__nStart; i < __nFinish; i++)
                i->reserve(DequeBufSize(sizeof(_Tp)));
            this->mImpl.mStart.mSetNode(__nStart);
            this->mImpl.mFinish.mSetNode(__nFinish);
            this->mImpl.mStart.mCur = mImpl.mStart.mFirst;
            this->mImpl.mFinish.mCur = (this->mImpl.mFinish.mFirst + __num_elements % DequeBufSize(sizeof(_Tp)));
        }
    };


    template <typename _Tp, typename _Alloc = std::allocator<_Tp> >
    class deque : public deque_base<_Tp, _Alloc>
    {
        typedef deque_base<_Tp, _Alloc>           _Base;
        typedef typename _Base::TpAllocType     TpAllocType;
    public:
        typedef _Tp                                         value_type;
        typedef typename TpAllocType::pointer            pointer;
        typedef typename TpAllocType::const_pointer      const_pointer;
        typedef typename TpAllocType::reference          reference;
        typedef typename TpAllocType::const_reference    const_reference;
        typedef typename _Base::iterator                     iterator;
        typedef typename _Base::const_iterator              const_iterator;
        // typedef typename _Base::reverse_iterator            reverse_iterator;
        // typedef typename _Base::const_reverse_iterator      const_reverse_iterator;
        typedef typename _Base::size_type                   size_type;
        typedef typename _Base::difference_type             difference_type;
        typedef _Alloc                                      allocator_type;
    protected:
        typedef pointer*                                    Map_pointer;

        static size_type sBufferSize()
        {
            return (DequeBufSize(sizeof(_Tp)));
        }
        
        using _Base::mImpl;

    public:
        deque()
            : _Base()
        {}
        explicit deque(const allocator_type &__a)
            : _Base(__a)
        {}
        explicit deque(size_type __n, const value_type &__value = value_type(), const allocator_type &__a = allocator_type())
            : _Base(__a, __n)
        {
            mFillInitialize(__value);
        }
        template <typename _InputIterator>
        deque (_InputIterator __first, _InputIterator __last, const allocator_type &__a = allocator_type())
            : _Base(__a)
        {}
        deque (const deque &__x)
            : _Base(__x.mGetTpAllocator(), __x.size())
        {
            std::uninitialized_copy(__x.begin(), __x.end(), this->mImpl.mStart);
        }
        ~deque()
        {
        }
    };
} // namespace ft