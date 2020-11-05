/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 10:31:47 by kmin              #+#    #+#             */
/*   Updated: 2020/11/05 16:13:48 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Node/MapNode.hpp"

namespace ft
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag: input_iterator_tag {};
	struct bidirectional_iterator_tag: forward_iterator_tag {};
	struct random_access_iterator_tag: bidirectional_iterator_tag {};

    template <typename key_type, typename value_type, typename Category = bidirectional_iterator_tag>
    class MapIterator
    {
    public:
        tree_node_base *mNode;
        // typedef key_type value_type;
        typedef key_type* pointer;
        typedef key_type& reference;
        typedef Category iterator_category;

        typedef MapIterator<key_type, value_type> _Self;
        typedef tree_node<key_type, value_type> _Node;
#ifdef __MAC__
        typedef ptrdiff_t difference_type; //mac에서 사용할 때
#endif
#ifdef __linux__
        typedef __gnu_cxx::ptrdiff_t difference_type;
#endif
        MapIterator()
            : mNode()
        {
        }
        MapIterator(tree_node_base *other)
            : mNode(other)
        {
        }
        _Self &operator=(const _Self &rhs)
        {
            this->mNode = rhs.mNode;
            return (*this);
        }
        reference operator*() const
        {
            return (static_cast<_Node *>(mNode)->mData);
        }
        pointer operator->() const
        {
            return (&static_cast<_Node *>(mNode)->mData);
        }
        _Self &operator++()
        {
            this->mNode = this->mNode->mNext;
            return (*this);
        }
        _Self operator++(int)
        {
            _Self temp = *this;
            this->mNode = this->mNode->mNext;
            return (temp);
        }
        _Self &operator--()
        {
            this->mNode = this->mNode->mPrev;
            return (*this);
        }
        _Self operator--(int)
        {
            _Self temp = *this;
            this->mNode = this->mNode->mPrev;
            return (temp);
        }
        bool operator==(const _Self &rhs) const
        {
            return (this->mNode == rhs.mNode);
        }
        bool operator!=(const _Self &rhs) const
        {
            return (this->mNode != rhs.mNode);
        }
        virtual ~MapIterator() {}
    };

    template <typename key_type, typename value_type, typename Category = bidirectional_iterator_tag>    
    class ConstMapIterator
    {
    public:
        const tree_node_base *mNode;

        // typedef key_type value_type;
        typedef const key_type* pointer;
        typedef const key_type& reference;
        typedef Category iterator_category;

        typedef ConstMapIterator<key_type, value_type> _Self;
        typedef const tree_node<key_type, value_type> _Node;
        typedef MapIterator<key_type, value_type> iterator;

#ifdef __MAC__
        typedef ptrdiff_t difference_type; //mac에서 사용할 때
#endif
#ifdef __linux__
        typedef __gnu_cxx::ptrdiff_t difference_type;
#endif
        ConstMapIterator()
            : mNode()
        {
        }
        ConstMapIterator(const tree_node_base *other)
            : mNode(other)
        {
        }
        ConstMapIterator(const iterator &rhs)
            : mNode(rhs.mNode)
        {
        }
        _Self &operator=(const _Self &rhs)
        {
            this->mNode = rhs.mNode;
            return (*this);
        }
        reference operator*() const
        {
            return (static_cast<_Node *>(mNode)->mData);
        }
        pointer operator->() const
        {
            return (&static_cast<_Node *>(mNode)->mData);
        }
        _Self &operator++()
        {
            this->mNode = this->mNode->mNext;
            return (*this);
        }
        _Self operator++(int)
        {
            _Self temp = *this;
            this->mNode = this->mNode->mNext;
            return (temp);
        }
        _Self &operator--()
        {
            this->mNode = this->mNode->mPrev;
            return (*this);
        }
        _Self operator--(int)
        {
            _Self temp = *this;
            this->mNode = this->mNode->mPrev;
            return (temp);
        }
        bool operator==(const _Self &rhs) const
        {
            return (this->mNode == rhs.mNode);
        }
        bool operator!=(const _Self &rhs) const
        {
            return (this->mNode != rhs.mNode);
        }
        virtual ~ConstMapIterator() {}
    };

    template <typename key_type, typename value_type, typename Category = bidirectional_iterator_tag>    
    class ReverseMapIterator
    {
    public:
        tree_node_base *mNode;
        // typedef key_type value_type;
        typedef key_type* pointer;
        typedef key_type& reference;
        typedef Category iterator_category;

        typedef ReverseMapIterator<key_type, value_type> _Self;
        typedef tree_node<key_type, value_type> _Node;

#ifdef __MAC__
        typedef ptrdiff_t difference_type; //mac에서 사용할 때
#endif
#ifdef __linux__
        typedef __gnu_cxx::ptrdiff_t difference_type;
#endif
        ReverseMapIterator()
            : mNode()
        {
        }
        ReverseMapIterator(tree_node_base *other)
            : mNode(other)
        {
        }
        _Self &operator=(const _Self &rhs)
        {
            this->mNode = rhs.mNode;
            return (*this);
        }
        reference operator*() const
        {
            return (static_cast<_Node *>(mNode)->mData);
        }
        pointer operator->() const
        {
            return (&static_cast<_Node *>(mNode)->mData);
        }
        _Self &operator++()
        {
            this->mNode = this->mNode->mPrev;
            return (*this);
        }
        _Self operator++(int)
        {
            _Self temp = *this;
            this->mNode = this->mNode->mPrev;
            return (temp);
        }
        _Self &operator--()
        {
            this->mNode = this->mNode->mNext;
            return (*this);
        }
        _Self operator--(int)
        {
            _Self temp = *this;
            this->mNode = this->mNode->mNext;
            return (temp);
        }
        bool operator==(const _Self &rhs) const
        {
            return (this->mNode == rhs.mNode);
        }
        bool operator!=(const _Self &rhs) const
        {
            return (this->mNode != rhs.mNode);
        }
        virtual ~ReverseMapIterator() {}
    };

    template <typename key_type, typename value_type, typename Category = bidirectional_iterator_tag>    
    class ConstReverseMapIterator
    {
    public:
        const tree_node_base *mNode;
        // typedef key_type value_type;
        typedef const key_type* pointer;
        typedef const key_type& reference;
        typedef Category iterator_category;

        typedef ConstReverseMapIterator<key_type, value_type> _Self;
        typedef const tree_node<key_type, value_type> _Node;

#ifdef __MAC__
        typedef ptrdiff_t difference_type; //mac에서 사용할 때
#endif
#ifdef __linux__
        typedef __gnu_cxx::ptrdiff_t difference_type;
#endif
        ConstReverseMapIterator()
            : mNode()
        {
        }
        ConstReverseMapIterator(tree_node_base *other)
            : mNode(other)
        {
        }
        _Self &operator=(const _Self &rhs)
        {
            this->mNode = rhs.mNode;
            return (*this);
        }
        reference operator*() const
        {
            return (static_cast<_Node *>(mNode)->mData);
        }
        pointer operator->() const
        {
            return (&static_cast<_Node *>(mNode)->mData);
        }
        _Self &operator++()
        {
            this->mNode = this->mNode->mPrev;
            return (*this);
        }
        _Self operator++(int)
        {
            _Self temp = *this;
            this->mNode = this->mNode->mPrev;
            return (temp);
        }
        _Self &operator--()
        {
            this->mNode = this->mNode->mNext;
            return (*this);
        }
        _Self operator--(int)
        {
            _Self temp = *this;
            this->mNode = this->mNode->mNext;
            return (temp);
        }
        bool operator==(const _Self &rhs) const
        {
            return (this->mNode == rhs.mNode);
        }
        bool operator!=(const _Self &rhs) const
        {
            return (this->mNode != rhs.mNode);
        }
        virtual ~ConstReverseMapIterator() {}
    };
} // namespace ft

template <typename key_type, typename value_type>
inline bool operator==(const ft::MapIterator<key_type, value_type> &x, const ft::ConstMapIterator<key_type, value_type> &y)
{
    return (x.mNode == y.mNode);
}
template <typename key_type, typename value_type>
inline bool operator!=(const ft::MapIterator<key_type, value_type> &x, const ft::ConstMapIterator<key_type, value_type> &y)
{
    return (x.mNode != y.mNode);
}
template <typename key_type, typename value_type>
inline bool operator>(const ft::MapIterator<key_type, value_type> &x, const ft::ConstMapIterator<key_type, value_type> &y)
{
    return (x.mNode > y.mNode);
}
template <typename key_type, typename value_type>
inline bool operator>=(const ft::MapIterator<key_type, value_type> &x, const ft::ConstMapIterator<key_type, value_type> &y)
{
    return (x.mNode >= y.mNode);
}template <typename key_type, typename value_type>
inline bool operator<(const ft::MapIterator<key_type, value_type> &x, const ft::ConstMapIterator<key_type, value_type> &y)
{
    return (x.mNode < y.mNode);
}
template <typename key_type, typename value_type>
inline bool operator<=(const ft::MapIterator<key_type, value_type> &x, const ft::ConstMapIterator<key_type, value_type> &y)
{
    return (x.mNode <= y.mNode);
}