#include "map.hpp"
#include "minunit.h"

void test_setup() {}

void test_teardown() {}

MU_TEST( test_map_assignment )
{

    ft::map<const char *, int> m;

    m["a"] = 1;
    mu_assert( m["a"] == 1, "m[\"a\"] == 1" );
}

MU_TEST( test_map_pairs )
{
    ft::pair<const char *, int> p1( "a", 1 );
    ft::pair<const char *, int> p2( "b", 2 );
    ft::map<const char *, int>  m;

    m.insert( p1 );
    m.insert( p2 );
    mu_assert( m["a"] == 1, "m[\"a\"] == 1" );
    mu_assert( m["b"] == 2, "m[\"b\"] == 2" );
}

MU_TEST_SUITE( suite_name )
{
    MU_RUN_TEST( test_map_assignment );
    MU_RUN_TEST( test_map_pairs );
}

int main()
{
    MU_SUITE_CONFIGURE( &test_setup, &test_teardown );
    MU_RUN_SUITE( suite_name );
    MU_REPORT();
    return MU_EXIT_CODE;
}
