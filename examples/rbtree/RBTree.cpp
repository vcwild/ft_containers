#include "RBTree.hpp"
#include <cassert>

RBNode *RBTree::_nil = RBTree::_create( NULL, BLACK, 0 ); // Sentinel value

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

RBTree::RedBlackTree() : _root( NULL ) {}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

RBTree::~RedBlackTree()
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

RBNode *RBTree::search( int value ) { _search( _root, value ); }

RBNode *RBTree::min( RBNode *node )
{
    while ( node->left != _nil ) {
        node = node->left;
    }
    return node;
}

RBNode *RBTree::max( RBNode *node )
{
    while ( node->right != _nil ) {
        node = node->right;
    }
    return node;
}

RBNode *RBTree::successor( RBNode *node )
{
    if ( node->right != _nil ) {
        return min( node->right );
    }

    RBNode *parent = node->parent;

    while ( parent != _nil && node == parent->right ) {
        node   = parent;
        parent = parent->parent;
    }

    return parent;
}

RBNode *RBTree::predecessor( RBNode *node )
{
    if ( node->left != _nil ) {
        return max( node->left );
    }

    RBNode *parent = node->parent;

    while ( parent != _nil && node == parent->left ) {
        node   = parent;
        parent = parent->parent;
    }

    return parent;
}

/*
** ------------------------------ PRIVATE METHODS -----------------------------
*/

RBNode *RBTree::_create( RBNode *parent, t_color color, int value )
{
    RBNode *node = new RBNode();
    node->left   = NULL;
    node->right  = NULL;
    node->color  = color;
    node->parent = parent;
    node->value  = value;

    return node;
}

RBNode *RBTree::_rotate( RBNode *subRoot, t_rot_dir dir )
{
    RBNode *G = subRoot->parent;
    RBNode *S = subRoot->child[1 - dir];
    RBNode *C;

    assert( S != NULL );

    C                       = S->child[dir];
    subRoot->child[1 - dir] = C;

    if ( C != NULL )
        C->parent = subRoot;
    S->child[dir]   = subRoot;
    subRoot->parent = S;
    S->parent       = G;

    if ( G != NULL )
        G->child[subRoot == G->right ? RIGHT : LEFT] = S;
    else
        this->_root = S;

    return S;
}

RBNode *RBTree::_rotateLeft( RBNode *subRoot ) { _rotate( subRoot, LEFT ); }
RBNode *RBTree::_rotateRight( RBNode *subRoot ) { _rotate( subRoot, RIGHT ); }

void RBTree::_destroy( RBNode *node )
{
    if ( node != NULL ) {
        _destroy( node->left );
        _destroy( node->right );
        delete node;
    }
}

RBNode *RBTree::_search( RBNode *node, int value )
{
    if ( node == NULL )
        return NULL;
    if ( value == node->value )
        return node;
    if ( value < node->value )
        return _search( node->left, value );
    return _search( node->right, value );
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */
