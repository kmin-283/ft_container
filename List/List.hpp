/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 13:19:12 by kmin              #+#    #+#             */
/*   Updated: 2020/10/12 18:50:51 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <memory>
#include <limits>
#include "../Iterator/Iterator.hpp"

namespace ft
{
    template <typename T, typename _Alloc>
    class ListBase
    {
    protected:
        typedef typename _Alloc::template rebind<Node<T> >::other _Node_Alloc_type;
        struct ListImpl : public _Node_Alloc_type // node<T>를 상속받음
        {
            Node_base mNode; //Node와 Node_Base는 다름
            ListImpl(const _Node_Alloc_type &__a) // Node<T> __a를 받아서
                : _Node_Alloc_type(__a) // 동일한 Node<T> __a 를 생성
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
        typedef std::reverse_iterator<iterator>         reverse_iterator;
        typedef std::reverse_iterator<const_iterator>   const_reverse_iterator;
        typedef size_t                                  size_type;
        typedef ptrdiff_t                               difference_type;
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
            }
            return (__p);
        }
    public:
        explicit list(const allocator_type &__a = allocator_type())
            : _Base(__a)
        {
        }
        list(size_type __n, const value_type &__value, const allocator_type &__a = allocator_type())
            : _Base(__a)
        {
            this->insert(begin(), __n, __value);
        }
        explicit list(size_type __n)
            : _Base(allocator_type())
        {
            this->insert(begin(), __n, value_type());
        }
        list(const list &__x)
            : _Base(__x.getAllocator())
        {
            this->insert(begin(), __x.begin(), __x.end());
        }
        template <typename _InputIterator>
        list(_InputIterator __first, _InputIterator __last, const allocator_type &__a = allocator_type())
            : _Base(__a)
        {
            this->insert(begin(), __first, __last);
        }
        list &operator=(const list &__x)
        {
            // iterator로 반복을 돌면서 __x의 크기만큼 Node<T>생성 //
            (void)__x;
            return (*this);
        }
        void assign(size_type __n, const value_type &__val)
        {
            mFillAssign(__n, __val);
        }
        template <typename _InputIterator>
        void assign(_InputIterator __first, _InputIterator __last)
        {
            typedef typename std::is_integral<_InputIterator>::_Integral _Integral;
            mAssignDispatch(__first, __last, _Integral());
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
            return (std::distance(begin(), end()));
        }
        size_type max_size() const
        {
            return (size_type(-1));
        }
        ~list();
    };
} // namespace ft
