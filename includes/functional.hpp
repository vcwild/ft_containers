#ifndef FUNCTIONAL_HPP
#define FUNCTIONAL_HPP

namespace ft {

template <typename T>
struct less
{
    bool operator()( const T &lhs, const T &rhs ) const { return lhs < rhs; };
};

} // namespace ft

#endif // FUNCTIONAL_HPP
