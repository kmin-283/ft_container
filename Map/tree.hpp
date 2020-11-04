/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:02:26 by kmin              #+#    #+#             */
/*   Updated: 2020/11/04 19:53:28 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#define BLACK true
#define RED false

namespace ft
{
    struct tree_node_base
    {        
        tree_node_base *mLeft;
        tree_node_base *mRight;
        tree_node_base *mParent;
    };

    template <typename _Key, typename _Val>
    struct tree_node : public tree_node_base
    {
        std::pair<_Key, _Val> mData;
        bool color;
    };

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
        }
    };

    template <typename key_type, typename value_type, typename key_compare, typename _Pair_alloc_type>
    class red_black_tree : public red_black_tree_base<key_type, value_type, _Pair_alloc_type>
    {
        typedef tree_node<key_type, value_type>* node_pointer;
        typedef red_black_tree_base<key_type, value_type, _Pair_alloc_type>         _Base;
        typedef typename _Base::allocator_type          allocator_type;

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
                __p->mData.first = __x;
                __p->mData.second = __y;
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

        void initializeNULLNode(node_pointer node, node_pointer parent)
        {
            node->mData = 0;
            node->mParent = parent;
            node->mLeft = 0;
            node->mRight = 0;
            node->color = BLACK;
        }
        
        node_pointer searchTreeHelper(node_pointer node, key_type key)
        {
            if (node == TNULL || key == node->mData)
            {
                return (node);
            }
            if (key < node->mData)
            {
                return (searchTreeHelper(node->mLeft, key));
            }
            return searchTreeHelper(node->mRight, key);
        }
        void deleteFix(node_pointer __x)
        {
            node_pointer s;

            while (__x != root && __x->color == BLACK)
            {
                if (__x == __x->mParent->mLeft)
                {
                    s = __x->mParent->mRight;
                    if (s->color == RED)
                    {
                        s->color = BLACK;
                        __x->mParent->color = RED;
                        leftRotate(__x->mParent);
                        s = __x->mParent->mRight;
                    }
                    
                    if (s->mLeft->color == RED && s->mRight->color == BLACK)
                    {
                        s->color = RED;
                        __x = __x->mParent;
                    }
                    else
                    {
                        if (s->mRight->color == BLACK)
                        {
                            s->mLeft->color = BLACK;
                            s->color = RED;
                            rightRotate(s);
                            s = __x->mParent->mRight;
                        }
                        s->color = __x->mParent->color;
                        __x->mParent->color = BLACK;
                        s->mRight->color = BLACK;
                        leftRotate(__x->mParent);
                        __x = root;
                    }
                }
                else
                {
                    s = __x->mParent->left;
                    if (s->color == RED)
                    {
                        s->color = BLACK;
                        __x->mParent->color = RED;
                        rightRotate(__x->mParent);
                        s = __x->mParent->mLeft;
                    }
                    if (s->mRight->color == BLACK && s->mRight->color == BLACK)
                    {
                        s->color = RED;
                        __x = __x->mParent;
                    }
                    else
                    {
                        if (s->mLeft->color == BLACK)
                        {
                            s->mRight->color = BLACK;
                            s->color = RED;
                            leftRotate(s);
                            s = __x->mParent->mLeft;
                        }
                        s->color = __x->mParent->color;
                        __x->mParent->color = BLACK;
                        s->mLeft->color = BLACK;
                        rightRotate(__x->mParent);
                        __x = root;
                    }
                }
            }
            __x->color = BLACK;
        }
        void rbTransplant(node_pointer u, node_pointer v)
        {
            if (u->mParent == 0)
                root = v;
            else if (u == u->mParent->mLeft)
                u->mParent->mLeft = v;
            else
                u->mParent->mRight = v;
            v->mParent = u->mParent;
        }
        void deleteNodeHelper(node_pointer node, key_type key)
        {
        }

    public:
        red_black_tree(const key_compare &__comp, const allocator_type &__a = allocator_type())
            : _Base(__a)
        {
            mCreateNode();
        }
        ~red_black_tree()
        {
        }
    };
} // namespace ft