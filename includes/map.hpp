/*
 * Copyright 2022 ©️ vcwild under the GNU Affero General Public License v3.0.
 */
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
    /**
     * @brief Inserts a element into the map container
     *
     * @param val The value to insert
     * @return ft::pair<iterator, bool> Returns a pair, with its member
     * pair::first
     */
    ft::pair<iterator, bool> insert( const value_type &val )
    {
        iterator it = find( val.first );
        if ( it != end() ) {
            return ft::make_pair( it, false );
        } else {
            return ft::make_pair( _rb_tree.insert_unique( val ), true );
        }
    };

    /**
     * @brief Inserts a element into the map container
     *
     *
     * @param position The iterator with the position where the element will be
     * inserted
     * @param val The value to insert
     * @return iterator Returns an iterator to the inserted element
     */
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

    /**
     * @brief Inserts a range of elements into the map container
     *
     *
     * @tparam InputIterator The iterator type
     * @param first The iterator to the first element of the range
     * @param last The iterator to the last element of the range
     */
    template <typename InputIterator>
    void insert( InputIterator first, InputIterator last )
    {
        while ( first != last ) {
            insert( *first );
            ++first;
        }
    };

    /**
     * @brief Erases an element from the map container
     *
     *
     * @param it The iterator to the element to erase
     */
    void erase( iterator it ) { _rb_tree.erase( it->first ); };

    /**
     * @brief Eraes an element from the map container
     *
     *
     * @param k The key of the element to erase
     *
     * @return size_type Returns the number of elements erased
     */
    size_type erase( const key_type &k )
    {
        if ( find( k ) == end() ) {
            return 0;
        }
        _rb_tree.erase( k );
        return 1;
    };

    /**
     * @brief Erases a range of elements from the map container
     *
     * @param first The iterator to the first element of the range
     * @param last The iterator to the last element of the range
     */
    void erase( iterator first, iterator last )
    {
        while ( first != last ) {
            erase( first );
            ++first;
        }
    };

    /**
     * @brief Swaps the contents of two map containers
     *
     * @param x The map container to swap with
     */
    void swap( map &x ) { _rb_tree.swap( x._rb_tree ); };

    /**
     * @brief Clears the contents of the map container
     *
     */
    void clear() { _rb_tree.clear(); };

    // Observers
    key_compare   key_comp() const { return _rb_tree.key_comp(); };
    value_compare value_comp() const
    {
        return value_compare( _rb_tree.key_comp() );
    };

    // Operations
    /**
     * @brief Finds an element with a specific key
     *
     * @param k The key to search for
     * @return iterator Returns an iterator to the element, if the element is
     * not found, the function returns an iterator to map::end
     */
    iterator find( const key_type &k )
    {
        return iterator( _rb_tree.search( k ) );
    };

    /**
     * @brief Finds an element with a specific key
     *
     * @param k The key to search for
     * @return const_iterator Returns an iterator to the element, if the element
     * is not found, the function returns an iterator to map::end
     */
    const_iterator find( const key_type &k ) const
    {
        return const_iterator( _rb_tree.search( k ) );
    };

    /**
     * @brief Counts the number of elements with a specific key
     *
     * @param k The key to count elements with
     * @return size_type Returns the number of elements with the specified key
     */
    size_type count( const key_type &k ) const { return _rb_tree.count( k ); };

    /**
     * @brief Returns a reference to the mapped value of the element identified
     with key k.

     *
     * @param k The key to search for
     * @return iterator Returns an iterator to the first element not less than k
     */
    iterator lower_bound( const key_type &k )
    {
        return _rb_tree.lower_bound( k );
    };

    /**
     * @brief Returns a reference to the mapped value of the element identified
     * with key k.
     *
     * @param k The key to search for
     * @return const_iterator Returns an iterator to the first element not less
     * than k
     */
    mapped_type &at( const key_type &k )
    {
        iterator it = find( k );
        if ( it == end() ) {
            throw std::out_of_range( "map::at" );
        }
        return it->second;
    };

    /**
     * @brief  Returns a reference to the mapped value of the element identified
     * with key k.
     *
     * @param k The key to search for
     * @return const_iterator Returns an iterator to the first element not less
     * than k
     */
    const mapped_type &at( const key_type &k ) const
    {
        const_iterator it = find( k );
        if ( it == end() ) {
            throw std::out_of_range( "map::at" );
        }
        return it->second;
    };

    /**
     * @brief The lower bound of a key
     *
     * @param k The key to search for
     * @return iterator Returns an iterator to the first element not less than k
     */
    const_iterator lower_bound( const key_type &k ) const
    {
        return _rb_tree.lower_bound( k );
    };

    /**
     * @brief The upper bound of a key
     *
     * @param k The key to search for
     * @return iterator Returns an iterator to the first element greater than k
     */
    iterator upper_bound( const key_type &k )
    {
        return _rb_tree.upper_bound( k );
    };

    /**
     * @brief The upper bound of a key
     *
     * @param k The key to search for
     * @return iterator Returns an iterator to the first element greater than k
     */
    const_iterator upper_bound( const key_type &k ) const
    {
        return _rb_tree.upper_bound( k );
    };

    /**
     * @brief Gets a range of elements with a specific key
     *
     * @param k The key to search for
     * @return ft::pair<const_iterator, const_iterator> Returns a pair of
     * iterators, the first is the lower bound, the second is the upper bound
     */
    ft::pair<iterator, iterator> equal_range( const key_type &k )
    {
        return _rb_tree.equal_range( k );
    };

    /**
     * @brief Gets a range of elements with a specific key
     *
     * @param k The key to search for
     * @return ft::pair<const_iterator, const_iterator> Returns a pair of
     * iterators, the first is the lower bound, the second is the upper bound
     */
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
}

template < MAP_TEMPLATE_ARGS >
bool operator!=( const MAP_CLASS_TYPE &lhs, const MAP_CLASS_TYPE &rhs )
{
    return !( lhs == rhs );
}

template < MAP_TEMPLATE_ARGS >
bool operator<( const MAP_CLASS_TYPE &lhs, const MAP_CLASS_TYPE &rhs )
{
    return lhs._rb_tree < rhs._rb_tree;
}

template < MAP_TEMPLATE_ARGS >
bool operator<=( const MAP_CLASS_TYPE &lhs, const MAP_CLASS_TYPE &rhs )
{
    return !( rhs < lhs );
}

template < MAP_TEMPLATE_ARGS >
bool operator>( const MAP_CLASS_TYPE &lhs, const MAP_CLASS_TYPE &rhs )
{
    return rhs < lhs;
}

template < MAP_TEMPLATE_ARGS >
bool operator>=( const MAP_CLASS_TYPE &lhs, const MAP_CLASS_TYPE &rhs )
{
    return !( lhs < rhs );
}

template < MAP_TEMPLATE_ARGS >
void swap( MAP_CLASS_TYPE &x, MAP_CLASS_TYPE &y )
{
    x.swap( y );
}

} // namespace ft

#endif // MAP_HPP
