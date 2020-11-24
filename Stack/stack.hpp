/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:02:10 by kmin              #+#    #+#             */
/*   Updated: 2020/11/24 16:42:50 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "../Vector/vector.hpp"

namespace ft
{
    template <typename _Tp, typename _Sequence = ft::vector<_Tp> >
    class stack
    {
        typedef typename _Sequence::value_type _Sequence_value_type;

    public:
        typedef typename _Sequence::value_type value_type;
        typedef typename _Sequence::reference reference;
        typedef typename _Sequence::const_reference const_reference;
        typedef typename _Sequence::size_type size_type;
        typedef _Sequence container_type;

    protected:
        container_type c;

    public:
        explicit stack(const container_type &__c = container_type())
            : c(__c)
        {
        }
        bool empty() const
        {
            return (c.empty());
        }
        size_type size() const
        {
            return (c.size());
        }
        reference top()
        {
            return (c.back());
        }
        void push(const value_type &__x)
        {
            c.push_back(__x);
        }
        void pop()
        {
            c.pop_back();
        }
    };
    template <typename _Tp, typename _Seq>
    inline bool operator==(const stack<_Tp, _Seq> &__x, const stack<_Tp, _Seq> &__y)
    {
        return (__x.c == __y.c);
    }
    template <typename _Tp, typename _Seq>
    inline bool operator<(const stack<_Tp, _Seq> &__x, const stack<_Tp, _Seq> &__y)
    {
        return (__x.c < __y.c);
    }
    template <typename _Tp, typename _Seq>
    inline bool operator!=(const stack<_Tp, _Seq> &__x, const stack<_Tp, _Seq> &__y)
    {
        return !(__x == __y);
    }
    template <typename _Tp, typename _Seq>
    inline bool operator>(const stack<_Tp, _Seq> &__x, const stack<_Tp, _Seq> &__y)
    {
        return (__y < __x);
    }
    template <typename _Tp, typename _Seq>
    inline bool operator>=(const stack<_Tp, _Seq> &__x, const stack<_Tp, _Seq> &__y)
    {
        return !(__x < __y);
    }
    template <typename _Tp, typename _Seq>
    inline bool operator<=(const stack<_Tp, _Seq> &__x, const stack<_Tp, _Seq> &__y)
    {
        return !(__y < __x);
    }
} // namespace ft

