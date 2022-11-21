#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include "algorithm.hpp"
#include "functional.hpp"
#include "rb_iterator.hpp"
#include "reverse_iterator.hpp"
#include "utility.hpp"
#include <iostream>
#include <memory.h>

#define RB_TEMPLATE_ARGS                                                       \
    typename Key, typename T, typename KeyOfValue, typename Compare,           \
        typename Alloc
#define RB_CLASS_TYPE rb_tree< Key, T, KeyOfValue, Compare, Alloc >

namespace ft {

template < typename Key,
           typename T,
           typename KeyOfValue,
           typename Compare,
           typename Alloc = std::allocator< T > >
class rb_tree {

public:
    typedef Key                                                  key_type;
    typedef T                                                    value_type;
    typedef Compare                                              key_compare;
    typedef typename Alloc::template rebind< rb_node<T> >::other allocator_type;

    typedef value_type       &reference;
    typedef const value_type &const_reference;
    typedef value_type       *pointer;
    typedef const value_type *const_pointer;
    typedef ptrdiff_t         difference_type;
    typedef size_t            size_type;

    typedef ft::rb_iterator<pointer>             iterator;
    typedef ft::rb_iterator<const_pointer>       const_iterator;
    typedef ft::reverse_iterator<iterator>       reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    typedef rb_node<value_type> node;
    typedef node               *node_pointer;
    typedef const node         *const_node_pointer;

private:
    allocator_type _alloc;
    node_pointer   _root;
    node_pointer   _sentinel;
    size_type      _size;
    key_compare    _comp;

public:
    // Constructors
    explicit rb_tree( const key_compare    &comp  = key_compare(),
                      const allocator_type &alloc = allocator_type() ) :
        _alloc( alloc ),
        _root( NULL ), _sentinel( NULL ), _size( 0 ), _comp( comp )
    {
        _sentinel
            = new node( value_type(), NULL, NULL, NULL, NULL, NULL, BLACK );
    };

    rb_tree( const rb_tree &rbt ) :
        _alloc( rbt._alloc ), _size( rbt._size ), _comp( rbt._comp )
    {
        _root = _copy( rbt._root, _sentinel );
    };

    // Destructor
    ~rb_tree()
    {
        _clear( _root );
        _alloc.deallocate( _sentinel, 1 );
    };

    // Assignment operator
    rb_tree &operator=( const rb_tree &rhs )
    {
        if ( this != &rhs ) {
            _clear( _root );
            _alloc.deallocate( _sentinel, 1 );
            _root = _copy( rhs._root, _sentinel );
            _size = rhs._size;
            _comp = rhs._comp;
        }
        return *this;
    };

    // Iterators

    iterator begin() { return iterator( _minimum( _root ) ); };

    iterator end() { return iterator( NULL ); };

    const_iterator begin() const
    {
        return const_iterator( _minimum( _root ) );
    };

    const_iterator end() const { return const_iterator( NULL ); };

    reverse_iterator rbegin() { return reverse_iterator( _maximum( _root ) ); };

    reverse_iterator rend() { return reverse_iterator( NULL ); };

    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator( _maximum( _root ) );
    };

    const_reverse_iterator rend() const
    {
        return const_reverse_iterator( NULL );
    };

    // Accessors

    size_type size() const { return _size; };

    bool empty() const { return _size == 0; };

    size_type max_size() const { return _alloc.max_size(); };

    key_compare key_comp() const { return _comp; };

    allocator_type get_allocator() const { return _alloc; };

    // Modifiers

    ft::pair<iterator, bool> insert( const value_type &val )
    {
        node_pointer new_node = _alloc.allocate( 1 );
        _alloc.construct( new_node, node( val, _root, _sentinel ) );
        return _insert( new_node );
    };

    iterator insert( iterator position, const value_type &val )
    {
        ( void ) position;
        node_pointer new_node = _alloc.allocate( 1 );
        _alloc.construct( new_node, node( val, _root, _sentinel ) );
        return _insert( new_node ).first;
    };

    void insert( value_type val, node_pointer _root )
    {
        node_pointer existing_node = search( KeyOfValue()( val ), _root );
        if ( existing_node != _sentinel ) {
            _erase( existing_node );
        }
        node_pointer new_node = _alloc.allocate( 1 );
        _alloc.construct( new_node, node( val, _root, _sentinel ) );
        _insert( new_node );
    }

    template < typename InputIterator >
    void insert( InputIterator first, InputIterator last )
    {
        while ( first != last ) {
            node_pointer new_node = _alloc.allocate( 1 );
            _alloc.construct( new_node, node( *first, _root, _sentinel ) );
            _insert( new_node );
            ++first;
        }
    };

    template < typename InputIterator >
    void insert_unique( InputIterator first, InputIterator last )
    {
        while ( first != last ) {
            node_pointer new_node = _alloc.allocate( 1 );
            _alloc.construct( new_node, node( *first, _root, _sentinel ) );
            if ( _insert_unique( new_node ).second )
                ++_size;
            ++first;
        }
    };

    void erase( iterator position )
    {
        node_pointer node = position.base();
        _erase( node );
    };

    size_type erase( const key_type &k )
    {
        node_pointer node = _search( k );
        if ( node == NULL ) {
            return 0;
        }
        _erase( node );
        return 1;
    };

    void erase( iterator first, iterator last )
    {
        while ( first != last ) {
            node_pointer node = first.base();
            ++first;
            _erase( node );
        }
    };

    void swap( rb_tree &rbt )
    {
        allocator_type tmp_alloc    = _alloc;
        node_pointer   tmp_root     = _root;
        node_pointer   tmp_sentinel = _sentinel;
        size_type      tmp_size     = _size;
        key_compare    tmp_comp     = _comp;

        rbt._alloc    = _alloc;
        rbt._root     = _root;
        rbt._sentinel = _sentinel;
        rbt._size     = _size;
        rbt._comp     = _comp;

        _alloc    = tmp_alloc;
        _root     = tmp_root;
        _sentinel = tmp_sentinel;
        _size     = tmp_size;
        _comp     = tmp_comp;
    };

    void clear()
    {
        _clear( _root );
        _root     = NULL;
        _sentinel = NULL;
        _size     = 0;
    };

    // Observers

    value_type &operator[]( const key_type &key )
    {
        node_pointer node = _search( key );
        if ( node == NULL ) {
            node_pointer new_node = _alloc.allocate( 1 );
            _alloc.construct(
                new_node,
                node( value_type( key, value_type() ), _root, _sentinel ) );
            _insert( new_node );
            return new_node->value.second;
        }
        return node->value.second;
    };

    // Operations

    iterator search( const key_type &k )
    {
        node_pointer node = _search( k );
        if ( node == NULL ) {
            return end();
        }
        return iterator( node );
    };

    const_iterator search( const key_type &k ) const
    {
        node_pointer node = _search( k );
        if ( node == NULL ) {
            return end();
        }
        return const_iterator( node );
    };

    size_type count( const key_type &k ) const
    {
        node_pointer node = _search( k );
        if ( node == NULL ) {
            return 0;
        }
        return 1;
    };

    iterator lower_bound( const key_type &k )
    {
        node_pointer node = _root;
        node_pointer y    = _sentinel;
        while ( node != _sentinel ) {
            if ( !_comp( KeyOfValue()( node->data ), k ) ) {
                y    = node;
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return iterator( y );
    };

    const_iterator lower_bound( const key_type &k ) const
    {
        node_pointer node = _root;
        node_pointer y    = _sentinel;
        while ( node != _sentinel ) {
            if ( !_comp( KeyOfValue()( node->data ), k ) ) {
                y    = node;
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return iterator( y );
    };

    iterator upper_bound( const key_type &k )
    {
        node_pointer node = _root;
        node_pointer y    = _sentinel;
        while ( node != _sentinel ) {
            if ( _comp( k, KeyOfValue()( node->data ) ) ) {
                y    = node;
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return iterator( y );
    };

    const_iterator upper_bound( const key_type &k ) const
    {
        node_pointer node = _root;
        node_pointer y    = _sentinel;
        while ( node != _sentinel ) {
            if ( _comp( k, KeyOfValue()( node->data ) ) ) {
                y    = node;
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return iterator( y );
    };

    ft::pair<const_iterator, const_iterator>
    equal_range( const key_type &k ) const
    {
        return ft::pair<const_iterator, const_iterator>( lower_bound( k ),
                                                         upper_bound( k ) );
    };

    ft::pair<iterator, iterator> equal_range( const key_type &k )
    {
        return ft::pair<iterator, iterator>( lower_bound( k ),
                                             upper_bound( k ) );
    };

    // Debug

    void print() const
    {
        _print( _root );
        std::cout << std::endl;
    };

private:
    // Member functions
    node_pointer _copy( node_pointer node, node_pointer &end )
    {
        if ( node == NULL ) {
            return NULL;
        }
        node_pointer new_node = _alloc.allocate( 1 );
        _alloc.construct( new_node, node->data );
        new_node->root  = _root;
        new_node->leaf  = _sentinel;
        new_node->left  = _copy( node->left, end );
        new_node->right = _copy( node->right, end );
        if ( new_node->left != NULL ) {
            new_node->left->parent = new_node;
        }
        if ( new_node->right != NULL ) {
            new_node->right->parent = new_node;
        }
        if ( node->parent == NULL ) {
            _root = new_node;
        }
        if ( node->right == NULL ) {
            end = new_node;
        }
        return new_node;
    };

    void _clear( node_pointer node )
    {
        if ( node == NULL ) {
            return;
        }
        _clear( node->left );
        _clear( node->right );
        _alloc.destroy( node );
        _alloc.deallocate( node, 1 );
    };

    void _insert( node_pointer node, node_pointer &end )
    {
        node_pointer y = _sentinel;
        node_pointer x = _root;
        while ( x != _sentinel ) {
            y = x;
            if ( _comp( KeyOfValue()( node->data ),
                        KeyOfValue()( x->data ) ) ) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        node->parent = y;
        if ( y == _sentinel ) {
            _root = node;
        } else if ( _comp( KeyOfValue()( node->data ),
                           KeyOfValue()( y->data ) ) ) {
            y->left = node;
        } else {
            y->right = node;
        }
        if ( node->right == NULL ) {
            end = node;
        }
        _insert_fix( node );
    };

    void _insert_fix( node_pointer node )
    {
        while ( node->parent != NULL && node->parent->color == RED ) {
            if ( node->parent == node->parent->parent->left ) {
                node_pointer uncle = node->parent->parent->right;
                if ( uncle != NULL && uncle->color == RED ) {
                    node->parent->color         = BLACK;
                    uncle->color                = BLACK;
                    node->parent->parent->color = RED;
                    node                        = node->parent->parent;
                } else {
                    if ( node == node->parent->right ) {
                        node = node->parent;
                        _left_rotate( node );
                    }
                    node->parent->color         = BLACK;
                    node->parent->parent->color = RED;
                    _right_rotate( node->parent->parent );
                }
            } else {
                node_pointer uncle = node->parent->parent->left;
                if ( uncle != NULL && uncle->color == RED ) {
                    node->parent->color         = BLACK;
                    uncle->color                = BLACK;
                    node->parent->parent->color = RED;
                    node                        = node->parent->parent;
                } else {
                    if ( node == node->parent->left ) {
                        node = node->parent;
                        _right_rotate( node );
                    }
                    node->parent->color         = BLACK;
                    node->parent->parent->color = RED;
                    _left_rotate( node->parent->parent );
                }
            }
        }
        _root->color = BLACK;
    };

    void _left_rotate( node_pointer node )
    {
        node_pointer right = node->right;
        node->right        = right->left;
        if ( right->left != NULL ) {
            right->left->parent = node;
        }
        right->parent = node->parent;
        if ( node->parent == NULL ) {
            _root = right;
        } else if ( node == node->parent->left ) {
            node->parent->left = right;
        } else {
            node->parent->right = right;
        }
        right->left  = node;
        node->parent = right;
    };

    void _right_rotate( node_pointer node )
    {
        node_pointer left = node->left;
        node->left        = left->right;
        if ( left->right != NULL ) {
            left->right->parent = node;
        }
        left->parent = node->parent;
        if ( node->parent == NULL ) {
            _root = left;
        } else if ( node == node->parent->right ) {
            node->parent->right = left;
        } else {
            node->parent->left = left;
        }
        left->right  = node;
        node->parent = left;
    };

    void _transplant( node_pointer u, node_pointer v )
    {
        if ( u->parent == NULL ) {
            _root = v;
        } else if ( u == u->parent->left ) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        if ( v != NULL ) {
            v->parent = u->parent;
        }
    };

    void _erase( node_pointer node )
    {
        node_pointer    y = node;
        node_pointer    x;
        t_rb_node_color y_original_color = y->color;
        if ( node->left == NULL ) {
            x = node->right;
            _transplant( node, node->right );
        } else if ( node->right == NULL ) {
            x = node->left;
            _transplant( node, node->left );
        } else {
            y                = _minimum( node->right );
            y_original_color = y->color;
            x                = y->right;
            if ( y->parent == node ) {
                if ( x != NULL ) {
                    x->parent = y;
                }
            } else {
                _transplant( y, y->right );
                y->right         = node->right;
                y->right->parent = y;
            }
            _transplant( node, y );
            y->left         = node->left;
            y->left->parent = y;
            y->color        = node->color;
        }
        if ( y_original_color == BLACK ) {
            _erase_fix( x );
        }
    };

    void _erase_fix( node_pointer node )
    {
        while ( node != _root && ( node == NULL || node->color == BLACK ) ) {
            if ( node == node->parent->left ) {
                node_pointer w = node->parent->right;
                if ( w->color == RED ) {
                    w->color            = BLACK;
                    node->parent->color = RED;
                    _left_rotate( node->parent );
                    w = node->parent->right;
                }
                if ( ( w->left == NULL || w->left->color == BLACK )
                     && ( w->right == NULL || w->right->color == BLACK ) ) {
                    w->color = RED;
                    node     = node->parent;
                } else {
                    if ( w->right == NULL || w->right->color == BLACK ) {
                        w->left->color = BLACK;
                        w->color       = RED;
                        _right_rotate( w );
                        w = node->parent->right;
                    }
                    w->color            = node->parent->color;
                    node->parent->color = BLACK;
                    w->right->color     = BLACK;
                    _left_rotate( node->parent );
                    node = _root;
                }
            } else {
                node_pointer w = node->parent->left;
                if ( w->color == RED ) {
                    w->color            = BLACK;
                    node->parent->color = RED;
                    _right_rotate( node->parent );
                    w = node->parent->left;
                }
                if ( ( w->right == NULL || w->right->color == BLACK )
                     && ( w->left == NULL || w->left->color == BLACK ) ) {
                    w->color = RED;
                    node     = node->parent;
                } else {
                    if ( w->left == NULL || w->left->color == BLACK ) {
                        w->right->color = BLACK;
                        w->color        = RED;
                        _left_rotate( w );
                        w = node->parent->left;
                    }
                    w->color            = node->parent->color;
                    node->parent->color = BLACK;
                    w->left->color      = BLACK;
                    _right_rotate( node->parent );
                    node = _root;
                }
            }
        }
        if ( node != NULL ) {
            node->color = BLACK;
        }
    };

    node_pointer _minimum( node_pointer node )
    {
        return node::minimum( node );
    };

    node_pointer _maximum( node_pointer node )
    {
        return node::maximum( node );
    };

    node_pointer _successor( node_pointer node )
    {
        return node::successor( node );
    };

    node_pointer _predecessor( node_pointer node )
    {
        return node::predecessor( node );
    };

    node_pointer _search( const value_type &value )
    {
        node_pointer node = _root;
        while ( node != NULL ) {
            if ( value < node->value ) {
                node = node->left;
            } else if ( node->value < value ) {
                node = node->right;
            } else {
                return node;
            }
        }
        return node;
    };
};

template < RB_TEMPLATE_ARGS >
inline bool operator==( const RB_CLASS_TYPE &lhs, const RB_CLASS_TYPE &rhs )
{
    return lhs.size() == rhs.size()
        && ft::equal( lhs.begin(), lhs.end(), rhs.begin() );
};

template < RB_TEMPLATE_ARGS >
inline bool operator!=( const RB_CLASS_TYPE &lhs, const RB_CLASS_TYPE &rhs )
{
    return !( lhs == rhs );
};

template < RB_TEMPLATE_ARGS >
inline bool operator<( const RB_CLASS_TYPE &lhs, const RB_CLASS_TYPE &rhs )
{
    return ft::lexicographical_compare(
        lhs.begin(), lhs.end(), rhs.begin(), rhs.end() );
};

template < RB_TEMPLATE_ARGS >
inline bool operator<=( const RB_CLASS_TYPE &lhs, const RB_CLASS_TYPE &rhs )
{
    return !( rhs < lhs );
};

template < RB_TEMPLATE_ARGS >
inline bool operator>( const RB_CLASS_TYPE &lhs, const RB_CLASS_TYPE &rhs )
{
    return rhs < lhs;
};

template < RB_TEMPLATE_ARGS >
inline bool operator>=( const RB_CLASS_TYPE &lhs, const RB_CLASS_TYPE &rhs )
{
    return !( lhs < rhs );
};

template < RB_TEMPLATE_ARGS >
inline void swap( RB_CLASS_TYPE &lhs, RB_CLASS_TYPE &rhs )
{
    lhs.swap( rhs );
};

} // namespace ft

#endif // RB_TREE_HPP
