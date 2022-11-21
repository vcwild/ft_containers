#include "stack.hpp"
#include "minunit.h"

#define TEST_STACK_SIZE 5

static ft::stack<int> demoStack;
static ft::stack<int> stackInt;

void test_setup()
{
    for ( int i = 0; i < TEST_STACK_SIZE; i++ )
        stackInt.push( i );
}

void test_teardown() {}

MU_TEST( test_stack_copy_constructor )
{
    ft::stack<int> copyStack( stackInt );
    mu_assert_int_eq( copyStack.size(), stackInt.size() );
    mu_assert_int_eq( copyStack.top(), stackInt.top() );
}

MU_TEST( test_stack_empty )
{
    mu_check( demoStack.empty() == true );
    mu_check( stackInt.empty() == false );
}

MU_TEST( test_stack_size )
{
    mu_assert( demoStack.size() == 0, "stack size is wrong" );
    mu_assert( stackInt.size() != 0, "stack size is wrong" );
}

MU_TEST( test_stack_top )
{
    mu_check( demoStack.top() == 0 );
    mu_check( stackInt.top() == TEST_STACK_SIZE - 1 );
}

MU_TEST( test_stack_pop )
{
    ft::stack<int> mutStack;

    for ( int i = 0; i < TEST_STACK_SIZE; i++ )
        mutStack.push( i );

    for ( int i = TEST_STACK_SIZE - 1; i >= 0; i-- ) {
        mu_check( mutStack.top() == i );
        mutStack.pop();
        mu_check( mutStack.size() == ( long unsigned int ) i );
    }
    mu_check( mutStack.empty() == true );
}

MU_TEST( test_equal )
{
    ft::stack<int> stack1;
    ft::stack<int> stack2;

    for ( int i = 0; i < TEST_STACK_SIZE; i++ ) {
        stack1.push( i );
        stack2.push( i );
    }

    mu_check( stack1 == stack2 );
}

MU_TEST( test_not_equal )
{
    ft::stack<int> stack1;
    ft::stack<int> stack2;

    for ( int i = 0; i < TEST_STACK_SIZE; i++ ) {
        stack1.push( i );
        stack2.push( i );
    }

    stack1.push( 42 );

    mu_check( stack1 != stack2 );
}

MU_TEST( test_less )
{
    ft::stack<int> stack1;
    ft::stack<int> stack2;

    for ( int i = 0; i < TEST_STACK_SIZE; i++ ) {
        stack1.push( i );
        stack2.push( i );
    }

    stack2.push( 42 );

    mu_check( stack1 < stack2 );
}

MU_TEST( test_less_equal )
{
    ft::stack<int> stack1;
    ft::stack<int> stack2;

    for ( int i = 0; i < TEST_STACK_SIZE; i++ ) {
        stack1.push( i );
        stack2.push( i );
    }

    mu_check( stack1 <= stack2 );
}

MU_TEST( test_greater )
{
    ft::stack<int> stack1;
    ft::stack<int> stack2;

    for ( int i = 0; i < TEST_STACK_SIZE; i++ ) {
        stack1.push( i );
        stack2.push( i );
    }

    stack2.push( 42 );

    mu_check( stack2 > stack1 );
}

MU_TEST( test_greater_equal )
{
    ft::stack<int> stack1;
    ft::stack<int> stack2;

    for ( int i = 0; i < TEST_STACK_SIZE; i++ ) {
        stack1.push( i );
        stack2.push( i );
    }

    mu_check( stack2 >= stack1 );
}

MU_TEST_SUITE( suite_stack )
{
    MU_RUN_TEST( test_stack_copy_constructor );
    MU_RUN_TEST( test_stack_empty );
    MU_RUN_TEST( test_stack_size );
    MU_RUN_TEST( test_stack_top );
    MU_RUN_TEST( test_stack_pop );
    MU_RUN_TEST( test_equal );
    MU_RUN_TEST( test_not_equal );
    MU_RUN_TEST( test_less );
    MU_RUN_TEST( test_less_equal );
    MU_RUN_TEST( test_greater );
    MU_RUN_TEST( test_greater_equal );
}

int main()
{
    MU_SUITE_CONFIGURE( &test_setup, &test_teardown );
    MU_RUN_SUITE( suite_stack );
    MU_REPORT();
    return MU_EXIT_CODE;
}
