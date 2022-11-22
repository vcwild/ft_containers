/*
 * Copyright 2022 ©️ vcwild under the GNU Affero General Public License v3.0.
 */
#include "type_traits.hpp"
#include "minunit.h"
#include <limits.h>

MU_TEST( test_is_integral_bool )
{
    mu_assert( ft::is_integral<bool>::value == true,
               "is_integral<bool>::value == true" );
}

MU_TEST( test_is_integral_char )
{
    mu_assert( ft::is_integral<char>::value == true,
               "is_integral<char>::value == true" );
}

MU_TEST( test_is_integral_wchar_t )
{
    mu_assert( ft::is_integral<wchar_t>::value == true,
               "is_integral<wchar_t>::value == true" );
}

MU_TEST( test_is_integral_signed_char )
{
    mu_assert( ft::is_integral<signed char>::value == true,
               "is_integral<signed char>::value == true" );
}

MU_TEST( test_is_integral_short_int )
{
    mu_assert( ft::is_integral<short int>::value == true,
               "is_integral<short int>::value == true" );
}

MU_TEST( test_is_integral_int )
{
    mu_assert( ft::is_integral<int>::value == true,
               "is_integral<int>::value == true" );
}

MU_TEST( test_is_integral_long_int )
{
    mu_assert( ft::is_integral<long int>::value == true,
               "is_integral<long int>::value == true" );
}

MU_TEST( test_is_integral_long_long_int )
{
    mu_assert( ft::is_integral<long long int>::value == true,
               "is_integral<long long int>::value == true" );
}

MU_TEST( test_is_integral_unsigned_char )
{
    mu_assert( ft::is_integral<unsigned char>::value == true,
               "is_integral<unsigned char>::value == true" );
}

MU_TEST( test_is_integral_unsigned_short_int )
{
    mu_assert( ft::is_integral<unsigned short int>::value == true,
               "is_integral<unsigned short int>::value == true" );
}

MU_TEST( test_is_integral_unsigned_int )
{
    mu_assert( ft::is_integral<unsigned int>::value == true,
               "is_integral<unsigned int>::value == true" );
}

MU_TEST( test_is_integral_unsigned_long_int )
{
    mu_assert( ft::is_integral<unsigned long int>::value == true,
               "is_integral<unsigned long int>::value == true" );
}

MU_TEST( test_is_integral_unsigned_long_long_int )
{
    mu_assert( ft::is_integral<unsigned long long int>::value == true,
               "is_integral<unsigned long long int>::value == true" );
}

MU_TEST( test_is_integral_float )
{
    mu_assert( ft::is_integral<float>::value == false,
               "is_integral<float>::value == false" );
}

MU_TEST( test_is_integral_double )
{
    mu_assert( ft::is_integral<double>::value == false,
               "is_integral<double>::value == false" );
}

MU_TEST( test_is_integral_int_volatile )
{
    mu_assert( ft::is_integral<int volatile>::value == true,
               "is_integral<int volatile>::value == true" );
}

MU_TEST( test_is_integral_int_const )
{
    mu_assert( ft::is_integral<int const>::value == true,
               "is_integral<int const>::value == true" );
}

MU_TEST( test_is_integral_int_const_volatile )
{
    mu_assert( ft::is_integral<int const volatile>::value == true,
               "is_integral<int const volatile>::value == true" );
}

MU_TEST( test_is_integral_int_ptr )
{
    mu_assert( ft::is_integral<int *>::value == false,
               "is_integral<int *>::value == false" );
}

MU_TEST( test_is_integral_int_const_ptr )
{
    mu_assert( ft::is_integral<int const *>::value == false,
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

int main()
{
    MU_RUN_SUITE( suite_type_traits );
    MU_REPORT();
    return MU_EXIT_CODE;
}
