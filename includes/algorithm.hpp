/*
 * Copyright 2022 ©️ vcwild under the GNU Affero General Public License v3.0.
 */
#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <cstddef>

namespace ft {

template <typename InputIt1, typename InputIt2>
bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 )
{
    while ( first1 != last1 ) {
        if ( !( *first1 == *first2 ) ) {
            return false;
        }
        ++first1;
        ++first2;
    }
    return true;
}

template < typename InputIt1, typename InputIt2, typename BinaryPredicate >
bool equal( InputIt1        first1,
            InputIt1        last1,
            InputIt2        first2,
            BinaryPredicate p )
{
    while ( first1 != last1 ) {
        if ( !p( *first1, *first2 ) ) {
            return false;
        }
        ++first1;
        ++first2;
    }
    return true;
}

template < typename InputIt1, typename InputIt2 >
bool lexicographical_compare( InputIt1 first1,
                              InputIt1 last1,
                              InputIt2 first2,
                              InputIt2 last2 )
{
    while ( ( first1 != last1 ) && ( first2 != last2 ) ) {
        if ( *first2 < *first1 )
            return false;
        if ( *first1 < *first2 )
            return true;
        ++first1;
        ++first2;
    }
    return ( first1 == last1 ) && ( first2 != last2 );
}

template < typename InputIt1, typename InputIt2, typename Compare >
bool lexicographical_compare( InputIt1 first1,
                              InputIt1 last1,
                              InputIt2 first2,
                              InputIt2 last2,
                              Compare  comp )
{
    while ( first1 != last1 ) {
        if ( first2 == last2 || comp( *first2, *first1 ) ) {
            return false;
        }
        if ( comp( *first1, *first2 ) ) {
            return true;
        }
        ++first1;
        ++first2;
    }
    return ( first2 != last2 );
}

} // namespace ft

#endif // ALGORITHM_HPP
