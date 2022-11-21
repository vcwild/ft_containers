#include "minunit.h"

void test_setup() {}

void test_teardown() {}

MU_TEST( test_1 ) { mu_assert_int_eq( 1, 1 ); }
MU_TEST( test_2 ) { mu_assert_int_eq( 1, 1 ); }

MU_TEST_SUITE( suite_name )
{
    MU_RUN_TEST( test_1 );
    MU_RUN_TEST( test_2 );
}

int main()
{
    MU_SUITE_CONFIGURE( &test_setup, &test_teardown );
    MU_RUN_SUITE( suite_name );
    MU_REPORT();
    return MU_EXIT_CODE;
}
