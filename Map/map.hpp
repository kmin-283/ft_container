/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:20:31 by kmin              #+#    #+#             */
/*   Updated: 2020/11/02 17:02:18 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <memory>
#include "tree.hpp"

namespace ft
{
    template <typename _Key, typename _Tp, typename _Compare = std::less<_Key>, typename _Alloc = std::allocator<std::pair<const _Key, _Tp> > >
    class map
    {
    public:
        typedef _Key                        key_type;
        typedef _Tp                         mappedn_type;
        typedef std::pair<const _Key, _Tp>  value_type;
        typedef _Compare                    key_compare;
        typedef _Alloc                      allocator_type;
    
    private:
        typedef typename _Alloc::value_type             _Alloc_value_type;
    public:
        class value_compare : public std::binary_function<value_type, value_type, bool>
        {
            friend class map<_Key, _Tp, _Compare, _Alloc>;
        protected:
            _Compare comp;
            
            value_compare(_Compare __c)
                : comp(__c)
            {}
        public:
            bool operator()(const value_type &__x, const value_type &__y) const
            {
                return comp(__x.first, __y.first);
            }
        };
    private:
        typedef typename _Alloc::template rebind<value_type>:: other _Pair_alloc_type;
        typedef red_black_tree<key_type, value_type> _Rep_type;
    };
}