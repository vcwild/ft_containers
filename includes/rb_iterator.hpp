#ifndef RB_ITERATOR
#define RB_ITERATOR

#include "iterator_traits.hpp"
#include "rb_node.hpp"

using namespace ft;

namespace ft {

template < typename Iterator >
class rb_iterator : public iterator< bidirectional_iterator_tag, Iterator > {
public:
    typedef Iterator                                            iterator_type;
    typedef typename iterator_traits<Iterator>::value_type      value_type;
    typedef typename iterator_traits<Iterator>::pointer         pointer;
    typedef typename iterator_traits<Iterator>::reference       reference;
    typedef typename iterator_traits<Iterator>::difference_type difference_type;
    typedef rb_node<value_type>                                 node;
    typedef node                                               *node_pointer;

    // Constructors
    rb_iterator() : node( NULL ) {};

    explicit rb_iterator( node_pointer nptr ) : _node( nptr ) {};

    template < typename OtherIt >
    rb_iterator( const rb_iterator<OtherIt> &it ) : _node( it.base() ) {};

    // Destructor
    ~rb_iterator() {};

    // Operators
    template < typename OtherIt >
    rb_iterator &operator=( const rb_iterator< OtherIt > &it )
    {
        _node = it.base();
        return *this;
    };

    reference operator*() const { return _node->data; };

    rb_iterator operator++( int )
    {
        node_pointer tmp = _node;
        _node            = node::successor( _node );
        return rb_iterator( tmp );
    };

    rb_iterator &operator++()
    {
        _node = node::successor( _node );
        return *this;
    };

    rb_iterator operator--( int )
    {
        node_pointer tmp = _node;
        _node            = node::predecessor( _node );
        return rb_iterator( tmp );
    };

    rb_iterator &operator--()
    {
        _node = node::predecessor( _node );
        return *this;
    };

    pointer operator->() const { return &( operator*() ); };

    // Accessors
    node_pointer base() const { return _node; };

protected:
    node_pointer _node;
};

template < typename Iterator >
inline bool operator==( const rb_iterator< Iterator > &lhs,
                        const rb_iterator< Iterator > &rhs )
{
    return lhs.base() == rhs.base();
}

template < typename Iterator >
inline bool operator!=( const rb_iterator< Iterator > &lhs,
                        const rb_iterator< Iterator > &rhs )
{
    return lhs.base() != rhs.base();
}

template < typename It1, typename It2 >
inline bool operator==( const rb_iterator< It1 > &lhs,
                        const rb_iterator< It2 > &rhs )
{
    return lhs.base() == rhs.base();
}

template < typename It1, typename It2 >
inline bool operator!=( const rb_iterator< It1 > &lhs,
                        const rb_iterator< It2 > &rhs )
{
    return lhs.base() != rhs.base();
}

} // namespace ft

#endif // RB_ITERATOR
