#ifndef FALCON_STRING_CONCAT_HPP
#define FALCON_STRING_CONCAT_HPP

#if __cplusplus >= 201103L
# include <utility>
#endif
#include <falcon/string/append.hpp>
#include <falcon/c++/reference.hpp>
#include <falcon/c++/boost_or_std.hpp>

#include FALCON_BOOST_OR_STD_TRAITS(remove_cv)
#include FALCON_BOOST_OR_STD_TRAITS(remove_reference)

namespace falcon {

template<typename T>
struct string_type_helper_impl
{ typedef typename T::value_type type; };

template<typename T>
struct string_type_helper_impl<T*>
{ typedef T type; };

template<typename T, std::size_t N>
struct string_type_helper_impl<T[N]>
{ typedef T type; };

template<typename T>
struct string_type_helper
: string_type_helper_impl<
  typename FALCON_BOOST_OR_STD_NAMESPACE::remove_cv<
    typename FALCON_BOOST_OR_STD_NAMESPACE::remove_reference<T>::type
  >::type
> {};

template<typename T, typename U>
struct __dispatch_concat
{
  typedef std::basic_string<typename string_type_helper<T>::type> result_type;

  static result_type
  concat(const T & lhs, const U & rhs)
  { return lhs + rhs; }

  static result_type
  concat(T && lhs, const U & rhs)
  { return std::move(lhs) + rhs; }
};

template<typename CharT, typename Traits, typename Alloc, typename T>
struct __dispatch_concat<std::basic_string<CharT, Traits, Alloc>, T>
{
  typedef std::basic_string<CharT, Traits, Alloc> result_type;

  static result_type
  concat(const result_type & lhs, const T & rhs)
  { return lhs + rhs; }

  static result_type
  concat(result_type && lhs, const T & rhs)
  { return std::move(lhs) + rhs; }
};

template<typename CharT, typename Traits, typename Alloc, typename Traits2, typename Alloc2>
struct __dispatch_concat<std::basic_string<CharT, Traits, Alloc>
, std::basic_string<CharT, Traits2, Alloc2> >
{
  typedef std::basic_string<CharT, Traits, Alloc> result_type;
  static result_type
  concat(const result_type & lhs,
         const std::basic_string<CharT, Traits2, Alloc2> & rhs)
  {
    std::basic_string<CharT, Traits, Alloc> ret(lhs);
    ret.append(rhs.begin(), rhs.end());
    return ret;
  }

  static result_type
  concat(result_type && lhs,
         const std::basic_string<CharT, Traits2, Alloc2> & rhs)
  { return std::move(lhs.append(rhs.begin(), rhs.end())); }
};

template<typename T, typename U>
inline typename __dispatch_concat<T, U>::result_type
concat(const T & lhs, const U & rhs)
{ return __dispatch_concat<T, U>::concat(lhs, rhs); }

#if __cplusplus >= 201103L
template<typename T, typename U>
inline typename __dispatch_concat<typename std::remove_reference<T>::type, U>::result_type
concat(T && lhs, const U & rhs)
{ return __dispatch_concat<typename std::remove_reference<T>::type, U>::concat(std::move(lhs), rhs); }

template<typename CharT, typename Traits, typename Alloc, typename T, typename... Ts>
inline std::basic_string<CharT, Traits, Alloc>
concat(std::basic_string<CharT, Traits, Alloc>&& lhs, const T & rhs1, const Ts &... rhs2)
{
  std::basic_string<CharT, Traits, Alloc> ret(std::move(lhs));
  append(ret, rhs1, rhs2...);
  return ret;
}

template<typename T, typename U, typename... Ts>
inline std::basic_string<typename string_type_helper<T>::type>
concat(T&& lhs, const U & rhs1, const Ts &... rhs2)
{
  std::basic_string<typename string_type_helper<T>::type> ret;
  append(ret, lhs, rhs1, rhs2...);
  return ret;
}
#else
template<typename CharT, typename Traits, typename Alloc, typename T1, typename T2>
inline std::basic_string<CharT, Traits, Alloc>
concat(const std::basic_string<CharT, Traits, Alloc>& lhs,
       const T1& rhs1, const T2& rhs2)
{
  std::basic_string<CharT, Traits, Alloc> ret;
  append(ret, lhs, rhs1, rhs2);
  return ret;
}

template<typename T1, typename T2, typename T3>
inline std::basic_string<typename string_type_helper<T1>::type>
concat(const T1& rhs1, const T2& rhs2, const T3& rhs3)
{
  std::basic_string<typename string_type_helper<T>::type> ret;
  append(ret, rhs1, rhs2, rhs3);
  return ret;
}
#endif

}

#endif
