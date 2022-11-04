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
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef pointer                                  iterator;
    typedef const_pointer                            const_iterator;
    typedef std::reverse_iterator<iterator>          reverse_iterator;
    typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;

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

    reference       operator[]( size_type n ) { return _data[n]; };
    const_reference operator[]( size_type n ) const { return _data[n]; };

    difference_type operator-( const vector &x ) const
    {
        return ( _data - x._data );
    };

    // Accessors
    size_type size() const { return _size; };
    size_type capacity() const { return _capacity; };
    pointer   data() { return _data; };

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

protected:
    allocator_type _alloc;
    size_type      _size;
    size_type      _capacity;
    pointer        _data;
};

} // namespace ft

#endif // VECTOR_HPP
