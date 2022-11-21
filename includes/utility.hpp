#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <iostream>

namespace ft {

template < typename T1, typename T2 >
struct pair
{
    T1 first;
    T2 second;

    pair() : first(), second() {};
    pair( const T1 &x, const T2 &y ) : first( x ), second( y ) {};

    template < typename U, typename V >
    pair( const pair<U, V> &p ) : first( p.first ), second( p.second ) {};

    ~pair() {};

    pair &operator=( const pair &p )
    {
        if ( this != &p ) {
            first  = p.first;
            second = p.second;
        }
        return *this;
    };
};

template < typename T1, typename T2 >
pair< T1, T2 > make_pair( T1 key, T2 val )
{
    return pair< T1, T2 >( key, val );
}

template < typename T1, typename T2 >
inline bool operator==( const pair<T1, T2> &lhs, const pair<T1, T2> &rhs )
{
    return lhs.first == rhs.first && lhs.second == rhs.second;
}

template < typename T1, typename T2 >
inline bool operator!=( const pair<T1, T2> &lhs, const pair<T1, T2> &rhs )
{
    return !( lhs == rhs );
}

template < typename T1, typename T2 >
inline bool operator<( const pair<T1, T2> &lhs, const pair<T1, T2> &rhs )
{
    return lhs.first < rhs.first
        || ( lhs.first == rhs.first && lhs.second < rhs.second );
}

template < typename T1, typename T2 >
inline bool operator<=( const pair<T1, T2> &lhs, const pair<T1, T2> &rhs )
{
    return lhs < rhs || lhs == rhs;
}

template < typename T1, typename T2 >
inline bool operator>( const pair<T1, T2> &lhs, const pair<T1, T2> &rhs )
{
    return !( lhs <= rhs );
}

template < typename T1, typename T2 >
inline bool operator>=( const pair<T1, T2> &lhs, const pair<T1, T2> &rhs )
{
    return !( lhs < rhs );
}

} // namespace ft

#endif // UTILITY_HPP
