#ifndef FALCON_STRING_APPEND_HPP
#define FALCON_STRING_APPEND_HPP

#include <falcon/detail/string_size.hpp>

#if __cplusplus >= 201103L

#include <falcon/c++1x/unpack.hpp>

#include <cassert>
#include <utility>
#include <type_traits>
#include <initializer_list>

namespace falcon {

template<typename T>
std::size_t __verify_size(T const x)
{
  assert("x must be a positive integer" && x >= 0);
  return x;
}

template<typename T>
void __append(T& s, const T& other, unsigned& pos, const std::initializer_list<std::size_t>&)
{ s += other; ++pos; }

template<typename T, typename U>
void __append(T& s, U& other, unsigned& pos, const std::initializer_list<std::size_t>&)
///TODO use trait (append_trait< T,U>)
{ s += other.data(); ++pos; }

template<typename T, typename U>
void __append(T& s, const U * other, unsigned& pos,
              const std::initializer_list<std::size_t>& sz)
{ s.append(other, *(sz.begin() + pos++)); }

template<typename T, typename... Ts>
T& append(T& s, const Ts&... ss)
{
  std::size_t len_sum = 0;
  std::size_t len_amt;
  auto const len_max = s.max_size();
  std::initializer_list<std::size_t> sz {(
    len_amt = __verify_size(::falcon::detail::string_size<
      typename std::remove_reference<Ts>::type
    >::size(ss)),
    assert(len_max-len_sum >= len_amt),
    len_sum += len_amt,
    len_amt
  )...};
  s.reserve(len_sum);
  unsigned pos = 0;
  CPP1X_UNPACK(__append(s, ss, pos, sz));
  return s;
}

}

#else

namespace falcon {

template<typename T, typename U>
void __append(T& s, const U& other, std::size_t)
{ s += other; }

template<typename T, typename U>
void __append(T& s, const U * other, std::size_t size)
{ s.append(other, size); }

template<typename T, typename U>
inline T& append(T& lhs, const U& rhs)
{ return lhs += rhs; }

template<typename T, typename U1, typename U2>
inline T& append(T& lhs, const U1& rhs1, const U2& rhs2)
{
  std::size_t sz1 = ::falcon::detail::string_size::size(rhs1);
  std::size_t sz2 = ::falcon::detail::string_size::size(rhs2);
  lhs.reserve(sz1 + sz2);
  __append(lhs, rhs1, sz1);
  __append(lhs, rhs2, sz2);
  return lhs;
}

template<typename T, typename U1, typename U2, typename U3>
inline T& append(T& lhs, const U1& rhs1, const U2& rhs2, const U3& rhs3)
{
  std::size_t sz1 = ::falcon::detail::string_size::size(rhs1);
  std::size_t sz2 = ::falcon::detail::string_size::size(rhs2);
  std::size_t sz3 = ::falcon::detail::string_size::size(rhs3);
  lhs.reserve(sz1 + sz2 + sz3);
  __append(lhs, rhs1, sz1);
  __append(lhs, rhs2, sz2);
  __append(lhs, rhs3, sz3);
  return lhs;
}

}

#endif

#endif
