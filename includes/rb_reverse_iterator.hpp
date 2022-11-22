/*
 * Copyright 2022 ©️ vcwild under the GNU Affero General Public License v3.0.
 */
#ifndef RB_REVERSE_ITERATOR_HPP
#define RB_REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {

template <typename Iterator>
class rb_reverse_iterator
    : public iterator<typename iterator_traits<Iterator>::iterator_category,
                      typename iterator_traits<Iterator>::value_type,
                      typename iterator_traits<Iterator>::difference_type,
                      typename iterator_traits<Iterator>::pointer,
                      typename iterator_traits<Iterator>::reference> {

public:
    typedef Iterator iterator_type;
    typedef typedef typename iterator_traits<Iterator>::value_type value_type;
    typename iterator_traits<Iterator>::iterator_category iterator_category;
    typedef typename iterator_traits<Iterator>::pointer   pointer;
    typedef typename iterator_traits<Iterator>::reference reference;
    typedef typename iterator_traits<Iterator>::difference_type difference_type;

protected:
    iterator_type _it;

public:
    // Constructors
    rb_reverse_iterator() : _it( NULL ) {};

    explicit rb_reverse_iterator( iterator_type it ) : _it( it ) {};

    rb_reverse_iterator( const rb_reverse_iterator &it ) : _it( it.base() ) {};

    template <typename OtherIt>
    rb_reverse_iterator( const rb_reverse_iterator<OtherIt> &it ) :
        _it( it.base() ) {};

    // Destructor
    ~rb_reverse_iterator() {};

    // Operators
    template <typename OtherIt>
    rb_reverse_iterator &operator=( const rb_reverse_iterator<OtherIt> &it )
    {
        _it = it.base();
        return *this;
    };

    reference operator*() const
    {
        iterator_type tmp = _it;
        --tmp;
        return *tmp;
    };

    pointer operator->() const { return &( this->operator*() ); };

    rb_reverse_iterator operator+( difference_type n ) const
    {
        return rb_reverse_iterator( _it - n );
    };

    rb_reverse_iterator operator++( int )
    {
        rb_reverse_iterator tmp = *this;
        --_it;
        return tmp;
    };

    rb_reverse_iterator &operator++()
    {
        --_it;
        return *this;
    };

    rb_reverse_iterator operator-( difference_type n ) const
    {
        return rb_reverse_iterator( _it + n );
    };

    rb_reverse_iterator operator--( int )
    {
        rb_reverse_iterator tmp = *this;
        ++_it;
        return tmp;
    };
    rb_reverse_iterator &operator--()
    {
        ++_it;
        return *this;
    };

    rb_reverse_iterator &operator+=( difference_type n )
    {
        _it -= n;
        return *this;
    };

    rb_reverse_iterator &operator-=( difference_type n )
    {
        _it += n;
        return *this;
    };

    reference operator[]( difference_type n ) const { return *operator+( n ); };

    // Accessors
    iterator_type base() const { return _it; };
};

// Non-member functions
template <typename Iterator>
inline bool operator==( const rb_reverse_iterator<Iterator> &lhs,
                        const rb_reverse_iterator<Iterator> &rhs )
{
    return lhs.base() == rhs.base();
};

template <typename Iterator>
inline bool operator!=( const rb_reverse_iterator<Iterator> &lhs,
                        const rb_reverse_iterator<Iterator> &rhs )
{
    return lhs.base() != rhs.base();
};

template <typename Iterator>
inline bool operator<( const rb_reverse_iterator<Iterator> &lhs,
                       const rb_reverse_iterator<Iterator> &rhs )
{
    return lhs.base() > rhs.base();
};

template <typename Iterator>
inline bool operator<=( const rb_reverse_iterator<Iterator> &lhs,
                        const rb_reverse_iterator<Iterator> &rhs )
{
    return lhs.base() >= rhs.base();
};

template <typename Iterator>
inline bool operator>( const rb_reverse_iterator<Iterator> &lhs,
                       const rb_reverse_iterator<Iterator> &rhs )
{
    return lhs.base() < rhs.base();
};

template <typename Iterator>
inline bool operator>=( const rb_reverse_iterator<Iterator> &lhs,
                        const rb_reverse_iterator<Iterator> &rhs )
{
    return lhs.base() <= rhs.base();
};

template <typename Iterator>
inline typename rb_reverse_iterator<Iterator>::difference_type
operator-( const rb_reverse_iterator<Iterator> &lhs,
           const rb_reverse_iterator<Iterator> &rhs )
{
    return rhs.base() - lhs.base();
};

template <typename Iterator>
inline rb_reverse_iterator<Iterator>
operator+( typename rb_reverse_iterator<Iterator>::difference_type n,
           const rb_reverse_iterator<Iterator>                    &it )
{
    return rb_reverse_iterator<Iterator>( it.base() - n );
};

template <typename It1, typename It2>
inline bool operator==( const rb_reverse_iterator<It1> &lhs,
                        const rb_reverse_iterator<It2> &rhs )
{
    return lhs.base() == rhs.base();
};

template <typename It1, typename It2>
inline bool operator!=( const rb_reverse_iterator<It1> &lhs,
                        const rb_reverse_iterator<It2> &rhs )
{
    return lhs.base() != rhs.base();
};

template <typename It1, typename It2>
inline bool operator<( const rb_reverse_iterator<It1> &lhs,
                       const rb_reverse_iterator<It2> &rhs )
{
    return lhs.base() > rhs.base();
};

template <typename It1, typename It2>
inline bool operator<=( const rb_reverse_iterator<It1> &lhs,
                        const rb_reverse_iterator<It2> &rhs )
{
    return lhs.base() >= rhs.base();
};

template <typename It1, typename It2>
inline bool operator>( const rb_reverse_iterator<It1> &lhs,
                       const rb_reverse_iterator<It2> &rhs )
{
    return lhs.base() < rhs.base();
};

template <typename It1, typename It2>
inline bool operator>=( const rb_reverse_iterator<It1> &lhs,
                        const rb_reverse_iterator<It2> &rhs )
{
    return lhs.base() <= rhs.base();
};

template <typename It1, typename It2>
inline typename rb_reverse_iterator<It1>::difference_type
operator-( const rb_reverse_iterator<It1> &lhs,
           const rb_reverse_iterator<It2> &rhs )
{
    return rhs.base() - lhs.base();
};

template <typename It1, typename It2>
inline rb_reverse_iterator<It1>
operator+( typename rb_reverse_iterator<It1>::difference_type n,
           const rb_reverse_iterator<It2>                    &it )
{
    return rb_reverse_iterator<It1>( it.base() - n );
};

} // namespace ft

#endif // RB_REVERSE_ITERATOR_HPP
