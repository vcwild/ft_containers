/*
 * Copyright 2022 ©️ vcwild under the GNU Affero General Public License v3.0.
 */
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "algorithm.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>

namespace ft {

template < typename T, typename Alloc = std::allocator<T> >
class vector {
public:
    typedef T                                         value_type;
    typedef Alloc                                     allocator_type;
    typedef typename allocator_type::reference        reference;
    typedef typename allocator_type::const_reference  const_reference;
    typedef typename allocator_type::pointer          pointer;
    typedef typename allocator_type::const_pointer    const_pointer;
    typedef typename allocator_type::difference_type  difference_type;
    typedef typename allocator_type::size_type        size_type;
    typedef ft::random_access_iterator<pointer>       iterator;
    typedef ft::random_access_iterator<const_pointer> const_iterator;
    typedef ft::reverse_iterator<iterator>            reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>      const_reverse_iterator;

protected:
    allocator_type _alloc;
    pointer        _data;
    size_type      _size;
    size_type      _capacity;

public:
    explicit vector( const allocator_type &alloc = allocator_type() ) :
        _alloc( alloc ), _data( NULL ), _size( 0 ), _capacity( 0 ) {};

    explicit vector( size_type             n,
                     const value_type     &val   = value_type(),
                     const allocator_type &alloc = allocator_type() ) :
        _alloc( alloc ),
        _data( NULL ), _size( 0 ), _capacity( n )
    {
        if ( n > max_size() ) {
            throw std::length_error( "std::length_error" );
        }
        _data = _alloc.allocate( _capacity );
        if ( _data == NULL ) {
            throw std::bad_alloc();
        }
        for ( size_t i = 0; i < _capacity; i++ ) {
            _alloc.construct( _data + i, val );
            _size++;
        }
    };

    template <typename Iterator>
    vector( Iterator              first,
            Iterator              last,
            const allocator_type &alloc = allocator_type() ) :
        _alloc( alloc ),
        _data( NULL ), _size( 0 ), _capacity( 0 )
    {
        typename ft::is_integral<Iterator>::type is_integral;
        _handle_integral_type( first, last, is_integral );
    };

    template < typename Integer >
    void _handle_integral_type( Integer n, Integer val, true_type )
    {

        _capacity = n;
        _data     = _alloc.allocate( _capacity );
        if ( _data == NULL )
            throw std::bad_alloc();
        for ( size_type i = 0; i < _capacity; i++ )
            _alloc.construct( _data + i, val );
        _size++;
    };

    template < typename Iterator >
    void _handle_integral_type( Iterator first, Iterator last, false_type )
    {
        size_type n = ft::distance( first, last );
        _capacity   = n;
        _data       = _alloc.allocate( _capacity );
        if ( _data == NULL )
            throw std::bad_alloc();
        for ( size_type i = 0; i < _capacity; i++ )
            _alloc.construct( _data + i, *first++ );
        _size++;
    };

    vector( const vector &x ) :
        _alloc( x.get_allocator() ), _data( NULL ), _size( 0 ), _capacity( 0 )
    {
        *this = x;
    };

    ~vector()
    {
        clear();
        _alloc.deallocate( _data, _capacity );
    };

    vector &operator=( const vector &x )
    {
        if ( this == &x )
            return *this;
        for ( size_type i = 0; i < _size; i++ )
            _alloc.destroy( _data + i );
        _alloc.deallocate( _data, _capacity );
        _alloc    = x.get_allocator();
        _size     = x.size();
        _capacity = x.capacity();
        _data     = _alloc.allocate( _capacity );
        if ( _data == NULL )
            throw std::bad_alloc();
        for ( size_type i = 0; i < _size; i++ )
            _alloc.construct( _data + i, x._data[i] );
        return *this;
    };

    // Iterators
    iterator       begin() { return iterator( _data ); };
    const_iterator begin() const { return const_iterator( _data ); };

    iterator       end() { return iterator( _data + _size ); };
    const_iterator end() const { return const_iterator( _data + _size ); };

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

    const_iterator cbegin() const { return begin(); };
    const_iterator cend() const { return end(); };

    const_reverse_iterator crbegin() const { return rbegin(); };
    const_reverse_iterator crend() const { return rend(); };

    // Capacity
    size_type size() const { return _size; };
    size_type max_size() const { return _alloc.max_size(); };

    /**
     * @brief Resizes the container so that it contains n elements.
     *
     * @param n The new container size, expressed in number of elements.
     * @param val The value to initialize the new elements with.
     */
    void resize( size_type n, value_type val = value_type() )
    {
        if ( n > _size ) {
            if ( n > _capacity )
                reserve( n );
            for ( size_type i = _size; i < n; i++ )
                _alloc.construct( _data + i, val );
        } else {
            for ( size_type i = n; i < _size; i++ )
                _alloc.destroy( _data + i );
        }
        _size = n;
    };

    size_type capacity() const { return _capacity; };
    bool      empty() const { return ( _size == 0 ); };

    /**
     * @brief Reserves the storage capacity for the container to be at least
     * enough to contain n elements.
     *
     * @param n The size of the memory to reserve
     */
    void reserve( size_type n )
    {
        if ( n > _capacity ) {
            pointer tmp = _alloc.allocate( n );
            if ( tmp == NULL )
                throw std::bad_alloc();
            for ( size_type i = 0; i < _size; i++ )
                _alloc.construct( tmp + i, _data[i] );
            for ( size_type i = 0; i < _size; i++ )
                _alloc.destroy( _data + i );
            _alloc.deallocate( _data, _capacity );
            _data     = tmp;
            _capacity = n;
        }
    };

    /**
     * @brief Shrinks the capacity of the vector to fit its size. It is done by
     * creating a new vector and copying the elements of the current vector to
     * the new one and then destroying the current vector.
     */
    void shrink_to_fit()
    {
        if ( _size < _capacity ) {
            pointer tmp = _alloc.allocate( _size );
            if ( tmp == NULL )
                throw std::bad_alloc();
            for ( size_type i = 0; i < _size; i++ )
                _alloc.construct( tmp + i, _data[i] );
            for ( size_type i = 0; i < _size; i++ )
                _alloc.destroy( _data + i );
            _alloc.deallocate( _data, _capacity );
            _data     = tmp;
            _capacity = _size;
        }
    };

    // Element access
    reference       operator[]( size_type n ) { return at( n ); };
    const_reference operator[]( size_type n ) const { return at( n ); };

    /**
     * @brief Fetches the element at position n in the vector.
     *
     * @param n The position of the element to fetch.
     * @return reference A reference to the element at position n.
     */
    reference at( size_type n )
    {
        if ( n >= _size )
            throw std::out_of_range( "vector::at" );
        return _data[n];
    };
    const_reference at( size_type n ) const
    {
        if ( n >= _size )
            throw std::out_of_range( "vector::at" );
        return _data[n];
    };

    reference       front() { return _data[0]; };
    const_reference front() const { return _data[0]; };

    reference       back() { return _data[_size - 1]; };
    const_reference back() const { return _data[_size - 1]; };

    pointer       data() { return _data; };
    const_pointer data() const { return _data; };

    // Modifiers
    /**
     * @brief Assigns new contents to the vector, replacing its current
     *
     * @param n Number of elements to assign
     * @param val Value to assign
     */
    void assign( size_type n, const value_type &val )
    {
        clear();
        reserve( n );
        for ( size_type i = 0; i < n; i++ )
            push_back( val );
    };

    /**
     * @brief Pushes a new element at the end of the vector.
     *
     * @param val The value to be copied (or moved) to the new element.
     */
    void push_back( const value_type &val )
    {
        if ( _size == _capacity )
            reserve( _capacity + 1 );
        _alloc.construct( _data + _size, val );
        _size++;
    };

    /**
     * @brief Removes the last element in the vector, effectively reducing the
     * container size by one.
     */
    void pop_back()
    {
        if ( _size > 0 ) {
            _alloc.destroy( _data + _size - 1 );
            _size--;
        }
    };

    /**
     * @brief Inserts elements at the specified location in the container.
     *
     * @param position Iterator to the element before which the content will be
     * inserted. position may be the end() iterator.
     * @param val Value to be copied (or moved) to the inserted elements.
     * @return Iterator pointing to the first element inserted, or position if
     * no elements were inserted.
     */
    iterator insert( iterator position, const value_type &val )
    {
        size_type pos = position - begin();

        if ( _size == _capacity )
            reserve( _capacity + 1 );
        for ( size_type i = _size; i > pos; i-- )
            _alloc.construct( _data + i, _data[i - 1] );
        _alloc.construct( _data + pos, val );
        _size++;
        return begin() + pos;
    };

    /**
     * @brief Inserts elements at the specified location in the container.
     *
     * @param position Iterator to the element before which the content will be
     * inserted. position may be the end() iterator.
     * @param n Number of elements to insert. Each element is initialized to a
     * copy of val.
     * @param val Value to be copied (or moved) to the inserted elements.
     */
    void insert( iterator position, size_type n, const value_type &val )
    {
        if ( position < begin() || position > end() )
            throw std::out_of_range( "vector::insert" );
        if ( n == 0 )
            return;
        if ( n > max_size() - _size )
            throw std::length_error( "vector::insert" );
        if ( _size + n > _capacity )
            reserve( _size + n );
        for ( size_type i = _capacity; i > _size; i-- )
            _alloc.construct( _data + i - 1, _data[i - n - 1] );
        for ( size_type i = 0; i < n; i++ )
            _alloc.construct( _data + i, val );
        _size += n;
    };

    /**
     * @brief Template version of insert
     *
     * @tparam Iterator The type of the iterator
     * @param position The position to insert the elements
     * @param first The typenamed iterator to the first element to insert
     * @param last The typenamed iterator to the last element to insert
     */
    template <typename Iterator>
    void insert( iterator position, Iterator first, Iterator last )
    {
        if ( position < begin() || position > end() )
            throw std::out_of_range( "vector::insert" );
        size_type n = last - first;
        if ( n == 0 )
            return;
        if ( n > ( max_size() - _size ) )
            throw std::length_error( "vector::insert" );
        if ( _size + n > _capacity )
            reserve( _size + n );
        size_type pos = position - begin();
        for ( size_type i = _size; i > pos; i-- )
            _alloc.construct( _data + i + n - 1, _data[i - 1] );
        for ( size_type i = 0; i < n; i++ )
            _alloc.construct( _data + pos + i, first[i] );
        _size += n;
    };

    /**
     * @brief Erases the specified elements from the container.
     *
     * @param position Iterator pointing to the first element to be erased.
     * @return Iterator pointing to the element that followed the last element
     * erased by the function call. This is the container end if the operation
     * erased the last element in the sequence.
     */
    iterator erase( iterator position )
    {
        if ( position < begin() || position >= end() )
            throw std::out_of_range( "vector::erase" );
        size_type pos = position - begin();
        _alloc.destroy( _data + pos );
        for ( size_type i = pos; i < _size - 1; i++ )
            _alloc.construct( _data + i, _data[i + 1] );
        _size--;
        return begin() + pos;
    };

    /**
     * @brief Erases the specified elements from the container.
     *
     * @param first Iterator pointing to the first element to be erased.
     * @param last Iterator pointing to the element following the last element
     * to be erased.
     * @return Iterator pointing to the element that followed the last element
     * erased by the function call. This is the container end if the operation
     * erased the last element in the sequence.
     */
    iterator erase( iterator first, iterator last )
    {
        if ( first < begin() || first > end() || last < begin()
             || last > end() )
            throw std::out_of_range( "vector::erase" );
        if ( first == last )
            return first;
        size_type pos = first - begin();
        size_type n   = last - first;
        for ( size_type i = pos; i < _size - n; i++ )
            _alloc.construct( _data + i, _data[i + n] );
        for ( size_type i = _size - n; i < _size; i++ )
            _alloc.destroy( _data + i );
        _size -= n;
        return begin() + pos;
    };

    /**
     * @brief Exchanges the content of the container by the content of x,
     * which is another vector object of the same type. Sizes may differ.
     *
     * @param x Another vector object of the same type (with the same class
     * template arguments T, Alloc).
     */
    void swap( vector &x )
    {
        pointer        tmp_data     = _data;
        size_type      tmp_size     = _size;
        size_type      tmp_capacity = _capacity;
        allocator_type tmp_alloc    = _alloc;

        _data     = x.data();
        _size     = x.size();
        _capacity = x.capacity();
        _alloc    = x.get_allocator();

        x._data     = tmp_data;
        x._size     = tmp_size;
        x._capacity = tmp_capacity;
        x._alloc    = tmp_alloc;
    }

    /**
     * @brief Removes all elements from the vector (which are destroyed),
     * leaving the container with a size of 0.
     */
    void clear()
    {
        for ( size_type i = 0; i < _size; i++ )
            _alloc.destroy( _data + i );
        _size = 0;
    };

    // Allocator accessor
    allocator_type get_allocator() const { return _alloc; };
};

template < typename T, typename Alloc >
inline bool operator==( const vector<T, Alloc> &lhs,
                        const vector<T, Alloc> &rhs )
{
    return ( lhs.size() == rhs.size()
             && ft::equal( lhs.begin(), lhs.end(), rhs.begin() ) );
}

template < typename T, typename Alloc >
inline bool operator!=( const vector<T, Alloc> &lhs,
                        const vector<T, Alloc> &rhs )
{
    return !( lhs == rhs );
}

template < typename T, typename Alloc >
inline bool operator<( const vector<T, Alloc> &lhs,
                       const vector<T, Alloc> &rhs )
{
    return ( ft::lexicographical_compare(
        lhs.begin(), lhs.end(), rhs.begin(), rhs.end() ) );
}

template < typename T, typename Alloc >
inline bool operator<=( const vector<T, Alloc> &lhs,
                        const vector<T, Alloc> &rhs )
{
    return !( rhs < lhs );
}

template < typename T, typename Alloc >
inline bool operator>( const vector<T, Alloc> &lhs,
                       const vector<T, Alloc> &rhs )
{
    return rhs < lhs;
}

template < typename T, typename Alloc >
inline bool operator>=( const vector<T, Alloc> &lhs,
                        const vector<T, Alloc> &rhs )
{
    return !( lhs < rhs );
}

template < typename T, typename Alloc >
inline void swap( vector<T, Alloc> &x, vector<T, Alloc> &y )
{
    x.swap( y );
}

} // namespace ft

#endif // VECTOR_HPP
