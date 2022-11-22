/*
 * Copyright 2022 ©️ vcwild under the GNU Affero General Public License v3.0.
 */
#include "rb_iterator.hpp"
#include "minunit.h"
#include "utility.hpp"
#include <stdexcept>

using namespace ft;

MU_TEST( test_rb_iterator_create_int_iterator )
{
    static ft::rb_node<int> root( 0, NULL, NULL );
    static ft::rb_node<int> leaf( 1, &root, NULL );
    static ft::rb_node<int> node1( 2, &root, &leaf );
    ft::rb_iterator<int *>  it( &node1 );

    mu_assert( it.base() == &node1, "is not the same as node" );
    mu_assert( it.base()->root == &root, "is not the same as node" );
    mu_assert( it.base()->leaf == &leaf, "is not the same as node" );
}

MU_TEST( test_rb_iterator_create_int_const_iterator )
{
    static ft::rb_node<int>      root( 0, NULL, NULL );
    static ft::rb_node<int>      leaf( 1, &root, NULL );
    static ft::rb_node<int>      node1( 2, &root, &leaf );
    ft::rb_iterator<const int *> it( &node1 );

    mu_assert( it.base() == &node1, "is not the same as node" );
    mu_assert( it.base()->root == &root, "is not the same as node" );
    mu_assert( it.base()->leaf == &leaf, "is not the same as node" );
}

MU_TEST( test_rb_iterator_create_string_iterator )
{
    static ft::rb_node<std::string> root( "0", NULL, NULL );
    static ft::rb_node<std::string> leaf( "1", &root, NULL );
    static ft::rb_node<std::string> node1( "2", &root, &leaf );
    ft::rb_iterator<std::string *>  it( &node1 );

    mu_assert( it.base() == &node1, "is not the same as node" );
    mu_assert( it.base()->root == &root, "is not the same as node" );
    mu_assert( it.base()->leaf == &leaf, "is not the same as node" );
}

MU_TEST_SUITE( suite_rb_iterator )
{
    MU_RUN_TEST( test_rb_iterator_create_int_iterator );
    MU_RUN_TEST( test_rb_iterator_create_int_const_iterator );
    MU_RUN_TEST( test_rb_iterator_create_string_iterator );
}

int main()
{
    MU_RUN_SUITE( suite_rb_iterator );
    MU_REPORT();
    return MU_EXIT_CODE;
}
