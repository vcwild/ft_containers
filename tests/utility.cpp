/*
 * Copyright 2022 ©️ vcwild under the GNU Affero General Public License v3.0.
 */
#include "utility.hpp"
#include "minunit.h"

MU_TEST( test_int_float_pair )
{
    ft::pair<int, float> p1( 42, 3.14 );

    mu_assert_int_eq( p1.first, 42 );
    mu_assert_double_eq( p1.second, 3.140000104904 );
}

MU_TEST( test_char_int_pair )
{
    ft::pair<char, int> p1( 'a', 42 );

    mu_assert_int_eq( p1.first, 'a' );
    mu_assert_int_eq( p1.second, 42 );
}

MU_TEST( test_string_string_pair )
{
    ft::pair<std::string, std::string> p1( "Hello", "World" );

    mu_assert_string_eq( p1.first.c_str(), "Hello" );
    mu_assert_string_eq( p1.second.c_str(), "World" );
}

MU_TEST( test_pair_equality )
{
    ft::pair<int, float> p1( 42, 3.14 );
    ft::pair<int, float> p2( 42, 3.14 );

    mu_assert( p1 == p2, "p1 == p2" );
}

MU_TEST( test_pair_inequality )
{
    ft::pair<int, float> p1( 42, 3.14 );
    ft::pair<int, float> p2( 42, 3.15 );

    mu_assert( p1 != p2, "p1 != p2" );
}

MU_TEST( test_pair_less_than )
{
    ft::pair<int, float> p1( 42, 3.14 );
    ft::pair<int, float> p2( 42, 3.15 );

    mu_assert( p1 < p2, "p1 < p2" );
}

MU_TEST( test_pair_less_than_or_equal )
{
    ft::pair<int, float> p1( 42, 3.14 );
    ft::pair<int, float> p2( 42, 3.14 );

    mu_assert( p1 <= p2, "p1 <= p2" );
}

MU_TEST( test_pair_greater_than )
{
    ft::pair<int, float> p1( 42, 3.15 );
    ft::pair<int, float> p2( 42, 3.14 );

    mu_assert( p1 > p2, "p1 > p2" );
}

MU_TEST( test_pair_greater_than_or_equal )
{
    ft::pair<int, float> p1( 42, 3.14 );
    ft::pair<int, float> p2( 42, 3.14 );

    mu_assert( p1 >= p2, "p1 >= p2" );
}

MU_TEST( test_assignment_operator )
{
    ft::pair<int, float> p1( 42, 3.14 );
    ft::pair<int, float> p2;

    p2 = p1;

    mu_assert_int_eq( p2.first, p1.first );
    mu_assert_double_eq( p2.second, p1.second );
}

MU_TEST( test_make_pair )
{
    ft::pair<int, float> p1( 42, 3.14 );
    ft::pair<int, float> p2 = ft::make_pair( p1.first, p1.second );

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

int main()
{
    MU_RUN_SUITE( suite_utility );
    MU_REPORT();
    return MU_EXIT_CODE;
}
