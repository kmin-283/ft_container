/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 13:19:12 by kmin              #+#    #+#             */
/*   Updated: 2020/10/17 21:28:35 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <memory>
#include <limits>
#include "../Iterator/Iterator.hpp"
#include <iostream>

namespace ft
{
    template <typename T, typename _Alloc>
    class ListBase
    {
    protected:
        typedef typename _Alloc::template rebind<Node<T> >::other _Node_Alloc_type;
        struct ListImpl : public _Node_Alloc_type // NodeBase allocator를 상속받음
        {
            NodeBase mNode;
            ListImpl(const _Node_Alloc_type &__a) // NodeBase allocator object를 받아서
                : _Node_Alloc_type(__a) // NodeBase allocator object 생성.
            {
            }
        };
        ListImpl mImpl;
        Node<T> *mGetNode()
        {
            return mImpl._Node_Alloc_type::allocate(1);
        }

        void mPutNode(Node<T> *__p)
        {
            mImpl._Node_Alloc_type::deallocate(__p, 1);
        }

    public:
        typedef _Alloc allocator_type;

        allocator_type getAllocator() const
        {
            return (allocator_type(*static_cast<const _Node_Alloc_type *>(&this->mImpl)));
        }
        ListBase(const allocator_type &__a)
            : mImpl(__a)
        {
            mInit();
        }
        virtual ~ListBase()
        {
            mClear();
        }
        void mClear()
        {
        }
        void mInit()
        {
            this->mImpl.mNode.mNext = &this->mImpl.mNode;
            this->mImpl.mNode.mPrev = &this->mImpl.mNode;
        }
    };

    template <typename T, typename _Alloc = std::allocator<T> >
    class list : protected ListBase<T, _Alloc>
    {
        typedef ListBase <T, _Alloc>    _Base;
    public:
        typedef T                                       value_type;
        typedef typename _Alloc::pointer                pointer;
        typedef typename _Alloc::const_pointer          const_pointer;
        typedef typename _Alloc::reference              reference;
        typedef typename _Alloc::const_reference        const_reference;
        typedef Iterator<T>                             iterator;
        typedef ConstIterator<T>                        const_iterator;
        typedef ReverseIterator<T>                      reverse_iterator;
        typedef ConstReverseIterator<T>                 const_reverse_iterator;
        typedef __gnu_cxx::size_t                                  size_type;
        // typedef ptrdiff_t                               difference_type; // mac에서 사용할 때
        typedef __gnu_cxx::ptrdiff_t difference_type;
        typedef typename _Base::allocator_type          allocator_type;
    protected:
        typedef Node<T>                                 _Node;

        using _Base::mImpl;
        using _Base::mPutNode;
        using _Base::mGetNode;
        _Node *mCreateNode(const value_type &__x)
        {
            _Node *__p;
            try
            {
                __p = this->mGetNode();
                __p->mData = __x;
            }
            catch (...)
            {
                this->mPutNode(__p);
                throw;
            }
            return (__p);
        }
        _Node *mCreateNode()
        {
            _Node *__p;
            try
            {
                __p =  this->mGetNode();
            }
            catch(...)
            {
                this->mPutNode(__p);
                throw;
            }
            return (__p);
        }
    public:
        explicit list(const allocator_type &__a = allocator_type()) // default constructor
            : _Base(__a)
        {
        }
        list(size_type __n, const value_type &__value, const allocator_type &__a = allocator_type()) // fill constructor
            : _Base(__a)
        {
            this->insert(begin(), __n, __value);
        }
        explicit list(size_type __n) // size constructor?
            : _Base(allocator_type())
        {
            this->insert(begin(), __n, value_type());
        }
        list(const list &__x) // copy constructor
            : _Base(__x.getAllocator())
        {
            this->insert(begin(), __x.begin(), __x.end());
        }
        list(const_iterator __first, const_iterator __last, const allocator_type &__a = allocator_type()) // range constructor
            : _Base(__a)
        {
            this->insert(begin(), __first, __last);
        }
        list &operator=(const list &__x) // assign operator
        {
            // iterator로 반복을 돌면서 __x의 크기만큼 Node<T>생성 //
            this->insert(begin(), __x.begin(), __x.end());
            return (*this);
        }
        void assign(size_type __n, const value_type &__val)
        {
            mFillAssign(__n, __val);
        }
        void assign(const_iterator __first, const_iterator __last)
        {
            mAssignDispatch(__first, __last);
        }
        allocator_type getAllocator() const
        {
            return (_Base::getAllocator());
        }
        iterator begin()
        {
            return (this->mImpl.mNode.mNext);
        }
        const_iterator begin() const
        {
            return (this->mImpl.mNode.mNext);
        }
        iterator end()
        {
            return (&this->mImpl.mNode);
        }
        const_iterator end() const
        {
            return (&this->mImpl.mNode);
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
        bool empty() const
        {
            return (this->mImpl.mNode.mNext == &this->mImpl.mNode);
        }
        size_type size() const
        {
            size_type ret = 0;
            const_iterator start = begin();
            while (start != end())
            {
                ret++;
                start++;
            }
            return (ret);
        }
        size_type max_size() const
        {
            return (size_type(-1));
        }
        void resize(size_type __new_size, const value_type &__x)
        {
            size_type thisSize = this->size();
            if (thisSize > __new_size)
            {
                for (size_type i = 0; i < thisSize - __new_size; i++)
                    pop_back();
            }
            else
            {
                for (size_type i = 0; i < __new_size - thisSize; i++)
                    push_back(__x);
            }
        }
        void resize(size_type __new_size)
        {
            this->resize(__new_size, value_type());
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
            return *(--end());
        }
        const_reference back() const
        {
            return *(--end());
        }
        void push_front(const value_type &__x)
        {
            this->mInsert(begin(), __x);
        }
        void pop_front()
        {
            this->mErase(begin());
        }
        void push_back(const value_type &__x)
        {
            this->mInsert(end(), __x);
        }
        void pop_back()
        {
            this->mErase(this->mImpl.mNode.mPrev);
        }
        iterator insert(iterator __position, const value_type &__x)
        {
            mInsert(__position, __x);
            return (begin());
        }
        void insert(iterator __position, size_type __n, const value_type &__x)
        {
            mFillInsert(__position, __n, __x);
        }
        template <typename _InputIterator>
        void insert(iterator __position, _InputIterator __first, _InputIterator __last)
        {
            mInsertDispatch(__position, __first, __last);
        }
        iterator erase(iterator __position)
        {
            iterator ret = ++__position;
            mErase(--__position);
            return (ret);
        }
        iterator erase(iterator __first, iterator __last)
        {
            while (__first != __last)
                __first = erase(__first);
            return (__last);
        }
        void clear()
        {
            _Base::mClear();
            _Base::mInit();
        }
        void splice(iterator __position, list &__x)
        {
            (void)__position;
            (void)__x;
        }
        void splice(iterator __position, list &__x, iterator __i)
        {
            (void)__position;
            (void)__x;
            (void)__i;
        }
        void splice(iterator __position, list &, iterator __first, iterator __last)
        {
            (void)__position;
            (void)__first;
            (void)__last;
        }
        void remove(const T &value)
        {
            (void)value;
        }
        template <typename _Predicate>
        void remove_if(_Predicate __value)
        {
            (void)__value;
        }
        void unique()
        {

        }
        void merge(list &__x)
        {
            (void)__x;
        }
        template <typename _StrictWeakOrdering>
        void merge(list &a, _StrictWeakOrdering b)
        {
            (void)a;
            (void)b;
        }
        void reverse()
        {
            this->mImpl.mNode.reverse();
        }
        void sort()
        {

        }
        template <typename _StrictWeakOrdering>
        void sort(_StrictWeakOrdering a)
        {
            (void)a;
        }
        virtual ~list() {}
    protected:
        void mAssignDispatch(const_iterator __first, const_iterator __last) //mac에서는 std::__false_type, wsl에서는 std::__false_type
        {
            (void)__first;
            (void)__last;
        }
        void mFillAssign(size_type __n, const value_type &__val)
        {
            iterator i = begin();
            for (;i != end() && __n > 0; i++, __n--)
                *i = __val;
            if (__n)
                insert(end(), __n, __val);
            else
                erase(i, end());
        }
        void mInsertDispatch(iterator __pos, const_iterator __first, const_iterator __last) // mac에서는 std::false_type
        {
            for (; __first != __last; __first++)
                mInsert(__pos, *__first);
        }
        void mFillInsert(iterator __pos, size_type __n, const value_type &__x)
        {
            for (; __n > 0; __n--)
                mInsert(__pos, __x);   
        }
        void mTransfer(iterator __position, iterator __first, iterator __last)
        {
            (void)__position;
            (void)__first;
            (void)__last;
        }
        void mInsert(iterator __position, const value_type &__x)
        {
            _Node *__tmp = mCreateNode(__x);
            __tmp->hook(__position.mNode);
        }
        void mErase(iterator __position)
        {
            __position.mNode->unhook();
            _Node * __n = static_cast<_Node *>(__position.mNode);
            std::_Destroy(&__n->mData);
            mPutNode(__n);
        }
    };
} // namespace ft
