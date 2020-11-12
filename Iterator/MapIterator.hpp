/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 10:31:47 by kmin              #+#    #+#             */
/*   Updated: 2020/11/12 16:12:33 by kmin             ###   ########.fr       */
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

    template <typename _Tp, typename Category = bidirectional_iterator_tag>
    class MapIterator
    {
    public:
        typedef _Tp value_type;
        typedef _Tp* pointer;
        typedef _Tp& reference;
        typedef Category iterator_category;

        typedef MapIterator<_Tp>                _Self;
        typedef rb_tree_node_base::base_ptr     _Base_ptr;
        typedef rb_tree_node<_Tp>*              _Link_type;

        _Base_ptr mNode;
#ifdef __APPLE__
        typedef ptrdiff_t difference_type; //mac에서 사용할 때
#endif
#ifdef __linux__
        typedef __gnu_cxx::ptrdiff_t difference_type;
#endif
        MapIterator()
            : mNode()
        {
        }
        explicit MapIterator(_Link_type __x)
            : mNode(__x)
        {
        }
        _Self &operator=(const _Self &rhs)
        {
            this->mNode = rhs.mNode;
            return (*this);
        }
        reference operator*() const
        {
            return (static_cast<_Link_type>(mNode)->mValueField);
        }
        pointer operator->() const
        {
            return (&static_cast<_Link_type>(mNode)->mValueField);
        }
        _Self &operator++()
        {
            this->mNode = rb_tree_increment(this->mNode);
            return (*this);
        }
        _Self operator++(int)
        {
            _Self temp = *this;
            this->mNode = rb_tree_increment(this->mNode);
            return (temp);
        }
        _Self &operator--()
        {
            this->mNode = rb_tree_decrement(this->mNode);
            return (*this);
        }
        _Self operator--(int)
        {
            _Self temp = *this;
            this->mNode = rb_tree_decrement(this->mNode);
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

    template <typename _Tp, typename Category = bidirectional_iterator_tag>
    class ConstMapIterator
    {
    public:
        typedef _Tp value_type;
        typedef const _Tp* pointer;
        typedef const _Tp& reference;
        typedef Category iterator_category;

        typedef MapIterator<_Tp>                            iterator;

        typedef ConstMapIterator<_Tp>                       _Self;
        typedef rb_tree_node_base::const_base_ptr           _Base_ptr;
        typedef const rb_tree_node<_Tp>*                    _Link_type;

        _Base_ptr mNode;
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
        explicit ConstMapIterator(_Link_type __x)
            : mNode(__x)
        {
        }
        ConstMapIterator(const iterator &__it)
            : mNode(__it.mNode)
        {
        }
        _Self &operator=(const _Self &rhs)
        {
            this->mNode = rhs.mNode;
            return (*this);
        }
        reference operator*() const
        {
            return (static_cast<_Link_type>(mNode)->mValueField);
        }
        pointer operator->() const
        {
            return (&static_cast<_Link_type>(mNode)->mValueField);
        }
        _Self &operator++()
        {
            this->mNode = rb_tree_increment(this->mNode);
            return (*this);
        }
        _Self operator++(int)
        {
            _Self temp = *this;
            this->mNode = rb_tree_increment(this->mNode);
            return (temp);
        }
        _Self &operator--()
        {
            this->mNode = rb_tree_decrement(this->mNode);
            return (*this);
        }
        _Self operator--(int)
        {
            _Self temp = *this;
            this->mNode = rb_tree_decrement(this->mNode);
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

    template <typename _Tp, typename Category = bidirectional_iterator_tag>
    class ReverseMapIterator
    {
    public:
        typedef _Tp value_type;
        typedef _Tp* pointer;
        typedef _Tp& reference;
        typedef Category iterator_category;

        typedef MapIterator<_Tp>                            iterator;

        typedef ReverseMapIterator<_Tp> _Self;
        typedef rb_tree_node_base::base_ptr    _Base_ptr;
        typedef rb_tree_node<_Tp>*                  _Link_type;

        _Base_ptr mNode;
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
        explicit ReverseMapIterator(_Link_type __x)
            : mNode(__x)
        {
        }
        ReverseMapIterator(const iterator &__it)
            : mNode(__it.mNode)
        {
        }
        _Self &operator=(const _Self &rhs)
        {
            this->mNode = rhs.mNode;
            return (*this);
        }
        reference operator*() const
        {
            return (static_cast<_Link_type>(mNode)->mValueField);
        }
        pointer operator->() const
        {
            return (&static_cast<_Link_type>(mNode)->mValueField);
        }
        _Self &operator++()
        {
            this->mNode = rb_tree_increment(this->mNode);
            return (*this);
        }
        _Self operator++(int)
        {
            _Self temp = *this;
            this->mNode = rb_tree_increment(this->mNode);
            return (temp);
        }
        _Self &operator--()
        {
            this->mNode = rb_tree_decrement(this->mNode);
            return (*this);
        }
        _Self operator--(int)
        {
            _Self temp = *this;
            this->mNode = rb_tree_decrement(this->mNode);
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

    template <typename _Tp, typename Category = bidirectional_iterator_tag>
    class ConstReverseMapIterator
    {
    public:
        typedef _Tp value_type;
        typedef const _Tp* pointer;
        typedef const _Tp& reference;
        typedef Category iterator_category;

        typedef MapIterator<_Tp>                            iterator;

        typedef ConstReverseMapIterator<_Tp>                       _Self;
        typedef rb_tree_node_base::const_base_ptr      _Base_ptr;
        typedef const rb_tree_node<_Tp>*                    _Link_type;

        _Base_ptr mNode;
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
        explicit ConstReverseMapIterator(_Link_type __x)
            : mNode(__x)
        {
        }
        ConstReverseMapIterator(const iterator &__it)
            : mNode(__it.mNode)
        {
        }
        _Self &operator=(const _Self &rhs)
        {
            this->mNode = rhs.mNode;
            return (*this);
        }
        reference operator*() const
        {
            return (static_cast<_Link_type>(mNode)->mValueField);
        }
        pointer operator->() const
        {
            return (&static_cast<_Link_type>(mNode)->mValueField);
        }
        _Self &operator++()
        {
            this->mNode = rb_tree_increment(this->mNode);
            return (*this);
        }
        _Self operator++(int)
        {
            _Self temp = *this;
            this->mNode = rb_tree_increment(this->mNode);
            return (temp);
        }
        _Self &operator--()
        {
            this->mNode = rb_tree_decrement(this->mNode);
            return (*this);
        }
        _Self operator--(int)
        {
            _Self temp = *this;
            this->mNode = rb_tree_decrement(this->mNode);
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

template <typename _Val>
inline bool operator==(const ft::MapIterator<_Val> &x, const ft::ConstMapIterator<_Val> &y)
{
    return (x.mNode == y.mNode);
}
template <typename _Val>
inline bool operator!=(const ft::MapIterator<_Val> &x, const ft::ConstMapIterator<_Val> &y)
{
    return (x.mNode != y.mNode);
}
