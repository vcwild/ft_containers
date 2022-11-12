#include "iterator.hpp"
#include "minunit.h"
#include <stdexcept>

using namespace ft;

void test_setup() {}

void test_teardown() {}

MU_TEST( test_create_int_iterator )
{
    int                           a[5] = { 1, 2, 3, 4, 5 };
    int                          *p    = a;
    random_access_iterator<int *> it( p );
    mu_check( it.base() == p );
    mu_check( *it == 1 );
    mu_check( *( it + 1 ) == 2 );
    mu_check( *( ++it ) == 2 );
    mu_check( *( it++ ) == 2 );
    mu_check( *( it ) == 3 );
    mu_check( *( it - 2 ) == 1 );
    mu_check( *( --it ) == 2 );
    mu_check( *( it-- ) == 2 );
    mu_check( *( it + 2 ) == 3 );
    mu_check( it[2] == 3 );
}

MU_TEST( test_compare_iterators )
{
    int                           a[6] = { 1, 2, 3, 4, 5, 1 };
    int                          *p    = a;
    random_access_iterator<int *> it( p );
    random_access_iterator<int *> it2( p + 2 );
    mu_check( it.operator==( it ) );
    mu_check( it == it );
    mu_check( it.operator!=( it + 2 ) );
    mu_check( it != ( it2 ) );
    mu_check( it.operator<( it + 2 ) );
    mu_check( it < it2 );
    mu_check( it.operator<=( it + 2 ) );
    mu_check( it <= it2 );
    mu_check( ( it + 2 ).operator>( it ) );
    mu_check( it2 > it );
    mu_check( ( it + 2 ).operator>=( it ) );
    mu_check( it2 >= it );
}

MU_TEST( test_difference_between_two_iterators )
{
    int                           a[5] = { 1, 2, 3, 4, 5 };
    int                          *p    = a;
    random_access_iterator<int *> it( p );
    random_access_iterator<int *> it2( p + 3 );
    mu_check( it2.operator-( it ) == 3 );
    mu_check( it2 - it == 3 );
    mu_check( it.operator-( it2 ) == -3 );
    mu_check( it - it2 == -3 );
}

MU_TEST( test_iterate_while_true_loop )
{
    int                           a[5] = { 1, 2, 3, 4, 5 };
    int                          *p    = a;
    random_access_iterator<int *> it( p );
    random_access_iterator<int *> it2( p + 3 );
    int                           i = 0;
    while ( it != it2 ) {
        mu_check( *it == a[i] );
        ++it;
        ++i;
    }
}

MU_TEST( test_access_invalid_index )
{
    int                           a[5] = { 1, 2, 3, 4, 5 };
    int                          *p    = a;
    random_access_iterator<int *> it( p );
    try {
        it[5];
    } catch ( std::out_of_range &e ) {
        mu_check( true );
    }
    try {
        it[-1];
    } catch ( std::out_of_range &e ) {
        mu_check( true );
    }
}

MU_TEST( test_swap_iterators )
{
    int                           a[5] = { 1, 2, 3, 4, 5 };
    int                          *p    = a;
    random_access_iterator<int *> it( p );
    random_access_iterator<int *> it2( p + 3 );
    swap( it, it2 );
    mu_check( *it == 4 );
    mu_check( *it2 == 1 );
    it.swap( it2 );
    mu_check( *it == 1 );
    mu_check( *it2 == 4 );
}

MU_TEST( test_compare_iterators_int_char )
{
    int                            a[5] = { 48, 49, 50, 51, 52 };
    char                           b[5] = { '0', '1', '2', '3', '4' };
    random_access_iterator<int *>  it( a );
    random_access_iterator<char *> it2( b );

    mu_check( it == it2 );
    mu_check( it2 == it );
    mu_check( it != it2 );
}

MU_TEST_SUITE( suite_name )
{
    MU_RUN_TEST( test_create_int_iterator );
    MU_RUN_TEST( test_compare_iterators );
    MU_RUN_TEST( test_difference_between_two_iterators );
    MU_RUN_TEST( test_iterate_while_true_loop );
    MU_RUN_TEST( test_access_invalid_index );
    MU_RUN_TEST( test_swap_iterators );
    MU_RUN_TEST( test_compare_iterators_int_char );
}

int main()
{
    MU_SUITE_CONFIGURE( &test_setup, &test_teardown );
    MU_RUN_SUITE( suite_name );
    MU_REPORT();
    return MU_EXIT_CODE;
}
