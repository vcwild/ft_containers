#include "BinaryTree.hpp"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <stdio.h>
/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

BinaryTree::BinaryTree() : _root( NULL ) {}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

BinaryTree::~BinaryTree()
{
    if ( _root != NULL ) {
        _destroy( _root );
    }
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

/*
** --------------------------------- METHODS ----------------------------------
*/

bool BinaryTree::insert( int value ) { return _insert( &_root, value ); }

bool BinaryTree::remove( int value ) { return true; }

void BinaryTree::print() { _print( _root, 0 ); }

void BinaryTree::_print( TreeNode *node, int level )
{
    if ( node != NULL ) {
        if ( node->right ) {
            _print( node->right, level + 4 );
        }
        if ( level ) {
            std::cout << std::setw( level ) << ' ';
        }
        if ( node->right )
            std::cout << " /\n" << std::setw( level ) << ' ';
        std::cout << node->value << "\n ";
        if ( node->left ) {
            std::cout << std::setw( level ) << ' ' << " \\" << std::endl;
            _print( node->left, level + 4 );
        }
    }
    std::cout << std::endl;
}

TreeNode *BinaryTree::search( int value ) { return _search( _root, value ); }

TreeNode *BinaryTree::_search( TreeNode *node, int value )
{
    if ( node == NULL )
        return NULL;
    if ( value == node->value )
        return node;
    if ( value < node->value )
        return _search( node->left, value );
    return _search( node->right, value );
}

TreeNode *BinaryTree::_create( int value )
{
    TreeNode *node = new TreeNode;
    node->value    = value;
    node->left     = NULL;
    node->right    = NULL;

    return node;
}

bool BinaryTree::_insert( TreeNode **node, int value )
{
    if ( *node == NULL )
        return ( *node = _create( value ), true );
    if ( value == ( *node )->value )
        return false;
    if ( value < ( *node )->value )
        return _insert( &( *node )->left, value );
    return _insert( &( *node )->right, value );
}

bool BinaryTree::_find( TreeNode **node, int value )
{
    if ( *node == NULL )
        return false;
    if ( value == ( *node )->value )
        return true;
    if ( value < ( *node )->value )
        return _find( &( *node )->left, value );
    return _find( &( *node )->right, value );
}

void BinaryTree::_destroy( TreeNode *node )
{
    if ( node != NULL ) {
        _destroy( node->left );
        _destroy( node->right );
        delete node;
    }
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */
