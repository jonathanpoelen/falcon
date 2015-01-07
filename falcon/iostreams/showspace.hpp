#ifndef FALCON_IOSTREAM_SHOWSPACE_HPP
#define FALCON_IOSTREAM_SHOWSPACE_HPP

#include <falcon/iostreams/ostream_write.hpp>
#include <falcon/iostreams/ostream_fill.hpp>
#include <falcon/type_traits/is_string.hpp>
#include <falcon/type_traits/eval_if.hpp>
#include <falcon/type_traits/if.hpp>
#include <falcon/type_traits/use.hpp>
#include <falcon/c++/empty_class.hpp>

#include <cmath> // std:signbit
#include <limits>
#include <sstream>
#include <type_traits>

namespace falcon {
namespace iostreams {

namespace aux_ {

template<class T, class CharT = void>
struct showspace_t {
  T x_;
  CharT c_;

  template<class Traits>
  std::basic_ostream<CharT, Traits>&
  putc_(std::basic_ostream<CharT, Traits>& os) const
  { return os << c_; }

  template<class OStream>
  OStream& putc_(OStream & os) const
  { return os << typename OStream::char_type(c_); }
};

template<class T>
struct showspace_t<T, char> {
  T x_;
  char c_;

  template<class OStream>
  OStream& putc_(OStream & os) const
  { return os << os.widen(c_); }
};

template<class T>
struct showspace_t<T, void> {
  T x_;

  template<class OStream>
  OStream& putc_(OStream & os) const
  { return os << os.widen(' '); }
};

CPP_EMPTY_CLASS(char_showspace_tag);
CPP_EMPTY_CLASS(str_showspace_tag);
CPP_EMPTY_CLASS(signed_showspace_tag);
CPP_EMPTY_CLASS(unsigned_showspace_tag);
CPP_EMPTY_CLASS(unknow_showspace_tag);

template<class CharT, class Traits, class T, class S>
std::basic_ostream<CharT, Traits>&
showspace_impl(
  char_showspace_tag
, std::basic_ostream<CharT, Traits>& os
, T x, S const &)
{ return os << x; }

template<class CharT, class Traits, class T, class S>
std::basic_ostream<CharT, Traits>&
showspace_impl(
  str_showspace_tag
, std::basic_ostream<CharT, Traits>& os
, T const & x, S const & s
) {
  if (x.empty()) {
    return s.putc_(os);
  }
  return os << x;
}

template<class CharT, class Traits, class T, class S>
std::basic_ostream<CharT, Traits>&
showspace_impl(
  str_showspace_tag
, std::basic_ostream<CharT, Traits>& os
, T * x, S const & s
) {
  if (!*x) {
    return s.putc_(os);
  }
  return os << x;
}

template<class CharT, class Traits, class T, class S>
std::basic_ostream<CharT, Traits>&
showspace_with_fill(
  std::basic_ostream<CharT, Traits>& os
, T const & x, S const & s)
{
  constexpr auto buflen
  = std::is_same<T, bool>::value
  ? 5
  : ((std::numeric_limits<T>::digits10
      ? std::numeric_limits<T>::digits10
      : std::numeric_limits<int>::digits10
    )
    + (std::is_floating_point<T>::value ? 10 : 0)
    + 1
  );
  CharT buf[buflen];
  std::basic_ostringstream<CharT, Traits> oss;
  oss.rdbuf()->pubsetbuf(buf, buflen);
  oss.imbue(os.getloc());
  oss << x;

  auto sz = std::streamsize(oss.tellp());

  if (os.flags() & std::ios::left) {
    const std::streamsize w = os.width(0);
    s.putc_(os);

    if (sz <= decltype(sz)(buflen)) {
      ostream_write(os, buf, sz);
    }
    else {
      auto str = oss.str();
      sz = decltype(sz)(str.size());
      os << str;
    }

    if (sz < w - 1) {
      ostream_fill(os, w - 1 - sz, os.fill());
    }
  }
  else {
    os.width(os.width() - std::min(std::streamsize(sz), os.width()));
    s.putc_(os);

    if (sz <= decltype(sz)(buflen)) {
      ostream_write(os, buf, sz);
    }
    else {
      os << oss.str();
    }
  }

  return os;
}

template<class CharT, class Traits, class T, class S>
std::basic_ostream<CharT, Traits>&
showspace_impl(
  signed_showspace_tag
, std::basic_ostream<CharT, Traits>& os
, T const & x, S const & s
) {
  using std::signbit;
  if (!signbit(x)) {
    if (os.width()) {
      return showspace_with_fill(os, x, s);
    }
    s.putc_(os);
  }
  return os << x;
}

template<class CharT, class Traits, class T, class S>
std::basic_ostream<CharT, Traits>&
showspace_impl(
  unsigned_showspace_tag
, std::basic_ostream<CharT, Traits>& os
, T const & x, S const & s
) {
  if (os.width()) {
    return showspace_with_fill(os, x, s);
  }
  return s.putc_(os) << x;
}

template<class CharT, class Traits, class S>
std::basic_ostream<CharT, Traits>&
showspace_impl(
  unsigned_showspace_tag
, std::basic_ostream<CharT, Traits>& os
, bool x, S const & s
) {
  if (os.flags() & std::ios::boolalpha) {
    return os << x;
  }
  if (os.width()) {
    if (os.flags() & std::ios::left) {
      const std::streamsize w = os.width(0);
      s.putc_(os);
      os.width(w-1);
      return os << x;
    }
    os.width(os.width()-1);
  }
  return os << os.widen(' ') << x;
}

template<class CharT, class Traits, class T, class S>
std::basic_ostream<CharT, Traits>&
showspace_impl_unknow(
  std::false_type
, std::basic_ostream<CharT, Traits>& os
, T const & x, S const &)
// TODO
{ return os << x; }


#define MAKE_SHOWSPACE_IMPL_CAST(type, tag)    \
  template<class CharT, class Traits, class S> \
  void showspace_impl_cast(                    \
    std::basic_ostream<CharT, Traits>& os      \
  , type x, S const & s)                       \
  { showspace_impl(tag (), os, x, s); }

MAKE_SHOWSPACE_IMPL_CAST(bool, unsigned_showspace_tag)
MAKE_SHOWSPACE_IMPL_CAST(unsigned char, unsigned_showspace_tag)
MAKE_SHOWSPACE_IMPL_CAST(unsigned short, unsigned_showspace_tag)
MAKE_SHOWSPACE_IMPL_CAST(unsigned, unsigned_showspace_tag)
MAKE_SHOWSPACE_IMPL_CAST(unsigned long, unsigned_showspace_tag)
MAKE_SHOWSPACE_IMPL_CAST(unsigned long long, unsigned_showspace_tag)
MAKE_SHOWSPACE_IMPL_CAST(signed char, signed_showspace_tag)
MAKE_SHOWSPACE_IMPL_CAST(short, signed_showspace_tag)
MAKE_SHOWSPACE_IMPL_CAST(int, signed_showspace_tag)
MAKE_SHOWSPACE_IMPL_CAST(long, signed_showspace_tag)
MAKE_SHOWSPACE_IMPL_CAST(long long, signed_showspace_tag)
MAKE_SHOWSPACE_IMPL_CAST(float, signed_showspace_tag)
MAKE_SHOWSPACE_IMPL_CAST(double, signed_showspace_tag)
MAKE_SHOWSPACE_IMPL_CAST(long double, signed_showspace_tag)
MAKE_SHOWSPACE_IMPL_CAST(char const *, str_showspace_tag)
MAKE_SHOWSPACE_IMPL_CAST(volatile char const *, str_showspace_tag)

#undef MAKE_SHOWSPACE_IMPL_CAST

template<class CharT, class Traits, class S>
void showspace_impl_cast(
  std::basic_ostream<CharT, Traits>& os
, char x, S const &)
{ os << x; }

template<class Traits, class S>
void showspace_impl_cast(
  std::basic_ostream<char, Traits>& os
, unsigned char x, S const &)
{ os << x; }

template<class Traits, class S>
void showspace_impl_cast(
  std::basic_ostream<char, Traits>& os
, signed char x, S const &)
{ os << x; }

#define MAKE_SHOWSPACE_IMPL_CAST(type) \
template<class Traits, class S>        \
void showspace_impl_cast(              \
  std::basic_ostream<char, Traits>& os \
, type const * x, S const & s)         \
{ showspace_impl(str_showspace_tag(), os, x, s); }

MAKE_SHOWSPACE_IMPL_CAST(signed char)
MAKE_SHOWSPACE_IMPL_CAST(volatile signed char)
MAKE_SHOWSPACE_IMPL_CAST(unsigned char)
MAKE_SHOWSPACE_IMPL_CAST(volatile unsigned char)

#undef MAKE_SHOWSPACE_IMPL_CAST

template<class CharT, class Traits, class S>
void showspace_impl_cast(
  std::basic_ostream<CharT, Traits>& os
, CharT const * x, S const & s)
{ showspace_impl(str_showspace_tag(), os, x, s); }

template<class CharT, class Traits, class S>
void showspace_impl_cast(
  std::basic_ostream<CharT, Traits>& os
, volatile CharT const * x, S const & s)
{ showspace_impl(str_showspace_tag(), os, x, s); }


template<class CharT, class Traits, class T, class S>
std::basic_ostream<CharT, Traits>&
showspace_impl_unknow(
  std::true_type
, std::basic_ostream<CharT, Traits>& os
, T const & x, S const & s)
{
  showspace_impl_cast(os, x, s);
  return os;
}

template<class OStream, class T, class = OStream&>
struct showspace_ostream_is_overload
: std::is_convertible<T, bool>
{};

template<class OStream, class T>
struct showspace_ostream_is_overload<
  OStream, T
, decltype(operator<<(std::declval<OStream&>(), std::declval<T const &>()))
> : std::false_type
{};

template<class CharT, class Traits, class T, class S>
std::basic_ostream<CharT, Traits>&
showspace_impl(
  unknow_showspace_tag
, std::basic_ostream<CharT, Traits>& os
, T const & x, S const & s)
{ return showspace_impl_unknow(
  showspace_ostream_is_overload<decltype(os), T>()
, os, x, s); }

template<class CharT, class Traits, class T, class S>
std::basic_ostream<CharT, Traits>&
showspace_impl(
  unknow_showspace_tag
, std::basic_ostream<CharT, Traits>& os
, T * x, S const &)
{ return os << x; }

template<class CharT, class T>
eval_if_t<
  (std::is_same<CharT, T>::value || std::is_same<char, T>::value
  || (std::is_same<CharT, char>::value
    && (std::is_same<T, signed char>::value
     || std::is_same<T, unsigned char>::value)
   )
  )
, use<char_showspace_tag>
, eval_if_c<
    std::is_arithmetic<T>
  , if_c<std::is_signed<T>, signed_showspace_tag, unsigned_showspace_tag>
  , if_c<is_string<T>, str_showspace_tag, unknow_showspace_tag>
  >
>
showspace_impl_tag(T const &)
{ return {}; }

template<class CharT, class Traits, class T, class C>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, showspace_t<T, C> const & x)
{
  typedef typename std::remove_reference<T>::type remove_reference;
  if (std::is_integral<remove_reference>::value
   && std::is_signed<remove_reference>::value
   && (os.flags()
     & (std::ios_base::showpos | std::ios_base::hex | std::ios_base::oct)
  )) {
    return os << x.x_;
  }
  return showspace_impl(showspace_impl_tag<CharT>(x.x_), os, x.x_, x);
}

template<class CharT, class Traits, class T>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is, showspace_t<T> const & x)
{ return is >> std::forward<T>(x.x_); }

}

/// \brief A blank should be left before a positive number (or empty string) produced by a signed conversion.
template<class T>
auto showspace(T && x) noexcept
-> aux_::showspace_t<decltype(std::forward<T>(x))>
{ return {std::forward<T>(x)}; }

/// \brief A character \a c should be left before a positive number (or empty string) produced by a signed conversion.
template<class T, class CharT>
auto showspace(T && x, CharT c) noexcept
-> aux_::showspace_t<decltype(std::forward<T>(x)), CharT>
{ return {std::forward<T>(x), std::move(c)}; }

}
}

#endif
