void _printTree( TreeNode *node, int level )
{
    if ( node != NULL ) {
        if ( node->right ) {
            _printTree( node->right, level + 4 );
        }
        if ( level ) {
            std::cout << std::setw( level ) << ' ';
        }
        if ( node->right )
            std::cout << " /\n" << std::setw( level ) << ' ';
        std::cout << node->value << "\n ";
        if ( node->left ) {
            std::cout << std::setw( level ) << ' ' << " \\\n";
            _printTree( node->left, level + 4 );
        }
    }
}
