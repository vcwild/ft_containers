#include "rb_node.hpp"
#include "minunit.h"

static ft::rb_node<int> root( 0, NULL, NULL );
static ft::rb_node<int> leaf( 1, &root, NULL );
static ft::rb_node<int> node1( 2, &leaf, &leaf );

void test_setup() {}

void test_teardown() {}

MU_TEST( test_root )
{
    mu_assert_int_eq( root.data, 0 );
    mu_assert( root.parent == NULL, "is not the same as parent" );
    mu_assert( root.left == NULL, "is not the same as left" );
    mu_assert( root.right == NULL, "is not the same right" );
    mu_assert( root.leaf == NULL, "is not the same as leaf" );
    mu_assert( root.color == ft::BLACK, "is not black" );
}

MU_TEST( test_leaf )
{
    mu_assert_int_eq( leaf.data, 1 );
    mu_assert( leaf.parent == NULL, "is not the same as parent" );
    mu_assert( leaf.left == NULL, "is not the same as left" );
    mu_assert( leaf.right == NULL, "is not the same right" );
    mu_assert( leaf.root == &root, "is not the same as root" );
    mu_assert( leaf.leaf == NULL, "is not the same as leaf" );
    mu_assert( leaf.color == ft::BLACK, "is not black" );
}

MU_TEST( test_node1 )
{
    mu_assert_int_eq( node1.data, 2 );
    mu_assert( node1.parent == NULL, "is not the same as parent" );
    mu_assert( node1.left == NULL, "is not the same as left" );
    mu_assert( node1.right == NULL, "is not the same right" );
    mu_assert( node1.root == &leaf, "is not the same as root" );
    mu_assert( node1.leaf == &leaf, "is not the same as leaf" );
    mu_assert( node1.color == ft::BLACK, "is not black" );
}

MU_TEST_SUITE( suite_rb_node )
{
    MU_RUN_TEST( test_root );
    MU_RUN_TEST( test_leaf );
    MU_RUN_TEST( test_node1 );
}

int main()
{
    MU_SUITE_CONFIGURE( &test_setup, &test_teardown );
    MU_RUN_SUITE( suite_rb_node );
    MU_REPORT();
    return MU_EXIT_CODE;
}
