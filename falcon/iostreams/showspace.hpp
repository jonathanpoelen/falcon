#ifndef FALCON_IOSTREAM_SHOWSPACE_HPP
#define FALCON_IOSTREAM_SHOWSPACE_HPP

#include <falcon/iostreams/ostream_insert.hpp>
#include <falcon/iostreams/ostream_fill.hpp>
#include <falcon/type_traits/is_string.hpp>
#include <falcon/type_traits/eval_if.hpp>
#include <falcon/type_traits/if.hpp>
#include <falcon/c++/empty_class.hpp>

#include <ios>
#include <cmath>
#include <limits>
#include <sstream>
#include <type_traits>

namespace falcon {
namespace iostreams {

namespace aux_ {

template<class T>
struct showspace_t {
  T x_;
};

CPP_EMPTY_CLASS(str_showspace_tag);
CPP_EMPTY_CLASS(signed_showspace_tag);
CPP_EMPTY_CLASS(unsigned_showspace_tag);
CPP_EMPTY_CLASS(unknow_showspace_tag);

template<class CharT, class Traits, class T>
std::basic_ostream<CharT, Traits>&
showspace_impl(
  str_showspace_tag
, std::basic_ostream<CharT, Traits>& os
, T const & x
) {
  if (x.empty()) {
    return os << os.widen(' ');
  }
  return os << x;
}

template<class CharT, class Traits, class T>
std::basic_ostream<CharT, Traits>&
showspace_impl(
  str_showspace_tag
, std::basic_ostream<CharT, Traits>& os
, T * x
) {
  if (!*x) {
    return os << os.widen(' ');
  }
  return os << x;
}

template<class CharT, class Traits, class T>
std::basic_ostream<CharT, Traits>&
showspace_with_fill(std::basic_ostream<CharT, Traits>& os, T const & x)
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
    os << os.widen(' ');

    if (sz <= decltype(sz)(buflen)) {
      ostream_insert(os, buf, sz);
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
    os << os.widen(' ');

    if (sz <= decltype(sz)(buflen)) {
      ostream_insert(os, buf, sz);
    }
    else {
      os << oss.str();
    }
  }

  return os;
}

template<class CharT, class Traits, class T>
std::basic_ostream<CharT, Traits>&
showspace_impl(
  signed_showspace_tag
, std::basic_ostream<CharT, Traits>& os
, T const & x
) {
  using std::signbit;
  if (!signbit(x)) {
    if (os.width()) {
      return showspace_with_fill(os, x);
    }
    os << os.widen(' ');
  }
  return os << x;
}

template<class CharT, class Traits, class T>
std::basic_ostream<CharT, Traits>&
showspace_impl(
  unsigned_showspace_tag
, std::basic_ostream<CharT, Traits>& os
, T const & x
) {
  if (os.width()) {
    return showspace_with_fill(os, x);
  }
  return os << os.widen(' ') << x;
}

template<class CharT, class Traits, class T>
std::basic_ostream<CharT, Traits>&
showspace_impl(
  unknow_showspace_tag
, std::basic_ostream<CharT, Traits>& os
, T const & x
) {
  // TODO unimplemented (check a implicit cast)
  return os << x;
}

template<class T>
eval_if_c_t<
  std::is_arithmetic<T>
, if_c<std::is_signed<T>, signed_showspace_tag, unsigned_showspace_tag>
, if_c<is_string<T>, str_showspace_tag, unknow_showspace_tag>
>
showspace_impl_tag(T const &)
{ return {}; }

template<class CharT, class Traits, class T>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, showspace_t<T> const & x)
{
  typedef typename std::remove_reference<T>::type remove_reference;
  if (std::is_integral<remove_reference>::value
   && std::is_signed<remove_reference>::value
   && (os.flags()
     & (std::ios_base::showpos | std::ios_base::hex | std::ios_base::oct)
  )) {
    return os << x.x_;
  }
  return showspace_impl(showspace_impl_tag(x.x_), os, x.x_);
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

}
}

#endif
