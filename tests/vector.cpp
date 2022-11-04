#include "vector.hpp"
#include "minunit.h"

static ft::vector<int> vint( 10 );

void test_setup()
{
    for ( int i = 0; i < vint.size(); i++ )
        vint[i] = i;
}

void test_teardown() {}

MU_TEST( test_iter )
{
    for ( int i = 0; i < vint.size(); i++ )
        mu_assert_int_eq( i, vint[i] );
}

MU_TEST( test_vec_iter )
{
    for ( ft::vector<int>::iterator it = vint.begin(); it != vint.end(); it++ )
        mu_assert_int_eq( *it, vint[it - vint.begin()] );
}

MU_TEST_SUITE( test_vector )
{
    MU_RUN_TEST( test_iter );
    MU_RUN_TEST( test_vec_iter );
}

int main( int argc, char *argv[] )
{
    MU_SUITE_CONFIGURE( &test_setup, &test_teardown );
    MU_RUN_SUITE( test_vector );
    MU_REPORT();
    return MU_EXIT_CODE;
}
