/*
 * Copyright 2022 ©️ vcwild under the GNU Affero General Public License v3.0.
 */
#include "minunit.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits.h>
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#define SSTR( x )                                                              \
    static_cast< std::ostringstream & >(                                       \
        ( std::ostringstream() << std::dec << x ) )                            \
        .str()

using namespace std;

bool is_palindrome( const std::string &s )
{
    return std::equal( s.begin(), s.begin() + s.size() / 2, s.rbegin() );
}

bool is_equal( const std::string &s1, const std::string &s2 )
{
    return std::equal( s1.begin(), s1.end(), s2.begin() );
}

bool is_lexicographical_compare( const std::string &s1, const std::string &s2 )
{
    return std::lexicographical_compare(
        s1.begin(), s1.end(), s2.begin(), s2.end() );
}

MU_TEST( test_algorithm_is_palindrome )
{
    mu_assert( is_palindrome( "radar" ), "radar is a palindrome" );
}

MU_TEST( test_algorithm_not_palindrome )
{
    mu_assert( !is_palindrome( "hello" ), "hello is not a palindrome" );
}

MU_TEST( test_algorithm_is_equal )
{
    mu_assert( is_equal( "hello", "hello" ), "hello is equal to hello" );
}

MU_TEST( test_algorithm_is_not_equal )
{
    mu_assert( !is_equal( "hello", "world" ), "hello is not equal to world" );
}

MU_TEST( test_algorithm_is_lexicographical_compare )
{
    mu_assert( is_lexicographical_compare( "hello", "world" ),
               "hello is lexicographically less than world" );
}

MU_TEST( test_algorithm_is_not_lexicographical_compare )
{
    mu_assert( !is_lexicographical_compare( "world", "hello" ),
               "world is not lexicographically less than hello" );
}

MU_TEST_SUITE( suite_algorithm )
{
    MU_RUN_TEST( test_algorithm_is_palindrome );
    MU_RUN_TEST( test_algorithm_not_palindrome );
    MU_RUN_TEST( test_algorithm_is_equal );
    MU_RUN_TEST( test_algorithm_is_not_equal );
    MU_RUN_TEST( test_algorithm_is_lexicographical_compare );
    MU_RUN_TEST( test_algorithm_is_not_lexicographical_compare );
}
// ---------------------------------------------------------------------------

MU_TEST( test_map_assignment )
{

    std::map<const char *, int> m;

    m["a"] = 4;
    m["b"] = 5;
    m["c"] = 6;

    mu_assert( m["a"] == 4, "m[\"a\"] == 4" );
    mu_assert( m["b"] == 5, "m[\"b\"] == 5" );
    mu_assert( m["c"] == 6, "m[\"c\"] == 6" );
    mu_assert( m.size() == 3, "m.size() == 3" );

    std::map<const char *, int> mcopy( m );
    m.clear();

    mu_assert( m.size() == 0, "m.size() == 0" );
    mu_assert( m.empty(), "m.empty()" );
    mu_assert( m["a"] == 0, "m[\"a\"] == 0" );
    mu_assert( m["b"] == 0, "m[\"b\"] == 0" );
    mu_assert( m["c"] == 0, "m[\"c\"] == 0" );
    mu_assert( m["nil"] == 0, "m[\"nil\"] == 0" );
    mu_assert( mcopy["a"] == 4, "mcopy[\"a\"] == 4" );
    mu_assert( mcopy["b"] == 5, "mcopy[\"b\"] == 5" );
    mu_assert( mcopy["c"] == 6, "mcopy[\"c\"] == 6" );
    mu_assert( mcopy.size() == 3, "mcopy.size() == 3" );
}

MU_TEST( test_map_pairs )
{
    std::map<char, std::string> m;

    m.insert( std::make_pair( 'a', "amora" ) );
    m.insert( std::make_pair( 'b', "banana" ) );

    mu_assert( m.size() == 2, "m.size() == 2" );
    mu_assert( m['a'] == "amora", "m['a'] == \"amora\"" );
    mu_assert( m['b'] == "banana", "m['b'] == \"banana\"" );
}

MU_TEST( test_map_string_pairs )
{
    std::map<const std::string, int> v;

    v.insert( make_pair( "sun", 1 ) );
    v.insert( make_pair( "moon", 2 ) );
    v.insert( make_pair( "stars", 3 ) );

    mu_assert( v.size() == 3, "v.size() == 3" );
    mu_assert( v["sun"] == 1, "v[\"sun\"] == 1" );
    mu_assert( v["moon"] == 2, "v[\"moon\"] == 2" );
    mu_assert( v["stars"] == 3, "v[\"stars\"] == 3" );
    v.erase( "moon" );
    mu_assert( v.size() == 2, "v.size() == 2" );
    mu_assert( v["moon"] == 0, "v[\"moon\"] == 0" );
    v["sun"] = 4;
    mu_assert( v["sun"] == 4, "v[\"sun\"] == 4" );
}

MU_TEST( test_map_iterate )
{
    // create a map of ints from 0 to 50
    std::map<int, int> m;
    for ( int i = 0; i < 50; i++ ) {
        m[i] = i;
    }

    // iterate over the map and check that the values are correct
    std::map<int, int>::iterator it  = m.begin();
    std::map<int, int>::iterator ite = m.end();
    for ( int i = 0; it != ite; ++it, ++i ) {
        mu_assert( it->first == i, "it->first == i" );
        mu_assert( it->second == i, "it->second == i" );
    }
}

MU_TEST( test_map_add_duplicates )
{
    std::map<int, int> m;
    m[1] = 9;
    m[1] = 10;
    mu_assert( m.size() == 1, "m.size() == 1" );
    mu_assert( m[1] == 10, "m[1] == 10" );
}

MU_TEST( test_map_find )
{
    std::map<int, int> m;
    for ( int i = 0; i < 10; i++ ) {
        m[i] = i + 2;
    }

    std::map<int, int>::iterator it = m.find( 5 );
    mu_assert( it->first == 5, "it->first == 5" );
    mu_assert( it->second == 7, "it->second == 7" );
    it = m.find( 11 );
    mu_assert( it == m.end(), "it is at map end" );
}

MU_TEST( test_map_erase_iterator )
{
    std::map<int, int> m;
    for ( int i = 0; i < 10; i++ ) {
        m[i] = i + 2;
    }

    std::map<int, int>::iterator it = m.find( 5 );
    m.erase( it );
    mu_assert( m.size() == 9, "m.size() == 9" );
    mu_assert( m[5] == 0, "m[5] == 0" );
}

MU_TEST( test_map_key_compare )
{
    std::map<int, int> m;
    for ( int i = 0; i < 10; i++ ) {
        m[i] = i + 2;
    }

    std::map<int, int>::key_compare comp = m.key_comp();
    std::map<int, int>::iterator    it   = m.begin();
    std::map<int, int>::iterator    ite  = m.end();
    for ( int i = 0; it != ite; ++it, ++i ) {
        mu_assert( !comp( it->first, it->first ),
                   "not comp( it->first, it->first )" );
    }
}

MU_TEST( test_map_insert_input_iterator )
{
    std::map<int, int>           m;
    std::map<int, int>::iterator it;

    it = m.insert( m.begin(), std::make_pair( 1, 1 ) );
    mu_assert( it->first == 1, "it->first == 1" );
    mu_assert( it->second == 1, "it->second == 1" );
    mu_assert( m.size() == 1, "m.size() == 1" );

    it = m.insert( m.begin(), std::make_pair( 2, 2 ) );
    mu_assert( it->first == 2, "it->first == 2" );
    mu_assert( it->second == 2, "it->second == 2" );
    mu_assert( m.size() == 2, "m.size() == 2" );

    it = m.insert( m.begin(), std::make_pair( 3, 3 ) );
    mu_assert( it->first == 3, "it->first == 3" );
    mu_assert( it->second == 3, "it->second == 3" );
    mu_assert( m.size() == 3, "m.size() == 3" );

    it = m.insert( m.begin(), std::make_pair( 4, 4 ) );
    mu_assert( it->first == 4, "it->first == 4" );
    mu_assert( it->second == 4, "it->second == 4" );
    mu_assert( m.size() == 4, "m.size() == 4" );

    it = m.insert( m.begin(), std::make_pair( 5, 5 ) );
    mu_assert( it->first == 5, "it->first == 5" );
    mu_assert( it->second == 5, "it->second == 5" );
    mu_assert( m.size() == 5, "m.size() == 5" );
}

MU_TEST( test_map_swap )
{
    std::map<char, int> foo, bar;

    foo['x'] = 100;
    foo['y'] = 200;

    bar['a'] = 11;
    bar['b'] = 22;
    bar['c'] = 33;

    foo.swap( bar );

    mu_assert( foo.size() == 3, "foo.size() == 3" );
    mu_assert( bar.size() == 2, "bar.size() == 2" );
    mu_assert( foo['a'] == 11, "foo['a'] == 11" );
    mu_assert( bar['x'] == 100, "bar['x'] == 100" );

    swap( bar, foo );

    mu_assert( foo.size() == 2, "foo.size() == 2" );
    mu_assert( bar.size() == 3, "bar.size() == 3" );
    mu_assert( bar['a'] == 11, "bar['a'] == 11" );
    mu_assert( foo['x'] == 100, "foo['x'] == 100" );
}

MU_TEST( test_map_max_size )
{
    std::map<int, int> m;
    mu_assert( m.max_size() > 0, "m.max_size() > 0" );
}

MU_TEST( test_map_count )
{
    std::map<int, int> m;
    for ( int i = 0; i < 10; i++ ) {
        m[i] = i + 2;
    }

    mu_assert( m.count( 5 ) == 1, "m.count( 5 ) == 1" );
    mu_assert( m.count( 11 ) == 0, "m.count( 11 ) == 0" );
}

MU_TEST( test_map_lower_bound )
{
    std::map<int, int> m;
    for ( int i = 0; i < 10; i++ ) {
        m[i] = i + 2;
    }

    std::map<int, int>::iterator it = m.lower_bound( 5 );
    mu_assert( it->first == 5, "it->first == 5" );
    mu_assert( it->second == 7, "it->second == 7" );
    it = m.lower_bound( 11 );
    mu_assert( it == m.end(), "it is at map end" );
}

MU_TEST( test_map_upper_bound )
{
    std::map<int, int> m;
    for ( int i = 0; i < 10; i++ ) {
        m[i] = i + 2;
    }

    std::map<int, int>::iterator it = m.upper_bound( 5 );
    mu_assert( it->first == 6, "it->first == 6" );
    mu_assert( it->second == 8, "it->second == 8" );
    it = m.upper_bound( 11 );
    mu_assert( it == m.end(), "it is at map end" );
}

MU_TEST( test_map_equal_range )
{
    std::map<int, int> m;
    for ( int i = 0; i < 10; i++ ) {
        m[i] = i + 2;
    }

    std::pair<std::map<int, int>::iterator, std::map<int, int>::iterator> ret;
    ret = m.equal_range( 5 );

    mu_assert( ret.first->first == 5, "ret.first->first == 5" );
    mu_assert( ret.first->second == 7, "ret.first->second == 7" );
    mu_assert( ret.second->first == 6, "ret.second->first == 6" );
    mu_assert( ret.second->second == 8, "ret.second->second == 8" );

    ret = m.equal_range( 11 );
    mu_assert( ret.first == m.end(), "ret.first is at map end" );
    mu_assert( ret.second == m.end(), "ret.second is at map end" );
}

MU_TEST( test_map_equal )
{
    std::map<int, int> m1;
    std::map<int, int> m2;
    for ( int i = 0; i < 10; i++ ) {
        m1[i] = i + 2;
        m2[i] = i + 2;
    }
    mu_assert( m1 == m2, "m1 == m2" );
}

MU_TEST( test_map_not_equal )
{
    std::map<int, int> m1;
    std::map<int, int> m2;
    for ( int i = 0; i < 10; i++ ) {
        m1[i] = i + 2;
        m2[i] = i + 2;
    }
    m2[5] = 42;
    mu_assert( m1 != m2, "m1 != m2" );
}

MU_TEST( test_map_less_than )
{
    std::map<int, int> m1;
    std::map<int, int> m2;
    for ( int i = 0; i < 10; i++ ) {
        m1[i] = i + 2;
        m2[i] = i + 2;
    }
    m2[5] = 42;
    mu_assert( m1 < m2, "m1 < m2" );
}

MU_TEST( test_map_less_than_or_equal )
{
    std::map<int, int> m1;
    std::map<int, int> m2;
    for ( int i = 0; i < 10; i++ ) {
        m1[i] = i + 2;
        m2[i] = i + 2;
    }
    m2[5] = 42;
    mu_assert( m1 <= m2, "m1 <= m2" );
}

MU_TEST( test_map_greater_than )
{
    std::map<int, int> m1;
    std::map<int, int> m2;
    for ( int i = 0; i < 10; i++ ) {
        m1[i] = i + 2;
        m2[i] = i + 2;
    }
    m2[5] = 42;
    mu_assert( m2 > m1, "m2 > m1" );
}

MU_TEST( test_map_greater_than_or_equal )
{
    std::map<int, int> m1;
    std::map<int, int> m2;
    for ( int i = 0; i < 10; i++ ) {
        m1[i] = i + 2;
        m2[i] = i + 2;
    }
    m2[5] = 42;
    mu_assert( m2 >= m1, "m2 >= m1" );
}

MU_TEST_SUITE( suite_map )
{
    MU_RUN_TEST( test_map_assignment );
    MU_RUN_TEST( test_map_pairs );
    MU_RUN_TEST( test_map_string_pairs );
    MU_RUN_TEST( test_map_iterate );
    MU_RUN_TEST( test_map_add_duplicates );
    MU_RUN_TEST( test_map_find );
    MU_RUN_TEST( test_map_erase_iterator );
    MU_RUN_TEST( test_map_key_compare );
    MU_RUN_TEST( test_map_insert_input_iterator );
    MU_RUN_TEST( test_map_swap );
    MU_RUN_TEST( test_map_max_size );
    MU_RUN_TEST( test_map_count );
    MU_RUN_TEST( test_map_lower_bound );
    MU_RUN_TEST( test_map_upper_bound );
    MU_RUN_TEST( test_map_equal_range );
    MU_RUN_TEST( test_map_equal );
    MU_RUN_TEST( test_map_not_equal );
    MU_RUN_TEST( test_map_less_than );
    MU_RUN_TEST( test_map_less_than_or_equal );
    MU_RUN_TEST( test_map_greater_than );
    MU_RUN_TEST( test_map_greater_than_or_equal );
}
// ---------------------------------------------------------------------------

MU_TEST( test_set_create )
{
    std::set<int>           s;
    std::set<int>::iterator it;

    for ( int i = 1; i <= 5; i++ ) {
        s.insert( i * 10 );
    }
    it = s.find( 20 );
    mu_assert_int_eq( *it, 20 );
    mu_assert_int_eq( s.size(), 5 );
    s.erase( it );
    mu_assert_int_eq( s.size(), 4 );
    s.erase( s.find( 40 ) );
    mu_assert_int_eq( s.size(), 3 );
}

MU_TEST( test_set_copy_constructor )
{
    std::set<int>           s;
    std::set<int>::iterator it;

    for ( int i = 1; i <= 5; i++ ) {
        s.insert( i * 10 );
    }

    std::set<int> s2( s );
    it = s2.find( 20 );
    mu_assert_int_eq( *it, 20 );
    mu_assert_int_eq( s2.size(), 5 );
    s2.erase( it );
    mu_assert_int_eq( s2.size(), 4 );
    s2.erase( s2.find( 40 ) );
    mu_assert_int_eq( s2.size(), 3 );
    it = s.find( 20 );
    mu_assert_int_eq( *it, 20 );
}

MU_TEST( test_set_capacities )
{
    std::set<int>           s;
    std::set<int>::iterator it;

    for ( int i = 1; i <= 5; i++ ) {
        s.insert( i * 10 );
    }

    mu_assert_int_eq( s.size(), 5 );
    mu_assert_int_eq( s.empty(), false );
}

MU_TEST( test_set_pair_insert )
{
    std::set<int>           s;
    std::set<int>::iterator it;

    for ( int i = 1; i <= 5; i++ ) {
        s.insert( i * 10 );
    }

    std::pair<std::set<int>::iterator, bool> p = s.insert( 20 );
    mu_assert_int_eq( *p.first, 20 );
    mu_assert_int_eq( p.second, false );
    mu_assert_int_eq( s.size(), 5 );
}

MU_TEST( test_set_iterator_insert )
{
    std::set<int>           s;
    std::set<int>::iterator it;

    for ( int i = 1; i <= 5; i++ ) {
        s.insert( i * 10 );
    }

    it = s.insert( s.begin(), 20 );
    mu_assert_int_eq( *it, 20 );
    mu_assert_int_eq( s.size(), 5 );
}

MU_TEST( test_set_input_iterator )
{
    std::set<int>           s;
    std::set<int>::iterator it;

    for ( int i = 1; i <= 5; i++ ) {
        s.insert( i * 10 );
    }

    std::set<int> s2( s.begin(), s.end() );
    it = s2.find( 20 );
    mu_assert_int_eq( *it, 20 );
    mu_assert_int_eq( s2.size(), 5 );
    s2.erase( it );
    mu_assert_int_eq( s2.size(), 4 );
    s2.erase( s2.find( 40 ) );
    mu_assert_int_eq( s2.size(), 3 );
    it = s.find( 20 );
    mu_assert_int_eq( *it, 20 );
}

MU_TEST( test_set_erase_first_last )
{
    std::set<int>           s;
    std::set<int>::iterator it;

    for ( int i = 1; i <= 5; i++ ) {
        s.insert( i * 10 );
    }

    s.erase( s.begin(), s.find( 40 ) );
    mu_assert_int_eq( s.size(), 2 );
    mu_assert_int_eq( *s.begin(), 40 );
    mu_assert_int_eq( *s.rbegin(), 50 );
}

MU_TEST( test_set_swap )
{
    std::set<int>           s;
    std::set<int>::iterator it;

    for ( int i = 1; i <= 5; i++ ) {
        s.insert( i * 10 );
    }

    std::set<int> s2;
    for ( int i = 1; i <= 5; i++ ) {
        s2.insert( i * 10 );
    }

    s.swap( s2 );
    mu_assert_int_eq( s.size(), 5 );
    mu_assert_int_eq( s2.size(), 5 );
    mu_assert_int_eq( *s.begin(), 10 );
    mu_assert_int_eq( *s2.begin(), 10 );

    swap( s, s2 );
    mu_assert_int_eq( s.size(), 5 );
    mu_assert_int_eq( s2.size(), 5 );
    mu_assert_int_eq( *s.begin(), 10 );
    mu_assert_int_eq( *s2.begin(), 10 );
}

MU_TEST( test_set_clear )
{
    std::set<int>           s;
    std::set<int>::iterator it;

    for ( int i = 1; i <= 5; i++ ) {
        s.insert( i * 10 );
    }

    s.clear();
    mu_assert_int_eq( s.size(), 0 );
    mu_assert_int_eq( s.empty(), true );
}

MU_TEST( test_set_observers )
{
    std::set<int>           s;
    std::set<int>::iterator it;

    for ( int i = 1; i <= 5; i++ ) {
        s.insert( i * 10 );
    }

    std::set<int>::key_compare comp = s.key_comp();
    mu_assert_int_eq( comp( 10, 20 ), true );
    mu_assert_int_eq( comp( 20, 10 ), false );
    mu_assert_int_eq( comp( 20, 20 ), false );
}

MU_TEST( test_set_count )
{
    std::set<int>           s;
    std::set<int>::iterator it;

    for ( int i = 1; i <= 5; i++ ) {
        s.insert( i * 10 );
    }

    // try adding duplicates
    s.insert( 10 );
    s.insert( 20 );
    s.insert( 30 );

    mu_assert_int_eq( s.count( 10 ), 1 );
    mu_assert_int_eq( s.count( 20 ), 1 );
    mu_assert_int_eq( s.count( 30 ), 1 );
    mu_assert_int_eq( s.count( 40 ), 1 );
    mu_assert_int_eq( s.count( 50 ), 1 );
    mu_assert_int_eq( s.count( 60 ), 0 );
}

MU_TEST( test_set_bounds )
{
    std::set<int>           s;
    std::set<int>::iterator it;

    for ( int i = 1; i <= 5; i++ ) {
        s.insert( i * 10 );
    }

    it = s.lower_bound( 20 );
    mu_assert_int_eq( *it, 20 );
    it = s.upper_bound( 20 );
    mu_assert_int_eq( *it, 30 );
    std::pair<std::set<int>::iterator, std::set<int>::iterator> p
        = s.equal_range( 20 );
    mu_assert_int_eq( *p.first, 20 );
    mu_assert_int_eq( *p.second, 30 );
}

MU_TEST( test_set_lesser )
{
    std::set<int> s;
    s.insert( 1 );
    s.insert( 2 );
    s.insert( 3 );
    s.insert( 4 );
    s.insert( 5 );

    std::set<int>::iterator it  = s.begin();
    std::set<int>::iterator ite = s.end();
    mu_assert_int_eq( *it, 1 );
    ++it;
    mu_assert_int_eq( *it, 2 );
    ++it;
    mu_assert_int_eq( *it, 3 );
    ++it;
    mu_assert_int_eq( *it, 4 );
    ++it;
    mu_assert_int_eq( *it, 5 );
    ++it;
    mu_assert_int_eq( *it, *ite );
}

MU_TEST( test_set_greater )
{
    std::set<int> s;
    s.insert( 1 );
    s.insert( 2 );
    s.insert( 3 );
    s.insert( 4 );
    s.insert( 5 );

    std::set<int>::reverse_iterator it  = s.rbegin();
    std::set<int>::reverse_iterator ite = s.rend();
    mu_assert_int_eq( *it, 5 );
    ++it;
    mu_assert_int_eq( *it, 4 );
    ++it;
    mu_assert_int_eq( *it, 3 );
    ++it;
    mu_assert_int_eq( *it, 2 );
    ++it;
    mu_assert_int_eq( *it, 1 );
    ++it;
    mu_assert_int_eq( *it, *ite );
}

MU_TEST( test_set_less_equal )
{
    std::set<int> s;
    s.insert( 1 );
    s.insert( 2 );
    s.insert( 3 );
    s.insert( 4 );
    s.insert( 5 );

    std::set<int>::iterator it  = s.begin();
    std::set<int>::iterator ite = s.end();
    mu_assert_int_eq( *it, 1 );
    it++;
    mu_assert_int_eq( *it, 2 );
    it++;
    mu_assert_int_eq( *it, 3 );
    it++;
    mu_assert_int_eq( *it, 4 );
    it++;
    mu_assert_int_eq( *it, 5 );
    it++;
    mu_assert_int_eq( *it, *ite );
}

MU_TEST( test_set_greater_equal )
{
    std::set<int> s;
    s.insert( 1 );
    s.insert( 2 );
    s.insert( 3 );
    s.insert( 4 );
    s.insert( 5 );

    std::set<int>::reverse_iterator it  = s.rbegin();
    std::set<int>::reverse_iterator ite = s.rend();
    mu_assert_int_eq( *it, 5 );
    it++;
    mu_assert_int_eq( *it, 4 );
    it++;
    mu_assert_int_eq( *it, 3 );
    it++;
    mu_assert_int_eq( *it, 2 );
    it++;
    mu_assert_int_eq( *it, 1 );
    it++;
    mu_assert_int_eq( *it, *ite );
}

MU_TEST( test_set_equal )
{
    std::set<int> s1;
    std::set<int> s2;
    s1.insert( 1 );
    s1.insert( 2 );
    s1.insert( 3 );
    s1.insert( 4 );
    s1.insert( 5 );
    s2.insert( 1 );
    s2.insert( 2 );
    s2.insert( 3 );
    s2.insert( 4 );
    s2.insert( 5 );
    mu_assert_int_eq( s1 == s2, true );
}

MU_TEST( test_set_different )
{
    std::set<int> s1;
    std::set<int> s2;
    s1.insert( 1 );
    s1.insert( 2 );
    s1.insert( 3 );
    s1.insert( 4 );
    s1.insert( 5 );
    s2.insert( 1 );
    s2.insert( 2 );
    s2.insert( 3 );
    s2.insert( 4 );
    s2.insert( 6 );
    mu_assert_int_eq( s1 != s2, true );
}

MU_TEST_SUITE( suite_set )
{
    MU_RUN_TEST( test_set_create );
    MU_RUN_TEST( test_set_copy_constructor );
    MU_RUN_TEST( test_set_capacities );
    MU_RUN_TEST( test_set_pair_insert );
    MU_RUN_TEST( test_set_iterator_insert );
    MU_RUN_TEST( test_set_input_iterator );
    MU_RUN_TEST( test_set_erase_first_last );
    MU_RUN_TEST( test_set_swap );
    MU_RUN_TEST( test_set_clear );
    MU_RUN_TEST( test_set_observers );
    MU_RUN_TEST( test_set_count );
    MU_RUN_TEST( test_set_bounds );
    MU_RUN_TEST( test_set_lesser );
    MU_RUN_TEST( test_set_greater );
    MU_RUN_TEST( test_set_less_equal );
    MU_RUN_TEST( test_set_greater_equal );
    MU_RUN_TEST( test_set_equal );
    MU_RUN_TEST( test_set_different );
}
//------------------------------------------------------------

#define TEST_STACK_SIZE 5

static std::stack<int> demoStack;
static std::stack<int> stackInt;

void test_stack_setup()
{
    for ( int i = 0; i < TEST_STACK_SIZE; i++ )
        stackInt.push( i );
}

void test_stack_teardown() {}

MU_TEST( test_stack_copy_constructor )
{
    std::stack<int> copyStack( stackInt );
    mu_assert_int_eq( copyStack.size(), stackInt.size() );
    mu_assert_int_eq( copyStack.top(), stackInt.top() );
}

MU_TEST( test_stack_empty )
{
    mu_check( demoStack.empty() == true );
    mu_check( stackInt.empty() == false );
}

MU_TEST( test_stack_size )
{
    mu_assert( demoStack.size() == 0, "stack size is wrong" );
    mu_assert( stackInt.size() != 0, "stack size is wrong" );
}

MU_TEST( test_stack_top )
{
    // mu_check( demoStack.top() == 0 );
    mu_check( stackInt.top() == TEST_STACK_SIZE - 1 );
}

MU_TEST( test_stack_pop )
{
    std::stack<int> mutStack;

    for ( int i = 0; i < TEST_STACK_SIZE; i++ )
        mutStack.push( i );

    for ( int i = TEST_STACK_SIZE - 1; i >= 0; i-- ) {
        mu_check( mutStack.top() == i );
        mutStack.pop();
        mu_check( mutStack.size() == ( long unsigned int ) i );
    }
    mu_check( mutStack.empty() == true );
}

MU_TEST( test_stack_equal )
{
    std::stack<int> stack1;
    std::stack<int> stack2;

    for ( int i = 0; i < TEST_STACK_SIZE; i++ ) {
        stack1.push( i );
        stack2.push( i );
    }

    mu_check( stack1 == stack2 );
}

MU_TEST( test_stack_not_equal )
{
    std::stack<int> stack1;
    std::stack<int> stack2;

    for ( int i = 0; i < TEST_STACK_SIZE; i++ ) {
        stack1.push( i );
        stack2.push( i );
    }

    stack1.push( 42 );

    mu_check( stack1 != stack2 );
}

MU_TEST( test_stack_less )
{
    std::stack<int> stack1;
    std::stack<int> stack2;

    for ( int i = 0; i < TEST_STACK_SIZE; i++ ) {
        stack1.push( i );
        stack2.push( i );
    }

    stack2.push( 42 );

    mu_check( stack1 < stack2 );
}

MU_TEST( test_stack_less_equal )
{
    std::stack<int> stack1;
    std::stack<int> stack2;

    for ( int i = 0; i < TEST_STACK_SIZE; i++ ) {
        stack1.push( i );
        stack2.push( i );
    }

    mu_check( stack1 <= stack2 );
}

MU_TEST( test_stack_greater )
{
    std::stack<int> stack1;
    std::stack<int> stack2;

    for ( int i = 0; i < TEST_STACK_SIZE; i++ ) {
        stack1.push( i );
        stack2.push( i );
    }

    stack2.push( 42 );

    mu_check( stack2 > stack1 );
}

MU_TEST( test_stack_greater_equal )
{
    std::stack<int> stack1;
    std::stack<int> stack2;

    for ( int i = 0; i < TEST_STACK_SIZE; i++ ) {
        stack1.push( i );
        stack2.push( i );
    }

    mu_check( stack2 >= stack1 );
}

MU_TEST_SUITE( suite_stack )
{
    MU_RUN_TEST( test_stack_copy_constructor );
    MU_RUN_TEST( test_stack_empty );
    MU_RUN_TEST( test_stack_size );
    MU_RUN_TEST( test_stack_top );
    MU_RUN_TEST( test_stack_pop );
    MU_RUN_TEST( test_stack_equal );
    MU_RUN_TEST( test_stack_not_equal );
    MU_RUN_TEST( test_stack_less );
    MU_RUN_TEST( test_stack_less_equal );
    MU_RUN_TEST( test_stack_greater );
    MU_RUN_TEST( test_stack_greater_equal );
}
//------------------------------------------------------------

MU_TEST( test_is_integral_bool )
{
    mu_assert( std::is_integral<bool>::value == true,
               "is_integral<bool>::value == true" );
}

MU_TEST( test_is_integral_char )
{
    mu_assert( std::is_integral<char>::value == true,
               "is_integral<char>::value == true" );
}

MU_TEST( test_is_integral_wchar_t )
{
    mu_assert( std::is_integral<wchar_t>::value == true,
               "is_integral<wchar_t>::value == true" );
}

MU_TEST( test_is_integral_signed_char )
{
    mu_assert( std::is_integral<signed char>::value == true,
               "is_integral<signed char>::value == true" );
}

MU_TEST( test_is_integral_short_int )
{
    mu_assert( std::is_integral<short int>::value == true,
               "is_integral<short int>::value == true" );
}

MU_TEST( test_is_integral_int )
{
    mu_assert( std::is_integral<int>::value == true,
               "is_integral<int>::value == true" );
}

MU_TEST( test_is_integral_long_int )
{
    mu_assert( std::is_integral<long int>::value == true,
               "is_integral<long int>::value == true" );
}

MU_TEST( test_is_integral_long_long_int )
{
    mu_assert( std::is_integral<long long int>::value == true,
               "is_integral<long long int>::value == true" );
}

MU_TEST( test_is_integral_unsigned_char )
{
    mu_assert( std::is_integral<unsigned char>::value == true,
               "is_integral<unsigned char>::value == true" );
}

MU_TEST( test_is_integral_unsigned_short_int )
{
    mu_assert( std::is_integral<unsigned short int>::value == true,
               "is_integral<unsigned short int>::value == true" );
}

MU_TEST( test_is_integral_unsigned_int )
{
    mu_assert( std::is_integral<unsigned int>::value == true,
               "is_integral<unsigned int>::value == true" );
}

MU_TEST( test_is_integral_unsigned_long_int )
{
    mu_assert( std::is_integral<unsigned long int>::value == true,
               "is_integral<unsigned long int>::value == true" );
}

MU_TEST( test_is_integral_unsigned_long_long_int )
{
    mu_assert( std::is_integral<unsigned long long int>::value == true,
               "is_integral<unsigned long long int>::value == true" );
}

MU_TEST( test_is_integral_float )
{
    mu_assert( std::is_integral<float>::value == false,
               "is_integral<float>::value == false" );
}

MU_TEST( test_is_integral_double )
{
    mu_assert( std::is_integral<double>::value == false,
               "is_integral<double>::value == false" );
}

MU_TEST( test_is_integral_int_volatile )
{
    mu_assert( std::is_integral<int volatile>::value == true,
               "is_integral<int volatile>::value == true" );
}

MU_TEST( test_is_integral_int_const )
{
    mu_assert( std::is_integral<int const>::value == true,
               "is_integral<int const>::value == true" );
}

MU_TEST( test_is_integral_int_const_volatile )
{
    mu_assert( std::is_integral<int const volatile>::value == true,
               "is_integral<int const volatile>::value == true" );
}

MU_TEST( test_is_integral_int_ptr )
{
    mu_assert( std::is_integral<int *>::value == false,
               "is_integral<int *>::value == false" );
}

MU_TEST( test_is_integral_int_const_ptr )
{
    mu_assert( std::is_integral<int const *>::value == false,
               "is_integral<int const *>::value == false" );
}

MU_TEST_SUITE( suite_type_traits )
{
    MU_RUN_TEST( test_is_integral_bool );
    MU_RUN_TEST( test_is_integral_char );
    MU_RUN_TEST( test_is_integral_wchar_t );
    MU_RUN_TEST( test_is_integral_signed_char );
    MU_RUN_TEST( test_is_integral_short_int );
    MU_RUN_TEST( test_is_integral_int );
    MU_RUN_TEST( test_is_integral_long_int );
    MU_RUN_TEST( test_is_integral_long_long_int );
    MU_RUN_TEST( test_is_integral_unsigned_char );
    MU_RUN_TEST( test_is_integral_unsigned_short_int );
    MU_RUN_TEST( test_is_integral_unsigned_int );
    MU_RUN_TEST( test_is_integral_unsigned_long_int );
    MU_RUN_TEST( test_is_integral_unsigned_long_long_int );
    MU_RUN_TEST( test_is_integral_float );
    MU_RUN_TEST( test_is_integral_double );
    MU_RUN_TEST( test_is_integral_int_volatile );
    MU_RUN_TEST( test_is_integral_int_const );
    MU_RUN_TEST( test_is_integral_int_const_volatile );
    MU_RUN_TEST( test_is_integral_int_ptr );
    MU_RUN_TEST( test_is_integral_int_const_ptr );
}
// ---------------------------------------------------------------------------

MU_TEST( test_int_float_pair )
{
    std::pair<int, float> p1( 42, 3.14 );

    mu_assert_int_eq( p1.first, 42 );
    mu_assert_double_eq( p1.second, 3.140000104904 );
}

MU_TEST( test_char_int_pair )
{
    std::pair<char, int> p1( 'a', 42 );

    mu_assert_int_eq( p1.first, 'a' );
    mu_assert_int_eq( p1.second, 42 );
}

MU_TEST( test_string_string_pair )
{
    std::pair<std::string, std::string> p1( "Hello", "World" );

    mu_assert_string_eq( p1.first.c_str(), "Hello" );
    mu_assert_string_eq( p1.second.c_str(), "World" );
}

MU_TEST( test_pair_equality )
{
    std::pair<int, float> p1( 42, 3.14 );
    std::pair<int, float> p2( 42, 3.14 );

    mu_assert( p1 == p2, "p1 == p2" );
}

MU_TEST( test_pair_inequality )
{
    std::pair<int, float> p1( 42, 3.14 );
    std::pair<int, float> p2( 42, 3.15 );

    mu_assert( p1 != p2, "p1 != p2" );
}

MU_TEST( test_pair_less_than )
{
    std::pair<int, float> p1( 42, 3.14 );
    std::pair<int, float> p2( 42, 3.15 );

    mu_assert( p1 < p2, "p1 < p2" );
}

MU_TEST( test_pair_less_than_or_equal )
{
    std::pair<int, float> p1( 42, 3.14 );
    std::pair<int, float> p2( 42, 3.14 );

    mu_assert( p1 <= p2, "p1 <= p2" );
}

MU_TEST( test_pair_greater_than )
{
    std::pair<int, float> p1( 42, 3.15 );
    std::pair<int, float> p2( 42, 3.14 );

    mu_assert( p1 > p2, "p1 > p2" );
}

MU_TEST( test_pair_greater_than_or_equal )
{
    std::pair<int, float> p1( 42, 3.14 );
    std::pair<int, float> p2( 42, 3.14 );

    mu_assert( p1 >= p2, "p1 >= p2" );
}

MU_TEST( test_assignment_operator )
{
    std::pair<int, float> p1( 42, 3.14 );
    std::pair<int, float> p2;

    p2 = p1;

    mu_assert_int_eq( p2.first, p1.first );
    mu_assert_double_eq( p2.second, p1.second );
}

MU_TEST( test_make_pair )
{
    std::pair<int, float> p1( 42, 3.14 );
    std::pair<int, float> p2 = std::make_pair( p1.first, p1.second );

    mu_assert_int_eq( p1.first, p2.first );
    mu_assert_double_eq( p1.second, p2.second );
}

MU_TEST_SUITE( suite_utility )
{
    MU_RUN_TEST( test_int_float_pair );
    MU_RUN_TEST( test_char_int_pair );
    MU_RUN_TEST( test_string_string_pair );
    MU_RUN_TEST( test_pair_equality );
    MU_RUN_TEST( test_pair_inequality );
    MU_RUN_TEST( test_pair_less_than );
    MU_RUN_TEST( test_pair_less_than_or_equal );
    MU_RUN_TEST( test_pair_greater_than );
    MU_RUN_TEST( test_pair_greater_than_or_equal );
    MU_RUN_TEST( test_assignment_operator );
    MU_RUN_TEST( test_make_pair );
}
// ---------------------------------------------------------------------------

#define TEST_VECTOR_SIZE 10

MU_TEST( test_vec_copy_constructor )
{
    std::vector<int> vecInt( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        vecInt[i] = i;

    std::vector<int> copyVec( vecInt );
    mu_assert_int_eq( copyVec.size(), vecInt.size() );
    mu_assert_int_eq( copyVec[0], vecInt[0] );
    mu_assert_int_eq( copyVec[1], vecInt[1] );
    mu_assert_int_eq( copyVec[2], vecInt[2] );
    mu_assert_int_eq( copyVec[3], vecInt[3] );
    mu_assert_int_eq( copyVec[4], vecInt[4] );
    mu_assert_int_eq( copyVec[5], vecInt[5] );
    mu_assert_int_eq( copyVec[6], vecInt[6] );
    mu_assert_int_eq( copyVec[7], vecInt[7] );
    mu_assert_int_eq( copyVec[8], vecInt[8] );
    mu_assert_int_eq( copyVec[9], vecInt[9] );
}

MU_TEST( test_vec_integral_constructor )
{
    std::vector<int> vec( TEST_VECTOR_SIZE, 42 );
    for ( int i = 0; i < ( int ) vec.size(); i++ )
        mu_assert( vec[i] == 42, "all vector values must be 42" );
}

MU_TEST( test_vec_iterators_constructor )
{
    std::vector<int> vecInt( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        vecInt[i] = i;
    std::vector<int> vec( vecInt.begin(), vecInt.end() );
    for ( int i = 0; i < ( int ) vec.size(); i++ )
        mu_assert( vec[i] == vecInt[i], "all vector values must be equal" );
}

MU_TEST( test_vec_begin )
{
    std::vector<int> vecInt( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        vecInt[i] = i;
    mu_assert( *( vecInt.begin() ) == 0,
               "vector begin is equal to the first element" );
}

MU_TEST( test_vec_end )
{
    std::vector<int> vecInt( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        vecInt[i] = i;
    mu_assert( *( --vecInt.end() ) == ( TEST_VECTOR_SIZE - 1 ),
               "vector end - 1 is equal to the last element added" );
}

MU_TEST( test_vec_rbegin )
{
    std::vector<int> vecInt( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        vecInt[i] = i;
    mu_assert( *( vecInt.rbegin() ) == 9,
               "vector rbegin is equal to the last element" );
}

MU_TEST( test_vec_rend )
{
    std::vector<int> vecInt( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        vecInt[i] = i;
    mu_assert( *( --vecInt.rend() ) == 0,
               "vector rend - 1 is equal to the first element added" );
}

MU_TEST( test_vec_cbegin )
{
    std::vector<int> vecInt( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        vecInt[i] = i;
    mu_assert( *( vecInt.cbegin() ) == 0,
               "vector cbegin is equal to the first element" );
}

MU_TEST( test_vec_cend )
{
    std::vector<int> vecInt( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        vecInt[i] = i;
    mu_assert( *( --vecInt.cend() ) == ( TEST_VECTOR_SIZE - 1 ),
               "vector cend - 1 is equal to the last element added" );
}

MU_TEST( test_vec_crbegin )
{
    std::vector<int> vecInt( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        vecInt[i] = i;
    mu_assert( *( vecInt.crbegin() ) == 9,
               "vector crbegin is equal to the last element" );
}

MU_TEST( test_vec_crend )
{
    std::vector<int> vecInt( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        vecInt[i] = i;
    mu_assert( *( --vecInt.crend() ) == 0,
               "vector crend - 1 is equal to the first element added" );
}

MU_TEST( test_vec_size )
{
    std::vector<int> vecInt( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        vecInt[i] = i;
    mu_assert( vecInt.size() == TEST_VECTOR_SIZE,
               "vector size is equal to the number of elements added" );
}

MU_TEST( test_vec_max_size )
{
    std::vector<int> vecInt( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        vecInt[i] = i;
    mu_assert( vecInt.max_size() >= TEST_VECTOR_SIZE,
               "vector max_size is greater than or equal to the number of "
               "elements added" );
}

MU_TEST( test_vec_reserve )
{
    std::vector<int> vecMut( TEST_VECTOR_SIZE );
    vecMut.reserve( 2 * TEST_VECTOR_SIZE );

    mu_assert( vecMut.capacity() >= 2 * TEST_VECTOR_SIZE,
               "vector capacity is greater than or equal to the number of "
               "elements reserved" );
}

MU_TEST( test_vec_resize )
{
    std::vector<int> vecMut( TEST_VECTOR_SIZE );

    vecMut.resize( 5 );
    mu_assert( vecMut.size() == 5, "vector size is equal to the new size" );
}

MU_TEST( test_vec_capacity )
{
    std::vector<int> vecInt( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        vecInt[i] = i;
    mu_assert( vecInt.capacity() >= TEST_VECTOR_SIZE,
               "vector capacity is greater than or equal to the number of "
               "elements added" );
}

MU_TEST( test_vec_empty )
{
    std::vector<int> vecInt( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        vecInt[i] = i;
    mu_assert( vecInt.empty() == false, "vector is not empty" );
}

MU_TEST( test_iter_brackets )
{
    std::vector<int> vecInt( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        vecInt[i] = i;
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        mu_assert_int_eq( i, vecInt[i] );
}

MU_TEST( test_vec_int_iter )
{
    std::vector<int> vecInt( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        vecInt[i] = i;
    for ( std::vector<int>::iterator it = vecInt.begin(); it != vecInt.end();
          it++ )
        mu_assert_int_eq( *it, vecInt[it - vecInt.begin()] );
}

MU_TEST( test_vec_reverse_iter )
{
    std::vector<int> vecInt( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        vecInt[i] = i;
    for ( std::vector<int>::reverse_iterator it = vecInt.rbegin();
          it != vecInt.rend();
          it++ )
        mu_assert_int_eq( *it, vecInt[vecInt.rend() - it - 1] );
}

MU_TEST( test_vec_iter_char )
{
    std::vector<char> vecChar( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecChar.size(); i++ )
        vecChar[i] = i + '0';
    for ( std::vector<char>::iterator it = vecChar.begin(); it != vecChar.end();
          it++ )
        mu_assert_int_eq( *it, vecChar[it - vecChar.begin()] );
}

MU_TEST( test_vec_reverse_iter_char )
{
    std::vector<char> vecChar( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecChar.size(); i++ )
        vecChar[i] = i + '0';
    for ( std::vector<char>::reverse_iterator it = vecChar.rbegin();
          it != vecChar.rend();
          it++ )
        mu_assert_int_eq( *it, vecChar[vecChar.rend() - it - 1] );
}

MU_TEST( test_vec_iter_string )
{
    std::vector<std::string> vecStr( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecStr.size(); i++ )
        vecStr[i] = std::to_string( i );
    for ( std::vector<std::string>::iterator it = vecStr.begin();
          it != vecStr.end();
          it++ )
        mu_assert( *it == vecStr[it - vecStr.begin()], "is the same string" );
}

MU_TEST( test_vec_reverse_iter_string )
{
    std::vector<std::string> vecStr( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecStr.size(); i++ )
        vecStr[i] = std::to_string( i );
    for ( std::vector<std::string>::reverse_iterator it = vecStr.rbegin();
          it != vecStr.rend();
          it++ )
        mu_assert( *it == vecStr[vecStr.rend() - it - 1],
                   "is the same reverse string" );
}

MU_TEST( test_vec_assert_out_of_range )
{
    std::vector<int> vecInt( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        vecInt[i] = i;
    try {
        vecInt.at( 100 );
    } catch ( std::out_of_range &e ) {
        mu_assert( true, "out of range exception" );
    }
}

MU_TEST( test_vec_front )
{
    std::vector<int> vecInt( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        vecInt[i] = i;
    mu_assert_int_eq( vecInt.front(), 0 );
}

MU_TEST( test_vec_const_front )
{
    std::vector<int> vecInt( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        vecInt[i] = i;
    const std::vector<int> &vec = vecInt;
    mu_assert_int_eq( vec.front(), 0 );
}

MU_TEST( test_vec_back )
{
    std::vector<int> vecInt( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        vecInt[i] = i;
    mu_assert_int_eq( vecInt.back(), 9 );
}

MU_TEST( test_vec_const_back )
{
    std::vector<int> vecInt( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        vecInt[i] = i;
    const std::vector<int> &vec = vecInt;
    mu_assert_int_eq( vec.back(), 9 );
}

MU_TEST( test_vec_data )
{
    std::vector<int> vecInt( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        vecInt[i] = i;
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        mu_assert_int_eq( i, vecInt.data()[i] );
}

MU_TEST( test_vec_const_data )
{
    std::vector<int> vecInt( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        vecInt[i] = i;
    const std::vector<int> &vec = vecInt;
    for ( int i = 0; i < ( int ) vec.size(); i++ )
        mu_assert_int_eq( i, vec.data()[i] );
}

MU_TEST( test_vec_assign )
{
    std::vector<int> vecMut( TEST_VECTOR_SIZE );
    vecMut.assign( 10, 42 );
    mu_assert_int_eq( 42, vecMut[0] );
}

MU_TEST( test_vec_push_back )
{
    std::vector<int> vecMut( TEST_VECTOR_SIZE );
    vecMut.push_back( 42 );
    mu_assert_int_eq( 42, vecMut[TEST_VECTOR_SIZE] );
}

MU_TEST( test_vec_pop_back )
{
    std::vector<int> vecMut( TEST_VECTOR_SIZE );
    vecMut.push_back( 42 );
    vecMut.push_back( 43 );
    vecMut.pop_back();
    mu_assert_int_eq( *( --vecMut.end() ), 42 );
}

MU_TEST( test_vec_insert_pos_val )
{
    std::vector<int> vecMut( TEST_VECTOR_SIZE );
    vecMut.insert( vecMut.begin(), 42 );
    mu_assert_int_eq( 42, vecMut[0] );
}

MU_TEST( test_vec_insert_pos_nsize_val )
{
    std::vector<int>                vecMut( TEST_VECTOR_SIZE );
    std::vector<int>::iterator      position   = vecMut.begin();
    std::allocator<int>::size_type  n          = 10;
    std::allocator<int>::value_type value_type = 42;

    vecMut.insert( position, n, value_type );
    for ( int i = 0; i < ( int ) n; i++ )
        mu_assert_int_eq( 42, vecMut[i] );
}

MU_TEST( test_vec_insert_pos_range )
{
    std::vector<int> vecInt( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        vecInt[i] = i;
    std::vector<int> vecMut( TEST_VECTOR_SIZE );
    vecMut.insert( vecMut.begin(), vecInt.begin(), vecInt.end() );
    mu_assert_int_eq( 0, vecMut[0] );
}

MU_TEST( test_vec_erase_first )
{
    std::vector<int> vecInt( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        vecInt[i] = i;
    std::vector<int> vecMut( TEST_VECTOR_SIZE );
    vecMut = vecInt;
    vecMut.erase( vecMut.begin() );
    for ( int i = 0; i < ( int ) vecMut.size(); i++ )
        mu_assert( i + 1 == vecMut[i], "values are shistded forward" );
    mu_assert( vecMut.size() == ( TEST_VECTOR_SIZE - 1 ),
               "size is reduced by 1" );
}

MU_TEST( test_vec_erase_range )
{
    std::vector<int> vecInt( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        vecInt[i] = i;
    std::vector<int> vecMut( TEST_VECTOR_SIZE );
    vecMut = vecInt;
    vecMut.erase( vecMut.begin(), vecMut.begin() + 5 );
    for ( int i = 0; i < ( int ) vecMut.size(); i++ )
        mu_assert( i + 5 == vecMut[i], "values are shistded forward" );
    mu_assert( vecMut.size() == ( TEST_VECTOR_SIZE - 5 ),
               "size is reduced by 5" );
}

MU_TEST( test_vec_swap_empty )
{
    std::vector<int> vecMut;
    std::vector<int> vecMut2;
    vecMut.insert( vecMut.begin(), 42 );
    vecMut.swap( vecMut2 );
    mu_assert_int_eq( 42, vecMut2[0] );
    mu_assert_int_eq( 0, vecMut.size() );
    vecMut.swap( vecMut2 );
    mu_assert_int_eq( 42, vecMut[0] );
    mu_assert_int_eq( 0, vecMut2.size() );
}

MU_TEST( test_vec_swap )
{
    std::vector<int> vecMut( TEST_VECTOR_SIZE, 42 );
    std::vector<int> vecMut2( TEST_VECTOR_SIZE, 43 );
    vecMut.swap( vecMut2 );
    mu_assert_int_eq( 43, vecMut[0] );
    mu_assert_int_eq( 42, vecMut2[0] );
}

MU_TEST( test_vec_clear )
{
    std::vector<int> vecMut( TEST_VECTOR_SIZE, 42 );
    vecMut.clear();
    mu_assert_int_eq( 0, vecMut.size() );
}

MU_TEST( test_vec_allocator )
{
    std::vector<int> vecInt( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        vecInt[i] = i;
    std::vector<int> vecMut( vecInt );
    mu_assert( vecMut.get_allocator() == vecInt.get_allocator(),
               "allocator is the same" );
}

MU_TEST( test_vec_lesser_than )
{
    std::vector<int> vecMut( TEST_VECTOR_SIZE, 42 );
    std::vector<int> vecMut2( TEST_VECTOR_SIZE, 43 );
    mu_assert( vecMut < vecMut2, "vecMut is lesser than vecMut2" );
}

MU_TEST( test_vec_less_than_or_equal )
{
    std::vector<int> vecMut( TEST_VECTOR_SIZE, 42 );
    std::vector<int> vecMut2( TEST_VECTOR_SIZE, 43 );
    mu_assert( vecMut <= vecMut2, "vecMut is lesser than vecMut2" );
}

MU_TEST( test_vec_greater_than )
{
    std::vector<int> vecMut( TEST_VECTOR_SIZE, 42 );
    std::vector<int> vecMut2( TEST_VECTOR_SIZE, 43 );
    mu_assert( vecMut2 > vecMut, "vecMut2 is greater than vecMut" );
}

MU_TEST( test_vec_greater_than_or_equal )
{
    std::vector<int> vecMut( TEST_VECTOR_SIZE, 42 );
    std::vector<int> vecMut2( TEST_VECTOR_SIZE, 43 );
    mu_assert( vecMut2 >= vecMut, "vecMut2 is greater than vecMut" );
}

MU_TEST( test_vec_equal )
{
    std::vector<int> vecMut( TEST_VECTOR_SIZE, 42 );
    std::vector<int> vecMut2( TEST_VECTOR_SIZE, 42 );
    mu_assert( vecMut == vecMut2, "vecMut is equal to vecMut2" );
}

MU_TEST( test_vec_not_equal )
{
    std::vector<int> vecMut( TEST_VECTOR_SIZE, 42 );
    std::vector<int> vecMut2( TEST_VECTOR_SIZE, 43 );
    mu_assert( vecMut != vecMut2, "vecMut is not equal to vecMut2" );
}

MU_TEST( test_vec_of_vecs )
{
    std::vector<int> vecInt( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        vecInt[i] = i;
    std::vector<std::vector<int> > vecMut( TEST_VECTOR_SIZE, vecInt );
    mu_assert_int_eq( 0, vecMut[0][0] );
    mu_assert_int_eq( 1, vecMut[0][1] );
    mu_assert_int_eq( 2, vecMut[0][2] );
    mu_assert_int_eq( 3, vecMut[0][3] );
    mu_assert_int_eq( 4, vecMut[0][4] );
}

MU_TEST( test_vec_of_vecs_of_vecs )
{
    std::vector<int> vecInt( TEST_VECTOR_SIZE );
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        vecInt[i] = i;
    std::vector<std::vector<std::vector<int> > > vecMut(
        TEST_VECTOR_SIZE,
        std::vector<std::vector<int> >( TEST_VECTOR_SIZE, vecInt ) );
    mu_assert_int_eq( 0, vecMut[0][0][0] );
    mu_assert_int_eq( 1, vecMut[0][0][1] );
    mu_assert_int_eq( 2, vecMut[0][0][2] );
    mu_assert_int_eq( 3, vecMut[0][0][3] );
    mu_assert_int_eq( 4, vecMut[0][0][4] );
}

MU_TEST_SUITE( suite_vector )
{
    MU_RUN_TEST( test_vec_copy_constructor );
    MU_RUN_TEST( test_vec_integral_constructor );
    MU_RUN_TEST( test_vec_iterators_constructor );
    MU_RUN_TEST( test_vec_begin );
    MU_RUN_TEST( test_vec_end );
    MU_RUN_TEST( test_vec_rbegin );
    MU_RUN_TEST( test_vec_rend );
    MU_RUN_TEST( test_vec_cbegin );
    MU_RUN_TEST( test_vec_cend );
    MU_RUN_TEST( test_vec_crbegin );
    MU_RUN_TEST( test_vec_crend );
    MU_RUN_TEST( test_vec_size );
    MU_RUN_TEST( test_vec_max_size );
    MU_RUN_TEST( test_vec_reserve );
    MU_RUN_TEST( test_vec_resize );
    MU_RUN_TEST( test_vec_capacity );
    MU_RUN_TEST( test_vec_empty );
    MU_RUN_TEST( test_iter_brackets );
    MU_RUN_TEST( test_vec_int_iter );
    MU_RUN_TEST( test_vec_reverse_iter );
    MU_RUN_TEST( test_vec_iter_char );
    MU_RUN_TEST( test_vec_reverse_iter_char );
    MU_RUN_TEST( test_vec_iter_string );
    MU_RUN_TEST( test_vec_reverse_iter_string );
    MU_RUN_TEST( test_vec_assert_out_of_range );
    MU_RUN_TEST( test_vec_front );
    MU_RUN_TEST( test_vec_const_front );
    MU_RUN_TEST( test_vec_back );
    MU_RUN_TEST( test_vec_const_back );
    MU_RUN_TEST( test_vec_data );
    MU_RUN_TEST( test_vec_const_data );
    MU_RUN_TEST( test_vec_assign );
    MU_RUN_TEST( test_vec_push_back );
    MU_RUN_TEST( test_vec_pop_back );
    MU_RUN_TEST( test_vec_insert_pos_val );
    MU_RUN_TEST( test_vec_insert_pos_nsize_val );
    MU_RUN_TEST( test_vec_insert_pos_range );
    MU_RUN_TEST( test_vec_erase_first );
    MU_RUN_TEST( test_vec_erase_range );
    MU_RUN_TEST( test_vec_swap_empty );
    MU_RUN_TEST( test_vec_swap );
    MU_RUN_TEST( test_vec_clear );
    MU_RUN_TEST( test_vec_allocator );
    MU_RUN_TEST( test_vec_lesser_than );
    MU_RUN_TEST( test_vec_less_than_or_equal );
    MU_RUN_TEST( test_vec_greater_than );
    MU_RUN_TEST( test_vec_greater_than_or_equal );
    MU_RUN_TEST( test_vec_equal );
    MU_RUN_TEST( test_vec_not_equal );
    MU_RUN_TEST( test_vec_of_vecs );
    MU_RUN_TEST( test_vec_of_vecs_of_vecs );
}

int main()
{
    MU_RUN_SUITE( suite_algorithm );
    MU_RUN_SUITE( suite_map );
    MU_RUN_SUITE( suite_set );
    MU_SUITE_CONFIGURE( &test_stack_setup, &test_stack_teardown );
    MU_RUN_SUITE( suite_stack );
    MU_RUN_SUITE( suite_type_traits );
    MU_RUN_SUITE( suite_utility );
    MU_RUN_SUITE( suite_vector );
    MU_REPORT();
    return MU_EXIT_CODE;
}
