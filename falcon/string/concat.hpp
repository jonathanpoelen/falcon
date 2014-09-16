#ifndef FALCON_STRING_CONCAT_HPP
#define FALCON_STRING_CONCAT_HPP

#if __cplusplus >= 201103L
# include <utility>
#endif
#include <falcon/string/append.hpp>
#include <falcon/c++/reference.hpp>
#include <falcon/c++/boost_or_std.hpp>
#include <falcon/utility/move.hpp>

#include FALCON_BOOST_OR_STD_TRAITS(remove_cv)
#include FALCON_BOOST_OR_STD_TRAITS(remove_reference)

namespace falcon {

namespace aux_ { namespace string {

template<class T>
struct char_type_impl
{ typedef typename T::value_type type; };

template<class T>
struct char_type_impl<T*>
{ typedef T type; };

template<class T, std::size_t N>
struct char_type_impl<T[N]>
{ typedef T type; };

template<class T>
struct char_type
: char_type_impl<
  typename FALCON_BOOST_OR_STD_NAMESPACE::remove_cv<
    typename FALCON_BOOST_OR_STD_NAMESPACE::remove_reference<T>::type
  >::type
> {};

template<class T, class U>
struct dispatch_concat
{
  typedef std::basic_string<typename char_type<T>::type> result_type;

  static result_type
  concat(T CPP_RVALUE_OR_CONST_REFERENCE lhs, const U & rhs)
  { return FALCON_MOVE(lhs) + rhs; }
};

template<class CharT, class Traits, class Alloc, class T>
struct dispatch_concat<std::basic_string<CharT, Traits, Alloc>, T>
{
  typedef std::basic_string<CharT, Traits, Alloc> result_type;

  static result_type
  concat(result_type CPP_RVALUE_OR_CONST_REFERENCE lhs, const T & rhs)
  { return FALCON_MOVE(lhs) + rhs; }
};

template<class CharT, class Traits, class Alloc, class Traits2, class Alloc2>
struct dispatch_concat<std::basic_string<CharT, Traits, Alloc>
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

# if __cplusplus >= 201103L
  static result_type
  concat(result_type && lhs,
         const std::basic_string<CharT, Traits2, Alloc2> & rhs)
  { return std::move(lhs.append(rhs.begin(), rhs.end())); }
# endif
};

} }

template<class T, class U>
inline typename aux_::string::dispatch_concat<T, U>::result_type
concat(const T & lhs, const U & rhs)
{ return aux_::string::dispatch_concat<T, U>::concat(lhs, rhs); }

#if __cplusplus >= 201103L
template<class T, class U>
inline typename aux_::string::dispatch_concat<typename std::remove_reference<T>::type, U>::result_type
concat(T && lhs, const U & rhs)
{ return aux_::string::dispatch_concat<typename std::remove_reference<T>::type, U>::concat(std::move(lhs), rhs); }

template<class CharT, class Traits, class Alloc, class T, class... Ts>
inline std::basic_string<CharT, Traits, Alloc>
concat(std::basic_string<CharT, Traits, Alloc>&& lhs, const T & rhs1, const Ts &... rhs2)
{
  std::basic_string<CharT, Traits, Alloc> ret(std::move(lhs));
  append(ret, rhs1, rhs2...);
  return ret;
}

template<class T, class U, class... Ts>
inline std::basic_string<typename aux_::string::char_type<T>::type>
concat(T&& lhs, const U & rhs1, const Ts &... rhs2)
{
  std::basic_string<typename aux_::string::char_type<T>::type> ret;
  append(ret, lhs, rhs1, rhs2...);
  return ret;
}
#else
template<class CharT, class Traits, class Alloc, class T1, class T2>
inline std::basic_string<CharT, Traits, Alloc>
concat(const std::basic_string<CharT, Traits, Alloc>& lhs,
       const T1& rhs1, const T2& rhs2)
{
  std::basic_string<CharT, Traits, Alloc> ret;
  append(ret, lhs, rhs1, rhs2);
  return ret;
}

template<class T1, class T2, class T3>
inline std::basic_string<typename aux_::string::char_type<T1>::type>
concat(const T1& rhs1, const T2& rhs2, const T3& rhs3)
{
  std::basic_string<typename aux_::string::char_type<T>::type> ret;
  append(ret, rhs1, rhs2, rhs3);
  return ret;
}
#endif

}

#endif
