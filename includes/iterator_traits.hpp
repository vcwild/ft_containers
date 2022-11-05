#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include <cstddef>

namespace ft {

template < typename T,
           typename Category,
           typename Distance  = ptrdiff_t,
           typename Pointer   = T *,
           typename Reference = T & >
struct iterator
{
    typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
    typedef Category  iterator_category;
};

template < typename Iterator >
struct iterator_traits
{
    typedef typename Iterator::value_type        value_type;
    typedef typename Iterator::difference_type   difference_type;
    typedef typename Iterator::pointer           pointer;
    typedef typename Iterator::reference         reference;
    typedef typename Iterator::iterator_category iterator_category;
};

template < typename T >
struct iterator_traits<T *>
{
    typedef T                               value_type;
    typedef ptrdiff_t                       difference_type;
    typedef T                              *pointer;
    typedef T                              &reference;
    typedef std::random_access_iterator_tag iterator_category;
};

template < typename T >
struct iterator_traits<const T *>
{
    typedef T                               value_type;
    typedef ptrdiff_t                       difference_type;
    typedef const T                        *pointer;
    typedef const T                        &reference;
    typedef std::random_access_iterator_tag iterator_category;
};

} // namespace ft

#endif // ITERATOR_TRAITS_HPP
