/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:02:26 by kmin              #+#    #+#             */
/*   Updated: 2020/11/27 23:57:25 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "../Iterator/MapIterator.hpp"
#include <exception>
#include <functional>
#include <algorithm>

namespace ft
{
    template <typename _Pair>
    struct _Select1st : public std::unary_function<_Pair, typename _Pair::first_type>
    {
        typename _Pair::first_type &operator()(_Pair &__x) const
        {
            return (__x.first);
        }
        const typename _Pair::first_type &operator()(const _Pair &__x) const
        {
            return (__x.first);
        }
    };

    template<typename _Pair>
    struct _Identity : public std::unary_function<_Pair, _Pair>
    {
      _Pair&
      operator()(_Pair& __x) const
      { return __x; }

      const _Pair&
      operator()(const _Pair& __x) const
      { return __x; }
    };

    template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc = std::allocator<_Val> >
    class red_black_tree
    {
        typedef typename _Alloc::template rebind<rb_tree_node<_Val> >::other _Node_allocator;

    protected:
        typedef rb_tree_node_base *_Base_ptr;
        typedef const rb_tree_node_base *_Const_Base_ptr;

    public:
        typedef _Key key_type;
        typedef _Val value_type;
        typedef value_type *pointer;
        typedef const value_type *const_pointer;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef rb_tree_node<_Val> *_Link_type;
        typedef const rb_tree_node<_Val> *_Const_Link_type;
        typedef _Alloc allocator_type;

        typedef MapIterator<value_type> iterator;
        typedef ConstMapIterator<value_type> const_iterator;
        typedef ReverseMapIterator<value_type> reverse_iterator;
        typedef ConstReverseMapIterator<value_type> const_reverse_iterator;
#ifdef __APPLE__
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
#endif
#ifdef __linux__
        typedef __gnu_cxx::size_t size_type;
        typedef __gnu_cxx::ptrdiff_t difference_type;
#endif
        _Node_allocator &mGetNode_Allocator()
        {
            return *(static_cast<_Node_allocator *>(&this->mImpl));
        }
        const _Node_allocator &mGetNode_Allocator() const
        {
            return *(static_cast<const _Node_allocator *>(&this->mImpl));
        }
        allocator_type getAlloctor() const
        {
            return (allocator_type(mGetNode_Allocator()));
        }

    protected:
        _Link_type mGetNode()
        {
            return (mImpl._Node_allocator::allocate(1));
        }
        void mPutNode(_Link_type __p)
        {
            return (mImpl._Node_allocator::deallocate(__p, 1));
        }
        _Link_type mCreateNode(const value_type &__x)
        {
            _Link_type __tmp = mGetNode();

            try
            {
                getAlloctor().construct(&__tmp->mValueField, __x);
            }
            catch (const std::exception &e)
            {
                mPutNode(__tmp);
                throw;
            }
            return (__tmp);
        }
        void mDestroyNode(_Link_type __p)
        {
            getAlloctor().destroy(&__p->mValueField);
            mPutNode(__p);
        }
        _Link_type mCloneNode(_Const_Link_type __x)
        {
            _Link_type __tmp = mCreateNode(__x->mValueField);
            __tmp->mColor = __x->mColor;
            __tmp->mLeft = 0;
            __tmp->mRight = 0;
            return (__tmp);
        }

    protected:
        template <typename _Key_compare>
        struct rb_tree_impl : public _Node_allocator
        {
            _Key_compare mKeyCompare;
            rb_tree_node_base mHeader;
            size_type mNodeCount;

            rb_tree_impl()
                : _Node_allocator(), mKeyCompare(), mHeader(), mNodeCount(0)
            {
                mInitialize();
            }
            rb_tree_impl(const _Key_compare &__comp, const _Node_allocator &__a)
                : _Node_allocator(__a), mKeyCompare(__comp), mHeader(), mNodeCount(0)
            {
                mInitialize();
            }

        private:
            void mInitialize()
            {
                this->mHeader.mColor = RED;
                this->mHeader.mParent = 0;
                this->mHeader.mLeft = &this->mHeader;
                this->mHeader.mRight = &this->mHeader;
            }
        };

        rb_tree_impl<_Compare> mImpl;

    protected:
        _Base_ptr &mRoot()
        {
            return (this->mImpl.mHeader.mParent);
        }
        _Const_Base_ptr mRoot() const
        {
            return (this->mImpl.mHeader.mParent);
        }
        _Base_ptr &mLeftMost()
        {
            return (this->mImpl.mHeader.mLeft);
        }
        _Const_Base_ptr mLeftMost() const
        {
            return (this->mImpl.mHeader.mLeft);
        }
        _Base_ptr &mRightMost()
        {
            return (this->mImpl.mHeader.mRight);
        }
        _Const_Base_ptr mRightMost() const
        {
            return (this->mImpl.mHeader.mRight);
        }
        _Link_type mBegin()
        {
            return (static_cast<_Link_type>(this->mImpl.mHeader.mParent));
        }
        _Const_Link_type mBegin() const
        {
            return (static_cast<_Const_Link_type>(this->mImpl.mHeader.mParent));
        }
        _Link_type mEnd()
        {
            return (static_cast<_Link_type>(&this->mImpl.mHeader));
        }
        _Const_Link_type mEnd() const
        {
            return (static_cast<_Const_Link_type>(&this->mImpl.mHeader));
        }
        static const_reference sValue(_Const_Link_type __x)
        {
            return (__x->mValueField);
        }
        static const _Key &sKey(_Const_Link_type __x)
        {
            return (_KeyOfValue()(sValue(__x)));
        }
        static _Link_type sLeft(_Base_ptr __x)
        {
            return (static_cast<_Link_type>(__x->mLeft));
        }
        static _Const_Link_type sLeft(_Const_Base_ptr __x)
        {
            return (static_cast<_Const_Link_type>(__x->mLeft));
        }
        static _Link_type sRight(_Base_ptr __x)
        {
            return (static_cast<_Link_type>(__x->mRight));
        }
        static _Const_Link_type sRight(_Const_Base_ptr __x)
        {
            return (static_cast<_Const_Link_type>(__x->mRight));
        }
        static const_reference sValue(_Const_Base_ptr __x)
        {
            return (static_cast<_Const_Link_type>(__x)->mValueField);
        }
        static const _Key &sKey(_Const_Base_ptr __x)
        {
            return (_KeyOfValue()(sValue(__x)));
        }
        static _Base_ptr sMinimum(_Base_ptr __x)
        {
            return (rb_tree_node_base::S_minimum(__x));
        }
        static _Const_Base_ptr sMinimum(_Const_Base_ptr __x)
        {
            return (rb_tree_node_base::S_minimum(__x));
        }
        static _Base_ptr sMaximum(_Base_ptr __x)
        {
            return (rb_tree_node_base::S_maximum(__x));
        }
        static _Const_Base_ptr sMaximum(_Const_Base_ptr __x)
        {
            return (rb_tree_node_base::S_maximum(__x));
        }

    private:
        iterator mInsert(_Const_Base_ptr __x, _Const_Base_ptr __p, const value_type &__v)
        {
            bool __insert_left = (__x != 0 || __p == mEnd() || mImpl.mKeyCompare(_KeyOfValue()(__v), sKey(__p)));

            _Link_type __z = mCreateNode(__v);

            rb_tree_insert_and_rebalance(__insert_left, __z, const_cast<_Base_ptr>(__p), this->mImpl.mHeader);
            ++mImpl.mNodeCount;
            return (iterator(__z));
        }
        iterator mInsertLower(_Base_ptr __x, _Base_ptr __p, const value_type &__v)
        {
            bool __insert_left = (__x != 0 || __p == mEnd() || mImpl.mKeyCompare(sKey(__p), _KeyOfValue()(__v)));

            _Link_type __z = mCreateNode(__v);

            rb_tree_insert_and_rebalance(__insert_left, __z, __p, this->mImpl.mHeader);
            ++mImpl.mNodeCount;
            return (iterator(__z));
        }
        iterator mInsertEqualLower(const value_type &__v)
        {
            _Link_type __x = mBegin();
            _Link_type __y = mEnd();

            while (__x != 0)
            {
                __y = __x;
                __x = !mImpl.mKeyCompare(sKey(__x), _KeyOfValue()(__v)) ? sLeft(__x) : sRight(__x);
            }
            return (mInsertLower(__x, __y, __v));
        }
        _Link_type mCopy(_Const_Link_type __x, _Link_type __p)
        {
            _Link_type __top = mCloneNode(__x);
            __top->mParent = __p;

            try
            {
                if (__x->mRight)
                    __top->mRight = mCopy(sRight(__x), __top);
                __p = __top;
                __x = sLeft(__x);

                while (__x != 0)
                {
                    _Link_type __y = mCloneNode(__x);
                    __p->mLeft = __y;
                    __y->mParent = __p;
                    if (__x->mRight)
                        __y->mRight = mCopy(sRight(__x), __y);
                    __p = __y;
                    __x = sLeft(__x);
                }
            }
            catch (const std::exception &e)
            {
                mErase(__top);
                throw;
            }
            return (__top);
        }
        void mErase(_Link_type __x)
        {
            while (__x != 0)
            {
                mErase(sRight(__x));
                _Link_type __y = sLeft(__x);
                mDestroyNode(__x);
                __x = __y;
            }
        }
        iterator mLowerBound(_Link_type __x, _Link_type __y, const _Key &__k)
        {
            while (__x != 0)
            {
                if (!mImpl.mKeyCompare(sKey(__x), __k))
                {
                    __y = __x;
                    __x = sLeft(__x);
                }
                else
                    __x = sRight(__x);
            }
            return (iterator(__y));
        }
        const_iterator mLowerBound(_Const_Link_type __x, _Const_Link_type __y, const _Key &__k) const
        {
            while (__x != 0)
            {
                if (!mImpl.mKeyCompare(sKey(__x), __k))
                {
                    __y = __x;
                    __x = sLeft(__x);
                }
                else
                    __x = sRight(__x);
            }
            return (const_iterator(__y));
        }
        iterator mUpperBound(_Link_type __x, _Link_type __y, const _Key &__k)
        {
            while (__x != 0)
            {
                if (mImpl.mKeyCompare(__k, sKey(__x)))
                {
                    __y = __x;
                    __x = sLeft(__x);
                }
                else
                    __x = sRight(__x);
            }
            return (iterator(__y));
        }
        const_iterator mUpperBound(_Const_Link_type __x, _Const_Link_type __y, const _Key &__k) const
        {
            while (__x != 0)
            {
                if (mImpl.mKeyCompare(__k, sKey(__x)))
                {
                    __y = __x;
                    __x = sLeft(__x);
                }
                else
                    __x = sRight(__x);
            }
            return (const_iterator(__y));
        }

    public:
        red_black_tree()
        {
        }
        red_black_tree(const _Compare &__comp, const allocator_type &__a = allocator_type())
            : mImpl(__comp, __a)
        {
        }
        red_black_tree(const red_black_tree &__x)
            : mImpl(__x.mImpl.mKeyCompare, __x.mGetNode_Allocator())
        {
            if (__x.mRoot() != 0)
            {
                mRoot() = mCopy(__x.mBegin(), mEnd());
                mLeftMost() = sMinimum(mRoot());
                mRightMost() = sMaximum(mRoot());
                mImpl.mNodeCount = __x.mImpl.mNodeCount;
            }
        }
        red_black_tree &operator=(const red_black_tree &__x)
        {
            if (this != &__x)
            {
                clear();
                mImpl.mKeyCompare = __x.mImpl.mKeyCompare;
                if (__x.mRoot() != 0)
                {
                    mRoot() = mCopy(__x.mBegin(), mEnd());
                    mLeftMost() = sMinimum(mRoot());
                    mRightMost() = sMaximum(mRoot());
                    mImpl.mNodeCount = __x.mImpl.mNodeCount;
                }
            }
            return (*this);
        }
        ~red_black_tree()
        {
            mErase(mBegin());
        }
        _Compare key_comp() const
        {
            return (mImpl.mKeyCompare);
        }
        iterator begin()
        {
            return (iterator(static_cast<_Link_type>(this->mImpl.mHeader.mLeft)));
        }
        const_iterator begin() const
        {
            return (const_iterator(static_cast<_Const_Link_type>(this->mImpl.mHeader.mLeft)));
        }
        iterator end()
        {
            return (iterator(static_cast<_Link_type>(&this->mImpl.mHeader)));
        }
        const_iterator end() const
        {
            return (const_iterator(static_cast<_Const_Link_type>(&this->mImpl.mHeader)));
        }
        reverse_iterator rbegin()
        {
            iterator it = end();

            if (it == begin())
                return (reverse_iterator(it));
            return (reverse_iterator(--it));
        }
        const_reverse_iterator rbegin() const
        {
            iterator it = end();

            if (it == begin())
                return (const_reverse_iterator(it));
            return (const_reverse_iterator(--it));
        }
        reverse_iterator rend()
        {
            iterator it = begin();

            if (end() == it)
                return (reverse_iterator(it));
            return (reverse_iterator(--it));
        }
        const_reverse_iterator rend() const
        {
            iterator it = begin();

            if (end() == it)
                return (const_reverse_iterator(it));
            return (const_reverse_iterator(--it));
        }
        bool empty() const
        {
            return (mImpl.mNodeCount == 0);
        }
        size_type size() const
        {
            return (mImpl.mNodeCount);
        }
        size_type max_size() const
        {
            return (mGetNode_Allocator().max_size());
        }
        void swap(red_black_tree &__t)
        {
            if (mRoot() == 0)
            {
                if (__t.mRoot() == 0)
                {
                    mRoot() = __t.mRoot();
                    mLeftMost() = __t.mLeftMost();
                    mRightMost() = __t.mRightMost();
                    mRoot()->mParent = mEnd();

                    __t.mRoot() = 0;
                    __t.mLeftMost() = __t.mEnd();
                    __t.mRightMost() = __t.mEnd();
                }
            }
            else if (__t.mRoot() == 0)
            {
                __t.mRoot() = mRoot();
                __t.mLeftMost() = mLeftMost();
                __t.mRightMost() = mRightMost();
                __t.mRoot()->mParent = __t.mEnd();

                mRoot() = 0;
                mLeftMost() = mEnd();
                mRightMost() = mEnd();
            }
            else
            {
                std::swap(mRoot(), __t.mRoot());
                std::swap(mLeftMost(), __t.mLeftMost());
                std::swap(mRightMost(), __t.mRightMost());

                mRoot()->mParent = mEnd();
                __t.mRoot()->mParent = __t.mEnd();
            }
            std::swap(this->mImpl.mNodeCount, __t.mImpl.mNodeCount);
            std::swap(this->mImpl.mKeyCompare, __t.mImpl.mKeyCompare);
        }
        std::pair<iterator, bool> mInsertUnique(const value_type &__v)
        {
            _Link_type __x = mBegin();
            _Link_type __y = mEnd();
            bool __comp = true;

            while (__x != 0)
            {
                __y = __x;
                __comp = mImpl.mKeyCompare(_KeyOfValue()(__v), sKey(__x));
                __x = __comp ? sLeft(__x) : sRight(__x);
            }

            iterator __j = iterator(__y);

            if (__comp)
            {
                if (__j == begin())
                    return (std::pair<iterator, bool>(mInsert(__x, __y, __v), true));
                else
                    --__j;
            }
            if (mImpl.mKeyCompare(sKey(__j.mNode), _KeyOfValue()(__v)))
                return (std::pair<iterator, bool>(mInsert(__x, __y, __v), true));
            return (std::pair<iterator, bool>(__j, false));
        }
        iterator mInsertEqual(const value_type &__v)
        {
            _Link_type __x = mBegin();
            _Link_type __y = mEnd();

            while (__x != 0)
            {
                __y = __x;
                __x = mImpl.mKeyCompare(_KeyOfValue()(__v), sKey(__x)) ? sLeft(__x) : sRight(__x);
            }
            return (mInsert(__x, __y, __v));
        }
        iterator mInsertUnique(const_iterator __position, const value_type &__v)
        {
            if (__position.mNode == mEnd())
            {
                if (size() > 0 && mImpl.mKeyCompare(sKey(mRightMost()), _KeyOfValue()(__v)))
                    return (mInsert(0, mRightMost(), __v));
                else
                    return (mInsertUnique(__v).first);
            }
            else if (mImpl.mKeyCompare(_KeyOfValue()(__v), sKey(__position.mNode)))
            {
                const_iterator __before = __position;

                if (__position.mNode == mLeftMost())
                    return (mInsert(mLeftMost(), mLeftMost(), __v));
                else if (mImpl.mKeyCompare(sKey((--__before).mNode), _KeyOfValue()(__v)))
                {
                    if (sRight(__before.mNode) == 0)
                        return (mInsert(0, __before.mNode, __v));
                    else
                        return (mInsert(__position.mNode, __position.mNode, __v));
                }
                else
                    return (mInsertUnique(__v).first);
            }
            else if (mImpl.mKeyCompare(sKey(__position.mNode), _KeyOfValue()(__v)))
            {
                const_iterator __after = __position;

                if (__position.mNode == mRightMost())
                    return (mInsert(0, mRightMost(), __v));
                else if (mImpl.mKeyCompare(_KeyOfValue()(__v), sKey((++__after).mNode)))
                {
                    if (sRight(__position.mNode) == 0)
                        return (mInsert(0, __position.mNode, __v));
                    else
                        return (mInsert(__after.mNode, __after.mNode, __v));
                }
                else
                    return (mInsertUnique(__v).first);
            }
            else
                return (iterator(static_cast<_Link_type>(const_cast<_Base_ptr>(__position.mNode))));
        }
        iterator mInsertEqual(const_iterator __position, const value_type &__v)
        {
            if (__position.mNode == mEnd())
            {
                if (size() > 0 && !mImpl.mKeyCompare(_KeyOfValue()(__v),
                                                     sKey(mRightMost())))
                    return mInsert(0, mRightMost(), __v);
                else
                    return mInsertEqual(__v);
            }
            else if (!mImpl.mKeyCompare(sKey(__position.mNode),
                                        _KeyOfValue()(__v)))
            {
                // First, try before...
                const_iterator __before = __position;
                if (__position.mNode == mLeftMost()) // begin()
                    return mInsert(mLeftMost(), mLeftMost(), __v);
                else if (!mImpl.mKeyCompare(_KeyOfValue()(__v),
                                            sKey((--__before).mNode)))
                {
                    if (sRight(__before.mNode) == 0)
                        return mInsert(0, __before.mNode, __v);
                    else
                        return mInsert(__position.mNode,
                                       __position.mNode, __v);
                }
                else
                    return mInsertEqual(__v);
            }
            else
            {
                const_iterator __after = __position;

                if (__position.mNode == mRightMost())
                    return mInsert(0, mRightMost(), __v);
                else if (!mImpl.mKeyCompare(sKey((++__after).mNode),
                                            _KeyOfValue()(__v)))
                {
                    if (sRight(__position.mNode) == 0)
                        return mInsert(0, __position.mNode, __v);
                    else
                        return mInsert(__after.mNode, __after.mNode, __v);
                }
                else
                    return mInsertEqualLower(__v);
            }
        }
        template <typename _InputIterator>
        void mInsertUnique(_InputIterator __first, _InputIterator __last)
        {
            for (; __first != __last; ++__first)
                mInsertUnique(end(), *__first);
        }
        template <typename _InputIterator>
        void mInsertEqual(_InputIterator __first, _InputIterator __last)
        {
            for (; __first != __last; ++__first)
                mInsertEqual(end(), *__first);
        }
        void erase(iterator __position)
        {
            _Link_type __y =
                static_cast<_Link_type>(rb_tree_rebalance_for_erase(__position.mNode, this->mImpl.mHeader));
            mDestroyNode(__y);
            --mImpl.mNodeCount;
        }
        size_type erase(const key_type &__x)
        {
            std::pair<iterator, iterator> __p = equal_range(__x);
            const size_type __old_size = size();
            erase(__p.first, __p.second);
            return __old_size - size();
        }
        void erase(iterator __first, iterator __last)
        {
            if (__first == begin() && __last == end())
                clear();
            else
                while (__first != __last)
                    erase(__first++);
        }
        void erase(const_iterator __first, const_iterator __last)
        {
            if (__first == begin() && __last == end())
                clear();
            else
                while (__first != __last)
                    erase(__first++);
        }
        void clear()
        {
            mErase(mBegin());
            mLeftMost() = mEnd();
            mRoot() = 0;
            mRightMost() = mEnd();
            mImpl.mNodeCount = 0;
        }
        iterator find(const key_type &__k)
        {
            iterator __j = mLowerBound(mBegin(), mEnd(), __k);
            return (__j == end() || mImpl.mKeyCompare(__k, sKey(__j.mNode)))
                       ? end()
                       : __j;
        }
        const_iterator find(const key_type &__k) const
        {
            const_iterator __j = mLowerBound(mBegin(), mEnd(), __k);
            return (__j == end() || mImpl.mKeyCompare(__k, sKey(__j.mNode)))
                        ? end()
                        : __j;
        }
        size_type count(const key_type &__k) const
        {
            std::pair<const_iterator, const_iterator> __p = equal_range(__k);
            const size_type __n = std::distance(__p.first, __p.second);
            return __n;
        }
        iterator lower_bound(const key_type &__k)
        {
            return (mLowerBound(mBegin(), mEnd(), __k));
        }
        const_iterator lower_bound(const key_type &__k) const
        {
            return (mLowerBound(mBegin(), mEnd(), __k));
        }
        iterator upper_bound(const key_type &__k)
        {
            return (mUpperBound(mBegin(), mEnd(), __k));
        }
        const_iterator upper_bound(const key_type &__k) const
        {
            return (mUpperBound(mBegin(), mEnd(), __k));
        }
        std::pair<iterator, iterator> equal_range(const key_type &__k)
        {
            _Link_type __x = mBegin();
            _Link_type __y = mEnd();

            while (__x != 0)
            {
                if (mImpl.mKeyCompare(sKey(__x), __k))
                    __x = sRight(__x);
                else if (mImpl.mKeyCompare(__k, sKey(__x)))
                {
                    __y = __x;
                    __x = sLeft(__x);
                }
                else
                {
                    _Link_type __xu(__x);
                    _Link_type __yu(__y);

                    __y = __x;
                    __x = sLeft(__x);
                    __xu = sRight(__xu);
                    return (std::pair<iterator, iterator>(mLowerBound(__x, __y, __k),
                                                                      mUpperBound(__xu, __yu, __k)));
                }
            }
            return (std::pair<iterator, iterator>(iterator(__y), iterator(__y)));
        }
        std::pair<const_iterator, const_iterator> equal_range(const key_type &__k) const
        {
            _Const_Link_type __x = mBegin();
            _Const_Link_type __y = mEnd();

            while (__x != 0)
            {
                if (mImpl.mKeyCompare(sKey(__x), __k))
                    __x = sRight(__x);
                else if (mImpl.mKeyCompare(__k, sKey(__x)))
                {
                    __y = __x;
                    __x = sLeft(__x);
                }
                else
                {
                    _Link_type __xu(__x);
                    _Link_type __yu(__y);

                    __y = __x;
                    __x = sLeft(__x);
                    __xu = sRight(__xu);
                    return (std::pair<const_iterator, const_iterator>(mLowerBound(__x, __y, __k),
                                                          mUpperBound(__xu, __yu, __k)));
                }
            }
            return (std::pair<const_iterator, const_iterator>(const_iterator(__y), const_iterator(__y)));
        }
    };
    template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
    inline bool operator==(const red_black_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__x,
                        const red_black_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__y)
    {
        typedef typename red_black_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::const_iterator const_iterator;

        bool ret = true;
        const_iterator begin_x = __x.begin();
        const_iterator end_x = __x.end();
        const_iterator begin_y = __y.begin();

        for (; begin_x != end_x; ++begin_x, ++begin_y)
        {
            if (*begin_x == *begin_y)
            {
                ret = false;
                break ;
            }
        }

        return (__x.size() == __y.size() && ret);
    }
    template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
    inline bool operator<(const red_black_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__x,
                        const red_black_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__y)
    {
        typedef typename red_black_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::const_iterator const_iterator;

        const_iterator begin_x = __x.begin();
        const_iterator end_x = __x.end();
        const_iterator begin_y = __y.begin();
        const_iterator end_y = __y.end();

        for (; begin_y != end_y; ++begin_x, ++begin_y)
        {
            if (begin_x == end_x || *begin_x < *begin_y)
                return (true);
            if (*begin_y < *begin_x)
                return (false);
        }
        return (false);
    }
    template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
    inline bool operator!=(const red_black_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__x,
                        const red_black_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__y)
    {
        return (!(__x == __y));
    }
    template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
    inline bool operator>(const red_black_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__x,
                        const red_black_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__y)
    {
        return (__y < __x);
    }
    template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
    inline bool operator<=(const red_black_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__x,
                        const red_black_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__y)
    {
        return (!(__y < __x));
    }
    template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
    inline bool operator>=(const red_black_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__x,
                        const red_black_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__y)
    {
        return (!(__x < __y));
    }
    template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
    inline void swap(const red_black_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__x,
                    const red_black_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc> &__y)
    {
        __x.swap(__y);
    }

} // namespace ft
