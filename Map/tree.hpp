/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:02:26 by kmin              #+#    #+#             */
/*   Updated: 2020/11/05 16:21:18 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../Iterator/MapIterator.hpp"

#define BLACK true
#define RED false

namespace ft
{
    template <typename key_type, typename value_type, typename _Alloc>
    class red_black_tree_base
    {
    protected:
        typedef typename _Alloc::template rebind<tree_node<key_type, value_type> >::other _Node_Alloc_type;
        struct MapImpl : public _Node_Alloc_type // tree_node를 상속받음
        {
            tree_node_base mNode;
            MapImpl(const _Node_Alloc_type &__a) // tree_node object를 받아서
                : _Node_Alloc_type(__a) // tree_node object 생성.
            {
            }
        };
        MapImpl mImpl;

        tree_node<key_type, value_type> *mGetNode()
        {
            return mImpl._Node_Alloc_type::allocate(1);
        }

        void mPutNode(tree_node<key_type, value_type> *__p)
        {
            mImpl._Node_Alloc_type::deallocate(__p, 1);
        }
    public:
        typedef _Alloc allocator_type;

        allocator_type getAllocator() const
        {
            return (allocator_type(*static_cast<const _Node_Alloc_type *>(&this->mImpl)));
        }
        red_black_tree_base(const allocator_type &__a)
            : mImpl(__a)
        {
        }
        virtual ~red_black_tree_base()
        {
            mClear(&this->mImpl.mNode);
        }
        void mClear(tree_node_base *root)
        {
            tree_node<key_type, value_type> *tmp = static_cast<tree_node<key_type, value_type> *>(root);
            
            if (root->mLeft != NULL)
                mClear(root->mLeft);
            if (root->mRight != NULL)
                mClear(root->mRight);
            // getAllocator().destroy(&tmp->mData.first);
            // getAllocator().destroy(&tmp->mData.second);
            // mPutNode(tmp);
        }
    };

    template <typename key_type, typename value_type, typename key_compare, typename _Pair_alloc_type>
    class red_black_tree : public red_black_tree_base<key_type, value_type, _Pair_alloc_type>
    {
    public:
        typedef tree_node<key_type, value_type>* node_pointer;
        typedef red_black_tree_base<key_type, value_type, _Pair_alloc_type>     _Base;
        typedef typename _Base::allocator_type                                  allocator_type;
        typedef MapIterator<key_type, value_type>                               iterator;
        typedef ConstMapIterator<key_type, value_type>                          const_iterator;
        typedef ReverseMapIterator<key_type, value_type>                        reverse_iterator;
        typedef ConstReverseMapIterator<key_type, value_type>                   const_reverse_iterator;
        typedef size_t                                                          size_type;
        typedef ptrdiff_t                                                       difference_type;
    protected:
        typedef tree_node<key_type, value_type>                                 _Node;

        using _Base::mImpl;
        using _Base::mPutNode;
        using _Base::mGetNode;

        _Node *mCreateNode(const key_type &__x, const value_type &__y)
        {
            _Node *__p;
            try
            {
                __p = this->mGetNode();
                this->mImpl.getAllocator().construct(__p->mData.first, __x);
                this->mImpl.getAllocator().construct(__p->mData.second, __y);
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

    private:
        node_pointer root;
        node_pointer TNULL;

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
    };
} // namespace ft
