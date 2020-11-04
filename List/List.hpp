/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 13:19:12 by kmin              #+#    #+#             */
/*   Updated: 2020/11/04 17:54:54 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <memory>
#include <limits>
#include "../Iterator/ListIterator.hpp"
#include "../algorithms/algo.hpp"

namespace ft
{
    template <typename T, typename _Alloc>
    class ListBase
    {
    protected:
        typedef typename _Alloc::template rebind<Node<T> >::other _Node_Alloc_type;
        struct ListImpl : public _Node_Alloc_type // Node를 상속받음
        {
            NodeBase mNode;
            ListImpl(const _Node_Alloc_type &__a) // Node object를 받아서
                : _Node_Alloc_type(__a) // Node object 생성.
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
            NodeBase *cur = this->mImpl.mNode.mNext;
            while (cur != &this->mImpl.mNode)
            {
                Node<T> *tmp = static_cast<Node<T> *>(cur);
                // T *val = &tmp->mData; // linux
                cur = cur->mNext;
                // std::_Destroy(val); //소멸자를 호출. 그런데 Node의 주소값 == Node.mData의 주소값이다.
                getAllocator().destroy(&tmp->mData);
                mPutNode(tmp);
            }
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
        typedef ListIterator<T>                             iterator;
        typedef ConstListIterator<T>                        const_iterator;
        typedef ReverseListIterator<T>                      reverse_iterator;
        typedef ConstReverseListIterator<T>                 const_reverse_iterator;
#ifdef __linux__
        typedef __gnu_cxx::size_t                           size_type;
        typedef __gnu_cxx::ptrdiff_t                        difference_type;
#endif
#ifdef __APPLE__
        typedef size_t                                  size_type;
        typedef ptrdiff_t                               difference_type;
#endif
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
        template <typename _InputIterator>
        list(_InputIterator __first, _InputIterator __last, const allocator_type &__a = allocator_type()) // range constructor
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
            return (this->mImpl.mNode.mPrev);
        }
        const_reverse_iterator rbegin() const
        {
            return (this->mImpl.mNode.mPrev);
        }
        reverse_iterator rend()
        {
            return (&this->mImpl.mNode);
        }
        const_reverse_iterator rend() const
        {
            return (&this->mImpl.mNode);
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
            iterator finish = __x.end();
            if (!__x.empty())
                mTransferRange(__position, __x.begin(), --finish);
        }
        void splice(iterator __position, list &__x, iterator __i)
        {
            iterator __j = __i;
            ++__j;
            if (__position == __i || __position == __j)
                return ;
            if (!__x.empty())
                mTransfer(__position, __i, __j);
        }
        void splice(iterator __position, list &__x, iterator __first, iterator __last)
        {
            if (__first != __last)
            {
                if (__x.end() == __last)
                    mTransferRange(__position, __first, --__last);
                else
                    mTransferRange(__position, __first, __last);
            }
        }
        void remove(const T &value)
        {
            iterator i = begin();
            while (i != end())
            {
                iterator tmp = ++i;
                if (*--tmp == value)
                    erase(tmp);
            }
        }
        template <typename _Predicate>
        void remove_if(_Predicate __ifState)
        {
            iterator i = begin();
            while (i != end())
            {
                iterator tmp = ++i;
                if (__ifState(*--tmp))
                    erase(tmp);
            }
        }
        void unique()
        {
            unique(equal<value_type>);
        }
        template <typename _BinaryPredicate>
        void unique(_BinaryPredicate binary_pred)
        {
            iterator start = begin();
            while (true)
            {
                iterator finish = end();
                iterator next = ++start;
                --start;
                if (start == finish)
                    break ;
                if (next != finish && binary_pred(*start, *next))
                    start = erase(--next);
                else
                    ++start;
            }
        }
        void merge(list &__x)
        {
            merge(__x, &less<value_type>);
        }
        template <typename _StrictWeakOrdering>
        void merge(list &a, _StrictWeakOrdering b)
        {
            iterator this_start = begin();
            iterator this_end = end();
            iterator obj_start = a.begin();
            iterator obj_end = a.end();

            while (obj_start != obj_end && this_start != this_end)
            {
                if (b(*obj_start, *this_start))
                {
                    splice(this_start, a, obj_start);
                    obj_start = a.begin();
                }
                else
                    ++this_start;
            }
            splice(this_end, a);
        }
        void reverse()
        {
            iterator start = end();
            iterator finish = begin();
            iterator next;

            --start; // 가장 마지막 노드
            --start; // 뒤에서 2번째 노드
            next = start;
            while (start != finish)
            {
                if (next != finish)
                    --next;
                splice(end(), *this, start);
                start = next;
            }
            splice(end(), *this, start);
        }
        void sort()
        {
            sort(less<value_type>);
        }
        template <typename _StrictWeakOrdering>
        void sort(_StrictWeakOrdering a)
        {
            iterator start = begin();
            iterator next;

            while (start != end())
            {
                next = start;
                ++next;
                while (next != end())
                {
                    if (a(*next, *start))
                    {
                        splice(start, *this, next); // swap
                        next = start;
                        ++next;
                        start = begin();
                    }
                    else
                        ++next;
                }
                ++start;
            }
        }
        virtual ~list() {}
    protected:
        void mAssignDispatch(const_iterator __first, const_iterator __last) //mac에서는 std::__false_type, wsl에서는 std::__false_type
        {
            iterator i = begin();
            for (; i != end() && __first != __last; ++__first, ++i)
            {
                *i = *__first;
            }
            if (__first != __last)
                insert(end(), __first, __last);
            else
                erase(i, end());
        }
        void mFillAssign(size_type __n, const value_type &__val)
        {
            iterator i = begin();
            for (;i != end() && __n > 0; ++i, --__n)
                *i = __val;
            if (__n)
                insert(end(), __n, __val);
            else
                erase(i, end());
        }
        template <typename _Integer>
        void mInsertDispatch(iterator __pos, _Integer __first, _Integer __last) // mac에서는 std::false_type
        {
            for (; __first != __last; ++__first)
                mInsert(__pos, *__first);
        }
        void mInsertDispatch(iterator __pos, const_iterator __first, const_iterator __last) // mac에서는 std::false_type
        {
            for (; __first != __last; ++__first)
                mInsert(__pos, *__first);
        }
        void mFillInsert(iterator __pos, size_type __n, const value_type &__x)
        {
            for (; __n > 0; --__n)
                mInsert(__pos, __x);   
        }
        // void mTransferStartToEnd(iterator __position, iterator __first, iterator __last)
        // {
        //     __position.mNode->transfer_start_to_end(__first.mNode, __last.mNode);
        // }
        void mTransferRange(iterator __position, iterator __first, iterator __last)
        {
            __position.mNode->transfer_range(__first.mNode, __last.mNode);
        }
        void mTransfer(iterator __position, iterator __first, iterator __last)
        {
            __position.mNode->transfer(__first.mNode, __last.mNode);
        }
        void mInsert(iterator __position, const value_type &__x)
        {
            _Node *__tmp = mCreateNode(__x);
            if (__position == begin())
            {
                __tmp->hook_front(__position.mNode);
                this->mImpl.mNode.mNext = __tmp;
            }
            else if (__position == end())
                __tmp->hook_end(__position.mNode);
            else
                __tmp->hook_front(__position.mNode);
        }
        void mErase(iterator __position)
        {
            __position.mNode->unhook();
            _Node * __n = static_cast<_Node *>(__position.mNode);
#ifdef __linux__
            std::_Destroy(&__n->mData); // on linux
#endif
#ifdef __APPLE__
            getAllocator().destroy(&__n->mData);   // on mac
#endif
            mPutNode(__n);
        }
    };
} // namespace ft
