#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

#include <cstddef>

struct true_type
{
};

struct false_type
{
};

namespace ft {

template < typename T >
struct is_integral
{
    enum { value = false };
    typedef false_type type;
};

template <>
struct is_integral<bool>
{
    enum { value = true };
    typedef true_type type;
};

template <>
struct is_integral<char>
{
    enum { value = true };
    typedef true_type type;
};

template <>
struct is_integral<wchar_t>
{
    enum { value = true };
    typedef true_type type;
};

template <>
struct is_integral<signed char>
{
    enum { value = true };
    typedef true_type type;
};

template <>
struct is_integral<short int>
{
    enum { value = true };
    typedef true_type type;
};

template <>
struct is_integral<int>
{
    enum { value = true };
    typedef true_type type;
};

template <>
struct is_integral<long int>
{
    enum { value = true };
    typedef true_type type;
};

template <>
struct is_integral<long long int>
{
    enum { value = true };
    typedef true_type type;
};

template <>
struct is_integral<unsigned char>
{
    enum { value = true };
    typedef true_type type;
};

template <>
struct is_integral<unsigned short int>
{
    enum { value = true };
    typedef true_type type;
};

template <>
struct is_integral<unsigned int>
{
    enum { value = true };
    typedef true_type type;
};

template <>
struct is_integral<unsigned long int>
{
    enum { value = true };
    typedef true_type type;
};

template <>
struct is_integral<unsigned long long int>
{
    enum { value = true };
    typedef true_type type;
};

template < typename T >
struct is_integral<const T>
{
    enum { value = is_integral<T>::value };
};

template < typename T >
struct is_integral<volatile T>
{
    enum { value = is_integral<T>::value };
};

template < typename T >
struct is_integral<const volatile T>
{
    enum { value = is_integral<T>::value };
};

template < typename T >
struct is_floating_point
{
    enum { value = false };
    typedef false_type type;
};

template <>
struct is_floating_point<float>
{
    enum { value = true };
    typedef true_type type;
};

template <>
struct is_floating_point<double>
{
    enum { value = false };
    typedef false_type type;
};

template <>
struct is_floating_point<long double>
{
    enum { value = false };
    typedef false_type type;
};

template < typename T >
struct is_pointer
{
    enum { value = false };
    typedef false_type type;
};

template < typename T >
struct is_pointer<T *>
{
    enum { value = true };
    typedef true_type type;
};

template < typename T >
struct is_reference
{
    enum { value = false };
    typedef false_type type;
};

template < typename T >
struct is_reference<T &>
{
    enum { value = true };
    typedef true_type type;
};

template < typename T >
struct is_const
{
    enum { value = false };
    typedef false_type type;
};

template < typename T >
struct is_const<const T>
{
    enum { value = true };
    typedef true_type type;
};

template < typename T >
struct is_volatile
{
    enum { value = false };
    typedef false_type type;
};

template < typename T >
struct is_volatile<volatile T>
{
    enum { value = true };
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

template < bool B, class T = void >
using enable_if_t = typename enable_if<B, T>::type;

} // namespace ft

#endif // TYPE_TRAITS_HPP
