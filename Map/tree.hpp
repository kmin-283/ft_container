/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:02:26 by kmin              #+#    #+#             */
/*   Updated: 2020/11/02 17:03:03 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Node/Node.hpp"
#include <iostream>

namespace ft
{
    enum Color {BLACK, RED};
    
    struct tree_node_base
    {        
        tree_node_base *mLeft;
        tree_node_base *mRight;
        tree_node_base *mParent;
    };

    template <typename _Key, typename _Val>
    struct tree_node : public tree_node_base
    {

        std::pair<_key, _Val> mData;
        bool color;
    };

    template <typename T>
    class red_black_tree : public tree_node<T>
    {
        typedef tree_node<T>* node_pointer;
    private:
        node_pointer root;
        node_pointer TNULL;
        tree_node_base mImpl;

        void initializeNULLNode(node_pointer node, node_pointer parent)
        {
            node->mData = 0;
            node->mParent = parent;
            node->mLeft = 0;
            node->mRight = 0;
            node->color = BLACK;
        }
        
        template <typename T>
        node_pointer searchTreeHelper(node_pointer node, T key)
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
    };
} // namespace ft
