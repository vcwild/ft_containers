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
    reverse_iterator( const iterator_type &it ) : _it( it ) {};
    reverse_iterator( const reverse_iterator &rhs ) : _it( rhs.base() ) {};
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

    // Non-member function overloads
    friend reverse_iterator operator+( difference_type         n,
                                       const reverse_iterator &rhs )
    {
        return reverse_iterator( rhs.base() - n );
    };

    friend difference_type
    operator-( const reverse_iterator &rhs,
               const reverse_iterator &lhs ) { return lhs.base() - rhs.base() };

    friend bool operator==( const reverse_iterator &rhs,
                            const reverse_iterator &lhs )
    {
        return rhs.base() == lhs.base();
    };

    friend bool operator!=( const reverse_iterator &rhs,
                            const reverse_iterator &lhs )
    {
        return rhs.base() != lhs.base();
    };

    friend bool operator<( const reverse_iterator &rhs,
                           const reverse_iterator &lhs )
    {
        return rhs.base() > lhs.base();
    };

    friend bool operator<=( const reverse_iterator &rhs,
                            const reverse_iterator &lhs ) { return rhs.base()
                                                            >= lhs.base() };

    friend bool operator>( const reverse_iterator &rhs,
                           const reverse_iterator &lhs )
    {
        return rhs.base() < lhs.base();
    };

    friend bool operator>=( const reverse_iterator &rhs,
                            const reverse_iterator &lhs ) { return rhs.base()
                                                            <= lhs.base() };

    friend reverse_iterator operator+( difference_type         n,
                                       const reverse_iterator &rhs )
    {
        return reverse_iterator( rhs.base() - n );
    };

    friend reverse_iterator operator-( difference_type         n,
                                       const reverse_iterator &rhs )
    {
        return reverse_iterator( rhs.base() + n );
    };

protected:
    iterator_type _it;
};

template < typename Iterator >
reverse_iterator<Iterator> make_reverse_iterator( Iterator it )
{
    return reverse_iterator<Iterator>( it );
};

template < typename It1, typename It2 >
inline bool operator==( const reverse_iterator<It1> &lhs,
                        const reverse_iterator<It2> &rhs )
{
    return lhs.base() == rhs.base();
};

template < typename It1, typename It2 >
inline bool operator!=( const reverse_iterator<It1> &lhs,
                        const reverse_iterator<It2> &rhs )
{
    return lhs.base() != rhs.base();
};

template < typename It1, typename It2 >
inline bool operator<( const reverse_iterator<It1> &lhs,
                       const reverse_iterator<It2> &rhs )
{
    return lhs.base() > rhs.base();
};

template < typename It1, typename It2 >
inline bool operator<=( const reverse_iterator<It1> &lhs,
                        const reverse_iterator<It2> &rhs )
{
    return lhs.base() >= rhs.base();
};

template < typename It1, typename It2 >
inline bool operator>( const reverse_iterator<It1> &lhs,
                       const reverse_iterator<It2> &rhs )
{
    return lhs.base() < rhs.base();
};

template < typename It1, typename It2 >
inline bool operator>=( const reverse_iterator<It1> &lhs,
                        const reverse_iterator<It2> &rhs )
{
    return lhs.base() <= rhs.base();
};

template < typename It1, typename It2 >
inline reverse_iterator<It1>
operator+( typename reverse_iterator<It1>::difference_type n,
           const reverse_iterator<It2>                    &rhs )
{
    return reverse_iterator<It1>( rhs.base() - n );
};

template < typename It1, typename It2 >
inline typename reverse_iterator<It1>::difference_type
operator-( const reverse_iterator<It1> &lhs, const reverse_iterator<It2> &rhs )
{
    return rhs.base() - lhs.base();
};

template < typename It1, typename It2 >
inline reverse_iterator<It1>
operator-( typename reverse_iterator<It1>::difference_type n,
           const reverse_iterator<It2>                    &rhs )
{
    return reverse_iterator<It1>( rhs.base() + n );
};

} // namespace ft

#endif // REVERSE_ITERATOR_HPP
