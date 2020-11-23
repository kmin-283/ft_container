/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multimap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 20:53:02 by kmin              #+#    #+#             */
/*   Updated: 2020/11/23 23:47:03 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <memory>
#include "../Map/tree.hpp"

namespace ft
{
    template <typename _Key, typename _Tp, typename _Compare = std::less<_Key>, typename _Alloc = std::allocator<std::pair<const _Key, _Tp> > >
    class multimap
    {
    public:
        typedef _Key                                          key_type;
        typedef _Tp                                           mapped_type;
        typedef std::pair<const _Key, _Tp>                    value_type;
        typedef _Compare                                      key_compare;
        typedef _Alloc                                        allocator_type;

        class value_compare : public std::binary_function<value_type, value_type, bool>
        {
            friend class multimap<_Key, _Tp, _Compare, _Alloc>;
        protected:
            _Compare comp;

            value_compare(_Compare __c)
                : comp(__c)
            {}
        public:
            bool operator()(const value_type &__x, const value_type &__y) const
            {
                return (comp(__x.first, __y.first));
            }
        };
    private:
        typedef typename _Alloc::template rebind<value_type>::other _Pair_alloc_type;
        typedef red_black_tree<key_type, value_type, ft::_Select1st<value_type>, key_compare, _Pair_alloc_type> _Rep_type;
        _Rep_type mTree;
    public:
        typedef typename _Pair_alloc_type::pointer                  pointer;
        typedef typename _Pair_alloc_type::const_pointer            const_pointer;
        typedef typename _Pair_alloc_type::reference                reference;
        typedef typename _Pair_alloc_type::const_reference          const_reference;
        typedef typename _Rep_type::iterator                        iterator;
        typedef typename _Rep_type::const_iterator                  const_iterator;
        typedef typename _Rep_type::reverse_iterator                reverse_iterator;
        typedef typename _Rep_type::const_reverse_iterator          const_reverse_iterator;
        typedef typename _Rep_type::size_type                       size_type;
        typedef typename _Rep_type::difference_type                 difference_type;

        explicit multimap(const _Compare &__comp = key_compare(), const allocator_type &__a = allocator_type())
            : mTree(__comp, __a)
        {}
        template <typename _InputIterator>
        multimap(_InputIterator __first, _InputIterator __last, const key_compare &__comp = key_compare(), const allocator_type &__a = allocator_type())
            : mTree(__comp, __a)
        {
            mTree.mInsertEqual(__first, __last);
        }
        multimap(const multimap &__x) // copy constructor
            : mTree(__x.mTree)
        {}
        multimap &operator=(const multimap &__x)
        {
            mTree = __x.mTree;
            return (*this);
        }
        allocator_type getAllocator() const
        {
            return (mTree.getAllocator());
        }
        iterator begin()
        {
            return (mTree.begin());
        }
        const_iterator begin() const
        {
            return (mTree.begin());
        }
        iterator end()
        {
            return (mTree.end());
        }
        const_iterator end() const
        {
            return (mTree.end());
        }
        reverse_iterator rbegin()
        {
            return (mTree.rbegin());
        }
        const_reverse_iterator rbegin() const
        {
            return (mTree.rbegin());
        }
        reverse_iterator rend()
        {
            return (mTree.rend());
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
        iterator insert(const value_type &__val)
        {
            return (mTree.mInsertEqual(__val));
        }
        iterator insert(iterator __position, const value_type &__x)
        {
            return (mTree.mInsertEqual(__position, __x));
        }
        template <typename _InputIterator>
        void insert(_InputIterator __first, _InputIterator __last)
        {
            mTree.mInsertEqual(__first, __last);
        }
        void erase(iterator __position)
        {
            mTree.erase(__position);
        }
        size_type erase(const key_type &__k)
        {
            return (mTree.erase(__k));
        }
        void erase(iterator __first, iterator __last)
        {
            mTree.erase(__first, __last);
        }
        void swap(multimap& __x)
        {
            mTree.swap(__x.mTree);
        }
        void clear()
        {
            mTree.clear();
        }
        key_compare key_comp() const
        {
            return (mTree.key_comp());
        }
        value_compare value_comp() const
        {
            return (value_compare(mTree.key_comp()));
        }
        iterator find(const key_type &__k)
        {
            return (mTree.find(__k));
        }
        const_iterator find(const key_type &__k) const
        {
            return (mTree.find(__k));
        }
        size_type count(const key_type &__k) const
        {
            return (mTree.find(__k) == mTree.end() ? 0 : 1);
        }
        iterator lower_bound(const key_type &__k)
        {
            return (mTree.lower_bound(__k));
        }
        const_iterator lower_bound(const key_type &__k) const
        {
            return (mTree.lower_bound(__k));
        }
        iterator upper_bound(const key_type &__k)
        {
            return (mTree.upper_bound(__k));
        }
        const_iterator upper_bound(const key_type &__k) const
        {
            return (mTree.upper_bound(__k));
        }
        std::pair<const_iterator, const_iterator> equal_range(const key_type &__k) const
        {
            return (mTree.equal_range(__k));
        }
        std::pair<iterator, iterator> equal_range (const key_type &__k)
        {
            return (mTree.equal_range(__k));
        }

        template<typename _K1, typename _T1, typename _C1, typename _A1>
        friend bool operator==(const multimap<_K1, _T1, _C1, _A1>&, const multimap<_K1, _T1, _C1, _A1>&);
        template<typename _K1, typename _T1, typename _C1, typename _A1>
        friend bool operator<(const multimap<_K1, _T1, _C1, _A1>&, const multimap<_K1, _T1, _C1, _A1>&);
        ~multimap()
        {}
    };

    template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
    inline bool operator==(const ft::multimap<_Key, _Tp, _Compare, _Alloc> &__x,
                            const ft::multimap<_Key, _Tp, _Compare, _Alloc> &__y)
    {
        return (__x.mTree == __y.mTree);
    }
    template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
    inline bool operator!=(const ft::multimap<_Key, _Tp, _Compare, _Alloc> &__x,
                            const ft::multimap<_Key, _Tp, _Compare, _Alloc> &__y)
    {
        return (!(__x == __y));
    }
    template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
    inline bool operator<(const ft::multimap<_Key, _Tp, _Compare, _Alloc> &__x,
                            const ft::multimap<_Key, _Tp, _Compare, _Alloc> &__y)
    {
        return (__x.mTree < __y.mTree);
    }
    template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
    inline bool operator>(const ft::multimap<_Key, _Tp, _Compare, _Alloc> &__x,
                            const ft::multimap<_Key, _Tp, _Compare, _Alloc> &__y)
    {
        return (__y.mTree < __x.mTree);
    }
    template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
    inline bool operator<=(const ft::multimap<_Key, _Tp, _Compare, _Alloc> &__x,
                            const ft::multimap<_Key, _Tp, _Compare, _Alloc> &__y)
    {
        return (!(__x.mTree < __y.mTree));
    }
    template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
    inline bool operator>=(const ft::multimap<_Key, _Tp, _Compare, _Alloc> &__x,
                            const ft::multimap<_Key, _Tp, _Compare, _Alloc> &__y)
    {
        return (!(__y.mTree < __x.mTree));
    }
    template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
    inline void swap(ft::multimap<_Key, _Tp, _Compare, _Alloc> &__x,
                            ft::multimap<_Key, _Tp, _Compare, _Alloc> &__y)
    {
        __x.swap(__y);
    }
} // namespace ft
