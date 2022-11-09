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

MU_TEST( test_vec_begin )
{
    mu_assert( *( vecInt.begin() ) == 0,
               "vector begin is equal to the first element" );
}

MU_TEST( test_vec_end )
{
    mu_assert( *( --vecInt.end() ) == ( TEST_VECTOR_SIZE - 1 ),
               "vector end - 1 is equal to the last element added" );
}

MU_TEST( test_vec_rbegin )
{
    mu_assert( *( vecInt.rbegin() ) == 9,
               "vector rbegin is equal to the last element" );
}

MU_TEST( test_vec_rend )
{
    mu_assert( *( --vecInt.rend() ) == 0,
               "vector rend - 1 is equal to the first element added" );
}

MU_TEST( test_vec_cbegin )
{
    mu_assert( *( vecInt.cbegin() ) == 0,
               "vector cbegin is equal to the first element" );
}

MU_TEST( test_vec_cend )
{
    mu_assert( *( --vecInt.cend() ) == ( TEST_VECTOR_SIZE - 1 ),
               "vector cend - 1 is equal to the last element added" );
}

MU_TEST( test_vec_crbegin )
{
    mu_assert( *( vecInt.crbegin() ) == 9,
               "vector crbegin is equal to the last element" );
}

MU_TEST( test_vec_crend )
{
    mu_assert( *( --vecInt.crend() ) == 0,
               "vector crend - 1 is equal to the first element added" );
}

MU_TEST( test_vec_size )
{
    mu_assert( vecInt.size() == TEST_VECTOR_SIZE,
               "vector size is equal to the number of elements added" );
}

MU_TEST( test_vec_max_size )
{
    mu_assert( vecInt.max_size() >= TEST_VECTOR_SIZE,
               "vector max_size is greater than or equal to the number of "
               "elements added" );
}

MU_TEST( test_vec_reserve )
{
    ft::vector<int> vecInt2( TEST_VECTOR_SIZE );
    vecInt2.reserve( 2 * TEST_VECTOR_SIZE );

    mu_assert( vecInt2.capacity() >= 2 * TEST_VECTOR_SIZE,
               "vector capacity is greater than or equal to the number of "
               "elements reserved" );
}

MU_TEST( test_vec_resize )
{
    ft::vector<int> vecInt2( TEST_VECTOR_SIZE );

    vecInt2.resize( 5 );
    mu_assert( vecInt2.size() == 5, "vector size is equal to the new size" );
}

MU_TEST( test_vec_capacity )
{
    mu_assert( vecInt.capacity() >= TEST_VECTOR_SIZE,
               "vector capacity is greater than or equal to the number of "
               "elements added" );
}

MU_TEST( test_vec_empty )
{
    mu_assert( vecInt.empty() == false, "vector is not empty" );
}

MU_TEST( test_iter_brackets )
{
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        mu_assert_int_eq( i, vecInt[i] );
}

MU_TEST( test_vec_int_iter )
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
        mu_assert( *it == vecStr[it - vecStr.begin()], "is the same string" );
}

MU_TEST( test_vec_const_iter_string )
{
    for ( ft::vector<std::string>::const_iterator it = vecStr.begin();
          it != vecStr.end();
          it++ )
        mu_assert( *it == vecStr[it - vecStr.begin()],
                   "is the same constant string" );
}

MU_TEST( test_vec_reverse_iter_string )
{
    for ( ft::vector<std::string>::reverse_iterator it = vecStr.rbegin();
          it != vecStr.rend();
          it++ )
        mu_assert( *it == vecStr[vecStr.rend() - it - 1],
                   "is the same reverse string" );
}

MU_TEST( test_vec_const_reverse_iter_string )
{
    for ( ft::vector<std::string>::const_reverse_iterator it = vecStr.rbegin();
          it != vecStr.rend();
          it++ )
        mu_assert( *it == vecStr[vecStr.rend() - it - 1],
                   "is the same constant reverse string" );
}

MU_TEST( test_vec_assert_out_of_range )
{
    try {
        vecInt.at( 100 );
    } catch ( std::out_of_range &e ) {
        mu_assert( true, "out of range exception" );
    }
}

MU_TEST( test_vec_front ) { mu_assert_int_eq( vecInt.front(), 0 ); }

MU_TEST( test_vec_const_front )
{
    const ft::vector<int> &vec = vecInt;
    mu_assert_int_eq( vec.front(), 0 );
}

MU_TEST( test_vec_back ) { mu_assert_int_eq( vecInt.back(), 9 ); }

MU_TEST( test_vec_const_back )
{
    const ft::vector<int> &vec = vecInt;
    mu_assert_int_eq( vec.back(), 9 );
}

MU_TEST( test_vec_data )
{
    for ( int i = 0; i < ( int ) vecInt.size(); i++ )
        mu_assert_int_eq( i, vecInt.data()[i] );
}

MU_TEST( test_vec_const_data )
{
    const ft::vector<int> &vec = vecInt;
    for ( int i = 0; i < ( int ) vec.size(); i++ )
        mu_assert_int_eq( i, vec.data()[i] );
}

MU_TEST( test_vec_assign )
{
    ft::vector<int> vecInt2( TEST_VECTOR_SIZE );
    vecInt2.assign( 10, 42 );
    mu_assert_int_eq( 42, vecInt2[0] );
}

MU_TEST( test_vec_push_back )
{
    ft::vector<int> vecInt2( TEST_VECTOR_SIZE );
    vecInt2.push_back( 42 );
    mu_assert_int_eq( 42, vecInt2[TEST_VECTOR_SIZE] );
}

MU_TEST( test_vec_pop_back )
{
    ft::vector<int> vecInt2( TEST_VECTOR_SIZE );
    vecInt2.push_back( 42 );
    vecInt2.push_back( 43 );
    vecInt2.pop_back();
    mu_assert_int_eq( *( --vecInt2.end() ), 42 );
}

MU_TEST( test_vec_insert_pos_val )
{
    ft::vector<int> vecInt2( TEST_VECTOR_SIZE );
    vecInt2.insert( vecInt2.begin(), 42 );
    mu_assert_int_eq( 42, vecInt2[0] );
}

MU_TEST( test_vec_insert_pos_nsize_val )
{
    ft::vector<int>                   vecInt2( TEST_VECTOR_SIZE );
    ft::random_access_iterator<int *> position   = vecInt2.begin();
    std::allocator<int>::size_type    n          = 10;
    std::allocator<int>::value_type   value_type = 42;

    vecInt2.insert( position, n, value_type );
    for ( int i = 0; i < ( int ) n; i++ )
        mu_assert_int_eq( 42, vecInt2[i] );
}

MU_TEST( test_vec_insert_pos_range )
{
    ft::vector<int> vecInt2( TEST_VECTOR_SIZE );
    vecInt2.insert( vecInt2.begin(), vecInt.begin(), vecInt.end() );
    mu_assert_int_eq( 0, vecInt2[0] );
}

MU_TEST( test_vec_erase_pos )
{
    ft::vector<int> vecInt2( TEST_VECTOR_SIZE );
    vecInt2 = vecInt;
    vecInt2.erase( vecInt2.begin() );
    mu_assert_int_eq( 1, vecInt2[0] );
}

MU_TEST_SUITE( suite_vector )
{
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
    MU_RUN_TEST( test_vec_erase_pos );
}

int main()
{
    MU_SUITE_CONFIGURE( &test_setup, &test_teardown );
    MU_RUN_SUITE( suite_vector );
    MU_REPORT();
    return MU_EXIT_CODE;
}
