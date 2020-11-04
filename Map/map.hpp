/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:20:31 by kmin              #+#    #+#             */
/*   Updated: 2020/11/04 20:00:07 by kmin             ###   ########.fr       */
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
        typedef red_black_tree<key_type, value_type, key_compare, _Pair_alloc_type> _Rep_type;

        // actual tree structure
        _Rep_type _M_t; // _M_t가 무슨 의미인지 알 수 없음.... 이름을 바꾸자
    public:
        typedef typename _Pair_alloc_type::pointer                      pointer;
        typedef typename _Pair_alloc_type::const_pointer                const_pointer;
        typedef typename _Pair_alloc_type::reference                    reference;
        typedef typename _Pair_alloc_type::const_reference              const_reference;
        // typedef typename _Rep_type::iterator                            iterator;
        // typedef typename _Rep_type::const_iterator                      const_iterator;
        // typedef typename _Rep_type::size_type                           size_type;
        // typedef typename _Rep_type::difference_type                     difference_type;
        // typedef typename _Rep_type::reverse_iterator                    reverse_iterator;
        // typedef typename _Rep_type::const_reverse_iterator              const_reverse_iterator;


        explicit map(const _Compare &__comp = key_compare(), const allocator_type &__a = allocator_type())
            : _M_t(__comp, __a)
        {
        }
        template <typename _InputIterator>
        map(_InputIterator __first, _InputIterator __last, const key_compare &__comp = key_compare(), const allocator_type &__a = allocator_type()))
            : _M_t()
        {
            _M_t.nInsertUnique(__first, __last);
        }
        map(const map &__x) // copy constructor
            : _M_t(__x._M_t)
        {}
        ~map()
        {}
    };
}