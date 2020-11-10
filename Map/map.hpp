/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:20:31 by kmin              #+#    #+#             */
/*   Updated: 2020/11/10 16:53:28 by kmin             ###   ########.fr       */
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
        typedef _Tp                         mapped_type;
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
        typedef typename _Rep_type::iterator                            iterator;
        typedef typename _Rep_type::const_iterator                      const_iterator;
        typedef typename _Rep_type::size_type                           size_type;
        typedef typename _Rep_type::difference_type                     difference_type;
        typedef typename _Rep_type::reverse_iterator                    reverse_iterator;
        typedef typename _Rep_type::const_reverse_iterator              const_reverse_iterator;


        explicit map(const _Compare &__comp = key_compare(), const allocator_type &__a = allocator_type())
            : _M_t(__comp, __a)
        {
        }
        template <typename _InputIterator>
        map(_InputIterator __first, _InputIterator __last, const key_compare &__comp = key_compare(), const allocator_type &__a = allocator_type())
            : _M_t()
        {
            _M_t.mInsertUnique(__first, __last);
        }
        map(const map &__x) // copy constructor
            : _M_t(__x._M_t)
        {}
        map &operator=(const map &__x)
        {
            _M_t = __x._M_t;
            return (*this);
        }
        allocator_type getAllocator() const
        {
            return (_M_t.getAllocator());
        }
        iterator begin()
        {
            return (_M_t.begin());
        }
        const_iterator begin() const
        {
            return (_M_t.begin());
        }
        iterator end()
        {
            return (_M_t.end());
        }
        const_iterator end() const
        {
            return (_M_t.end());
        }
        reverse_iterator rbegin()
        {
            return (_M_t.rbegin());
        }
        const_reverse_iterator rbegin() const
        {
            return (_M_t.rbegin());
        }
        reverse_iterator rend()
        {
            return (_M_t.rend());
        }
        const_reverse_iterator rend() const
        {
            return (_M_t.rend());
        }
        bool empty() const
        {
            return (_M_t.empty());
        }
        size_type size() const
        {
            return (_M_t.size());
        }
        size_type max_size() const
        {
            return (_M_t.max_size());
        }
        mapped_type &operator[](const key_type &__k)
        {
            iterator __i = std::lower_bound(__k);
            
            if (__i == end() || key_comp()(__k, (*__i).first))
                __i = insert(__i, value_type(__k, mapped_type()));
            return (*__i).second;
        }
        std::pair<iterator, bool> insert(const value_type &__val)
        {
            return (_M_t.mInsertUnique(__val));
        }
        iterator insert(iterator __position, const value_type &__x)
        {
            return (_M_t.mInsertUnique(__position, __x));
        }
        template <typename _InputIterator>
        void insert(_InputIterator __first, _InputIterator __last)
        {
            _M_t.mInsertUnique(__first, __last);
        }
        void erase(iterator __position)
        {
            _M_t.erase(__position);
        }
        size_type erase(const key_type &__k)
        {
            return (_M_t.erase(__k));
        }
        void erase(iterator __first, iterator __last)
        {
            _M_t.erase(__first, __last);
        }
        void swap(map& __x)
        {
            _M_t.swap(__x._M_t);
        }
        void clear()
        {
            _M_t.clear();
        }
        key_compare key_comp() const
        {
            return (_M_t.key_comp());
        }
        value_compare value_comp() const
        {
            return (value_compare(_M_t.key_comp()));
        }
        iterator find(const key_type &__k)
        {
            return (_M_t.find(__k));
        }
        const_iterator find(const key_type &__k) const
        {
            return (_M_t.find(__k));
        }
        size_type count(const key_type &__k) const
        {
            return (_M_t.find(__k) == _M_t.end() ? 0 : 1);
        }
        iterator lower_bound(const key_type &__k)
        {
            return (_M_t.lower_bound(__k));
        }
        const_iterator lower_bound(const key_type &__k) const
        {
            return (_M_t.lower_bound(__k));
        }
        iterator upper_bound(const key_type &__k)
        {
            return (_M_t.upper_bound(__k));
        }
        const_iterator upper_bound(const key_type &__k) const
        {
            return (_M_t.upper_bound(__k));
        }
        std::pair<const_iterator, const_iterator> equal_range(const key_type &__k) const
        {
            return (_M_t.equal_range(__k));
        }
        std::pair<iterator, iterator> equal_range (const key_type &__k)
        {
            return (_M_t.equal_range(__k));
        }

        template<typename _K1, typename _T1, typename _C1, typename _A1>
        friend bool operator==(const map<_K1, _T1, _C1, _A1>&, const map<_K1, _T1, _C1, _A1>&)
        {
            
        }
        template<typename _K1, typename _T1, typename _C1, typename _A1>
        friend bool operator<(const map<_K1, _T1, _C1, _A1>&, const map<_K1, _T1, _C1, _A1>&)
        {
            
        }
        ~map()
        {}
    };
}