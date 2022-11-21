#include "set.hpp"
#include "minunit.h"

void test_setup() {}

void test_teardown() {}

MU_TEST( test_set_create )
{
    ft::set<int>           s;
    ft::set<int>::iterator it;

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
    ft::set<int>           s;
    ft::set<int>::iterator it;

    for ( int i = 1; i <= 5; i++ ) {
        s.insert( i * 10 );
    }

    ft::set<int> s2( s );
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
    ft::set<int>           s;
    ft::set<int>::iterator it;

    for ( int i = 1; i <= 5; i++ ) {
        s.insert( i * 10 );
    }

    mu_assert_int_eq( s.size(), 5 );
    mu_assert_int_eq( s.empty(), false );
}

MU_TEST( test_set_pair_insert )
{
    ft::set<int>           s;
    ft::set<int>::iterator it;

    for ( int i = 1; i <= 5; i++ ) {
        s.insert( i * 10 );
    }

    ft::pair<ft::set<int>::iterator, bool> p = s.insert( 20 );
    mu_assert_int_eq( *p.first, 20 );
    mu_assert_int_eq( p.second, false );
    mu_assert_int_eq( s.size(), 5 );
}

MU_TEST( test_set_iterator_insert )
{
    ft::set<int>           s;
    ft::set<int>::iterator it;

    for ( int i = 1; i <= 5; i++ ) {
        s.insert( i * 10 );
    }

    it = s.insert( s.begin(), 20 );
    mu_assert_int_eq( *it, 20 );
    mu_assert_int_eq( s.size(), 5 );
}

MU_TEST( test_set_input_iterator )
{
    ft::set<int>           s;
    ft::set<int>::iterator it;

    for ( int i = 1; i <= 5; i++ ) {
        s.insert( i * 10 );
    }

    ft::set<int> s2( s.begin(), s.end() );
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
    ft::set<int>           s;
    ft::set<int>::iterator it;

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
    ft::set<int>           s;
    ft::set<int>::iterator it;

    for ( int i = 1; i <= 5; i++ ) {
        s.insert( i * 10 );
    }

    ft::set<int> s2;
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
    ft::set<int>           s;
    ft::set<int>::iterator it;

    for ( int i = 1; i <= 5; i++ ) {
        s.insert( i * 10 );
    }

    s.clear();
    mu_assert_int_eq( s.size(), 0 );
    mu_assert_int_eq( s.empty(), true );
}

MU_TEST( test_set_observers )
{
    ft::set<int>           s;
    ft::set<int>::iterator it;

    for ( int i = 1; i <= 5; i++ ) {
        s.insert( i * 10 );
    }

    ft::set<int>::key_compare comp = s.key_comp();
    mu_assert_int_eq( comp( 10, 20 ), true );
    mu_assert_int_eq( comp( 20, 10 ), false );
    mu_assert_int_eq( comp( 20, 20 ), false );
}

MU_TEST( test_set_count )
{
    ft::set<int>           s;
    ft::set<int>::iterator it;

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
    ft::set<int>           s;
    ft::set<int>::iterator it;

    for ( int i = 1; i <= 5; i++ ) {
        s.insert( i * 10 );
    }

    it = s.lower_bound( 20 );
    mu_assert_int_eq( *it, 20 );
    it = s.upper_bound( 20 );
    mu_assert_int_eq( *it, 30 );
    ft::pair<ft::set<int>::iterator, ft::set<int>::iterator> p
        = s.equal_range( 20 );
    mu_assert_int_eq( *p.first, 20 );
    mu_assert_int_eq( *p.second, 30 );
}

MU_TEST( test_set_lesser )
{
    ft::set<int> s;
    s.insert( 1 );
    s.insert( 2 );
    s.insert( 3 );
    s.insert( 4 );
    s.insert( 5 );

    ft::set<int>::iterator it  = s.begin();
    ft::set<int>::iterator ite = s.end();
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
    ft::set<int> s;
    s.insert( 1 );
    s.insert( 2 );
    s.insert( 3 );
    s.insert( 4 );
    s.insert( 5 );

    ft::set<int>::reverse_iterator it  = s.rbegin();
    ft::set<int>::reverse_iterator ite = s.rend();
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
    ft::set<int> s;
    s.insert( 1 );
    s.insert( 2 );
    s.insert( 3 );
    s.insert( 4 );
    s.insert( 5 );

    ft::set<int>::iterator it  = s.begin();
    ft::set<int>::iterator ite = s.end();
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
    ft::set<int> s;
    s.insert( 1 );
    s.insert( 2 );
    s.insert( 3 );
    s.insert( 4 );
    s.insert( 5 );

    ft::set<int>::reverse_iterator it  = s.rbegin();
    ft::set<int>::reverse_iterator ite = s.rend();
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
    ft::set<int> s1;
    ft::set<int> s2;
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
    ft::set<int> s1;
    ft::set<int> s2;
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

int main()
{
    MU_SUITE_CONFIGURE( &test_setup, &test_teardown );
    MU_RUN_SUITE( suite_set );
    MU_REPORT();
    return MU_EXIT_CODE;
}
