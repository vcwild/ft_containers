#include "vector.hpp"
#include "minunit.h"
#include <string>

#define TEST_VECTOR_SIZE 10

static ft::vector<int>         vecInt( TEST_VECTOR_SIZE );
static ft::vector<char>        vecChar( TEST_VECTOR_SIZE );
static ft::vector<std::string> vecStr( TEST_VECTOR_SIZE );

void test_setup()
{
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        vecInt[i] = i;
    for ( int i = 0; i < ( int ) vecChar.size(); i++ )
        vecChar[i] = i + '0';
    for ( int i = 0; i < ( int ) vecStr.size(); i++ )
        vecStr[i] = std::to_string( i );
}

void test_teardown() {}

MU_TEST( test_iter )
{
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        mu_assert_int_eq( i, vecInt[i] );
}

MU_TEST( test_vec_iter )
{
    for ( ft::vector<int>::iterator it = vecInt.begin(); it != vecInt.end();
          it++ )
        mu_assert_int_eq( *it, vecInt[it - vecInt.begin()] );
}

MU_TEST( test_vec_const_iter )
{
    for ( ft::vector<int>::const_iterator it = vecInt.begin();
          it != vecInt.end();
          it++ )
        mu_assert_int_eq( *it, vecInt[it - vecInt.begin()] );
}

MU_TEST( test_vec_reverse_iter )
{
    for ( ft::vector<int>::reverse_iterator it = vecInt.rbegin();
          it != vecInt.rend();
          it++ )
        mu_assert_int_eq( *it, vecInt[vecInt.rend() - it - 1] );
}

MU_TEST( test_vec_const_reverse_iter )
{
    for ( ft::vector<int>::const_reverse_iterator it = vecInt.rbegin();
          it != vecInt.rend();
          it++ )
        mu_assert_int_eq( *it, vecInt[vecInt.rend() - it - 1] );
}

MU_TEST( test_vec_iter_char )
{
    for ( ft::vector<char>::iterator it = vecChar.begin(); it != vecChar.end();
          it++ )
        mu_assert_int_eq( *it, vecChar[it - vecChar.begin()] );
}

MU_TEST( test_vec_const_iter_char )
{
    for ( ft::vector<char>::const_iterator it = vecChar.begin();
          it != vecChar.end();
          it++ )
        mu_assert_int_eq( *it, vecChar[it - vecChar.begin()] );
}

MU_TEST( test_vec_reverse_iter_char )
{
    for ( ft::vector<char>::reverse_iterator it = vecChar.rbegin();
          it != vecChar.rend();
          it++ )
        mu_assert_int_eq( *it, vecChar[vecChar.rend() - it - 1] );
}

MU_TEST( test_vec_const_reverse_iter_char )
{
    for ( ft::vector<char>::const_reverse_iterator it = vecChar.rbegin();
          it != vecChar.rend();
          it++ )
        mu_assert_int_eq( *it, vecChar[vecChar.rend() - it - 1] );
}

MU_TEST( test_vec_iter_string )
{
    for ( ft::vector<std::string>::iterator it = vecStr.begin();
          it != vecStr.end();
          it++ )
        mu_assert( *it == vecStr[it - vecStr.begin()], "is string" );
}

MU_TEST( test_vec_const_iter_string )
{
    for ( ft::vector<std::string>::const_iterator it = vecStr.begin();
          it != vecStr.end();
          it++ )
        mu_assert( *it == vecStr[it - vecStr.begin()], "is constant string" );
}

MU_TEST( test_vec_reverse_iter_string )
{
    for ( ft::vector<std::string>::reverse_iterator it = vecStr.rbegin();
          it != vecStr.rend();
          it++ )
        mu_assert( *it == vecStr[vecStr.rend() - it - 1], "is reverse string" );
}

MU_TEST( test_vec_const_reverse_iter_string )
{
    for ( ft::vector<std::string>::const_reverse_iterator it = vecStr.rbegin();
          it != vecStr.rend();
          it++ )
        mu_assert( *it == vecStr[vecStr.rend() - it - 1],
                   "is constant reverse string" );
}

MU_TEST_SUITE( suite_vector )
{
    MU_RUN_TEST( test_iter );
    MU_RUN_TEST( test_vec_iter );
    MU_RUN_TEST( test_vec_const_iter );
    MU_RUN_TEST( test_vec_reverse_iter );
    MU_RUN_TEST( test_vec_const_reverse_iter );
    MU_RUN_TEST( test_vec_iter_char );
    MU_RUN_TEST( test_vec_const_iter_char );
    MU_RUN_TEST( test_vec_reverse_iter_char );
    MU_RUN_TEST( test_vec_const_reverse_iter_char );
    MU_RUN_TEST( test_vec_iter_string );
    MU_RUN_TEST( test_vec_const_iter_string );
    MU_RUN_TEST( test_vec_reverse_iter_string );
    MU_RUN_TEST( test_vec_const_reverse_iter_string );
}

int main()
{
    MU_SUITE_CONFIGURE( &test_setup, &test_teardown );
    MU_RUN_SUITE( suite_vector );
    MU_REPORT();
    return MU_EXIT_CODE;
}
