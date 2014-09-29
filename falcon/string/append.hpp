#ifndef FALCON_STRING_APPEND_HPP
#define FALCON_STRING_APPEND_HPP

#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/boost_or_std.hpp>
#include <falcon/type_traits/is_character.hpp>
#include <iosfwd>

namespace falcon { namespace aux_ { namespace string {

template<typename T, bool = ::falcon::is_character<T>::value>
struct string_size
{
  typedef const T& reference;
  static std::size_t size(reference s)
  { return s.size(); }
};

template<typename T>
struct string_size<T*, false>
{
  typedef T * reference;
  static std::size_t size(const T * s)
  { return std::char_traits<T>::length(s); }
};

template<typename T>
struct string_size<const T*, false>
{
  typedef const T * reference;
  static std::size_t size(reference s)
  { return std::char_traits<T>::length(s); }
};

template<typename T, std::size_t N>
struct string_size<T[N], false>
: string_size<T*, false>
{
  typedef T (&reference)[N];
};

template<typename T>
struct string_size<T, true>
{
  typedef T reference;
  CPP_CONSTEXPR static std::size_t size(const T &)
  { return 1; }
};

} } }


#if __cplusplus >= 201103L

#include <falcon/utility/unpack.hpp>

#include <type_traits>
#include <initializer_list>

namespace falcon {

namespace aux_ { namespace string {

using list_size = std::initializer_list<std::size_t>;

template<typename T>
void append(T& s, const T& other, unsigned, const list_size &)
{ s += other; }

template<typename T, typename U>
typename std::enable_if< ::falcon::is_character<U>::value>::type
append(T& s, const U& c, unsigned, const list_size &)
{ s += c; }

template<typename T, typename U>
typename std::enable_if<!::falcon::is_character<U>::value>::type
append(T& s, const U& other, unsigned, const list_size &)
{ s.append(other.data(), other.size()); }

template<typename T, typename U>
void append(T& s, U * other, unsigned pos, const list_size & sz)
{ s.append(other, *(sz.begin() + pos)); }

template<typename T, typename U>
void append(T& s, const U * other, unsigned pos, const list_size & sz)
{ s.append(other, *(sz.begin() + pos)); }

} }

template<typename T, typename... Ts>
T& append(T& s, const Ts&... ss)
{
  std::size_t len_sum = 0;
  std::size_t len_amt;
  ::falcon::aux_::string::list_size sz {(
    len_amt = ::falcon::aux_::string::string_size<
      typename std::remove_reference<Ts>::type
    >::size(ss),
    len_sum += len_amt,
    len_amt
  )...};
  s.reserve(len_sum);
  unsigned pos = 0;
  FALCON_UNPACK(aux_::string::append(s, ss, pos, sz), ++pos);
  return s;
}

}

#else

namespace falcon {

namespace aux_ { namespace string {

template<typename T>
void append(T& s, const T& other, std::size_t)
{ s += other; }

template<typename T, typename U>
void append(T& s, const U& other, std::size_t)
{ s.append(other, size); }

template<typename T, typename U>
void append(T& s, U * other, std::size_t size)
{ s.append(other, size); }

template<typename T, typename U>
void append(T& s, const U * other, std::size_t size)
{ s.append(other, size); }

} }

template<typename T, typename U>
inline T& append(T& lhs, const U& rhs)
{ return lhs += rhs; }

template<typename T, typename U1, typename U2>
inline T& append(T& lhs, const U1& rhs1, const U2& rhs2)
{
  const std::size_t sz1 = ::falcon::aux_::string::string_size<U1>::size(rhs1);
  const std::size_t sz2 = ::falcon::aux_::string::string_size<U2>::size(rhs2);
  lhs.reserve(sz1 + sz2);
  append(lhs, rhs1, sz1);
  append(lhs, rhs2, sz2);
  return lhs;
}

template<typename T, typename U1, typename U2, typename U3>
inline T& append(T& lhs, const U1& rhs1, const U2& rhs2, const U3& rhs3)
{
  const std::size_t sz1 = ::falcon::aux_::string::string_size<U1>::size(rhs1);
  const std::size_t sz2 = ::falcon::aux_::string::string_size<U2>::size(rhs2);
  const std::size_t sz3 = ::falcon::aux_::string::string_size<U3>::size(rhs3);
  lhs.reserve(sz1 + sz2 + sz3);
  append(lhs, rhs1, sz1);
  append(lhs, rhs2, sz2);
  append(lhs, rhs3, sz3);
  return lhs;
}

}

#endif

#endif
