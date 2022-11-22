/*
 * Copyright 2022 ©️ vcwild under the GNU Affero General Public License v3.0.
 */
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
