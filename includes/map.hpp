#ifndef MAP_HPP
#define MAP_HPP

#include "functional.hpp"
#include "rb_tree.hpp"
#include "utility.hpp"

#define MAP_TEMPLATE_ARGS                                                      \
    typename Key, typename T, typename Compare, typename Alloc

#define MAP_CLASS_TYPE map< Key, T, Compare, Alloc >

namespace ft {

template < typename Key,
           typename T,
           typename Compare = ft::less<Key>,
           typename Alloc   = std::allocator<ft::pair<const Key, T> > >
class map {
    template < typename P >
    struct select1st
    {
        Key operator()( const P &p ) const { return p.first; }
    };

public:
    typedef Key                             key_type;
    typedef T                               mapped_type;
    typedef ft::pair<const Key, T>          value_type;
    typedef Compare                         key_compare;
    typedef typename Alloc::reference       reference;
    typedef typename Alloc::const_reference const_reference;
    typedef typename Alloc::pointer         pointer;
    typedef typename Alloc::const_pointer   const_pointer;

    class value_compare
        : public std::binary_function<value_type, value_type, bool> {
        friend class map<Key, T, Compare, Alloc>;

    protected:
        Compare comp;

        explicit value_compare( Compare c ) : comp( c ) {}

    public:
        bool operator()( const value_type &x, const value_type &y ) const
        {
            return comp( x.first, y.first );
        }
    };

private:
    typedef rb_tree< key_type,
                     value_type,
                     select1st<value_type>,
                     key_compare,
                     Alloc >
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
    explicit map( const key_compare    &comp  = key_compare(),
                  const allocator_type &alloc = allocator_type() ) :
        _rb_tree( comp, alloc ) {};

    template <typename InputIterator>
    map( InputIterator         first,
         InputIterator         last,
         const key_compare    &comp  = key_compare(),
         const allocator_type &alloc = allocator_type() ) :
        _rb_tree( comp, alloc )
    {
        while ( first != last ) {
            insert( *first );
            ++first;
        }
    };

    map( const map &x ) : _rb_tree( x._rb_tree ) {};

    // Destructor
    ~map() { clear(); };

    // Operators
    map &operator=( const map &x )
    {
        _rb_tree = x._rb_tree;
        return *this;
    };

    // Iterators
    iterator               begin() { return _rb_tree.begin(); };
    const_iterator         begin() const { return _rb_tree.begin(); };
    iterator               end() { return _rb_tree.end(); };
    const_iterator         end() const { return _rb_tree.end(); };
    reverse_iterator       rbegin() { return _rb_tree.rbegin(); };
    const_reverse_iterator rbegin() const { return _rb_tree.rbegin(); };
    reverse_iterator       rend() { return _rb_tree.rend(); };
    const_reverse_iterator rend() const { return _rb_tree.rend(); };

    // Capacity
    bool      empty() const { return _rb_tree.empty(); };
    size_type size() const { return _rb_tree.size(); };
    size_type max_size() const { return _rb_tree.max_size(); };

    // Element access
    mapped_type &operator[]( const key_type &k )
    {
        iterator it = insert( begin(), ft::make_pair( k, mapped_type() ) );
        return it->second;
    };

    // Modifiers
    ft::pair<iterator, bool> insert( const value_type &val )
    {
        iterator it = find( val.first );
        if ( it != end() ) {
            return ft::make_pair( it, false );
        } else {
            return ft::make_pair( _rb_tree.insert_unique( val ), true );
        }
    };

    iterator insert( iterator position, const value_type &val )
    {
        iterator it = find( val.first );
        if ( it != end() ) {
            return it;
        } else {
            _rb_tree.insert( val, position.base() );
            return find( val.first );
        }
    };

    template <typename InputIterator>
    void insert( InputIterator first, InputIterator last )
    {
        while ( first != last ) {
            insert( *first );
            ++first;
        }
    };

    void      erase( iterator position ) { _rb_tree.erase( position->first ); };
    size_type erase( const key_type &k ) { return _rb_tree.erase( k ); };
    void      erase( iterator first, iterator last )
    {
        _rb_tree.erase( first, last );
    };
    void swap( map &x ) { _rb_tree.swap( x._rb_tree ); };
    void clear() { _rb_tree.clear(); };

    // Observers
    key_compare   key_comp() const { return _rb_tree.key_comp(); };
    value_compare value_comp() const
    {
        return value_compare( _rb_tree.key_comp() );
    };

    // Operations
    iterator find( const key_type &k )
    {
        return iterator( _rb_tree.search( k ) );
    };

    const_iterator find( const key_type &k ) const
    {
        return _rb_tree.search( k );
    };

    size_type count( const key_type &k ) const { return _rb_tree.count( k ); };

    iterator lower_bound( const key_type &k )
    {
        return _rb_tree.lower_bound( k );
    };

    const_iterator lower_bound( const key_type &k ) const
    {
        return _rb_tree.lower_bound( k );
    };

    iterator upper_bound( const key_type &k )
    {
        return _rb_tree.upper_bound( k );
    };

    const_iterator upper_bound( const key_type &k ) const
    {
        return _rb_tree.upper_bound( k );
    };

    ft::pair<iterator, iterator> equal_range( const key_type &k )
    {
        return _rb_tree.equal_range( k );
    };

    ft::pair<const_iterator, const_iterator>
    equal_range( const key_type &k ) const
    {
        return _rb_tree.equal_range( k );
    };

    // Allocator
    allocator_type get_allocator() const { return _rb_tree.get_allocator(); };

    // Non-member functions
    template <typename K1, typename T1, typename C1, typename A1>
    friend bool operator==( const map<K1, T1, C1, A1> &,
                            const map<K1, T1, C1, A1> & );

    template <typename K1, typename T1, typename C1, typename A1>
    friend bool operator<( const map<K1, T1, C1, A1> &,
                           const map<K1, T1, C1, A1> & );
};

template < MAP_TEMPLATE_ARGS >
bool operator==( const MAP_CLASS_TYPE &lhs, const MAP_CLASS_TYPE &rhs )
{
    return lhs._rb_tree == rhs._rb_tree;
};

template < MAP_TEMPLATE_ARGS >
bool operator!=( const MAP_CLASS_TYPE &lhs, const MAP_CLASS_TYPE &rhs )
{
    return !( lhs == rhs );
};

template < MAP_TEMPLATE_ARGS >
bool operator<( const MAP_CLASS_TYPE &lhs, const MAP_CLASS_TYPE &rhs )
{
    return lhs._rb_tree < rhs._rb_tree;
};

template < MAP_TEMPLATE_ARGS >
bool operator<=( const MAP_CLASS_TYPE &lhs, const MAP_CLASS_TYPE &rhs )
{
    return !( rhs < lhs );
};

template < MAP_TEMPLATE_ARGS >
bool operator>( const MAP_CLASS_TYPE &lhs, const MAP_CLASS_TYPE &rhs )
{
    return rhs < lhs;
};

template < MAP_TEMPLATE_ARGS >
bool operator>=( const MAP_CLASS_TYPE &lhs, const MAP_CLASS_TYPE &rhs )
{
    return !( lhs < rhs );
};

template < MAP_TEMPLATE_ARGS >
void swap( MAP_CLASS_TYPE &x, MAP_CLASS_TYPE &y )
{
    x.swap( y );
};

} // namespace ft

#endif // MAP_HPP
