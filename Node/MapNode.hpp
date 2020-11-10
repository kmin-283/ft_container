/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapNode.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 16:10:50 by kmin              #+#    #+#             */
/*   Updated: 2020/11/10 16:53:16 by kmin             ###   ########.fr       */
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
        typedef rb_tree_node_base* base_ptr;
        typedef const rb_tree_node_base* const_base_ptr;
        
        rb_tree_color       m_color;
        rb_tree_node_base   *mLeft;
        rb_tree_node_base   *mRight;
        rb_tree_node_base   *mParent;

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
        typedef rb_tree_node<_Val>* Link_type;
        _Val mValueField;
    };
} // namespace ft
