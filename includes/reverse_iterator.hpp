#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {

template < typename Iterator >
class reverse_iterator
    : public iterator<typename iterator_traits<Iterator>::iterator_category,
                      typename iterator_traits<Iterator>::value_type,
                      typename iterator_traits<Iterator>::difference_type,
                      typename iterator_traits<Iterator>::pointer,
                      typename iterator_traits<Iterator>::reference> {
public:
    typedef Iterator iterator_type;
    typedef
        typename iterator_traits<Iterator>::iterator_category iterator_category;
    typedef typename iterator_traits<Iterator>::value_type    value_type;
    typedef typename iterator_traits<Iterator>::difference_type difference_type;
    typedef typename iterator_traits<Iterator>::pointer         pointer;
    typedef typename iterator_traits<Iterator>::reference       reference;

    reverse_iterator() : _it( NULL ) {};
    explicit reverse_iterator( iterator_type it ) : _it( it ) {};
    reverse_iterator( const reverse_iterator &it ) : _it( it.base() ) {};
    template <typename It>
    reverse_iterator( const reverse_iterator<It> &it ) : _it( it.base() ) {};
    ~reverse_iterator() {};

    // accessors
    const iterator_type &base() const { return _it; };

    // assignment
    reverse_iterator &operator=( const reverse_iterator &rhs )
    {
        _it = rhs.base();
        return *this;
    };

    reference operator*() const
    {
        iterator_type tmp = _it;
        return *( --tmp );
    };

    reverse_iterator operator+( difference_type n ) const
    {
        return reverse_iterator( _it - n );
    };

    reverse_iterator operator++( int )
    {
        reverse_iterator tmp = *this;
        --_it;
        return tmp;
    };

    reverse_iterator &operator++()
    {
        --_it;
        return *this;
    };

    reverse_iterator &operator+=( difference_type n )
    {
        _it -= n;
        return *this;
    };

    reverse_iterator operator-( difference_type n ) const
    {
        return reverse_iterator( _it + n );
    };

    reverse_iterator operator--( int )
    {
        reverse_iterator tmp = *this;
        ++_it;
        return tmp;
    };

    reverse_iterator &operator--()
    {
        ++_it;
        return *this;
    };

    reverse_iterator &operator-=( difference_type n )
    {
        _it += n;
        return *this;
    };

    pointer operator->() const { return &( operator*() ); };

    reference operator[]( difference_type n ) const { return *operator+( n ); };

    // logic operators
    bool operator==( const reverse_iterator &rhs ) const
    {
        return _it == rhs.base();
    };

    bool operator!=( const reverse_iterator &rhs ) const
    {
        return _it != rhs.base();
    };

    bool operator<( const reverse_iterator &rhs ) const
    {
        return _it > rhs.base();
    };

    bool operator<=( const reverse_iterator &rhs ) const
    {
        return _it >= rhs.base();
    };

    bool operator>( const reverse_iterator &rhs ) const
    {
        return _it < rhs.base();
    };

    bool operator>=( const reverse_iterator &rhs ) const
    {
        return _it <= rhs.base();
    };

protected:
    iterator_type _it;
};

template < typename Iterator >
inline typename reverse_iterator<Iterator>::difference_type
operator-( const reverse_iterator<Iterator> &rhs,
           const reverse_iterator<Iterator> &lhs )
{
    return lhs.base() - rhs.base();
}

template < typename Iterator >
inline bool operator==( const reverse_iterator<Iterator> &rhs,
                        const reverse_iterator<Iterator> &lhs )
{
    return rhs.base() == lhs.base();
}

template < typename Iterator >
inline bool operator!=( const reverse_iterator<Iterator> &rhs,
                        const reverse_iterator<Iterator> &lhs )
{
    return rhs.base() != lhs.base();
}

template < typename Iterator >
inline bool operator<( const reverse_iterator<Iterator> &rhs,
                       const reverse_iterator<Iterator> &lhs )
{
    return rhs.base() > lhs.base();
}

template < typename Iterator >
inline bool operator<=( const reverse_iterator<Iterator> &rhs,
                        const reverse_iterator<Iterator> &lhs )
{
    return rhs.base() >= lhs.base();
}

template < typename Iterator >
inline bool operator>( const reverse_iterator<Iterator> &rhs,
                       const reverse_iterator<Iterator> &lhs )
{
    return rhs.base() < lhs.base();
}

template < typename Iterator >
inline bool operator>=( const reverse_iterator<Iterator> &rhs,
                        const reverse_iterator<Iterator> &lhs )
{
    return rhs.base() <= lhs.base();
}

template < typename Iterator >
inline reverse_iterator<Iterator>
operator+( typename reverse_iterator<Iterator>::difference_type n,
           const reverse_iterator<Iterator>                    &rhs )
{
    return reverse_iterator<Iterator>( rhs.base() - n );
}

template < typename Iterator >
inline reverse_iterator<Iterator>
operator-( typename reverse_iterator<Iterator>::difference_type n,
           const reverse_iterator<Iterator>                    &rhs )
{
    return reverse_iterator<Iterator>( rhs.base() + n );
}

template < typename Iterator >
reverse_iterator<Iterator> make_reverse_iterator( Iterator it )
{
    return reverse_iterator<Iterator>( it );
}

template < typename It1, typename It2 >
inline bool operator==( const reverse_iterator<It1> &lhs,
                        const reverse_iterator<It2> &rhs )
{
    return lhs.base() == rhs.base();
}

template < typename It1, typename It2 >
inline bool operator!=( const reverse_iterator<It1> &lhs,
                        const reverse_iterator<It2> &rhs )
{
    return lhs.base() != rhs.base();
}

template < typename It1, typename It2 >
inline bool operator<( const reverse_iterator<It1> &lhs,
                       const reverse_iterator<It2> &rhs )
{
    return lhs.base() > rhs.base();
}

template < typename It1, typename It2 >
inline bool operator<=( const reverse_iterator<It1> &lhs,
                        const reverse_iterator<It2> &rhs )
{
    return lhs.base() >= rhs.base();
}

template < typename It1, typename It2 >
inline bool operator>( const reverse_iterator<It1> &lhs,
                       const reverse_iterator<It2> &rhs )
{
    return lhs.base() < rhs.base();
}

template < typename It1, typename It2 >
inline bool operator>=( const reverse_iterator<It1> &lhs,
                        const reverse_iterator<It2> &rhs )
{
    return lhs.base() <= rhs.base();
}

template < typename It1, typename It2 >
inline reverse_iterator<It1>
operator+( typename reverse_iterator<It1>::difference_type n,
           const reverse_iterator<It2>                    &rhs )
{
    return reverse_iterator<It1>( rhs.base() - n );
}

template < typename It1, typename It2 >
inline typename reverse_iterator<It1>::difference_type
operator-( const reverse_iterator<It1> &lhs, const reverse_iterator<It2> &rhs )
{
    return rhs.base() - lhs.base();
}

template < typename It1, typename It2 >
inline reverse_iterator<It1>
operator-( typename reverse_iterator<It1>::difference_type n,
           const reverse_iterator<It2>                    &rhs )
{
    return reverse_iterator<It1>( rhs.base() + n );
}

} // namespace ft

#endif // REVERSE_ITERATOR_HPP
