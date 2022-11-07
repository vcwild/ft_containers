#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include <cstddef>

using namespace ft;

namespace ft {

// creates a random access iterator

template < typename Iterator >
class random_access_iterator
    : public iterator<random_access_iterator_tag, Iterator> {
public:
    typedef Iterator                                            iterator_type;
    typedef typename iterator_traits<Iterator>::value_type      value_type;
    typedef typename iterator_traits<Iterator>::difference_type difference_type;
    typedef typename iterator_traits<Iterator>::pointer         pointer;
    typedef typename iterator_traits<Iterator>::reference       reference;
    typedef
        typename iterator_traits<Iterator>::iterator_category iterator_category;

    random_access_iterator() : _it() {};
    explicit random_access_iterator( const iterator_type &it ) : _it( it ) {};
    random_access_iterator( const random_access_iterator &it ) :
        _it( it.base() ) {};
    template < typename It >
    random_access_iterator( const random_access_iterator<It> &it ) :
        _it( it.base() ) {};
    ~random_access_iterator() {};

    // accessors
    const iterator_type &base() const { return _it; };

    // iterator operations
    reference operator*() const { return *_it; };

    random_access_iterator operator+( difference_type n ) const
    {
        return iterator( _it + n );
    };

    random_access_iterator operator++( int )
    {
        iterator tmp = *this;
        ++_it;
        return tmp;
    };

    random_access_iterator &operator++()
    {
        ++_it;
        return *this;
    };

    random_access_iterator &operator+=( difference_type n )
    {
        _it += n;
        return *this;
    };

    random_access_iterator operator-( difference_type n ) const
    {
        return iterator( _it - n );
    };

    random_access_iterator operator--( int )
    {
        iterator tmp = *this;
        --_it;
        return tmp;
    };

    random_access_iterator &operator--()
    {
        --_it;
        return *this;
    };

    random_access_iterator &operator-=( difference_type n )
    {
        _it -= n;
        return *this;
    };

    pointer operator->() const { return _it; };

    reference operator[]( difference_type n ) const { return _it[n]; };

    // comparison operations
    bool operator==( const random_access_iterator &rhs ) const
    {
        return _it == rhs._it;
    };

    bool operator!=( const random_access_iterator &rhs ) const
    {
        return _it != rhs._it;
    };

    bool operator<( const random_access_iterator &rhs ) const
    {
        return _it < rhs._it;
    };

    bool operator<=( const random_access_iterator &rhs ) const
    {
        return _it <= rhs._it;
    };

    bool operator>( const random_access_iterator &rhs ) const
    {
        return _it > rhs._it;
    };

    bool operator>=( const random_access_iterator &rhs ) const
    {
        return _it >= rhs._it;
    };

    // arithmetic operations
    difference_type operator-( const random_access_iterator &rhs ) const
    {
        return _it - rhs._it;
    };

    // assignment operations
    random_access_iterator &operator=( const random_access_iterator &rhs )
    {
        _it = rhs._it;
        return *this;
    };

    template < typename It >
    random_access_iterator &operator=( const random_access_iterator<It> &rhs )
    {
        _it = rhs.base();
        return *this;
    };

    // conversion operations
    template < typename It >
    operator random_access_iterator<It>() const
    {
        return random_access_iterator<It>( _it );
    };

    // swap operations
    void swap( random_access_iterator &rhs )
    {
        iterator_type tmp = _it;
        _it               = rhs._it;
        rhs._it           = tmp;
    };

    // non-member functions
    friend void swap( random_access_iterator &lhs, random_access_iterator &rhs )
    {
        lhs.swap( rhs );
    };

    friend random_access_iterator operator+( difference_type               n,
                                             const random_access_iterator &it )
    {
        return random_access_iterator( it._it + n );
    };

    friend difference_type operator-( const random_access_iterator &lhs,
                                      const random_access_iterator &rhs )
    {
        return lhs._it - rhs._it;
    };

    friend bool operator==( const random_access_iterator &lhs,
                            const random_access_iterator &rhs )
    {
        return lhs._it == rhs._it;
    };

    friend bool operator!=( const random_access_iterator &lhs,
                            const random_access_iterator &rhs )
    {
        return lhs._it != rhs._it;
    };

    friend bool operator<( const random_access_iterator &lhs,
                           const random_access_iterator &rhs )
    {
        return lhs._it < rhs._it;
    };

    friend bool operator<=( const random_access_iterator &lhs,
                            const random_access_iterator &rhs )
    {
        return lhs._it <= rhs._it;
    };

    friend bool operator>( const random_access_iterator &lhs,
                           const random_access_iterator &rhs )
    {
        return lhs._it > rhs._it;
    };

    friend bool operator>=( const random_access_iterator &lhs,
                            const random_access_iterator &rhs )
    {
        return lhs._it >= rhs._it;
    };

protected:
    iterator_type _it;
};

template < typename It1, typename It2 >
inline bool operator==( const random_access_iterator<It1> &lhs,
                        const random_access_iterator<It2> &rhs )
{
    return lhs.base() == rhs.base();
};

template < typename It1, typename It2 >
inline bool operator!=( const random_access_iterator<It1> &lhs,
                        const random_access_iterator<It2> &rhs )
{
    return lhs.base() != rhs.base();
};

template < typename It1, typename It2 >
inline bool operator<( const random_access_iterator<It1> &lhs,
                       const random_access_iterator<It2> &rhs )
{
    return lhs.base() < rhs.base();
};

template < typename It1, typename It2 >
inline bool operator<=( const random_access_iterator<It1> &lhs,
                        const random_access_iterator<It2> &rhs )
{
    return lhs.base() <= rhs.base();
};

template < typename It1, typename It2 >
inline bool operator>( const random_access_iterator<It1> &lhs,
                       const random_access_iterator<It2> &rhs )
{
    return lhs.base() > rhs.base();
};

template < typename It1, typename It2 >
inline bool operator>=( const random_access_iterator<It1> &lhs,
                        const random_access_iterator<It2> &rhs )
{
    return lhs.base() >= rhs.base();
};

template < typename It1, typename It2 >
inline random_access_iterator<It1>
operator+( typename random_access_iterator<It1>::difference_type n,
           const random_access_iterator<It2>                    &it )
{
    return random_access_iterator<It1>( it.base() + n );
};

template < typename It1, typename It2 >
inline typename random_access_iterator<It1>::difference_type
operator-( const random_access_iterator<It1> &lhs,
           const random_access_iterator<It2> &rhs )
{
    return lhs.base() - rhs.base();
};

} // namespace ft

#endif // ITERATOR_HPP
