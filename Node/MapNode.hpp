/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapNode.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 16:10:50 by kmin              #+#    #+#             */
/*   Updated: 2020/11/21 20:07:14 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft
{
    enum rb_tree_color
    {
        RED = false,
        BLACK = true
    };

    struct rb_tree_node_base
    {
        typedef rb_tree_node_base *base_ptr;
        typedef const rb_tree_node_base *const_base_ptr;

        rb_tree_color mColor;
        rb_tree_node_base *mLeft;
        rb_tree_node_base *mRight;
        rb_tree_node_base *mParent;

        static base_ptr S_minimum(base_ptr __x)
        {
            while (__x->mLeft != 0)
                __x = __x->mLeft;
            return (__x);
        }
        static const_base_ptr S_minimum(const_base_ptr __x)
        {
            while (__x->mLeft != 0)
                __x = __x->mLeft;
            return (__x);
        }
        static base_ptr S_maximum(base_ptr __x)
        {
            while (__x->mRight != 0)
                __x = __x->mRight;
            return (__x);
        }
        static const_base_ptr S_maximum(const_base_ptr __x)
        {
            while (__x->mRight != 0)
                __x = __x->mRight;
            return (__x);
        }
    };

    template <typename _Val>
    struct rb_tree_node : public rb_tree_node_base
    {
        typedef rb_tree_node<_Val> *Link_type;
        _Val mValueField;
    };
} // namespace ft

static ft::rb_tree_node_base *local_rb_tree_increment(ft::rb_tree_node_base *__x) throw()
{
    if (__x->mRight != 0)
    {
        __x = __x->mRight;
        while (__x->mLeft != 0)
            __x = __x->mLeft;
    }
    else
    {
        ft::rb_tree_node_base *__y = __x->mParent;
        while (__x == __y->mRight)
        {
            __x = __y;
            __y = __y->mParent;
        }
        if (__x->mRight != __y)
            __x = __y;
    }
    return __x;
}

ft::rb_tree_node_base *rb_tree_increment(ft::rb_tree_node_base *__x) throw()
{
    return local_rb_tree_increment(__x);
}

const ft::rb_tree_node_base *rb_tree_increment(const ft::rb_tree_node_base *__x) throw()
{
    return local_rb_tree_increment(const_cast<ft::rb_tree_node_base *>(__x));
}

static ft::rb_tree_node_base *local_rb_tree_decrement(ft::rb_tree_node_base *__x) throw()
{
    if (__x->mColor == ft::RED && __x->mParent->mParent == __x)
        __x = __x->mRight; // reverse_iterator의 경우 header_node가 삽입되었을 때 가장 큰 노드로 변경시켜주어야만 정상적으로 동작하기 떄문에 header_node->mRight로 변경시켜줌.
    else if (__x->mLeft != 0)
    {
        ft::rb_tree_node_base *__y = __x->mLeft;
        while (__y->mRight != 0)
            __y = __y->mRight;
        __x = __y;
    }
    else
    {
        ft::rb_tree_node_base *__y = __x->mParent;
        while (__x == __y->mLeft)
        {
            __x = __y;
            __y = __y->mParent;
        }
        __x = __y;
    }
    return __x;
}

ft::rb_tree_node_base *rb_tree_decrement(ft::rb_tree_node_base *__x) throw()
{
    return local_rb_tree_decrement(__x);
}

const ft::rb_tree_node_base *rb_tree_decrement(const ft::rb_tree_node_base *__x) throw()
{
    return local_rb_tree_decrement(const_cast<ft::rb_tree_node_base *>(__x));
}

static void rb_tree_left_rotate(ft::rb_tree_node_base *const __x, ft::rb_tree_node_base *&__root)
{
    ft::rb_tree_node_base *const __y = __x->mRight;

    __x->mRight = __y->mLeft;
    if (__y->mLeft != 0)
        __y->mLeft->mParent = __x;
    __y->mParent = __x->mParent;

    if (__x == __root)
        __root = __y;
    else if (__x == __x->mParent->mLeft)
        __x->mParent->mLeft = __y;
    else
        __x->mParent->mRight = __y;
    __y->mLeft = __x;
    __x->mParent = __y;
}

static void rb_tree_right_rotate(ft::rb_tree_node_base *const __x, ft::rb_tree_node_base *&__root)
{
    ft::rb_tree_node_base *const __y = __x->mLeft;

    __x->mLeft = __y->mRight;
    if (__y->mRight != 0)
        __y->mRight->mParent = __x;
    __y->mParent = __x->mParent;

    if (__x == __root)
        __root = __y;
    else if (__x == __x->mParent->mRight)
        __x->mParent->mRight = __y;
    else
        __x->mParent->mLeft = __y;
    __y->mRight = __x;
    __x->mParent = __y;
}

void rb_tree_insert_and_rebalance(const bool __insert_left, ft::rb_tree_node_base *__target, ft::rb_tree_node_base *__p, ft::rb_tree_node_base &__header) throw()
{
    ft::rb_tree_node_base *&__root = __header.mParent;

    __target->mParent = __p;
    __target->mLeft = 0;
    __target->mRight = 0;
    __target->mColor = ft::RED;

    if (__insert_left)
    {
        __p->mLeft = __target;
        if (__p == &__header)
        {
            __header.mParent = __target;
            __header.mRight = __target;
        }
        else if (__p == __header.mLeft)
            __header.mLeft = __target;
    }
    else
    {
        __p->mRight = __target;
        if (__p == __header.mRight)
            __header.mRight = __target;
    }
    while (__target != __root && __target->mParent->mColor == ft::RED)
    {
        ft::rb_tree_node_base *const __target_greand_parent = __target->mParent->mParent;

        if (__target->mParent == __target_greand_parent->mLeft)
        {
            ft::rb_tree_node_base *const __y = __target_greand_parent->mRight;

            if (__y && __y->mColor == ft::RED)
            {
                __target->mParent->mColor = ft::BLACK;
                __y->mColor = ft::BLACK;
                __target_greand_parent->mColor = ft::RED;
                __target = __target_greand_parent;
            }
            else
            {
                if (__target == __target->mParent->mRight)
                {
                    __target = __target->mParent;
                    rb_tree_left_rotate(__target, __root);
                }
                __target->mParent->mColor = ft::BLACK;
                __target_greand_parent->mColor = ft::RED;
                rb_tree_right_rotate(__target_greand_parent, __root);
            }
        }
        else
        {
            ft::rb_tree_node_base *const __y = __target_greand_parent->mLeft;
            if (__y && __y->mColor == ft::RED)
            {
                __target->mParent->mColor = ft::BLACK;
                __y->mColor = ft::BLACK;
                __target_greand_parent->mColor = ft::RED;
                __target = __target_greand_parent;
            }
            else
            {
                if (__target == __target->mParent->mLeft)
                {
                    __target = __target->mParent;
                    rb_tree_right_rotate(__target, __root);
                }
                __target->mParent->mColor = ft::BLACK;
                __target_greand_parent->mColor = ft::RED;
                rb_tree_left_rotate(__target_greand_parent, __root);
            }
        }
    }
    __root->mColor = ft::BLACK;
}

ft::rb_tree_node_base *rb_tree_rebalance_for_erase(ft::rb_tree_node_base *const __target, ft::rb_tree_node_base &__header) throw()
{
    ft::rb_tree_node_base *&__root = __header.mParent;
    ft::rb_tree_node_base *&__leftmost = __header.mLeft;
    ft::rb_tree_node_base *&__rightmost = __header.mRight;
    ft::rb_tree_node_base *__y = __target;
    ft::rb_tree_node_base *__x = 0;
    ft::rb_tree_node_base *__x_parent = 0;

    if (__y->mLeft == 0)       // __target has at most one non-null child. y == z.
        __x = __y->mRight;     // __x might be null.
    else if (__y->mRight == 0) // __target has exactly one non-null child. y == z.
        __x = __y->mLeft;      // __x is not null.
    else
    {
        // __target has two non-null children.  Set __y to
        __y = __y->mRight; //   __target's successor.  __x might be null.
        while (__y->mLeft != 0)
            __y = __y->mLeft;
        __x = __y->mRight;
    }
    if (__y != __target)
    {
        // relink y in place of z.  y is z's successor
        __target->mLeft->mParent = __y;
        __y->mLeft = __target->mLeft;
        if (__y != __target->mRight)
        {
            __x_parent = __y->mParent;
            if (__x)
                __x->mParent = __y->mParent;
            __y->mParent->mLeft = __x; // __y must be a child of mLeft
            __y->mRight = __target->mRight;
            __target->mRight->mParent = __y;
        }
        else
            __x_parent = __y;
        if (__root == __target)
            __root = __y;
        else if (__target->mParent->mLeft == __target)
            __target->mParent->mLeft = __y;
        else
            __target->mParent->mRight = __y;
        __y->mParent = __target->mParent;
        std::swap(__y->mColor, __target->mColor);
        __y = __target;
        // __y now points to node to be actually deleted
    }
    else
    { // __y == __target
        __x_parent = __y->mParent;
        if (__x)
            __x->mParent = __y->mParent;
        if (__root == __target)
            __root = __x;
        else if (__target->mParent->mLeft == __target)
            __target->mParent->mLeft = __x;
        else
            __target->mParent->mRight = __x;
        if (__leftmost == __target)
        {
            if (__target->mRight == 0) // __target->mLeft must be null also
                __leftmost = __target->mParent;
            // makes __leftmost == _M_header if __target == __root
            else
                __leftmost = ft::rb_tree_node_base::S_minimum(__x);
        }
        if (__rightmost == __target)
        {
            if (__target->mLeft == 0) // __target->mRight must be null also
                __rightmost = __target->mParent;
            // makes __rightmost == _M_header if __target == __root
            else // __x == __target->mLeft
                __rightmost = ft::rb_tree_node_base::S_maximum(__x);
        }
    }
    if (__y->mColor != ft::RED) // __y->color == black ==> rebalancing
    {
        while (__x != __root && (__x == 0 || __x->mColor == ft::BLACK))
        {
            if (__x == __x_parent->mLeft)
            {
                ft::rb_tree_node_base *__w = __x_parent->mRight; // x->sibling

                if (__w->mColor == ft::RED)
                {
                    __w->mColor = ft::BLACK;
                    __x_parent->mColor = ft::RED;
                    rb_tree_left_rotate(__x_parent, __root);
                    __w = __x_parent->mRight;
                }
                if ((__w->mLeft == 0 ||
                     __w->mLeft->mColor == ft::BLACK) &&
                    (__w->mRight == 0 ||
                     __w->mRight->mColor == ft::BLACK))
                {
                    __w->mColor = ft::RED;
                    __x = __x_parent;
                    __x_parent = __x_parent->mParent;
                }
                else
                {
                    if (__w->mRight == 0 || __w->mRight->mColor == ft::BLACK)
                    {
                        __w->mLeft->mColor = ft::BLACK;
                        __w->mColor = ft::RED;
                        rb_tree_right_rotate(__w, __root);
                        __w = __x_parent->mRight;
                    }
                    __w->mColor = __x_parent->mColor;
                    __x_parent->mColor = ft::BLACK;
                    if (__w->mRight)
                        __w->mRight->mColor = ft::BLACK;
                    rb_tree_left_rotate(__x_parent, __root);
                    break;
                }
            }
            else
            {
                // same as above, with mRight <-> mLeft.
                ft::rb_tree_node_base *__w = __x_parent->mLeft; // x->sibling

                if (__w->mColor == ft::RED)
                {
                    __w->mColor = ft::BLACK;
                    __x_parent->mColor = ft::RED;
                    rb_tree_right_rotate(__x_parent, __root);
                    __w = __x_parent->mLeft;
                }
                if ((__w->mRight == 0 ||
                     __w->mRight->mColor == ft::BLACK) &&
                    (__w->mLeft == 0 ||
                     __w->mLeft->mColor == ft::BLACK))
                {
                    __w->mColor = ft::RED;
                    __x = __x_parent;
                    __x_parent = __x_parent->mParent;
                }
                else
                {
                    if (__w->mLeft == 0 || __w->mLeft->mColor == ft::BLACK)
                    {
                        __w->mRight->mColor = ft::BLACK;
                        __w->mColor = ft::RED;
                        rb_tree_left_rotate(__w, __root);
                        __w = __x_parent->mLeft;
                    }
                    __w->mColor = __x_parent->mColor;
                    __x_parent->mColor = ft::BLACK;
                    if (__w->mLeft)
                        __w->mLeft->mColor = ft::BLACK;
                    rb_tree_right_rotate(__x_parent, __root);
                    break;
                }
            }
        }
        if (__x)
            __x->mColor = ft::BLACK;
    }
    return __y;
}