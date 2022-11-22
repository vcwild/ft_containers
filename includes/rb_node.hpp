/*
 * Copyright 2022 ©️ vcwild under the GNU Affero General Public License v3.0.
 */
#ifndef RB_NODE
#define RB_NODE

#include <cstddef>

namespace ft {

typedef enum rb_node_color { RED = true, BLACK = false } t_rb_node_color;

template <typename T>
struct rb_node
{
    typedef rb_node<T> node;
    typedef node      *node_pointer;

    explicit rb_node( const T      &_data,
                      node_pointer  _root,
                      node_pointer  _leaf,
                      node_pointer  _parent = NULL,
                      node_pointer  _left   = NULL,
                      node_pointer  _right  = NULL,
                      rb_node_color _color  = BLACK ) :
        data( _data ),
        root( _root ), leaf( _leaf ), parent( _parent ), left( _left ),
        right( _right ), color( _color )
    {
    }

    // Public attributes
    T             data;
    node_pointer  root;
    node_pointer  leaf;
    node_pointer  parent;
    node_pointer  left;
    node_pointer  right;
    rb_node_color color;

    // Member functions
    static node_pointer minimum( node_pointer node )
    {
        while ( node->left != node->leaf ) {
            node = node->left;
        }
        return node;
    }

    static node_pointer maximum( node_pointer node )
    {
        while ( node->right != node->leaf ) {
            node = node->right;
        }
        return node;
    }

    static node_pointer successor( node_pointer x )
    {
        if ( x == x->leaf ) {
            return maximum( get_root( x ) );
        }
        if ( x->right != x->leaf ) {
            return minimum( x->right );
        }
        node_pointer y = x->parent;
        while ( y != y->leaf && x == y->right ) {
            x = y;
            y = y->parent;
        }
        return y;
    }

    static node_pointer predecessor( node_pointer x )
    {
        if ( x == x->leaf ) {
            return maximum( get_root( x ) );
        }
        if ( x->left != x->leaf ) {
            return maximum( x->left );
        }
        node_pointer y = x->parent;
        while ( y != y->leaf && x == y->left ) {
            x = y;
            y = y->parent;
        }
        return y;
    }

    // Accessors
    static node_pointer get_root( node_pointer node )
    {
        return node->leaf->root;
    }
};

} // namespace ft

#endif // RB_NODE
