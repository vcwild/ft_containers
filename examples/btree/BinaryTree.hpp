#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include <iostream>

struct TreeNode
{
    int       value;
    TreeNode *left;
    TreeNode *right;
};

class BinaryTree
{
public:
    BinaryTree();
    ~BinaryTree();

    bool      insert( int value );
    bool      remove( int value );
    void      print();
    TreeNode *search( int value );

private:
    TreeNode *_root;
    TreeNode *_search( TreeNode *node, int value );
    TreeNode *_create( int value );
    bool      _insert( TreeNode **node, int value );
    bool      _find( TreeNode **node, int value );
    void      _print( TreeNode *node, int level );
    void      _destroy( TreeNode *node );
};

#endif /* ****************************************************** BINARYTREE_H  \
        */
