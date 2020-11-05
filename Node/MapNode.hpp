/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapNode.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 16:10:50 by kmin              #+#    #+#             */
/*   Updated: 2020/11/05 16:11:01 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
} // namespace ft
