#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

#include <cstddef>

namespace ft {

template < typename T >
struct is_integral
{
    static const bool type = false;
};

template <>
struct is_integral<bool>
{
    static const bool type = true;
};

template <>
struct is_integral<char>
{
    static const bool type = true;
};

template <>
struct is_integral<wchar_t>
{
    static const bool type = true;
};

template <>
struct is_integral<signed char>
{
    static const bool type = true;
};

template <>
struct is_integral<short int>
{
    static const bool type = true;
};

template <>
struct is_integral<int>
{
    static const bool type = true;
};

template <>
struct is_integral<long int>
{
    static const bool type = true;
};

template <>
struct is_integral<long long int>
{
    static const bool type = true;
};

template <>
struct is_integral<unsigned char>
{
    static const bool type = true;
};

template <>
struct is_integral<unsigned short int>
{
    static const bool type = true;
};

template <>
struct is_integral<unsigned int>
{
    static const bool type = true;
};

template <>
struct is_integral<unsigned long int>
{
    static const bool type = true;
};

template <>
struct is_integral<unsigned long long int>
{
    static const bool type = true;
};

template < typename T >
struct is_integral<const T>
{
    static const bool type = is_integral<T>::type;
};

template < typename T >
struct is_integral<volatile T>
{
    static const bool type = is_integral<T>::type;
};

template < typename T >
struct is_integral<const volatile T>
{
    static const bool type = is_integral<T>::type;
};

template < typename T >
struct is_floating_point
{
    static const bool type = false;
};

template <>
struct is_floating_point<float>
{
    static const bool type = true;
};

template <>
struct is_floating_point<double>
{
    static const bool type = true;
};

template <>
struct is_floating_point<long double>
{
    static const bool type = true;
};

template < typename T >
struct is_pointer
{
    static const bool type = false;
};

template < typename T >
struct is_pointer<T *>
{
    static const bool type = true;
};

template < typename T >
struct is_reference
{
    static const bool type = false;
};

template < typename T >
struct is_reference<T &>
{
    static const bool type = true;
};

template < typename T >
struct is_const
{
    static const bool type = false;
};

template < typename T >
struct is_const<const T>
{
    static const bool type = true;
};

template < typename T >
struct is_volatile
{
    static const bool type = false;
};

template < typename T >
struct is_volatile<volatile T>
{
    static const bool type = true;
};

template < typename T >
struct is_class
{
    static const bool type = false;
};

template < typename T >
struct is_union
{
    static const bool type = false;
};

template < typename T >
struct is_array
{
    static const bool type = false;
};

template < bool B, typename T = void >
struct enable_if
{
};

template < typename T >
struct enable_if< true, T >
{
    typedef T type;
};

} // namespace ft

#endif // TYPE_TRAITS_HPP
