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

template <class Ch, class Tr, class String, class CountAdded = count_none>
std::streamsize safe_quoted_impl(
  std::basic_streambuf<Ch, Tr> & buf
, String const & string
, Ch escape, Ch delim
, CountAdded count_added = CountAdded{})
{
  constexpr auto eof = Tr::eof();

  if (buf.sputc(delim) == eof) {
    return 0;
  }

  {
    auto first = string.begin();
    auto last = string.end();
    for (; first != last; ++first) {
      if (*first == delim || *first == escape) {
        if (buf.sputc(escape) == eof) {
          return 0;
        }
        ++count_added;
      }
      if (buf.sputc(*first) == eof) {
        return 0;
      }
    }
  }

  if (buf.sputc(delim) == eof) {
    return 0;
  }

  return count_added + 2;
}


struct range_cstr_null_terminated {};

template<class Ch, class Tr>
struct range_cstr
{
  Ch const * str;

  Ch const * begin() const noexcept { return str; }

  range_cstr_null_terminated end() const noexcept { return {}; }

  std::size_t size() const noexcept
  { return Tr::length(str); }
};

template<class Ch>
bool operator!=(Ch const * p, range_cstr_null_terminated)
{ return *p; }


template <bool IsPtr, class Ch, class Tr, class String>
std::basic_ostream<Ch, Tr> & real_quoted_impl(
  std::basic_ostream<Ch, Tr> & os
, String const & string
, Ch escape, Ch delim)
{
  typename std::basic_ostream<Ch, Tr>::sentry cerb(os);
  if (cerb) {
    const std::streamsize w = IsPtr ? os.width() : os.width(0);
    if (w > (IsPtr ? 0 : std::streamsize(string.size()))) {
      const bool left
        = ((os.flags() & std::ios_base::adjustfield) == std::ios_base::left);
      if (!left) {
        std::streamsize sz = 2 + (IsPtr ? 0 : std::streamsize(string.size()));
        {
          auto first = string.begin();
          auto last = string.end();
          for (; first != last; ++first) {
            if (*first == delim || *first == escape) {
              ++sz;
            }
            if (IsPtr) {
              ++sz;
            }
          }
        }
        if (!ostream_fill(os, w - sz)
         || !safe_quoted_impl(*os.rdbuf(), string, escape, delim)) {
          os.setstate(std::ios_base::badbit);
        }
      }
      else if (std::streamsize count_escape = safe_quoted_impl(
        *os.rdbuf(), string, escape, delim, 0
      )){
        ostream_fill(
          os, w - (count_escape + std::streamsize(string.size())));
      }
      else {
        os.setstate(std::ios_base::badbit);
      }

      if (IsPtr) {
        os.width(0);
      }
    }
    else if (!safe_quoted_impl(*os.rdbuf(), string, escape, delim)) {
      os.setstate(std::ios_base::badbit);
    }
  }
  return os;
}


template <class Ch, class Tr, class Alloc>
std::basic_ostream<Ch, Tr> &
quoted_impl(
  std::basic_ostream<Ch, Tr> & os
, std::basic_string<Ch, Tr, Alloc> const & string
, Ch escape, Ch delim)
{ return real_quoted_impl<false>(os, string, escape, delim); }

template <class Ch, class Tr>
std::basic_ostream<Ch, Tr> &
quoted_impl(
  std::basic_ostream<Ch, Tr> & os
, Ch const * string
, Ch escape, Ch delim)
{ return real_quoted_impl<true>(
  os, range_cstr<Ch, Tr>{string}, escape, delim
); }


template <bool EscapeIsDelim, class Ch, class Tr, class String>
std::basic_istream<Ch, Tr> & real_quoted_impl(
  std::basic_istream<Ch, Tr> & is
, String & string
, Ch escape, Ch delim)
{
  typedef std::basic_istream<Ch, Tr>      istream_type;
  typedef typename istream_type::int_type int_type;

  string.clear();

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
    if (EscapeIsDelim ? (c != escape) : (c != delim)) {
      is >> string;
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
      if (c == escape) {
        cb = buf.sbumpc();
        if (Tr::eq_int_type(cb, eof)) {
          if (!EscapeIsDelim) {
            is.setstate(std::ios_base::eofbit | std::ios_base::failbit);
          }
          break;
        }
        c = Tr::to_char_type(cb);
        if (EscapeIsDelim && c != escape) {
          break;
        }
      }
      else if (!EscapeIsDelim && c == delim) {
        break;
      }

      string += c;
    }
  }

  return is;
}

template <class Ch, class Tr, class Alloc>
std::basic_istream<Ch, Tr> &
quoted_impl(
  std::basic_istream<Ch, Tr> & is
, std::basic_string<Ch, Tr, Alloc> & string
, Ch escape, Ch delim)
{
  if (delim == escape) {
    return real_quoted_impl<true>(is, string, escape, escape);
  }
  return real_quoted_impl<false>(is, string, escape, delim);
}


template<class Quoted>
struct quoted_fmt_proxy
{
  Quoted const & quoted;

  quoted_fmt_proxy& operator=(const quoted_fmt_proxy&) = delete;

  template<class Stream, class T>
  void operator()(Stream & stream, T & x) const
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
{ return apply_fmt_manipulator(make_quoted_fmt(proxy), is, proxy.string); }

} // aux_

}
}

#endif
