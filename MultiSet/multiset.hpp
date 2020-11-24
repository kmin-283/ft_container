/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiset.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 10:58:12 by kmin              #+#    #+#             */
/*   Updated: 2020/11/24 16:47:33 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "../Map/tree.hpp"

namespace ft
{
    template <typename _Key, typename _Compare = std::less<_Key>, typename _Alloc = std::allocator<_Key> >
    class multiset
    {
    public:
        typedef _Key                        key_type;
        typedef _Key                        value_type;
        typedef _Compare                    key_compare;
        typedef _Compare                    value_compare;
        typedef _Alloc                      allocator_type;
    private:
        typedef typename _Alloc::template rebind<_Key>::other _Key_alloc_type;
        typedef red_black_tree<key_type, value_type, std::_Identity<value_type>, key_compare, _Key_alloc_type> _Rep_type;
        _Rep_type mTree;
    public:
        typedef typename _Key_alloc_type::pointer               pointer;
        typedef typename _Key_alloc_type::const_pointer         const_pointer;
        typedef typename _Key_alloc_type::reference             reference;
        typedef typename _Key_alloc_type::const_reference       const_reference;
        typedef typename _Rep_type::iterator                    iterator;
        typedef typename _Rep_type::const_iterator              const_iterator;
        typedef typename _Rep_type::reverse_iterator            reverse_iterator;
        typedef typename _Rep_type::const_reverse_iterator      const_reverse_iterator;
        typedef typename _Rep_type::size_type                   size_type;
        typedef typename _Rep_type::difference_type             difference_type;
        explicit multiset(const key_compare &__comp = key_compare(), const allocator_type &__a = allocator_type())
            : mTree(__comp, __a)
        {}
        template <class InputIterator>
        multiset (InputIterator __first, InputIterator __last, const key_compare &__comp = key_compare(), const allocator_type &__a = allocator_type())
            : mTree(__comp, __a)
        {
            mTree.mInsertEqual(__first, __last);
        }
        multiset (const multiset &__x)
            : mTree(__x.mTree)
        {}
        multiset& operator=(const multiset &__x)
        {
            mTree = __x.mTree;
            return (*this);
        }
        key_compare key_comp() const
        {
            return (mTree.key_comp());
        }
        value_compare value_comp() const
        {
            return (mTree.key_comp());
        }
        allocator_type getAllocator() const
        {
            return (mTree.getAlloctor());
        }
        iterator begin()
        {
            return (mTree.begin());
        }
        iterator end()
        {
            return (mTree.end());
        }
        const_iterator begin() const
        {
            return (mTree.begin());
        }
        const_iterator end() const
        {
            return (mTree.end());
        }
        reverse_iterator rbegin()
        {
            return (mTree.rbegin());
        }
        reverse_iterator rend()
        {
            return (mTree.rend());
        }
        const_reverse_iterator rbegin() const
        {
            return (mTree.rbegin());
        }
        const_reverse_iterator rend() const
        {
            return (mTree.rend());
        }
        bool empty() const
        {
            return (mTree.empty());
        }
        size_type size() const
        {
            return (mTree.size());
        }
        size_type max_size() const
        {
            return (mTree.max_size());
        }
        void swap(multiset &__x)
        {
            mTree.swap(__x.mTree);
        }
        iterator insert(const value_type &__x)
        {
            return (mTree.mInsertEqual(__x));
        }
        iterator insert(iterator __position, const value_type &__x)
        {
            return (mTree.mInsertEqual(__position, __x));
        }
        template <typename _InputIteraror>
        void insert(_InputIteraror __first, _InputIteraror __last)
        {
            mTree.mInsertEqual(__first, __last);
        }
        void erase(iterator __position)
        {
            mTree.erase(__position);
        }
        size_type erase(const value_type &__val)
        {
            return (mTree.erase(__val));
        }
        void erase(iterator __first, iterator __last)
        {
            mTree.erase(__first, __last);
        }
        void clear()
        {
            mTree.clear();
        }
        iterator find(const key_type &__x)
        {
            return (mTree.find(__x));
        }
        const_iterator find(const key_type &__x) const
        {
            return (mTree.find(__x));
        }
        size_type count(const key_type &__x) const
        {
            return (mTree.find(__x) == mTree.end() ? 0 : 1);
        }
        iterator lower_bound(const key_type &__x)
        {
            return (mTree.lower_bound(__x));
        }
        const_iterator lower_bound(const key_type &__x) const
        {
            return (mTree.lower_bound(__x));
        }
        iterator upper_bound(const key_type &__x)
        {
            return (mTree.upper_bound(__x));
        }
        const_iterator upper_bound(const key_type &__x) const
        {
            return (mTree.upper_bound(__x));
        }
        std::pair<iterator, iterator> equal_range (const value_type& __x)
        {
            return (mTree.equal_range(__x));
        }
        std::pair<const_iterator, const_iterator> equal_range (const value_type& __x) const
        {
            return (mTree.equal_range(__x));
        }
        template<typename _K1, typename _C1, typename _A1>
        friend bool operator==(const multiset<_K1, _C1, _A1> &__x, const multiset<_K1, _C1, _A1> &__y);
        template<typename _K1, typename _C1, typename _A1>
        friend bool operator<(const multiset<_K1, _C1, _A1> &__x, const multiset<_K1, _C1, _A1> &__y);
    };
    template<typename _Key, typename _Compare, typename _Alloc>
    inline bool operator==(const multiset<_Key, _Compare, _Alloc> &__x, const multiset<_Key, _Compare, _Alloc> &__y)
    {
        return (__x.mTree == __y.mTree);
    }
    template<typename _Key, typename _Compare, typename _Alloc>
    inline bool operator<(const multiset<_Key, _Compare, _Alloc> &__x, const multiset<_Key, _Compare, _Alloc> &__y)
    {
        return (__x.mTree < __y.mTree);
    }
    template<typename _Key, typename _Compare, typename _Alloc>
    inline bool operator!=(const multiset<_Key, _Compare, _Alloc> &__x, const multiset<_Key, _Compare, _Alloc> &__y)
    {
        return !(__x == __y);
    }
    template<typename _Key, typename _Compare, typename _Alloc>
    inline bool operator>(const multiset<_Key, _Compare, _Alloc> &__x, const multiset<_Key, _Compare, _Alloc> &__y)
    {
        return (__y < __x);
    }
    template<typename _Key, typename _Compare, typename _Alloc>
    inline bool operator<=(const multiset<_Key, _Compare, _Alloc> &__x, const multiset<_Key, _Compare, _Alloc> &__y)
    {
        return !(__y < __x);
    }
    template<typename _Key, typename _Compare, typename _Alloc>
    inline bool operator>=(const multiset<_Key, _Compare, _Alloc> &__x, const multiset<_Key, _Compare, _Alloc> &__y)
    {
        return !(__x < __y);
    }
} // namespace ft

