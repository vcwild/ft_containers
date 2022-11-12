#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft {
/**
 * @brief The stack class is a container adapter that gives the programmer the
 * functionality of a stack - specifically, a FILO (first-in last-out) data
 * structure.
 *
 *
 * @tparam T The type of the elements contained in the stack.
 * @tparam Container The underlying container type. Defaults to vector<T>.
 */
template < class T, class Container = ft::vector<T> >
class stack {
public:
    typedef T                                        value_type;
    typedef Container                                container_type;
    typedef typename container_type::size_type       size_type;
    typedef typename container_type::reference       reference;
    typedef typename container_type::const_reference const_reference;

    // Constructors
    explicit stack( const container_type &ct = container_type() ) :
        _ct( ct ) {};

    // Destructor
    ~stack() {};

    // Member functions
    /**
     * @brief Returns whether the stack is empty: i.e. whether its size is zero.
     *
     * @return true if the container size is 0, false otherwise.
     */
    bool empty() const { return _ct.empty(); };

    /**
     * @brief Returns the number of elements in the stack.
     *
     * @return The number of elements in the container.
     */
    size_type size() const { return _ct.size(); };

    /**
     * @brief Returns a reference to the top element in the stack.
     *
     * @return A reference to the top element in the container.
     */
    reference top() { return _ct.back(); };

    /**
     * @brief Returns a reference to the top element in the stack.
     *
     * @return A reference to the top element in the container.
     */
    const_reference top() const { return _ct.back(); };

    /**
     * @brief Adds a new element at the top of the stack, above its current top
     * element. The content of this new element is initialized to a copy of val.
     *
     * @param val Value to which the inserted element is initialized.
     */
    void push( const value_type &val ) { _ct.push_back( val ); };

    /**
     * @brief Removes the element on top of the stack, effectively reducing its
     * size by one.
     */
    void pop() { _ct.pop_back(); };

    // Accessors
    /**
     * @brief Returns a reference to the underlying container object.
     *
     * @return container_type The underlying container object.
     */
    container_type ct() { return _ct; };

    /**
     * @brief Returns a reference to the underlying container object.
     *
     * @return container_type The underlying container object.
     */
    container_type ct() const { return _ct; };

protected:
    container_type _ct;
};

template < class T, class Container >
inline bool operator==( const stack<T, Container> &lhs,
                        const stack<T, Container> &rhs )
{
    return lhs.ct() == rhs.ct();
};

template < class T, class Container >
inline bool operator!=( const stack<T, Container> &lhs,
                        const stack<T, Container> &rhs )
{
    return lhs.ct() != rhs.ct();
};

template < class T, class Container >
inline bool operator<( const stack<T, Container> &lhs,
                       const stack<T, Container> &rhs )
{
    return lhs.ct() < rhs.ct();
};

template < class T, class Container >
inline bool operator<=( const stack<T, Container> &lhs,
                        const stack<T, Container> &rhs )
{
    return lhs.ct() <= rhs.ct();
};

template < class T, class Container >
inline bool operator>( const stack<T, Container> &lhs,
                       const stack<T, Container> &rhs )
{
    return lhs.ct() > rhs.ct();
};

template < class T, class Container >
inline bool operator>=( const stack<T, Container> &lhs,
                        const stack<T, Container> &rhs )
{
    return lhs.ct() >= rhs.ct();
};

} // namespace ft

#endif // STACK_HPP
