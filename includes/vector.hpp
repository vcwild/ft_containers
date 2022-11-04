#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstring>
#include <iostream>
#include <memory>

namespace ft {

template < typename T, typename Alloc = std::allocator<T> >
class vector {
public:
    typedef T                                        value_type;
    typedef Alloc                                    allocator_type;
    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;
    typedef pointer                                  iterator;
    typedef const_pointer                            const_iterator;
    typedef std::reverse_iterator<iterator>          reverse_iterator;
    typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;
    typedef typename allocator_type::difference_type difference_type;
    typedef typename allocator_type::size_type       size_type;

    // Constructors
    explicit vector( const allocator_type &alloc = allocator_type() )
    {
        _alloc    = alloc;
        _size     = 0;
        _capacity = 0;
        _data     = NULL;
    };

    vector( size_type             n,
            const value_type     &val   = value_type(),
            const allocator_type &alloc = allocator_type() )
    {
        _alloc    = alloc;
        _size     = n;
        _capacity = n;
        _data     = _alloc.allocate( n );
        for ( size_type i = 0; i < n; i++ )
            _alloc.construct( _data + i, val );
    };

    template <class InputIterator>
    vector( InputIterator         first,
            InputIterator         last,
            const allocator_type &alloc = allocator_type() )
    {
        _alloc    = alloc;
        _size     = 0;
        _capacity = 0;
        _data     = NULL;
        assign( first, last );
    };

    vector( const vector &x )
    {
        _alloc    = x._alloc;
        _size     = x._size;
        _capacity = x._capacity;
        _data     = _alloc.allocate( _capacity );
        for ( size_type i = 0; i < _size; i++ )
            _alloc.construct( _data + i, x._data[i] );
    };

    // Destructor
    ~vector()
    {
        for ( size_type i = 0; i < _size; i++ )
            _alloc.destroy( _data + i );
        _alloc.deallocate( _data, _capacity );
    };

    // Operators
    vector &operator=( const vector &x )
    {
        if ( this == &x )
            return *this;
        for ( size_type i = 0; i < _size; i++ )
            _alloc.destroy( _data + i );
        _alloc.deallocate( _data, _capacity );
        _alloc    = x._alloc;
        _size     = x._size;
        _capacity = x._capacity;
        _data     = _alloc.allocate( _capacity );
        for ( size_type i = 0; i < _size; i++ )
            _alloc.construct( _data + i, x._data[i] );
        return *this;
    };

    // Iterators
    iterator       begin() { return _data; };
    const_iterator begin() const { return _data; };

    iterator       end() { return _data + _size; };
    const_iterator end() const { return _data + _size; };

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
    // TODO: implement resize
    void      resize( size_type n, value_type val = value_type() );
    size_type capacity() const { return _capacity; };
    bool      empty() const { return ( _size == 0 ); };
    // TODO: implement reserve
    void reserve( size_type n );
    // TODO: implement shrink_to_fit
    void shrink_to_fit();

    // Element access
    reference       operator[]( size_type n ) { return _data[n]; };
    const_reference operator[]( size_type n ) const { return _data[n]; };

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
    void assign( size_type n, const value_type &val )
    {
        clear();
        reserve( n );
        for ( size_type i = 0; i < n; i++ )
            push_back( val );
    };

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
    iterator insert( iterator position, const value_type &val ) {};

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
        size_type pos = position - begin();
        for ( size_type i = _size; i > pos; i-- )
            _alloc.construct( _data + i + n - 1, _data[i - 1] );
        for ( size_type i = 0; i < n; i++ )
            _alloc.construct( _data + pos + i, val );
        _size += n;
    };

    // TODO: implement insert input iterator
    template <class InputIterator>
    void insert( iterator position, InputIterator first, InputIterator last );

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

    // TODO: implement swap
    /**
     * @brief Exchanges the content of the container by the content of x,
     * which is another vector object of the same type. Sizes may differ.
     *
     * @param x Another vector object of the same type (with the same class
     * template arguments T, Alloc).
     */
    void swap( vector &x );

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

    /**
     * @brief Resizes the container so that it contains n elements.
     *
     * @tparam ...Args Types of arguments to be passed to the constructor of
     * @param position Iterator to the element before which the content will be
     * @param ...args Arguments to be passed to the constructor of the new
     * @return An iterator that points to the newly emplaced element
     */
    template <class... Args>
    iterator emplace( const_iterator position, Args &&...args )
    {
        if ( position < begin() || position > end() )
            throw std::out_of_range( "vector::emplace" );
        size_type pos = position - begin();
        if ( _size == _capacity )
            reserve( _capacity + 1 );
        for ( size_type i = _size; i > pos; i-- )
            _alloc.construct( _data + i, _data[i - 1] );
        _alloc.construct( _data + pos, std::forward<Args>( args )... );
        _size++;
        return begin() + pos;
    };

    /**
     * @brief Inserts a new element at the end of the vector, right after its
     * current last element. This new element is constructed in place using args
     * as the arguments for its constructor.
     *
     * This effectively increases the container size by one, which causes an
     * automatic reallocation of the allocated storage space if -and only if-
     * the new vector size surpasses the current vector capacity.
     *
     * @tparam ...Args
     * @param ...args
     */
    template <class... Args>
    void emplace_back( Args &&...args )
    {
        if ( _size == _capacity )
            reserve( _capacity + 1 );
        _alloc.construct( _data + _size, std::forward<Args>( args )... );
        _size++;
    };

    // Allocator
    allocator_type get_allocator() const { return _alloc; };

    // Non-member function overloads
    friend bool operator==( const vector<T, Alloc> &lhs,
                            const vector<T, Alloc> &rhs )
    {
        if ( lhs.size() != rhs.size() )
            return false;
        for ( size_type i = 0; i < lhs.size(); i++ )
            if ( lhs[i] != rhs[i] )
                return false;
        return true;
    };

    friend bool operator!=( const vector<T, Alloc> &lhs,
                            const vector<T, Alloc> &rhs )
    {
        return !( lhs == rhs );
    }

    // TODO: implement lexicographical comparison
    friend bool operator<( const vector<T, Alloc> &lhs,
                           const vector<T, Alloc> &rhs );

    friend bool operator<=( const vector<T, Alloc> &lhs,
                            const vector<T, Alloc> &rhs );

    friend bool operator>( const vector<T, Alloc> &lhs,
                           const vector<T, Alloc> &rhs );

    friend bool operator>=( const vector<T, Alloc> &lhs,
                            const vector<T, Alloc> &rhs );

    friend void swap( vector<T, Alloc> &x, vector<T, Alloc> &y )
    {
        x.swap( y );
    };

protected:
    allocator_type _alloc;
    size_type      _size;
    size_type      _capacity;
    pointer        _data;
};

} // namespace ft

#endif // VECTOR_HPP
