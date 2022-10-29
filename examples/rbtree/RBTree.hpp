#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <iostream>
#include <string>

/**
 * @brief The color to set the Red-Black tree leave.
 *
 */
typedef enum tree_color { BLACK, RED } t_color;

/**
 * @brief The rotation direction of the Red-Black tree
 *
 */
typedef enum rotation_direction { LEFT, RIGHT } t_rot_dir;

#define left child[LEFT]
#define right child[RIGHT]

typedef struct RBNode
{
    RBNode *parent;
    RBNode *child[2];
    int     value;
    t_color color;
} RBNode;

typedef class RedBlackTree
{

public:
    RedBlackTree();
    ~RedBlackTree();

    bool    insert( int value );
    RBNode *search( int value );
    bool    remove( int value );

    RBNode *min( RBNode *node );
    RBNode *max( RBNode *node );
    RBNode *successor( RBNode *node );
    RBNode *predecessor( RBNode *node );

private:
    RBNode        *_root;
    static RBNode *_nil; // static void * sentinel

    static RBNode *_create( RBNode *parent, t_color color, int value );

    /**
     * @brief Rotates red black tree leaves. Requires an existing pointer to a
     * subtree node. Otherwise raises an exception.
     * G denotes the subtree grandparent node.
     *
     * @param subRoot The root of the subtree
     * @param dir The direction to rotate, 0 for left rotation, 1 for right
     * rotation
     * @return Returns the node for the root of the subtree
     */
    RBNode *_rotate( RBNode *subRoot, t_rot_dir dir );
    RBNode *_rotateLeft( RBNode *subRoot );
    RBNode *_rotateRight( RBNode *subRoot );

    RBNode *_search( RBNode *node, int value );
    void    _destroy( RBNode *node );
} RBTree;

#endif /* ********************************************************** RBTREE_H  \
        */
