/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:02:26 by kmin              #+#    #+#             */
/*   Updated: 2020/11/05 15:58:16 by kmin             ###   ########.fr       */
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
            if (node == TNULL || key == node->mData.first)
            {
                return (node);
            }
            if (key < node->mData.first)
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
            node_pointer z = TNULL;
            node_pointer x, y;

            while (node != TNULL)
            {
                if (node->mData.first == key)
                    z = node;
                if (node->mData.first <= key)
                    node = node->mRight;
                else
                    node = node->mLeft;
            }
            if (z == TNULL)
                return ;
            y = z;
            bool y_original_color = y->color;
            if (z->mLeft == TNULL)
            {
                x = z->mRight;
                rbTransplant(z, z->mRight);
            }
            else if (z->mRight == TNULL)
            {
                x = z->mLeft;
                rbTransplant(z, z->mLeft);
            }
            else
            {
                y = minimum(z->mRight);
                y_original_color = y->color;
                x = y->mRight;
                if (y->mParent == z)
                    x->mParent = y;
                else
                {
                    rbTransplant(y, y->mRight);
                    y->mRight = z->mRight;
                    y->mRight->mParent = y;
                }
                rbTransplant(z, y);
                y->mLeft = z->mLeft;
                y->mLeft->mParent = y;
                y->color = z->color;
            }
            this->getAllocator().destroy(z); // 되는건가..?
            this->mPutNode(z); // ??
            if (y_original_color == BLACK)
                deleteFix(x);
        }
        void insertFix(node_pointer k)
        {
            node_pointer u;

            while (k->mParent->color == RED)
            {
                if (k->mParent == k->mParent->mParent->right)
                {
                    u = k->mParent->mParent->mLeft;
                    if (u->color == RED)
                    {
                        u->color = BLACK;
                        k->mParent->color = BLACK;
                        k->mParent->mParent->color = RED;
                        k = k->mParent->mParent;
                    }
                    else
                    {
                        if (k == k->mParent->mLeft)
                        {
                            k = k->mParent;
                            rightRotate(k);
                        }
                        k->mParent->color = BLACK;
                        k->mParent->mParent->color = RED;
                        leftRotate(k->mParent->mParent);
                    }
                }
                else
                {
                    u = k->mParent->mParent->mRight;
                    if (u->color == RED)
                    {
                        u->color = BLACK;
                        k->mParent->color = BLACK;
                        k->mParent->mParent->color = RED;
                        k = k->mParent->mParent;
                    }
                    else
                    {
                        if (k == k->mParent->mRight)
                        {
                            k = k->mParent;
                            leftRotate(k);
                        }
                        k->mParent->color = BLACK;
                        k->mParent->mParent->color = RED;
                        rightRotate(k->mParent->mParent);
                    }
                }
                if (k == root)
                    break;
            }
            root->color = BLACK;
        }
    public:
        red_black_tree(const key_compare &__comp, const allocator_type &__a = allocator_type())
            : _Base(__a)
        {
        }
        ~red_black_tree()
        {
        }
        node_pointer searchTree(key_type k)
        {
            return searchTreeHelper(this->root, k);
        }
        node_pointer minimum(node_pointer node)
        {
            while (node->mLeft != TNULL)
                node = node->mLeft;
            return (node);
        }
        node_pointer maximum(node_pointer node)
        {
            while (node->mRight != TNULL)
                node = node->mRight;
            return (node);
        }
        node_pointer successor(node_pointer x)
        {
            if (x->mRight != TNULL)
                return minimum(x->mRight);
            node_pointer y = x->mParent;

            while (y != TNULL && x == y->mRight)
            {
                x = y;
                y = y->mParent;
            }
            return (y);
        }
        node_pointer predecessor(node_pointer x)
        {
            if (x->mLeft != TNULL)
                return maximum(x->mLeft);
            node_pointer y = x->mParent;
            
        }
        void leftRotate(node_pointer x)
        {
            node_pointer y = x->mRight;
            
            x->mRight = y->mLeft;
            if (y->mLeft != TNULL)
                y->mLeft->mParent = x;
            y->mParent = x->mParent;
            if (x->mParent == NULL)
                this->root = y;
            else if (x == x->mParent->mLeft)
                x->mParent->mLeft = y;
            else
                x->mParent->mRight = y;
            y->mLeft = x;
            x->mParent = y;
        }
        void rightRotate(node_pointer x)
        {
            node_pointer y = x->mLeft;
            x->mLeft = y->mRight;
            if (y->mRight != TNULL)
                y->mRight->mParent = x;
            y->mParent = x->mParent;
            if (x->mParent == NULL)
                this->root = y;
            else if (x == x->mParent->mRight)
                x->mParent->mRight = y;
            else
                x->mParent->mLeft = y;
            y->mRight = x;
            x->mParent = y;
        }
        void insert(key_type key, value_type val)
        {
            node_pointer node = mCreateNode(key, val);

            node->mParent = NULL;
            node->mLeft = TNULL;
            node->mRight = TNULL;
            node->color = RED;

            node_pointer y = NULL;
            node_pointer x = this->root;

            while (x != TNULL)
            {
                y = x;
                if (node->mData.first < x->mData.first)
                    x = x->mLeft;
                else
                    x = x->mRight;
            }
            node->mParent = y;
            if (y == NULL)
                root = node;
            else if (node->mData.first < y->mData.first)
                y->mLeft = node;
            else
                y->mRight = node;
            
            if (node->mParent == NULL)
            {
                node->color = BLACK;
                return ;
            }
            if (node->mParent->mParent == NULL)
                return ;
            insertFix(node);
        }
        node_pointer getRoot()
        {
            return (this->root);
        }
        void deleteNode(key_type key)
        {
            deleteNodeHelper(this->root, key);
        }
    };
} // namespace ft
