#include "algorithm.hpp"
#include "minunit.h"
#include <functional>
#include <iostream>
#include <string>

bool is_palindrome( const std::string &s )
{
    return ft::equal( s.begin(), s.begin() + s.size() / 2, s.rbegin() );
}

bool is_equal( const std::string &s1, const std::string &s2 )
{
    return ft::equal( s1.begin(), s1.end(), s2.begin() );
}

bool is_lexicographical_compare( const std::string &s1, const std::string &s2 )
{
    return ft::lexicographical_compare(
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

int main()
{
    MU_RUN_SUITE( suite_algorithm );
    MU_REPORT();
    return MU_EXIT_CODE;
}
