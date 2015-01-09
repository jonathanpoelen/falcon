#ifndef FALCON_IOSTREAMS_QUOTED_HPP
#define FALCON_IOSTREAMS_QUOTED_HPP

#include <falcon/iostreams/ostream_fill.hpp>

#include <ios>

namespace falcon {
namespace iostreams {

namespace aux_ {
template<class Str, class Ch>
struct quoted_proxy;
}

//  manipulator for const std::basic_string&
template <class Ch, class Tr, class Alloc>
aux_::quoted_proxy<std::basic_string<Ch, Tr, Alloc> const &, Ch>
quoted(const std::basic_string<Ch, Tr, Alloc> & s, Ch escape='\\', Ch delim='\"')
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

namespace aux_
{
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
    if (w > string.size()) {
      const bool left
        = ((os.flags() & std::ios_base::adjustfield) == std::ios_base::left);
      if (!left) {
        std::streamsize count_escape = 0;
        for (Ch const & c : string) {
          if (c == delim || c == escape) {
            ++count_escape;
          }
        }
        if (!ostream_fill(os, w - (count_escape + string.size()))
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

template <class Ch, class Tr, class Alloc>
std::basic_ostream<Ch, Tr> & operator<<(
  std::basic_ostream<Ch, Tr> & os
, quoted_proxy<std::basic_string<Ch, Tr, Alloc> const &, Ch> const & proxy)
{ return quoted_impl(os, proxy.string, proxy.escape, proxy.delim); }

template <class Ch, class Tr, class Alloc>
std::basic_ostream<Ch, Tr> & operator<<(
  std::basic_ostream<Ch, Tr> & os
, quoted_proxy<std::basic_string<Ch, Tr, Alloc> &, Ch> const & proxy)
{ return quoted_impl(os, proxy.string, proxy.escape, proxy.delim); }

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
std::basic_ostream<Ch, Tr> & operator<<(
  std::basic_ostream<Ch, Tr> & os
, quoted_proxy<const Ch*, Ch> const & proxy)
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
        for (Ch const * p = proxy.string; *p; ++p) {
          if (*p == proxy.delim || *p == proxy.escape) {
            ++count_escape;
          }
          ++sz;
        }
        if (!ostream_fill(os, w - (count_escape + sz + 2))
          || !safe_quoted_impl(
            *os.rdbuf(), proxy.string, proxy.escape, proxy.delim)
        ) {
          os.setstate(std::ios_base::badbit);
        }
      }
      else if (auto count_escape = safe_quoted_impl(
        *os.rdbuf(), proxy.string, proxy.escape, proxy.delim, 0
      )){
        ostream_fill(
          os, w - (count_escape + std::streamsize(Tr::length(proxy.string))));
      }
      else {
        os.setstate(std::ios_base::badbit);
      }
      os.width(0);
    }
    else if (!safe_quoted_impl(
      *os.rdbuf(), proxy.string, proxy.escape, proxy.delim)
    ) {
      os.setstate(std::ios_base::badbit);
    }
  }
  return os;
}

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
    Ch c;

    if (Tr::eq_int_type(cb, eof)) {
      is.setstate(std::ios_base::eofbit | std::ios_base::failbit);
      return is;
    }

    c = Tr::to_char_type(cb);
    if (c != proxy.delim) {
      return is >> proxy.string;
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

