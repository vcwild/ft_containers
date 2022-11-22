/*
 * Copyright 2022 ©️ vcwild under the GNU Affero General Public License v3.0.
 */
int rec[1000006];

void _printTree( TreeNode *curr, int depth )
{
    int i;
    if ( curr == NULL )
        return;
    printf( "\t" );
    for ( i = 0; i < depth; i++ )
        if ( i == depth - 1 )
            printf( "%s\u2014\u2014\u2014",
                    rec[depth - 1] ? "\u0371" : "\u221F" );
        else
            printf( "%s   ", rec[i] ? "\u23B8" : "  " );
    printf( "%d\n", curr->value );
    rec[depth] = 1;
    _printTree( curr->left, depth + 1 );
    rec[depth] = 0;
    _printTree( curr->right, depth + 1 );
}
