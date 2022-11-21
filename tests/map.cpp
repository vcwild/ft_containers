#include "map.hpp"
#include "minunit.h"

MU_TEST( test_map_assignment )
{

    ft::map<const char *, int> m;

    m["a"] = 4;
    m["b"] = 5;
    m["c"] = 6;

    mu_assert( m["a"] == 4, "m[\"a\"] == 4" );
    mu_assert( m["b"] == 5, "m[\"b\"] == 5" );
    mu_assert( m["c"] == 6, "m[\"c\"] == 6" );
    mu_assert( m.size() == 3, "m.size() == 3" );

    ft::map<const char *, int> mcopy( m );
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
    ft::map<char, std::string> m;

    m.insert( ft::make_pair( 'a', "amora" ) );
    m.insert( ft::make_pair( 'b', "banana" ) );

    mu_assert( m.size() == 2, "m.size() == 2" );
    mu_assert( m['a'] == "amora", "m['a'] == \"amora\"" );
    mu_assert( m['b'] == "banana", "m['b'] == \"banana\"" );
}

MU_TEST( test_map_string_pairs )
{
    ft::map<const std::string, int> v;

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
    ft::map<int, int> m;
    for ( int i = 0; i < 50; i++ ) {
        m[i] = i;
    }

    // iterate over the map and check that the values are correct
    ft::map<int, int>::iterator it  = m.begin();
    ft::map<int, int>::iterator ite = m.end();
    for ( int i = 0; it != ite; ++it, ++i ) {
        mu_assert( it->first == i, "it->first == i" );
        mu_assert( it->second == i, "it->second == i" );
    }
}

MU_TEST( test_map_add_duplicates )
{
    ft::map<int, int> m;
    m[1] = 9;
    m[1] = 10;
    mu_assert( m.size() == 1, "m.size() == 1" );
    mu_assert( m[1] == 10, "m[1] == 10" );
}

MU_TEST( test_map_find )
{
    ft::map<int, int> m;
    for ( int i = 0; i < 10; i++ ) {
        m[i] = i + 2;
    }

    ft::map<int, int>::iterator it = m.find( 5 );
    mu_assert( it->first == 5, "it->first == 5" );
    mu_assert( it->second == 7, "it->second == 7" );
    it = m.find( 11 );
    mu_assert( it == m.end(), "it is at map end" );
}

MU_TEST( test_map_erase_iterator )
{
    ft::map<int, int> m;
    for ( int i = 0; i < 10; i++ ) {
        m[i] = i + 2;
    }

    ft::map<int, int>::iterator it = m.find( 5 );
    m.erase( it );
    mu_assert( m.size() == 9, "m.size() == 9" );
    mu_assert( m[5] == 0, "m[5] == 0" );
}

MU_TEST( test_map_key_compare )
{
    ft::map<int, int> m;
    for ( int i = 0; i < 10; i++ ) {
        m[i] = i + 2;
    }

    ft::map<int, int>::key_compare comp = m.key_comp();
    ft::map<int, int>::iterator    it   = m.begin();
    ft::map<int, int>::iterator    ite  = m.end();
    for ( int i = 0; it != ite; ++it, ++i ) {
        mu_assert( !comp( it->first, it->first ),
                   "not comp( it->first, it->first )" );
    }
}

MU_TEST( test_map_insert_input_iterator )
{
    ft::map<int, int>           m;
    ft::map<int, int>::iterator it;

    it = m.insert( m.begin(), ft::make_pair( 1, 1 ) );
    mu_assert( it->first == 1, "it->first == 1" );
    mu_assert( it->second == 1, "it->second == 1" );
    mu_assert( m.size() == 1, "m.size() == 1" );

    it = m.insert( m.begin(), ft::make_pair( 2, 2 ) );
    mu_assert( it->first == 2, "it->first == 2" );
    mu_assert( it->second == 2, "it->second == 2" );
    mu_assert( m.size() == 2, "m.size() == 2" );

    it = m.insert( m.begin(), ft::make_pair( 3, 3 ) );
    mu_assert( it->first == 3, "it->first == 3" );
    mu_assert( it->second == 3, "it->second == 3" );
    mu_assert( m.size() == 3, "m.size() == 3" );

    it = m.insert( m.begin(), ft::make_pair( 4, 4 ) );
    mu_assert( it->first == 4, "it->first == 4" );
    mu_assert( it->second == 4, "it->second == 4" );
    mu_assert( m.size() == 4, "m.size() == 4" );

    it = m.insert( m.begin(), ft::make_pair( 5, 5 ) );
    mu_assert( it->first == 5, "it->first == 5" );
    mu_assert( it->second == 5, "it->second == 5" );
    mu_assert( m.size() == 5, "m.size() == 5" );
}

MU_TEST( test_map_swap )
{
    ft::map<char, int> foo, bar;

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
    ft::map<int, int> m;
    mu_assert( m.max_size() > 0, "m.max_size() > 0" );
}

MU_TEST( test_map_count )
{
    ft::map<int, int> m;
    for ( int i = 0; i < 10; i++ ) {
        m[i] = i + 2;
    }

    mu_assert( m.count( 5 ) == 1, "m.count( 5 ) == 1" );
    mu_assert( m.count( 11 ) == 0, "m.count( 11 ) == 0" );
}

MU_TEST( test_map_lower_bound )
{
    ft::map<int, int> m;
    for ( int i = 0; i < 10; i++ ) {
        m[i] = i + 2;
    }

    ft::map<int, int>::iterator it = m.lower_bound( 5 );
    mu_assert( it->first == 5, "it->first == 5" );
    mu_assert( it->second == 7, "it->second == 7" );
    it = m.lower_bound( 11 );
    mu_assert( it == m.end(), "it is at map end" );
}

MU_TEST( test_map_upper_bound )
{
    ft::map<int, int> m;
    for ( int i = 0; i < 10; i++ ) {
        m[i] = i + 2;
    }

    ft::map<int, int>::iterator it = m.upper_bound( 5 );
    mu_assert( it->first == 6, "it->first == 6" );
    mu_assert( it->second == 8, "it->second == 8" );
    it = m.upper_bound( 11 );
    mu_assert( it == m.end(), "it is at map end" );
}

MU_TEST( test_map_equal_range )
{
    ft::map<int, int> m;
    for ( int i = 0; i < 10; i++ ) {
        m[i] = i + 2;
    }

    ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator> ret;
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
    ft::map<int, int> m1;
    ft::map<int, int> m2;
    for ( int i = 0; i < 10; i++ ) {
        m1[i] = i + 2;
        m2[i] = i + 2;
    }
    mu_assert( m1 == m2, "m1 == m2" );
}

MU_TEST( test_map_not_equal )
{
    ft::map<int, int> m1;
    ft::map<int, int> m2;
    for ( int i = 0; i < 10; i++ ) {
        m1[i] = i + 2;
        m2[i] = i + 2;
    }
    m2[5] = 42;
    mu_assert( m1 != m2, "m1 != m2" );
}

MU_TEST( test_map_less_than )
{
    ft::map<int, int> m1;
    ft::map<int, int> m2;
    for ( int i = 0; i < 10; i++ ) {
        m1[i] = i + 2;
        m2[i] = i + 2;
    }
    m2[5] = 42;
    mu_assert( m1 < m2, "m1 < m2" );
}

MU_TEST( test_map_less_than_or_equal )
{
    ft::map<int, int> m1;
    ft::map<int, int> m2;
    for ( int i = 0; i < 10; i++ ) {
        m1[i] = i + 2;
        m2[i] = i + 2;
    }
    m2[5] = 42;
    mu_assert( m1 <= m2, "m1 <= m2" );
}

MU_TEST( test_map_greater_than )
{
    ft::map<int, int> m1;
    ft::map<int, int> m2;
    for ( int i = 0; i < 10; i++ ) {
        m1[i] = i + 2;
        m2[i] = i + 2;
    }
    m2[5] = 42;
    mu_assert( m2 > m1, "m2 > m1" );
}

MU_TEST( test_map_greater_than_or_equal )
{
    ft::map<int, int> m1;
    ft::map<int, int> m2;
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

int main()
{
    MU_RUN_SUITE( suite_map );
    MU_REPORT();
    return MU_EXIT_CODE;
}
