/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:40:25 by kmin              #+#    #+#             */
/*   Updated: 2020/11/22 22:07:54 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Vector/vector.hpp"

namespace ft
{
    template <typename _Tp, typename _Sequence = ft::vector<_Tp> >
    class queue
    {
    public:
        typedef typename _Sequence::value_type      value_type;
        typedef typename _Sequence::reference       reference;
        typedef typename _Sequence::const_reference const_reference;
        typedef typename _Sequence::size_type       size_type;
        typedef _Sequence                           container_type;
    protected:
        container_type c;
    public:
        explicit queue (const container_type &__c = container_type())
            : c(__c)
        {}
        bool empty() const
        {
            return (c.empty());
        }
        size_type size() const
        {
            return (c.size());
        }
        reference front()
        {
            return (c.front());
        }
        const_reference front() const
        {
            return (c.front());
        }
        reference back()
        {
            return (c.back());
        }
        const_reference back() const
        {
            return (c.back());
        }
        void push(const value_type &__x)
        {
            c.push_back(__x);
        }
        void pop()
        {
            c.erase(c.begin());
        }
    };

    template <typename _Tp, typename _Seq>
    inline bool operator==(const queue<_Tp, _Seq> &__x, const queue<_Tp, _Seq> &__y)
    {
        return (__x.c == __y.c);
    }
    template <typename _Tp, typename _Seq>
    inline bool operator<(const queue<_Tp, _Seq> &__x, const queue<_Tp, _Seq> &__y)
    {
        return (__x.c < __y.c);
    }
    template <typename _Tp, typename _Seq>
    inline bool operator!=(const queue<_Tp, _Seq> &__x, const queue<_Tp, _Seq> &__y)
    {
        return !(__x == __y);
    }
    template <typename _Tp, typename _Seq>
    inline bool operator>(const queue<_Tp, _Seq> &__x, const queue<_Tp, _Seq> &__y)
    {
        return (__y < __x);
    }
    template <typename _Tp, typename _Seq>
    inline bool operator>=(const queue<_Tp, _Seq> &__x, const queue<_Tp, _Seq> &__y)
    {
        return !(__x < __y);
    }
    template <typename _Tp, typename _Seq>
    inline bool operator<=(const queue<_Tp, _Seq> &__x, const queue<_Tp, _Seq> &__y)
    {
        return !(__y < __x);
    }
}