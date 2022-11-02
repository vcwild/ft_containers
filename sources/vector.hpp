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

    vector( const vector &rhs )
    {
        _alloc    = rhs._alloc;
        _size     = rhs._size;
        _capacity = rhs._capacity;
        _data     = _alloc.allocate( _capacity );
        for ( size_type i = 0; i < _size; i++ )
            _alloc.construct( _data + i, rhs._data[i] );
    };

    ~vector()
    {
        for ( size_type i = 0; i < _size; i++ )
            _alloc.destroy( _data + i );
        _alloc.deallocate( _data, _capacity );
    };

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

protected:
    allocator_type _alloc;
    size_type      _size;
    size_type      _capacity;
    pointer        _data;
};

} // namespace ft

#endif // VECTOR_HPP
