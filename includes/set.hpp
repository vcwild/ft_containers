#ifndef SET_HPP
#define SET_HPP

#define SET_TEMPLATE_ARGS typename T, typename Compare, typename Alloc
#define SET_CLASS_TYPE set<T, Compare, Alloc>

#include "functional.hpp"
#include "rb_tree.hpp"
#include "utility.hpp"
#include <memory.h>

namespace ft {

template < class T,
           class Compare = ft::less<T>,
           class Alloc   = std::allocator<T> >
class set {
    template <typename P>
    struct set_key_compare
    {
        T operator()( const P &x ) const { return x; }
    };

public:
    typedef T                               key_type;
    typedef T                               value_type;
    typedef Compare                         key_compare;
    typedef Compare                         value_compare;
    typedef typename Alloc::reference       reference;
    typedef typename Alloc::const_reference const_reference;
    typedef typename Alloc::pointer         pointer;
    typedef typename Alloc::const_pointer   const_pointer;

private:
    typedef rb_tree<key_type,
                    value_type,
                    set_key_compare<value_type>,
                    key_compare,
                    Alloc>
                 rb_tree_type;
    rb_tree_type _rb_tree;

public:
    typedef typename rb_tree_type::allocator_type  allocator_type;
    typedef typename rb_tree_type::size_type       size_type;
    typedef typename rb_tree_type::difference_type difference_type;

    typedef typename rb_tree_type::iterator         iterator;
    typedef typename rb_tree_type::const_iterator   const_iterator;
    typedef typename rb_tree_type::reverse_iterator reverse_iterator;
    typedef
        typename rb_tree_type::const_reverse_iterator const_reverse_iterator;

    // Constructors
    explicit set( const key_compare    &comp  = key_compare(),
                  const allocator_type &alloc = allocator_type() ) :
        _rb_tree( comp, alloc ) {};

    template <class InputIterator>
    set( InputIterator         first,
         InputIterator         last,
         const key_compare    &comp  = key_compare(),
         const allocator_type &alloc = allocator_type() ) :
        _rb_tree( comp, alloc )
    {
        while ( first != last )
            insert( *first++ );
    };

    set( const set &s ) : _rb_tree( s._rb_tree ) {};

    // Destructor
    ~set() { clear(); };

    // Assignment operator
    set &operator=( const set &s )
    {
        if ( this != &s )
            _rb_tree = s._rb_tree;
        return *this;
    };

    // Iterators
    iterator       begin() { return _rb_tree.begin(); };
    const_iterator begin() const { return _rb_tree.begin(); };

    iterator       end() { return _rb_tree.end(); };
    const_iterator end() const { return _rb_tree.end(); };

    reverse_iterator       rbegin() { return _rb_tree.rbegin(); };
    const_reverse_iterator rbegin() const { return _rb_tree.rbegin(); };

    reverse_iterator       rend() { return _rb_tree.rend(); };
    const_reverse_iterator rend() const { return _rb_tree.rend(); };

    // Capacity
    bool      empty() const { return _rb_tree.empty(); };
    size_type size() const { return _rb_tree.size(); };
    size_type max_size() const { return _rb_tree.max_size(); };

    // Modifiers
    ft::pair<iterator, bool> insert( const value_type &val )
    {
        iterator it = find( val );
        if ( it == end() ) {
            return ft::make_pair( _rb_tree.insert_unique( val ), true );
        }
        return ft::make_pair( it, false );
    };

    iterator insert( iterator position, const value_type &val )
    {
        iterator it = find( val );
        if ( it != end() ) {
            return it;
        }
        _rb_tree.insert( val, position.base() );
        return find( val );
    };

    template <class InputIterator>
    void insert( InputIterator first, InputIterator last )
    {
        while ( first != last )
            insert( *first++ );
    };

    void erase( iterator position ) { _rb_tree.erase( *position ); };

    size_type erase( const value_type &val )
    {
        iterator it = find( val );
        if ( it == end() ) {
            return 0;
        }
        erase( it );
        return 1;
    };

    void erase( iterator first, iterator last )
    {
        while ( first != last )
            erase( first++ );
    };

    void swap( set &s ) { _rb_tree.swap( s._rb_tree ); };

    void clear() { _rb_tree.clear(); };

    // Observers
    key_compare key_comp() const { return _rb_tree.key_comp(); };

    value_compare value_comp() const { return _rb_tree.key_comp(); };

    // Operations
    iterator find( const value_type &val ) const
    {
        return iterator( _rb_tree.search( val ) );
    };

    size_type count( const value_type &val ) const
    {
        if ( find( val ) == end() ) {
            return 0;
        }
        return 1;
    };

    iterator lower_bound( const value_type &val ) const
    {
        return _rb_tree.lower_bound( val );
    };

    iterator upper_bound( const value_type &val ) const
    {
        return _rb_tree.upper_bound( val );
    };

    ft::pair<iterator, iterator> equal_range( const value_type &val ) const
    {
        return ft::make_pair( lower_bound( val ), upper_bound( val ) );
    };

    // Allocator
    allocator_type get_allocator() const { return _rb_tree.get_allocator(); };

    // Non-member functions
    template <typename T1, typename C1, typename A1>
    friend bool operator==( const set<T1, C1, A1> &lhs,
                            const set<T1, C1, A1> &rhs );

    template <typename T1, typename C1, typename A1>
    friend bool operator!=( const set<T1, C1, A1> &lhs,
                            const set<T1, C1, A1> &rhs );

    template <typename T1, typename C1, typename A1>
    friend bool operator<( const set<T1, C1, A1> &lhs,
                           const set<T1, C1, A1> &rhs );

    template <typename T1, typename C1, typename A1>
    friend bool operator<=( const set<T1, C1, A1> &lhs,
                            const set<T1, C1, A1> &rhs );

    template <typename T1, typename C1, typename A1>
    friend bool operator>( const set<T1, C1, A1> &lhs,
                           const set<T1, C1, A1> &rhs );

    template <typename T1, typename C1, typename A1>
    friend bool operator>=( const set<T1, C1, A1> &lhs,
                            const set<T1, C1, A1> &rhs );
};

template < SET_TEMPLATE_ARGS >
inline bool operator==( const SET_CLASS_TYPE &lhs, const SET_CLASS_TYPE &rhs )
{
    return lhs._rb_tree == rhs._rb_tree;
};

template < SET_TEMPLATE_ARGS >
inline bool operator!=( const SET_CLASS_TYPE &lhs, const SET_CLASS_TYPE &rhs )
{
    return lhs._rb_tree != rhs._rb_tree;
};

template < SET_TEMPLATE_ARGS >
inline bool operator<( const SET_CLASS_TYPE &lhs, const SET_CLASS_TYPE &rhs )
{
    return lhs._rb_tree < rhs._rb_tree;
};

template < SET_TEMPLATE_ARGS >
inline bool operator<=( const SET_CLASS_TYPE &lhs, const SET_CLASS_TYPE &rhs )
{
    return lhs._rb_tree <= rhs._rb_tree;
};

template < SET_TEMPLATE_ARGS >
inline bool operator>( const SET_CLASS_TYPE &lhs, const SET_CLASS_TYPE &rhs )
{
    return lhs._rb_tree > rhs._rb_tree;
};

template < SET_TEMPLATE_ARGS >
inline bool operator>=( const SET_CLASS_TYPE &lhs, const SET_CLASS_TYPE &rhs )
{
    return lhs._rb_tree >= rhs._rb_tree;
};

template < SET_TEMPLATE_ARGS >
inline void swap( SET_CLASS_TYPE &lhs, SET_CLASS_TYPE &rhs )
{
    lhs.swap( rhs );
};

} // namespace ft

#endif // SET_HPP
