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


template<typename CharT, typename Traits, typename Alloc, typename T>
inline std::basic_string<CharT, Traits, Alloc>
concat(std::basic_string<CharT, Traits, Alloc> CPP_RVALUE_OR_CONST_REFERENCE lhs,
       T CPP_RVALUE_OR_CONST_REFERENCE rhs)
{ return lhs + rhs; }

template<typename T, typename U>
inline std::basic_string<typename string_type_helper<T>::type>
concat(T CPP_RVALUE_OR_CONST_REFERENCE lhs, U CPP_RVALUE_OR_CONST_REFERENCE rhs)
{ return lhs + rhs; }

#if __cplusplus >= 201103L
template<typename CharT, typename Traits, typename Alloc, typename T, typename... Ts>
inline std::basic_string<CharT, Traits, Alloc>
concat(std::basic_string<CharT, Traits, Alloc>&& lhs, T&& rhs1, Ts&&... rhs2)
{
  std::basic_string<CharT, Traits, Alloc> ret(std::move(lhs));
  append(ret, std::forward<T>(rhs1), std::forward<Ts>(rhs2)...);
  return ret;
}

template<typename T, typename U, typename... Ts>
inline std::basic_string<typename string_type_helper<T>::type>
concat(T&& lhs, U&& rhs1, Ts&&... rhs2)
{
  std::basic_string<typename string_type_helper<T>::type> ret;
  append(ret, std::forward<T>(lhs), std::forward<U>(rhs1), std::forward<Ts>(rhs2)...);
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
