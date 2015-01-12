#ifndef FALCON_IOSTREAMS_QUOTED_HPP
#define FALCON_IOSTREAMS_QUOTED_HPP

#include <falcon/type_traits/is_string.hpp>
#include <falcon/type_traits/enable_type.hpp>
#include <falcon/iostreams/ostream_fill.hpp>
#include <falcon/iostreams/fmt_manipulator.hpp>

#include <ios>

namespace falcon {
namespace iostreams {

namespace aux_ {
template<class Str, class Ch>
struct quoted_proxy;

template <class T, bool = is_fmt_manipulator<T>::value>
struct make_quoted_with_fmt {};
}

//  manipulator for const std::basic_string&
template <class Ch, class Tr, class Alloc>
aux_::quoted_proxy<std::basic_string<Ch, Tr, Alloc> const &, Ch>
quoted(std::basic_string<Ch, Tr, Alloc> const & s, Ch escape='\\', Ch delim='\"')
{ return {s, escape, delim}; }

//  manipulator for non-const std::basic_string&
template <class Ch, class Tr, class Alloc>
aux_::quoted_proxy<std::basic_string<Ch, Tr, Alloc> &, Ch>
quoted(std::basic_string<Ch, Tr, Alloc> & s, Ch escape='\\', Ch delim='\"')
{ return {s, escape, delim}; }

//  manipulator for const C-string*
template <class Ch>
aux_::quoted_proxy<Ch const *, Ch>
quoted(Ch const * s, Ch escape='\\', Ch delim='\"')
{ return {s, escape, delim}; }

template <class T>
typename aux_::make_quoted_with_fmt<T>::type
quoted(
  T const & s
, typename aux_::make_quoted_with_fmt<T>::char_type escape='\\'
, typename aux_::make_quoted_with_fmt<T>::char_type delim='\"')
{ return {s, escape, delim}; }


namespace aux_ {

template <class Ch, class Tr, class Alloc>
Ch quoted_char(std::basic_string<Ch, Tr, Alloc> const &);

template <class Ch, class Tr, class Alloc>
Ch quoted_char(std::basic_string<Ch, Tr, Alloc> &);

template <class Ch>
Ch quoted_char(Ch const *);

template <class T, class = void>
struct make_quoted_with_fmt_char
{};

template <class T>
struct make_quoted_with_fmt_char<
  T
, enable_type_t<decltype(quoted_char(std::declval<
    fmt_manipulator_type_t<T>
  >()))>
>
{
  using char_type = decltype(quoted_char(std::declval<
    fmt_manipulator_type_t<T>
  >()));
  using type = quoted_proxy<T, char_type>;
};

template <class T>
struct make_quoted_with_fmt<T, true>
: make_quoted_with_fmt_char<T>
{};


template <class Str, class Ch>
struct quoted_proxy
{
  Str string;
  Ch  escape;
  Ch  delim;

  quoted_proxy& operator=(const quoted_proxy&) = delete;
};

struct count_none {
  void operator = (int) {}
  void operator++() {}
  operator int () const noexcept { return 0; }
};

template <class Ch, class Tr, class Alloc, class CountAdded = count_none>
std::streamsize safe_quoted_impl(
  std::basic_streambuf<Ch, Tr> & buf
, std::basic_string<Ch, Tr, Alloc> const & string
, Ch escape, Ch delim
, CountAdded count_added = CountAdded{})
{
  constexpr auto eof = Tr::eof();

  if (buf.sputc(delim) == eof) {
    return 0;
  }

  for (Ch const & c : string) {
    if (c == delim || c == escape) {
      if (buf.sputc(escape) == eof) {
        return 0;
      }
      ++count_added;
    }
    if (buf.sputc(c) == eof) {
      return 0;
    }
  }

  if (buf.sputc(delim) == eof) {
    return 0;
  }

  return count_added + 2;
}

template <class Ch, class Tr, class Alloc>
std::basic_ostream<Ch, Tr> &
quoted_impl(
  std::basic_ostream<Ch, Tr> & os
, std::basic_string<Ch, Tr, Alloc> const & string
, Ch escape, Ch delim)
{
  typename std::basic_ostream<Ch, Tr>::sentry cerb(os);
  if (cerb) {
    const std::streamsize w = os.width();
    if (w > std::streamsize(string.size())) {
      const bool left
        = ((os.flags() & std::ios_base::adjustfield) == std::ios_base::left);
      if (!left) {
        std::streamsize count_escape = 0;
        for (Ch const & c : string) {
          if (c == delim || c == escape) {
            ++count_escape;
          }
        }
        if (!ostream_fill(
            os, w - (count_escape + std::streamsize(string.size()))
         )
         || !safe_quoted_impl(*os.rdbuf(), string, escape, delim)) {
          os.setstate(std::ios_base::badbit);
        }
      }
      else if (std::streamsize count_escape
        = safe_quoted_impl(*os.rdbuf(), string, escape, delim, 0)
      ){
        ostream_fill(os, w - (count_escape + std::streamsize(string.size())));
      }
      else {
        os.setstate(std::ios_base::badbit);
      }
    }
    else if (!safe_quoted_impl(*os.rdbuf(), string, escape, delim)) {
      os.setstate(std::ios_base::badbit);
    }
    os.width(0);
  }
  return os;
}


template <class Ch, class Tr, class CountAdded = count_none>
std::streamsize safe_quoted_impl(
  std::basic_streambuf<Ch, Tr> & buf
, Ch const * string
, Ch escape, Ch delim
, CountAdded count_added = CountAdded{})
{
  constexpr auto eof = Tr::eof();

  if (buf.sputc(delim) == eof) {
    return 0;
  }

  for (Ch const * p = string; *p; ++p) {
    if (*p == delim || *p == escape) {
      if (buf.sputc(escape) == eof) {
        return 0;
      }
      ++count_added;
    }
    if (buf.sputc(*p) == eof) {
      return 0;
    }
  }

  if (buf.sputc(delim) == eof) {
    return 0;
  }

  return count_added + 2;
}

template <class Ch, class Tr>
std::basic_ostream<Ch, Tr> & quoted_impl(
  std::basic_ostream<Ch, Tr> & os
, Ch const * string
, Ch escape, Ch delim)
{
  typename std::basic_ostream<Ch, Tr>::sentry cerb(os);
  if (cerb) {
    const std::streamsize w = os.width();
    if (w > 0) {
      const bool left
        = ((os.flags() & std::ios_base::adjustfield) == std::ios_base::left);
      if (!left) {
        std::streamsize count_escape = 0;
        std::streamsize sz = 0;
        for (Ch const * p = string; *p; ++p) {
          if (*p == delim || *p == escape) {
            ++count_escape;
          }
          ++sz;
        }
        if (!ostream_fill(os, w - (count_escape + sz + 2))
         || !safe_quoted_impl(*os.rdbuf(), string, escape, delim)) {
          os.setstate(std::ios_base::badbit);
        }
      }
      else if (auto count_escape = safe_quoted_impl(
        *os.rdbuf(), string, escape, delim, 0
      )){
        ostream_fill(
          os, w - (count_escape + std::streamsize(Tr::length(string))));
      }
      else {
        os.setstate(std::ios_base::badbit);
      }
      os.width(0);
    }
    else if (!safe_quoted_impl(*os.rdbuf(), string, escape, delim)) {
      os.setstate(std::ios_base::badbit);
    }
  }
  return os;
}


template<class Quoted>
struct quoted_fmt_proxy
{
  Quoted const & quoted;

  quoted_fmt_proxy& operator=(const quoted_fmt_proxy&) = delete;

  template<class Stream, class T>
  void operator()(Stream & stream, T const & x) const
  { quoted_impl(stream, x, quoted.escape, quoted.delim); }
};

template<class Quoted>
quoted_fmt_proxy<Quoted>
make_quoted_fmt(Quoted const & quoted) noexcept
{ return {quoted}; }

template <class Ch, class Tr, class T>
std::basic_ostream<Ch, Tr> & operator<<(
  std::basic_ostream<Ch, Tr> & os
, quoted_proxy<T, Ch> const & proxy)
{ return apply_fmt_manipulator(make_quoted_fmt(proxy), os, proxy.string); }


template <class Ch, class Tr, class Alloc>
std::basic_istream<Ch, Tr> &
operator>>(
  std::basic_istream<Ch, Tr> & is
, quoted_proxy<std::basic_string<Ch, Tr, Alloc> &, Ch> const & proxy)
{
  typedef std::basic_istream<Ch, Tr>      istream_type;
  typedef typename istream_type::int_type int_type;

  proxy.string.clear();

  typename istream_type::sentry cerb(is);
  if (cerb) {
    constexpr auto eof = Tr::eof();

    std::basic_streambuf<Ch, Tr> & buf = *is.rdbuf();

    int_type cb = buf.sgetc();

    if (Tr::eq_int_type(cb, eof)) {
      is.setstate(std::ios_base::eofbit | std::ios_base::failbit);
      return is;
    }

    Ch c = Tr::to_char_type(cb);
    if (c != proxy.delim) {
      is >> proxy.string;
      return is;
    }

    buf.sbumpc();

    for (;;)
    {
      cb = buf.sbumpc();
      if (Tr::eq_int_type(cb, eof)) {
        is.setstate(std::ios_base::eofbit | std::ios_base::failbit);
        break;
      }

      c = Tr::to_char_type(cb);
      if (c == proxy.escape) {
        cb = buf.sbumpc();
        if (Tr::eq_int_type(cb, eof)) {
          is.setstate(std::ios_base::eofbit | std::ios_base::failbit);
          break;
        }
        c = Tr::to_char_type(cb);
      }
      else if (c == proxy.delim) {
        break;
      }

      proxy.string += c;
    }
  }

  return is;
}

} // aux_

}
}

#endif
