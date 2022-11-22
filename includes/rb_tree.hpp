/*
 * Copyright 2022 ©️ vcwild under the GNU Affero General Public License v3.0.
 */
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
        _sentinel = _alloc.allocate( 1 );
        _alloc.construct( _sentinel, create_node( value_type(), BLACK ) );
        _root = _sentinel;
    };

    rb_tree( const rb_tree &rbt ) : _alloc( rbt._alloc )
    {
        _sentinel = _alloc.allocate( 1 );
        _alloc.construct( _sentinel, create_node( value_type(), BLACK ) );
        _root = _sentinel;
        _copy( rbt._root );
        _size = rbt._size;
        _comp = rbt._comp;
    };

    // Destructor
    ~rb_tree()
    {
        _clear( _root );
        _alloc.destroy( _sentinel );
        _alloc.deallocate( _sentinel, 1 );
        _size = 0;
    };

    // Assignment operator
    rb_tree &operator=( const rb_tree &rhs )
    {
        if ( this == &rhs ) {
            return *this;
        }
        this->~rb_tree();
        _alloc    = rhs._alloc;
        _sentinel = _alloc.allocate( 1 );
        _alloc.construct( _sentinel, create_node( value_type(), BLACK ) );
        _root = _sentinel;
        _copy( rhs._root );
        _size = rhs._size;
        _comp = rhs._comp;
        return *this;
    };

    // Iterators

    iterator       begin() { return iterator( minimum( _root ) ); };
    const_iterator begin() const { return const_iterator( minimum( _root ) ); };

    iterator       end() { return iterator( _sentinel ); };
    const_iterator end() const { return const_iterator( _sentinel ); };

    reverse_iterator       rbegin() { return reverse_iterator( end() ); };
    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator( end() );
    };

    reverse_iterator       rend() { return reverse_iterator( begin() ); };
    const_reverse_iterator rend() const
    {
        return const_reverse_iterator( begin() );
    };

    // Accessors

    size_type size() const { return _size; };

    bool empty() const { return _size == 0; };

    size_type max_size() const { return _alloc.max_size(); };

    key_compare key_comp() const { return _comp; };

    allocator_type get_allocator() const { return _alloc; };

    // Modifiers

    void insert( value_type val )
    {
        node_pointer z = search( KeyOfValue()( val ) );
        if ( z != _sentinel ) {
            _erase( z );
        }
        _insert( val );
    };

    void insert( value_type val, node_pointer nptr )
    {
        node_pointer z = search( KeyOfValue()( val ), nptr );
        if ( z != _sentinel ) {
            _erase( z );
        }
        _insert( val );
    };

    iterator insert_unique( value_type val ) { return _insert( val ); };

    void erase( key_type k )
    {
        node_pointer nptr = search( k );
        if ( nptr == _sentinel ) {
            return;
        }
        _erase( nptr );
    };

    void swap( rb_tree &rbt )
    {
        allocator_type tmp_alloc = rbt._alloc;
        node_pointer   tmp_root  = rbt._root;
        node_pointer   tmp_sent  = rbt._sentinel;
        size_type      tmp_size  = rbt._size;
        key_compare    tmp_comp  = rbt._comp;

        rbt._alloc    = _alloc;
        rbt._root     = _root;
        rbt._sentinel = _sentinel;
        rbt._size     = _size;
        rbt._comp     = _comp;

        _alloc    = tmp_alloc;
        _root     = tmp_root;
        _sentinel = tmp_sent;
        _size     = tmp_size;
        _comp     = tmp_comp;
    };

    void clear()
    {
        _clear( _root );
        _root = _sentinel;
        _size = 0;
    };

    // Operations

    node_pointer search( key_type k ) const { return _search( _root, k ); };

    node_pointer search( key_type k, node_pointer nptr ) const
    {
        return _search( nptr, k );
    };

    size_type count( const key_type &k ) const
    {
        node_pointer nptr = search( k );
        if ( nptr == _sentinel ) {
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

private:
    // Member functions
    void _copy( node_pointer nptr )
    {
        if ( nptr != nptr->leaf ) {
            insert_unique( nptr->data );
            _copy( nptr->left );
            _copy( nptr->right );
        }
    };

    void _clear( node_pointer nptr )
    {
        if ( nptr == _sentinel ) {
            return;
        }
        _clear( nptr->left );
        _clear( nptr->right );
        _alloc.destroy( nptr );
        _alloc.deallocate( nptr, 1 );
    };

    iterator _insert( value_type val )
    {
        node_pointer x = _root;
        node_pointer y = _sentinel;
        node_pointer z = _alloc.allocate( 1 );
        _alloc.construct( z, create_node( val, RED ) );
        while ( x != _sentinel ) {
            y = x;
            if ( _comp( KeyOfValue()( z->data ), KeyOfValue()( x->data ) ) ) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        z->parent = y;
        if ( y == _sentinel ) {
            _root = z;
        } else if ( _comp( KeyOfValue()( z->data ),
                           KeyOfValue()( y->data ) ) ) {
            y->left = z;
        } else {
            y->right = z;
            z->left  = _sentinel;
            z->right = _sentinel;
            z->color = RED;
        }
        _insert_fix( z );
        _sentinel->root = _root;
        _size++;
        return iterator( z );
    };

    void _insert_fix( node_pointer z )
    {
        node_pointer y;
        while ( z->parent->color == RED ) {
            if ( z->parent == z->parent->parent->left ) {
                y = z->parent->parent->right;
                if ( y->color == RED ) {
                    z->parent->color         = BLACK;
                    y->color                 = BLACK;
                    z->parent->parent->color = RED;
                    z                        = z->parent->parent;
                } else {
                    if ( z == z->parent->right ) {
                        z = z->parent;
                        _left_rotate( z );
                    }
                    z->parent->color         = BLACK;
                    z->parent->parent->color = RED;
                    _right_rotate( z->parent->parent );
                }
            } else {
                y = z->parent->parent->left;
                if ( y->color == RED ) {
                    z->parent->color         = BLACK;
                    y->color                 = BLACK;
                    z->parent->parent->color = RED;
                    z                        = z->parent->parent;
                } else {
                    if ( z == z->parent->left ) {
                        z = z->parent;
                        _right_rotate( z );
                    }
                    z->parent->color         = BLACK;
                    z->parent->parent->color = RED;
                    _left_rotate( z->parent->parent );
                }
            }
        }
        _root->color = BLACK;
    };

    void _left_rotate( node_pointer x )
    {
        node_pointer y;
        y        = x->right;
        x->right = y->left;
        if ( y->left != _sentinel ) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if ( x->parent == _sentinel ) {
            _root = y;
        } else if ( x == x->parent->left ) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left   = x;
        x->parent = y;
    };

    void _right_rotate( node_pointer x )
    {
        node_pointer y;
        y       = x->left;
        x->left = y->right;
        if ( y->right != _sentinel ) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if ( x->parent == _sentinel ) {
            _root = y;
        } else if ( x == x->parent->right ) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right  = x;
        x->parent = y;
    };

    void _transplant( node_pointer u, node_pointer v )
    {
        if ( u->parent == _sentinel ) {
            _root = v;
        } else if ( u == u->parent->left ) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    };

    void _erase( node_pointer z )
    {
        node_pointer    x                = NULL;
        node_pointer    y                = z;
        t_rb_node_color y_original_color = y->color;
        if ( z->left == _sentinel ) {
            x = z->right;
            _transplant( z, z->right );
        } else if ( z->right == _sentinel ) {
            x = z->left;
            _transplant( z, z->left );
        } else {
            y                = minimum( z->right );
            y_original_color = y->color;
            x                = y->right;
            if ( z != z->right ) {
                _transplant( y, y->right );
                y->right         = z->right;
                y->right->parent = y;
            } else {
                x->parent = y;
            }
            _transplant( z, y );
            y->left         = z->left;
            y->left->parent = y;
            y->color        = z->color;
        }
        _alloc.destroy( z );
        _alloc.deallocate( z, 1 );
        if ( y_original_color == BLACK ) {
            _erase_fix( x );
        }
        _sentinel->root = _root;
        _size--;
    };

    void _erase_fix( node_pointer x )
    {
        node_pointer w;

        while ( x != _root && x->color == BLACK ) {
            if ( x == x->parent->left ) {
                w = x->parent->right;

                if ( w->color == RED ) {
                    w->color         = BLACK;
                    x->parent->color = RED;
                    _left_rotate( x->parent );
                    w = x->parent->right;
                }
                if ( w->left->color == BLACK && w->right->color == BLACK ) {
                    w->color = RED;
                    x        = x->parent;
                } else {
                    if ( w->right->color == BLACK ) {
                        w->left->color = BLACK;
                        w->color       = RED;
                        _right_rotate( w );
                        w = x->parent->right;
                    }
                    w->color         = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color  = BLACK;
                    _left_rotate( x->parent );
                    x = _root;
                }
            } else {
                w = x->parent->left;

                if ( w->color == RED ) {
                    w->color         = BLACK;
                    x->parent->color = RED;
                    _right_rotate( x->parent );
                    w = x->parent->left;
                }
                if ( w->right->color == BLACK && w->left->color == BLACK ) {
                    w->color = RED;
                    x        = x->parent;
                } else {
                    if ( w->left->color == BLACK ) {
                        w->right->color = BLACK;
                        w->color        = RED;
                        _left_rotate( w );
                        w = x->parent->left;
                    }
                    w->color         = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color   = BLACK;
                    _right_rotate( x->parent );
                    x = _root;
                }
            }
        }
        x->color = BLACK;
    };

    node_pointer minimum( node_pointer nptr ) const
    {
        return node::minimum( nptr );
    };

    node_pointer maximum( node_pointer nptr ) const
    {
        return node::maximum( nptr );
    };

    node_pointer successor( node_pointer nptr ) const
    {
        return node::successor( nptr );
    };

    node_pointer predecessor( node_pointer nptr ) const
    {
        return node::predecessor( nptr );
    };

    node_pointer _search( node_pointer nptr, key_type k ) const
    {
        if ( nptr == _sentinel
             || ( !_comp( k, KeyOfValue()( nptr->data ) )
                  && !_comp( KeyOfValue()( nptr->data ), k ) ) ) {
            return nptr;
        }
        if ( _comp( k, KeyOfValue()( nptr->data ) ) ) {
            return _search( nptr->left, k );
        }
        return _search( nptr->right, k );
    };

    node create_node( value_type val, t_rb_node_color color )
    {
        return node(
            val, _root, _sentinel, _sentinel, _sentinel, _sentinel, color );
    }
};

template < RB_TEMPLATE_ARGS >
inline bool operator==( const RB_CLASS_TYPE &lhs, const RB_CLASS_TYPE &rhs )
{
    return lhs.size() == rhs.size()
        && ft::equal( lhs.begin(), lhs.end(), rhs.begin() );
}

template < RB_TEMPLATE_ARGS >
inline bool operator!=( const RB_CLASS_TYPE &lhs, const RB_CLASS_TYPE &rhs )
{
    return !( lhs == rhs );
}

template < RB_TEMPLATE_ARGS >
inline bool operator<( const RB_CLASS_TYPE &lhs, const RB_CLASS_TYPE &rhs )
{
    return ft::lexicographical_compare(
        lhs.begin(), lhs.end(), rhs.begin(), rhs.end() );
}

template < RB_TEMPLATE_ARGS >
inline bool operator<=( const RB_CLASS_TYPE &lhs, const RB_CLASS_TYPE &rhs )
{
    return !( rhs < lhs );
}

template < RB_TEMPLATE_ARGS >
inline bool operator>( const RB_CLASS_TYPE &lhs, const RB_CLASS_TYPE &rhs )
{
    return rhs < lhs;
}

template < RB_TEMPLATE_ARGS >
inline bool operator>=( const RB_CLASS_TYPE &lhs, const RB_CLASS_TYPE &rhs )
{
    return !( lhs < rhs );
}

template < RB_TEMPLATE_ARGS >
inline void swap( RB_CLASS_TYPE &lhs, RB_CLASS_TYPE &rhs )
{
    lhs.swap( rhs );
}

} // namespace ft

#endif // RB_TREE_HPP
