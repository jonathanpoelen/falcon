#ifndef FALCON_IOSTREAMS_FMT_MANIPULATOR_HPP
#define FALCON_IOSTREAMS_FMT_MANIPULATOR_HPP

#include <falcon/type_traits/enable_template.hpp>
#include <falcon/type_traits/enable_type.hpp>
#include <falcon/type_traits/enable_if.hpp>
#include <falcon/type_traits/eval_if.hpp>
#include <falcon/type_traits/use.hpp>

#include <iosfwd>


namespace falcon {
namespace iostreams {

namespace aux_ {

template <class T, class = void>
struct is_fmt_manipulator_impl
: std::false_type
{};

template <class T>
struct is_fmt_manipulator_impl<T, enable_template2_t<T::template fmt_lock>>
: std::true_type
{};

template <class T>
struct is_fmt_manipulator_impl<T, enable_type_t<typename T::fmt_lock>>
: std::true_type
{};

}

template <class T>
struct is_fmt_manipulator
: aux_::is_fmt_manipulator_impl<T>
{};


template <class T>
struct fmt_manipulator_type;

namespace aux_ {
  template <class T, bool = is_fmt_manipulator<T>::value>
  struct fmt_manipulator_type_impl
  { using type = T; };

  template <class T>
  struct fmt_manipulator_type_impl<T, true>
  : fmt_manipulator_type_impl<
    typename std::decay<
      decltype(std::declval<T>().value())
    >::type
  >
  {};
}

template <class T>
struct fmt_manipulator_type
{ using type = typename aux_::fmt_manipulator_type_impl<T>::type; };

template <class T>
using fmt_manipulator_type_t = typename fmt_manipulator_type<T>::type;


template<class Proxy, class Ch, class Tr, class Manipulator>
enable_if_t<
  !is_fmt_manipulator<Manipulator>::value
, std::basic_ostream<Ch, Tr> &
>
apply_fmt_manipulator(
  Proxy const & proxy
, std::basic_ostream<Ch, Tr> & os
, Manipulator const & manipulator)
{
  proxy(os, manipulator);
  return os;
}

template<class Proxy, class Ch, class Tr, class Manipulator>
enable_if_t<
  !is_fmt_manipulator<Manipulator>::value
, std::basic_ostream<Ch, Tr> &
>
apply_fmt_manipulator(
  Proxy const & proxy
, std::basic_ostream<Ch, Tr> & os
, Manipulator & manipulator)
{
  proxy(os, manipulator);
  return os;
}

template<class Proxy, class Ch, class Tr, class Manipulator>
enable_if_t<
  !is_fmt_manipulator<Manipulator>::value
, std::basic_istream<Ch, Tr> &
>
apply_fmt_manipulator(
  Proxy const & proxy
, std::basic_istream<Ch, Tr> & is
, Manipulator const & manipulator)
{
  proxy(is, manipulator);
  return is;
}

template<class Proxy, class Ch, class Tr, class Manipulator>
enable_if_t<
  !is_fmt_manipulator<Manipulator>::value
, std::basic_istream<Ch, Tr> &
>
apply_fmt_manipulator(
  Proxy const & proxy
, std::basic_istream<Ch, Tr> & is
, Manipulator & manipulator)
{
  proxy(is, manipulator);
  return is;
}

namespace aux_ {

template <class T, class StreamOrCh, class Tr = void, class = void>
struct fmt_lock_impl;

template <class T, class Stream>
struct fmt_lock_impl<T, Stream, void, enable_template2_t<T::template fmt_lock>>
{ using lock_type = typename T::template fmt_lock<
  typename Stream::char_type
, typename Stream::traits_type>;
};

template <class T, class Stream>
struct fmt_lock_impl<T, Stream, void, enable_type_t<typename T::fmt_lock>>
{ using lock_type = typename T::fmt_lock; };

template <class T, class Ch, class Tr>
struct fmt_lock_impl<T, Ch, Tr, enable_template2_t<T::template fmt_lock>>
{ using lock_type = typename T::template fmt_lock<Ch, Tr>; };

template <class T, class Ch, class Tr>
struct fmt_lock_impl<T, Ch, Tr, enable_type_t<typename T::fmt_lock>>
{ using lock_type = typename T::fmt_lock; };

}

template<class Manipulator, class StreamOrCh, class Tr = void>
using fmt_lock = typename aux_::fmt_lock_impl<
  Manipulator, StreamOrCh, Tr
>::lock_type;

template<class Proxy, class Stream, class Manipulator>
enable_if_t<
  is_fmt_manipulator<Manipulator>::value
, Stream &
>
apply_fmt_manipulator(
  Proxy const & proxy
, Stream & stream
, Manipulator const & manipulator)
{
  fmt_lock<Manipulator, Stream> lock(stream, manipulator);
  return apply_fmt_manipulator(proxy, stream, manipulator.value());
}

template<class Proxy, class Stream, class Manipulator>
enable_if_t<
  is_fmt_manipulator<Manipulator>::value
, Stream &
>
apply_fmt_manipulator(
  Proxy const & proxy
, Stream & stream
, Manipulator & manipulator)
{
  fmt_lock<Manipulator, Stream> lock(stream, manipulator);
  return apply_fmt_manipulator(proxy, stream, manipulator.value());
}

}
}

#endif
