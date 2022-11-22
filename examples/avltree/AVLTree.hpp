/*
 * Copyright 2022 ©️ vcwild under the GNU Affero General Public License v3.0.
 */
#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <iostream>
#include <string>

typedef struct AVLNode AVLNode;
typedef AVLNode       *AVLNodePtr;

struct AVLNode
{
    int        value;
    int        height;
    int        balance;
    AVLNodePtr left;
    AVLNodePtr right;
    AVLNode( int v ) :
        value( v ), height( 0 ), balance( -1 ), left( NULL ), right( NULL )
    {
    }
};

class AVLTree {
public:
    AVLTree() { _root = NULL; };
    ~AVLTree() { clear( _root ); };

    // main functions
    void insert( int value );
    void remove( int value );
    void clear( AVLNodePtr node );

    // accessors
    int  height() const;
    bool empty() const;
    bool contains( int value ) const;

    // node accessors
    AVLNodePtr root() const;
    AVLNodePtr left( AVLNodePtr node ) const;
    AVLNodePtr right( AVLNodePtr node ) const;
    AVLNodePtr grandparent( AVLNodePtr node ) const;
    AVLNodePtr uncle( AVLNodePtr node ) const;
    AVLNodePtr sibling( AVLNodePtr node ) const;

private:
    AVLNodePtr _root;
};

#endif // AVLTREE_HPP
