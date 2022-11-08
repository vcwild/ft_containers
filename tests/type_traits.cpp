#include "type_traits.hpp"
#include "minunit.h"
#include <limits.h>

void test_setup() {}

void test_teardown() {}

template <class T>
typename ft::enable_if<ft::is_integral<T>::type, bool>::type is_odd( T i )
{
    return bool( i % 2 );
}

template < class T,
           class = typename ft::enable_if<ft::is_integral<T>::type>::type>
bool is_even( T i )
{
    return !bool( i % 2 );
}

MU_TEST( test_enable_if_is_even )
{
    mu_assert( is_even( 2 ) == true, "is_even(2) == true" );
    mu_assert( is_even( 3 ) == false, "is_even(3) == false" );
}

MU_TEST( test_enable_if_is_odd )
{
    mu_assert( is_odd( 2 ) == false, "is_odd(2) == false" );
    mu_assert( is_odd( 3 ) == true, "is_odd(3) == true" );
}

MU_TEST( test_is_integral_bool )
{
    mu_assert( ft::is_integral<bool>::type == true,
               "is_integral<bool>::type == true" );
}

MU_TEST( test_is_integral_char )
{
    mu_assert( ft::is_integral<char>::type == true,
               "is_integral<char>::type == true" );
}

MU_TEST( test_is_integral_wchar_t )
{
    mu_assert( ft::is_integral<wchar_t>::type == true,
               "is_integral<wchar_t>::type == true" );
}

MU_TEST( test_is_integral_signed_char )
{
    mu_assert( ft::is_integral<signed char>::type == true,
               "is_integral<signed char>::type == true" );
}

MU_TEST( test_is_integral_short_int )
{
    mu_assert( ft::is_integral<short int>::type == true,
               "is_integral<short int>::type == true" );
}

MU_TEST( test_is_integral_int )
{
    mu_assert( ft::is_integral<int>::type == true,
               "is_integral<int>::type == true" );
}

MU_TEST( test_is_integral_long_int )
{
    mu_assert( ft::is_integral<long int>::type == true,
               "is_integral<long int>::type == true" );
}

MU_TEST( test_is_integral_long_long_int )
{
    mu_assert( ft::is_integral<long long int>::type == true,
               "is_integral<long long int>::type == true" );
}

MU_TEST( test_is_integral_unsigned_char )
{
    mu_assert( ft::is_integral<unsigned char>::type == true,
               "is_integral<unsigned char>::type == true" );
}

MU_TEST( test_is_integral_unsigned_short_int )
{
    mu_assert( ft::is_integral<unsigned short int>::type == true,
               "is_integral<unsigned short int>::type == true" );
}

MU_TEST( test_is_integral_unsigned_int )
{
    mu_assert( ft::is_integral<unsigned int>::type == true,
               "is_integral<unsigned int>::type == true" );
}

MU_TEST( test_is_integral_unsigned_long_int )
{
    mu_assert( ft::is_integral<unsigned long int>::type == true,
               "is_integral<unsigned long int>::type == true" );
}

MU_TEST( test_is_integral_unsigned_long_long_int )
{
    mu_assert( ft::is_integral<unsigned long long int>::type == true,
               "is_integral<unsigned long long int>::type == true" );
}

MU_TEST( test_is_integral_float )
{
    mu_assert( ft::is_integral<float>::type == false,
               "is_integral<float>::type == false" );
}

MU_TEST( test_is_integral_double )
{
    mu_assert( ft::is_integral<double>::type == false,
               "is_integral<double>::type == false" );
}

MU_TEST( test_is_integral_int_volatile )
{
    mu_assert( ft::is_integral<int volatile>::type == true,
               "is_integral<int volatile>::type == true" );
}

MU_TEST( test_is_integral_int_const )
{
    mu_assert( ft::is_integral<int const>::type == true,
               "is_integral<int const>::type == true" );
}

MU_TEST( test_is_integral_int_const_volatile )
{
    mu_assert( ft::is_integral<int const volatile>::type == true,
               "is_integral<int const volatile>::type == true" );
}

MU_TEST( test_is_integral_int_ptr )
{
    mu_assert( ft::is_integral<int *>::type == false,
               "is_integral<int *>::type == false" );
}

MU_TEST( test_is_integral_int_const_ptr )
{
    mu_assert( ft::is_integral<int const *>::type == false,
               "is_integral<int const *>::type == false" );
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
    MU_RUN_TEST( test_enable_if_is_even );
    MU_RUN_TEST( test_enable_if_is_odd );
}

int main()
{
    MU_SUITE_CONFIGURE( &test_setup, &test_teardown );
    MU_RUN_SUITE( suite_type_traits );
    MU_REPORT();
    return MU_EXIT_CODE;
}
