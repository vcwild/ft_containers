#include "RBTree.hpp"
#include <cassert>
#include <iomanip>

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
    _destroy( _nil );
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

/*
** --------------------------------- METHODS ----------------------------------
*/
void RBTree::print() { _print( _root, 0 ); }

RBNode *RBTree::search( int value ) { return _search( _root, value ); }

RBNode *RBTree::min( RBNode *node )
{
    while ( node->child[LEFT] != _nil ) {
        node = node->child[LEFT];
    }
    return node;
}

RBNode *RBTree::max( RBNode *node )
{
    while ( node->child[RIGHT] != _nil ) {
        node = node->child[RIGHT];
    }
    return node;
}

RBNode *RBTree::successor( RBNode *node )
{
    if ( node->child[RIGHT] != _nil ) {
        return min( node->child[RIGHT] );
    }

    RBNode *parent = node->parent;

    while ( parent != _nil && node == parent->child[RIGHT] ) {
        node   = parent;
        parent = parent->parent;
    }

    return parent;
}

RBNode *RBTree::predecessor( RBNode *node )
{
    if ( node->child[LEFT] != _nil ) {
        return max( node->child[LEFT] );
    }

    RBNode *parent = node->parent;

    while ( parent != _nil && node == parent->child[LEFT] ) {
        node   = parent;
        parent = parent->parent;
    }

    return parent;
}

bool RBTree::insert( int value ) { return _insert( &_root, value ); }

bool RBTree::_insert( RBNode **node, int value ) {}

void RBTree::_insertFixup( RBNode **node ) {}

/*
** ----------------------------- PRIVATE METHODS ----------------------------
*/

RBNode *RBTree::_create( RBNode *parent, t_color color, int value )
{
    RBNode *node       = new RBNode();
    node->child[LEFT]  = NULL;
    node->child[RIGHT] = NULL;
    node->color        = color;
    node->parent       = parent;
    node->value        = value;

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
        G->child[subRoot == G->child[RIGHT] ? RIGHT : LEFT] = S;
    else
        this->_root = S;

    return S;
}

RBNode *RBTree::_rotateLeft( RBNode *subRoot )
{
    return _rotate( subRoot, LEFT );
}
RBNode *RBTree::_rotateRight( RBNode *subRoot )
{
    return _rotate( subRoot, RIGHT );
}

void RBTree::_destroy( RBNode *node )
{
    if ( node != NULL ) {
        _destroy( node->child[LEFT] );
        _destroy( node->child[RIGHT] );
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
        return _search( node->child[LEFT], value );
    return _search( node->child[RIGHT], value );
}

void RBTree::_print( RBNode *node, int level )
{
    std::string nodeColor = node->color == RED ? "\e[31m" : "\e[33m";

    if ( node->child[RIGHT] ) {
        _print( node->child[RIGHT], level + 4 );
    }
    if ( level ) {
        std::cout << std::setw( level ) << ' ';
    }
    if ( node->child[RIGHT] )
        std::cout << " /\n" << std::setw( level ) << ' ';
    std::cout << nodeColor << node->value << "\e[0m\n ";
    if ( node->child[LEFT] ) {
        std::cout << std::setw( level ) << ' ' << " \\" << std::endl;
        _print( node->child[LEFT], level + 4 );
    }
    std::cout << std::endl;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* **************************************************************************
 */
