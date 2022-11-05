#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

#include <cstddef>

namespace ft {

template < typename T >
struct is_integral
{
    static const bool value = false;
};

template <>
struct is_integral<bool>
{
    static const bool value = true;
};

template <>
struct is_integral<char>
{
    static const bool value = true;
};

template <>
struct is_integral<signed char>
{
    static const bool value = true;
};

template <>
struct is_integral<unsigned char>
{
    static const bool value = true;
};

template <>
struct is_integral<wchar_t>
{
    static const bool value = true;
};

template <>
struct is_integral<short>
{
    static const bool value = true;
};

template <>
struct is_integral<unsigned short>
{
    static const bool value = true;
};

template <>
struct is_integral<int>
{
    static const bool value = true;
};

template <>
struct is_integral<unsigned int>
{
    static const bool value = true;
};

template <>
struct is_integral<long>
{
    static const bool value = true;
};

template <>
struct is_integral<unsigned long>
{
    static const bool value = true;
};

template <>
struct is_integral<long long>
{
    static const bool value = true;
};

template <>
struct is_integral<unsigned long long>
{
    static const bool value = true;
};

template < typename T >
struct is_floating_point
{
    static const bool value = false;
};

template <>
struct is_floating_point<float>
{
    static const bool value = true;
};

template <>
struct is_floating_point<double>
{
    static const bool value = true;
};

template <>
struct is_floating_point<long double>
{
    static const bool value = true;
};

template < typename T >
struct is_arithmetic
{
    static const bool value
        = is_integral<T>::value || is_floating_point<T>::value;
};

template < typename T >
struct is_pointer
{
    static const bool value = false;
};

template < typename T >
struct is_pointer<T *>
{
    static const bool value = true;
};

template < typename T >
struct is_reference
{
    static const bool value = false;
};

template < typename T >
struct is_reference<T &>
{
    static const bool value = true;
};

template < typename T >
struct is_const
{
    static const bool value = false;
};

template < typename T >
struct is_const<const T>
{
    static const bool value = true;
};

template < typename T >
struct is_volatile
{
    static const bool value = false;
};

template < typename T >
struct is_volatile<volatile T>
{
    static const bool value = true;
};

template < typename T >
struct is_pod
{
    static const bool value = is_arithmetic<T>::value || is_pointer<T>::value;
};

template < typename T >
struct is_scalar
{
    static const bool value
        = is_arithmetic<T>::value || is_pointer<T>::value || is_enum<T>::value;
};

template < typename T >
struct is_enum
{
    static const bool value = false;
};

template < typename T >
struct is_class
{
    static const bool value = false;
};

template < typename T >
struct is_union
{
    static const bool value = false;
};

template < typename T >
struct is_array
{
    static const bool value = false;
};

template < typename T >
struct is_function
{
    static const bool value = false;
};

template < typename T >
struct is_member_pointer
{
    static const bool value = false;
};

template < typename T >
struct is_member_object_pointer
{
    static const bool value = false;
};

template < typename T >
struct is_fundamental
{
    static const bool value = is_arithmetic<T>::value || is_void<T>::value;
};

template < typename T >
struct is_void
{
    static const bool value = false;
};

template <>
struct is_void<void>
{
    static const bool value = true;
};

template < typename T >
struct is_object
{
    static const bool value = !is_function<T>::value && !is_reference<T>::value
        && !is_void<T>::value;
};

template < typename T >
struct is_compound
{
    static const bool value = !is_fundamental<T>::value;
};

template < typename T >
struct is_member_function_pointer
{
    static const bool value = false;
};

template < typename T >
struct is_trivial
{
    static const bool value = is_pod<T>::value;
};

template < typename T >
struct is_trivially_copyable
{
    static const bool value = is_trivial<T>::value;
};

template < typename T >
struct is_standard_layout
{
    static const bool value = is_trivially_copyable<T>::value;
};

template < typename T >
struct is_empty
{
    static const bool value = false;
};

template < typename T >
struct is_polymorphic
{
    static const bool value = false;
};

template < typename T >
struct is_abstract
{
    static const bool value = false;
};

template < typename T >
struct is_signed
{
    static const bool value = is_integral<T>::value && T( -1 ) < T( 0 );
};

template < typename T >
struct is_unsigned
{
    static const bool value = is_integral<T>::value && T( -1 ) > T( 0 );
};

template < typename T >
struct is_bounded_array
{
    static const bool value = false;
};

template < typename T >
struct is_unbounded_array
{
    static const bool value = false;
};

template < typename T >
struct is_array
{
    static const bool value
        = is_bounded_array<T>::value || is_unbounded_array<T>::value;
};

template < typename T >
struct is_lvalue_reference
{
    static const bool value = false;
};

template < typename T >
struct is_lvalue_reference<T &>
{
    static const bool value = true;
};

template < typename T >
struct is_rvalue_reference
{
    static const bool value = false;
};

template < typename T >
struct is_rvalue_reference<T &&>
{
    static const bool value = true;
};

template < typename T >
struct is_reference
{
    static const bool value
        = is_lvalue_reference<T>::value || is_rvalue_reference<T>::value;
};

template < typename T >
struct is_lvalue_reference
{
    static const bool value = false;
};

template < typename T >
struct is_lvalue_reference<T &>
{
    static const bool value = true;
};

template < typename T >
struct is_reference
{
    static const bool value
        = is_lvalue_reference<T>::value || is_rvalue_reference<T>::value;
};

} // namespace ft

#endif // TYPE_TRAITS_HPP
