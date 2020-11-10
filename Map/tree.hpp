/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:02:26 by kmin              #+#    #+#             */
/*   Updated: 2020/11/10 17:52:37 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Iterator/MapIterator.hpp"
#include <exception>
#include <type_traits>

namespace ft
{
    template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc = std::allocator<_Val> >
    class red_black_tree
    {
        typedef typename _Alloc::template rebind<rb_tree_node<_Val> >::other _Node_allocator;
    protected:
        typedef rb_tree_node_base*                                              _Base_ptr;
        typedef const rb_tree_node_base*                                        _Const_Base_ptr;
        
    public:
        typedef _Key                                                            key_type;
        typedef _Val                                                            value_type;
        typedef value_type*                                                     pointer;
        typedef const value_type*                                               const_pointer;
        typedef value_type&                                                     reference;
        typedef const value_type&                                               const_reference;
        typedef rb_tree_node<_Val>*                                             _Link_type;
        typedef const rb_tree_node<_Val>*                                       _Const_Link_type;
        typedef _Alloc                                                          allocator_type;
        
        typedef MapIterator<key_type, value_type>                               iterator;
        typedef ConstMapIterator<key_type, value_type>                          const_iterator;
        typedef ReverseMapIterator<key_type, value_type>                        reverse_iterator;
        typedef ConstReverseMapIterator<key_type, value_type>                   const_reverse_iterator;
        
        typedef size_t                                                          size_type;
        typedef ptrdiff_t                                                       difference_type;

        _Node_allocator &mGetNode_Allocator()
        {
            return *(static_cast<_Node_allocator*>(&this->mImpl));
        }
        const _Node_allocator &mGetNode_Allocator() const
        {
            return *(static_cast<const _Node_allocator*>(&this->mImpl));
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
                getAlloctor().std::construct(&__tmp->mValueField, __x);
            }
            catch(const std::exception& e)
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
            _Link_type __tmp =  mCreateNode(__x->mValueField);
            __tmp->m_color = __x->m_color;
            __tmp->mLeft = 0;
            __tmp->mRight = 0;
            return (__tmp);
        }
    protected:
        template <typename _Key_compare>
        struct rb_tree_impl : public _Node_allocator
        {
            _Key_compare                    mKeyCompare;
            rb_tree_node_base               mHeader;
            size_type                       mNodeCount;

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
        static _Const_Link_type sLeft(_Base_ptr __x)
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
        
    public:
        red_black_tree(const key_compare &__comp, const allocator_type &__a = allocator_type())
            : _Base(__a)
        {
        }
        red_black_tree(const red_black_tree &rhs)
            : _Base(allocator_type())
        {
            
        }
        red_black_tree &operator=(const red_black_tree &other)
        {   
        }
        ~red_black_tree()
        {
        }
        std::pair<iterator, bool> mInsertUnique(const value_type &__val)
        {
            
        }
        iterator mInsertUnique(const_iterator __p, const value_type &__val)
        {
            
        }
        template <typename _InputIterator>
        void insert(_InputIterator __first, _InputIterator __last)
        {
            
        }
        iterator lower_bound(const key_type &__k)
        {
            
        }
        const_iterator lower_bound(const key_type &__k) const
        {
            
        }
        std::pair<const_iterator, const_iterator> equal_range(key_type __k) const
        {
            
        }
        std::pair<iterator, iterator> equal_range(key_type __k)
        {
            
        }
    };
} // namespace ft
