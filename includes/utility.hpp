#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <iostream>

namespace ft {

template < class T1, class T2 >
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

    friend bool operator==( const pair &lhs, const pair &rhs )
    {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    };

    friend bool operator!=( const pair &lhs, const pair &rhs )
    {
        return !( lhs == rhs );
    };

    friend bool operator<( const pair &lhs, const pair &rhs )
    {
        return lhs.first < rhs.first
            || ( lhs.first == rhs.first && lhs.second < rhs.second );
    };

    friend bool operator<=( const pair &lhs, const pair &rhs )
    {
        return lhs < rhs || lhs == rhs;
    };

    friend bool operator>( const pair &lhs, const pair &rhs )
    {
        return !( lhs <= rhs );
    };

    friend bool operator>=( const pair &lhs, const pair &rhs )
    {
        return !( lhs < rhs );
    };
};

} // namespace ft

#endif // UTILITY_HPP
