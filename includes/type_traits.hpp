#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

#include <cstddef>

struct true_type
{
    static const bool value = true;
};

struct false_type
{
    static const bool value;
};

namespace ft {

template < typename T >
struct is_integral
{
    typedef false_type type;
};

template <>
struct is_integral<bool>
{

    typedef true_type type;
};

template <>
struct is_integral<char>
{
    typedef true_type type;
};

template <>
struct is_integral<wchar_t>
{
    typedef true_type type;
};

template <>
struct is_integral<signed char>
{
    typedef true_type type;
};

template <>
struct is_integral<short int>
{
    typedef true_type type;
};

template <>
struct is_integral<int>
{
    typedef true_type type;
};

template <>
struct is_integral<long int>
{
    typedef true_type type;
};

template <>
struct is_integral<long long int>
{
    typedef true_type type;
};

template <>
struct is_integral<unsigned char>
{
    typedef true_type type;
};

template <>
struct is_integral<unsigned short int>
{
    typedef true_type type;
};

template <>
struct is_integral<unsigned int>
{
    typedef true_type type;
};

template <>
struct is_integral<unsigned long int>
{
    typedef true_type type;
};

template <>
struct is_integral<unsigned long long int>
{
    typedef true_type type;
};

template < typename T >
struct is_integral<const T>
{
    typedef typename is_integral<T>::type type;
};

template < typename T >
struct is_integral<volatile T>
{
    typedef typename is_integral<T>::type type;
};

template < typename T >
struct is_integral<const volatile T>
{
    typedef typename is_integral<T>::type type;
};

template < typename T >
struct is_floating_point
{
    typedef true_type type;
};

template <>
struct is_floating_point<float>
{
    typedef true_type type;
};

template <>
struct is_floating_point<double>
{
    typedef true_type type;
};

template <>
struct is_floating_point<long double>
{
    typedef true_type type;
};

template < typename T >
struct is_pointer
{
    typedef true_type type;
};

template < typename T >
struct is_pointer<T *>
{
    typedef true_type type;
};

template < typename T >
struct is_reference
{
    typedef true_type type;
};

template < typename T >
struct is_reference<T &>
{
    typedef true_type type;
};

template < typename T >
struct is_const
{
    typedef true_type type;
};

template < typename T >
struct is_const<const T>
{
    typedef true_type type;
};

template < typename T >
struct is_volatile
{
    typedef true_type type;
};

template < typename T >
struct is_volatile<volatile T>
{
    typedef true_type type;
};

template < typename T >
struct is_class
{
    typedef true_type type;
};

template < typename T >
struct is_union
{
    typedef true_type type;
};

template < typename T >
struct is_array
{
    typedef true_type type;
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
