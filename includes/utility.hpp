#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <iostream>

namespace ft {

template < typename T1, typename T2 >
struct pair
{
    typedef T1 first_type;
    typedef T2 second_type;

    T1 first;
    T2 second;

    pair() : first( T1() ), second( T2() ) {};
    pair( const T1 &x, const T2 &y ) : first( x ), second( y ) {};
    ~pair() {};

    pair &operator=( const pair &p )
    {
        first  = p.first;
        second = p.second;
        return *this;
    };
};

template < typename T1, typename T2 >
pair< T1, T2 > make_pair( T1 t, T2 u )
{
    return pair< T1, T2 >( t, u );
};

template < typename T1, typename T2 >
inline bool operator==( const pair<T1, T2> &lhs, const pair<T1, T2> &rhs )
{
    return lhs.first == rhs.first && lhs.second == rhs.second;
};

template < typename T1, typename T2 >
inline bool operator!=( const pair<T1, T2> &lhs, const pair<T1, T2> &rhs )
{
    return !( lhs == rhs );
};

template < typename T1, typename T2 >
inline bool operator<( const pair<T1, T2> &lhs, const pair<T1, T2> &rhs )
{
    return lhs.first < rhs.first
        || ( lhs.first == rhs.first && lhs.second < rhs.second );
};

template < typename T1, typename T2 >
inline bool operator<=( const pair<T1, T2> &lhs, const pair<T1, T2> &rhs )
{
    return lhs < rhs || lhs == rhs;
};

template < typename T1, typename T2 >
inline bool operator>( const pair<T1, T2> &lhs, const pair<T1, T2> &rhs )
{
    return !( lhs <= rhs );
};

template < typename T1, typename T2 >
inline bool operator>=( const pair<T1, T2> &lhs, const pair<T1, T2> &rhs )
{
    return !( lhs < rhs );
};

} // namespace ft

#endif // UTILITY_HPP
