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
template<class Str, class Ch, int Opt = 0>
struct quoted_proxy;

template<class Tag, int Opt, class Str, class... Ts>
struct extquoted_proxy;

class dynquoted_tag;
template<class Str, class Ch, class IsDelim, int Opt = 0>
using dynquoted_proxy = extquoted_proxy<dynquoted_tag, Opt, Str, Ch, IsDelim>;

class qquoted_tag;
template<class Str, class Ch, int Opt = 0>
using qquoted_proxy = extquoted_proxy<qquoted_tag, Opt, Str, Ch>;

class tquoted_tag;
template<class Str, class Policy>
using tquoted_proxy = extquoted_proxy<tquoted_tag, 0, Str, Policy>;

enum quoted_options {
  DEFAULT_QUOTED
, ALWAYS_QUOTED = 1 << 0
, DUPESC_QUOTED = 1 << 1
, UNIQUE_QUOTED = 1 << 2
, NOLEFT_QUOTED = 1 << 3
};

struct dynquoted_string {
  constexpr dynquoted_string() noexcept {}

  template<class Ch>
  constexpr bool operator()(Ch c) const noexcept
  { return c == Ch('\'') || c == Ch('"'); }
};

struct tquoted_policy
{
  constexpr tquoted_policy() noexcept {}

  static constexpr char escape() noexcept
  { return '\\'; }

  static constexpr bool always_quoted() noexcept
  { return false; }

  template<class Ch>
  static constexpr bool is_simple_delimiter(Ch c) noexcept
  { return c == Ch('\''); }

  template<class Ch>
  static constexpr bool is_interpret_delimiter(Ch c) noexcept
  { return c == Ch('"'); }

  template<class String, class Ch>
  static void simple_char(String & str, Ch c) noexcept
  { str += c; }

  template<class String, class Ch, class Buf>
  static void interpret_char(String & str, Ch c, Buf const &) noexcept
  {
    switch (c) {
      case 'n': str += '\n'; break;
      case 't': str += '\t'; break;
      case 'r': str += '\r'; break;
      default: str += Ch('\\'); str += c;
    }
  }

  struct validator
  {
    template<class Ch>
    constexpr bool operator()(Ch const &) const noexcept
    { return true; }
  };

  static validator simple_checker() noexcept
  { return {}; }

  static validator interpret_checker() noexcept
  { return {}; }
};

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

//  manipulator for const String with iofmts type
template <class String>
typename aux_::make_quoted_with_fmt<String>::type
quoted(
  String const & s
, typename aux_::make_quoted_with_fmt<String>::char_type escape='\\'
, typename aux_::make_quoted_with_fmt<String>::char_type delim='\"')
{ return {s, escape, delim}; }


///\brief  escape_string(s, delim) == quoted(s, delim, delim)
template<class T, class Ch>
auto escape_string(T & s, Ch delim='\"')
->decltype(quoted(s, delim, delim))
{ return quoted(s, delim, delim); }


///\brief  force the presence of \a escape
template<class Ch, class Tr, class Alloc>
aux_::quoted_proxy<std::basic_string<Ch, Tr, Alloc> &, Ch, aux_::ALWAYS_QUOTED>
aquoted(std::basic_string<Ch, Tr, Alloc> & s, Ch escape='\"', Ch delim='\"')
{ return {s, escape, delim}; }


/// \brief  the delimiter is ' or "
template<class Ch, class Tr, class Alloc>
aux_::dynquoted_proxy<
  std::basic_string<Ch, Tr, Alloc> &
, Ch, aux_::dynquoted_string>
squoted(std::basic_string<Ch, Tr, Alloc> & s, Ch escape='\\')
{ return {s, escape, aux_::dynquoted_string{}}; }


/// \brief  force the presence of delimiter ' or "
template<class Ch, class Tr, class Alloc>
aux_::dynquoted_proxy<
  std::basic_string<Ch, Tr, Alloc> &
, Ch, aux_::dynquoted_string, aux_::ALWAYS_QUOTED>
asquoted(std::basic_string<Ch, Tr, Alloc> & s, Ch escape='\\')
{ return {s, escape, aux_::dynquoted_string{}}; }


template<class Ch, class Tr, class Alloc, class IsDelim>
aux_::dynquoted_proxy<
  std::basic_string<Ch, Tr, Alloc> &
, Ch, IsDelim>
dquoted(std::basic_string<Ch, Tr, Alloc> & s, IsDelim is_delim, Ch escape='\\')
{ return {s, escape, is_delim}; }


///\brief  the stream is malformed if \a is_delim(c) not return false, true, 0 or 1
template<class Ch, class Tr, class Alloc, class IsDelim>
aux_::dynquoted_proxy<
  std::basic_string<Ch, Tr, Alloc> &
, Ch, IsDelim, aux_::ALWAYS_QUOTED>
adquoted(std::basic_string<Ch, Tr, Alloc> & s, IsDelim is_delim, Ch escape='\\')
{ return {s, escape, is_delim}; }


template<class Ch, class Tr, class Alloc>
aux_::qquoted_proxy<
  std::basic_string<Ch, Tr, Alloc> &
, Ch>
qquoted(std::basic_string<Ch, Tr, Alloc> & s, Ch left_delim, Ch right_delim)
{ return {s, left_delim, right_delim}; }


template<class Ch, class Tr, class Alloc>
aux_::qquoted_proxy<
  std::basic_string<Ch, Tr, Alloc> &
, Ch, (aux_::UNIQUE_QUOTED | aux_::NOLEFT_QUOTED)>
tag(std::basic_string<Ch, Tr, Alloc> & s, Ch left_delim, Ch right_delim)
{ return {s, left_delim, right_delim}; }


template<class Ch, class Tr, class Alloc>
aux_::qquoted_proxy<
  std::basic_string<Ch, Tr, Alloc> &
, Ch, aux_::UNIQUE_QUOTED>
qtag(std::basic_string<Ch, Tr, Alloc> & s, Ch left_delim, Ch right_delim)
{ return {s, left_delim, right_delim}; }


template<class Ch, class Tr, class Alloc, class Policy = aux_::tquoted_policy>
aux_::tquoted_proxy<
  std::basic_string<Ch, Tr, Alloc> &
, Policy>
tquoted(std::basic_string<Ch, Tr, Alloc> & s, Policy policy = Policy())
{ return {s, policy}; }


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


template <class Str, class Ch, int Opt>
struct quoted_proxy
{
  Str string;
  Ch  escape;
  Ch  delim;

  quoted_proxy& operator=(const quoted_proxy&) = delete;

  constexpr static int opt() { return Opt; }
};

template <int Opt, class Str, class Ch, class IsDelim>
struct extquoted_proxy<dynquoted_tag, Opt, Str, Ch, IsDelim>
{
  Str string;
  Ch  escape;
  IsDelim is_delim;

  extquoted_proxy& operator=(const extquoted_proxy&) = delete;

  constexpr static int opt() { return Opt; }
};

template <int Opt, class Str, class Ch>
struct extquoted_proxy<qquoted_tag, Opt, Str, Ch>
{
  Str string;
  Ch  left;
  Ch  right;

  extquoted_proxy& operator=(const extquoted_proxy&) = delete;

  constexpr static int opt() { return Opt; }
};

template <class Str, class Policy>
struct extquoted_proxy<tquoted_tag, 0, Str, Policy>
{
  Str string;
  Policy policy;

  extquoted_proxy& operator=(const extquoted_proxy&) = delete;

  constexpr static int opt() { return 0; }
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

struct escape_quoted_back_insert {
  template<class String, class Ch>
  void operator()(String & str, Ch c) const
  { str += c; }
};

using escape_quoted_validator = tquoted_policy::validator;

template <
  int opt, class Ch, class Tr, class String
, class BackInsert = escape_quoted_back_insert
, class IsValid = escape_quoted_validator>
std::basic_istream<Ch, Tr> &
escape_quoted_impl(
  std::basic_istream<Ch, Tr> & is
, std::basic_streambuf<Ch, Tr> & buf
, String & string
, Ch escape, Ch delim
, BackInsert back_insert = BackInsert(), IsValid is_valid = IsValid())
{
  typedef std::basic_istream<Ch, Tr>      istream_type;
  typedef typename istream_type::int_type int_type;

  constexpr auto eof = Tr::eof();

  for (;;)
  {
    int_type cb = buf.sbumpc();
    if (Tr::eq_int_type(cb, eof)) {
      is.setstate(std::ios_base::eofbit | std::ios_base::failbit);
      break;
    }

    Ch c = Tr::to_char_type(cb);
    if (c == escape) {
      cb = buf.sbumpc();
      if (Tr::eq_int_type(cb, eof)) {
        if (!(opt & DUPESC_QUOTED)) {
          is.setstate(std::ios_base::eofbit | std::ios_base::failbit);
        }
        break;
      }
      c = Tr::to_char_type(cb);
      if ((opt & DUPESC_QUOTED) && c != escape) {
        break;
      }
      back_insert(string, c);
      continue;
    }
    else if (!(opt & DUPESC_QUOTED) && c == delim) {
      break;
    }

    if (!is_valid(c)) {
      is.setstate(std::ios_base::eofbit | std::ios_base::failbit);
      break;
    }

    string += c;
  }

  return is;
}

template <int opt, class Ch, class Tr, class String>
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
    std::basic_streambuf<Ch, Tr> & buf = *is.rdbuf();

    {
      const int_type cb = buf.sgetc();

      if (Tr::eq_int_type(cb, Tr::eof())) {
        is.setstate(std::ios_base::eofbit | std::ios_base::failbit);
        return is;
      }

      const Ch c = Tr::to_char_type(cb);
      if ((opt & DUPESC_QUOTED) ? (c != escape) : (c != delim)) {
        if (opt & ALWAYS_QUOTED) {
          is.setstate(std::ios_base::eofbit | std::ios_base::failbit);
        }
        else {
          is >> string;
        }
        return is;
      }
    }

    buf.sbumpc();

    escape_quoted_impl<opt>(is, buf, string, escape, delim);
  }
  return is;
}


template <int opt, class Ch, class Tr, class String, class IsDelim>
std::basic_istream<Ch, Tr> & dynquoted_impl(
  std::basic_istream<Ch, Tr> & is
, String & string, Ch escape, IsDelim const & is_delim)
{
  typedef std::basic_istream<Ch, Tr>      istream_type;
  typedef typename istream_type::int_type int_type;

  string.clear();

  typename istream_type::sentry cerb(is);
  if (cerb) {
    std::basic_streambuf<Ch, Tr> & buf = *is.rdbuf();

    const int_type cb = buf.sgetc();

    if (Tr::eq_int_type(cb, Tr::eof())) {
      is.setstate(std::ios_base::eofbit | std::ios_base::failbit);
      return is;
    }

    const Ch c = Tr::to_char_type(cb);
    if (const auto res_delim = is_delim(c)) {
      if (c == escape) {
        if ((opt & DUPESC_QUOTED) || res_delim == 1) {
          buf.sbumpc();
          escape_quoted_impl<opt | DUPESC_QUOTED>(is, buf, string, escape, c);
        }
        else {
          is.setstate(std::ios_base::eofbit | std::ios_base::failbit);
        }
      }
      else {
        buf.sbumpc();
        escape_quoted_impl<opt>(is, buf, string, escape, c);
      }
    }
    else if (opt & ALWAYS_QUOTED) {
      is.setstate(std::ios_base::eofbit | std::ios_base::failbit);
    }
    else {
      is >> string;
    }
  }
  return is;
}


template <int opt, class Ch, class Tr, class String>
std::basic_istream<Ch, Tr> & qquoted_impl(
  std::basic_istream<Ch, Tr> & is
, String & string, Ch left, Ch right)
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
    if (c != left) {
        is.setstate(std::ios_base::eofbit | std::ios_base::failbit);
        return is;
    }

    buf.sbumpc();

    for (unsigned depth = 1;;)
    {
      cb = buf.sbumpc();
      if (Tr::eq_int_type(cb, eof)) {
        is.setstate(std::ios_base::eofbit | std::ios_base::failbit);
        break;
      }

      c = Tr::to_char_type(cb);
      if (c == right) {
        if ((opt & UNIQUE_QUOTED) || !--depth) {
          break;
        }
      }
      else if (!(opt & UNIQUE_QUOTED) && c == left) {
        ++depth;
      }
      else if ((opt & NOLEFT_QUOTED) && c == left) {
        is.setstate(std::ios_base::eofbit | std::ios_base::failbit);
        break;
      }

      string += c;
    }
  }
  return is;
}


template <class Ch, class Tr, class String, class Policy>
std::basic_istream<Ch, Tr> & tquoted_impl(
  std::basic_istream<Ch, Tr> & is
, String & string, Policy const & policy)
{
  typedef std::basic_istream<Ch, Tr>      istream_type;
  typedef typename istream_type::int_type int_type;

  string.clear();

  typename istream_type::sentry cerb(is);
  if (cerb) {
    std::basic_streambuf<Ch, Tr> & buf = *is.rdbuf();

    const int_type cb = buf.sgetc();

    if (Tr::eq_int_type(cb, Tr::eof())) {
      is.setstate(std::ios_base::eofbit | std::ios_base::failbit);
      return is;
    }

    const Ch escape(policy.escape());
    const Ch c = Tr::to_char_type(cb);
    if (policy.is_simple_delimiter(c)) {
      buf.sbumpc();
      auto inserter = [&policy](String & str, Ch c) {
        policy.simple_char(str, c);
      };
      if (c == escape) {
        escape_quoted_impl<DUPESC_QUOTED>(
          is, buf, string, escape, c, inserter, policy.simple_checker()
        );
      }
      else {
        escape_quoted_impl<0>(
          is, buf, string, escape, c, inserter, policy.simple_checker()
        );
      }
    }
    else if (policy.is_interpret_delimiter(c)) {
      buf.sbumpc();
      auto inserter = [&buf, &policy](String & str, Ch c) {
        policy.interpret_char(str, c, buf);
      };
      if (c == escape) {
        escape_quoted_impl<DUPESC_QUOTED>(
          is, buf, string, escape, c, inserter, policy.interpret_checker()
        );
      }
      else {
        escape_quoted_impl<0>(
          is, buf, string, escape, c, inserter, policy.interpret_checker()
        );
      }
    }
    else if (policy.always_quoted()) {
      is.setstate(std::ios_base::eofbit | std::ios_base::failbit);
    }
    else {
      is >> string;
    }
  }
  return is;
}


template<class Quoted>
struct quoted_fmt_proxy
{
  Quoted const & quoted;

  quoted_fmt_proxy& operator=(const quoted_fmt_proxy&) = delete;

  template<class Ch, class Tr, class T>
  void operator()(std::basic_ostream<Ch, Tr> & os, T const & x) const
  { quoted_impl(os, x, quoted.escape, quoted.delim); }

  template<class Ch, class Tr, class T>
  void operator()(std::basic_istream<Ch, Tr> & is, T & x) const
  {
    if ((Quoted::opt() & DUPESC_QUOTED) || quoted.delim == quoted.escape) {
      real_quoted_impl<Quoted::opt() | DUPESC_QUOTED>(
        is, x, quoted.escape, quoted.escape
      );
    }
    else {
      real_quoted_impl<Quoted::opt()>(is, x, quoted.escape, quoted.delim);
    }
  }
};

template<class Quoted>
quoted_fmt_proxy<Quoted>
make_quoted_fmt(Quoted const & quoted) noexcept
{ return {quoted}; }

template <class Str, class Ch, class Tr, int Opt>
std::basic_ostream<Ch, Tr> &
operator<<(
  std::basic_ostream<Ch, Tr> & os
, quoted_proxy<Str, Ch, Opt> const & proxy)
{ return apply_fmt_manipulator(make_quoted_fmt(proxy), os, proxy.string); }

template <class Str, class Ch, class Tr, int Opt>
std::basic_istream<Ch, Tr> &
operator>>(
  std::basic_istream<Ch, Tr> & is
, quoted_proxy<Str, Ch, Opt> const & proxy)
{ return apply_fmt_manipulator(make_quoted_fmt(proxy), is, proxy.string); }

template <class Ch, class Tr, class Tag, int Opt, class Str, class ... Ts>
std::basic_istream<Ch, Tr> &
operator>>(
  std::basic_istream<Ch, Tr> & is
, extquoted_proxy<Tag, Opt, Str, Ts...> const & proxy)
{ return apply_fmt_manipulator(make_quoted_fmt(proxy), is, proxy.string); }


template<class Quoted>
struct dynquoted_fmt_proxy
{
  Quoted const & quoted;

  dynquoted_fmt_proxy& operator=(const dynquoted_fmt_proxy&) = delete;

  template<class Ch, class Tr, class T>
  void operator()(std::basic_istream<Ch, Tr> & is, T & x) const
  { dynquoted_impl<Quoted::opt()>(is, x, quoted.escape, quoted.is_delim); }
};

template<class Str, class Ch, class IsDelim, int Opt>
dynquoted_fmt_proxy<dynquoted_proxy<Str, Ch, IsDelim, Opt>>
make_quoted_fmt(dynquoted_proxy<Str, Ch, IsDelim, Opt> const & quoted) noexcept
{ return {quoted}; }


template<class Quoted>
struct qquoted_fmt_proxy
{
  Quoted const & quoted;

  qquoted_fmt_proxy& operator=(const qquoted_fmt_proxy&) = delete;

  template<class Ch, class Tr, class T>
  void operator()(std::basic_istream<Ch, Tr> & is, T & x) const
  {
    if ((Quoted::opt() & UNIQUE_QUOTED) || quoted.left == quoted.right) {
      qquoted_impl<Quoted::opt() | UNIQUE_QUOTED>(
        is, x, quoted.left, quoted.right
      );
    }
    else {
      qquoted_impl<Quoted::opt()>(is, x, quoted.left, quoted.right);
    }
  }
};

template<int Opt, class Str, class Ch>
qquoted_fmt_proxy<qquoted_proxy<Str, Ch, Opt>>
make_quoted_fmt(qquoted_proxy<Str, Ch, Opt> const & quoted) noexcept
{ return {quoted}; }


template<class Quoted>
struct tquoted_fmt_proxy
{
  Quoted const & quoted;

  tquoted_fmt_proxy& operator=(const tquoted_fmt_proxy&) = delete;

  template<class Ch, class Tr, class T>
  void operator()(std::basic_istream<Ch, Tr> & is, T & x) const
  { tquoted_impl(is, x, quoted.policy); }
};

template<class Str, class Policy>
tquoted_fmt_proxy<tquoted_proxy<Str, Policy>>
make_quoted_fmt(tquoted_proxy<Str, Policy> const & quoted) noexcept
{ return {quoted}; }

} // aux_

}
}

#endif
