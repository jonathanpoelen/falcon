#ifndef FALCON_IOSTREAMS_QUOTED_HPP
#define FALCON_IOSTREAMS_QUOTED_HPP

#include <falcon/type_traits/enable_type.hpp>
#include <falcon/iostreams/ostream_fill.hpp>
#include <falcon/iostreams/fmt_manipulator.hpp>
#include <falcon/functional/to_compile_time_expression.hpp>

#include <ios>

namespace falcon {
namespace iostreams {

namespace aux_ {
template<class Str, class Ch>
struct quoted_proxy;

enum class escape_mode { unspecified, simple, interpret };

template<class Str, class Policy, escape_mode Mode = escape_mode::unspecified>
struct pquoted_proxy;

template<class Str, class Policy>
using pescaped_proxy = pquoted_proxy<Str, Policy, escape_mode::simple>;

template<class Str, class Policy>
using ipescaped_proxy = pquoted_proxy<Str, Policy, escape_mode::interpret>;

template <class T, bool = is_fmt_manipulator<T>::value>
struct make_quoted_with_fmt {};
}

namespace quoted_policies {

struct quoted_error {
  static const unsigned good                 = 0;
  static const unsigned delimiter            = 1 << 0;
  static const unsigned left_presence        = 1 << 1;
  static const unsigned invalid_character    = 1 << 2;
  static const unsigned escape_is_ambiguous  = 1 << 3;
  static const unsigned eof                  = 1 << 4;

  quoted_error(unsigned mask = good) noexcept
  : m_(mask)
  {}

  /// `const &` : disable warning on gcc (-Wconversion)
  operator unsigned const & () const noexcept
  { return m_; }

  operator unsigned & () noexcept
  { return m_; }

private:
  unsigned m_;
};

template<class Ch, class Trait, class Buf>
bool default_extended_escaped_puch_back(
  std::basic_string<Ch, Trait> & str, Ch c, Buf const &
) {
  switch (c) {
    case 'n': str += '\n'; break;
    case 't': str += '\t'; break;
    case 'r': str += '\r'; break;
    default: return false;
  }
  return true;
}

namespace aux_ {
  template<class Policy>
  struct normal_policy_base
  {
    using normal_policy = std::true_type;

    Policy const & get_normal_policy() const noexcept
    { return policy_; }

    Policy policy_;
  };

  template<class Policy>
  struct extended_policy_base
  {
    using extended_policy = std::true_type;

    Policy const & get_extended_policy() const noexcept
    { return policy_; }

    Policy policy_;
  };

  template<class Policy>
  struct long_policy_base
  {
    using long_policy = std::true_type;

    Policy const & get_long_policy() const noexcept
    { return policy_; }

    Policy policy_;
  };

  template<class Policy>
  struct long_extended_policy_base
  {
    using long_extended_policy = std::true_type;

    Policy const & get_long_extended_policy() const noexcept
    { return policy_; }

    Policy policy_;
  };

  struct void_policy_base {};

  template<template<class> class CRTPBase, class Policy>
  using to_base = typename std::conditional<
    std::is_void<Policy>::value
  , void_policy_base
  , CRTPBase<Policy>
  >::type;
}

template<
  class Normal = void
, class Extended = void
, class LongNormal = void
, class LongExtended = void
, bool AlWaysQuoted = false>
struct quoted_policy
: aux_::to_base<aux_::normal_policy_base, Normal>
, aux_::to_base<aux_::extended_policy_base, Extended>
, aux_::to_base<aux_::long_policy_base, LongNormal>
, aux_::to_base<aux_::long_extended_policy_base, LongExtended>
{
private:
  using normal_base_ = aux_::to_base<aux_::normal_policy_base, Normal>;
  using extended_base_ = aux_::to_base<aux_::extended_policy_base, Extended>;
  using long_base_
    = aux_::to_base<aux_::long_policy_base, LongNormal>;
  using long_extended_base_
    = aux_::to_base<aux_::long_extended_policy_base, LongExtended>;

public:
  constexpr quoted_policy(
    normal_base_ normal_quoted
  , extended_base_ extended_quoted
  , long_base_ long_quoted
  , long_extended_base_ long_extended_quoted)
  : normal_base_{std::move(normal_quoted)}
  , extended_base_{std::move(extended_quoted)}
  , long_base_{std::move(long_quoted)}
  , long_extended_base_{std::move(long_extended_quoted)}
  {}

  // does nothing
  void set_error(quoted_error) const noexcept
  {}

  static constexpr bool always_quoted() noexcept
  { return AlWaysQuoted; }
};


template<class Ch>
struct quoted_param3
{
  using char_type = Ch;

  constexpr quoted_param3(Ch left, Ch right, Ch escape = Ch{}) noexcept
  : left_(left)
  , right_(right)
  , escape_(escape)
  {}

  constexpr Ch escape() const noexcept
  { return escape_; }

  constexpr bool is_right(Ch c) const noexcept
  { return c == right_; }

  constexpr bool is_left(Ch c) const noexcept
  { return c == left_; }

private:
  Ch left_;
  Ch right_;
  Ch escape_;
};


template<class Ch>
struct quoted_param
{
  using char_type = Ch;

  constexpr quoted_param(Ch delim, Ch escape = '\\') noexcept
  : delim_(delim)
  , escape_(escape)
  {}

  constexpr Ch escape() const noexcept
  { return escape_; }

  constexpr bool is_right(Ch c) const noexcept
  { return c == delim_; }

  constexpr bool is_left(Ch c) const noexcept
  { return c == delim_; }

private:
  Ch delim_;
  Ch escape_;
};


template<class Ch>
struct tag_param
{
  using char_type = Ch;

  constexpr tag_param(Ch left, Ch right) noexcept
  : left_(left)
  , right_(right)
  {}

  constexpr Ch escape() const noexcept
  { return Ch{}; }

  constexpr bool is_right(Ch c) const noexcept
  { return c == right_; }

  constexpr bool is_left(Ch c) const noexcept
  { return c == left_; }

private:
  Ch left_;
  Ch right_;
};


struct quote_fn
{
  constexpr quote_fn() noexcept {}

  template<class Ch>
  constexpr bool operator()(Ch c) const noexcept
  { return c == '"' || c == '\''; }
};

template<class IsDelim, class Ch = char>
struct is_delimeter_quoted_param
{
  using char_type = Ch;

  constexpr is_delimeter_quoted_param(
    IsDelim is_delim, Ch escape = '\\'
  ) noexcept
  : is_delim_(is_delim)
  , escape_(escape)
  {}

  constexpr is_delimeter_quoted_param(Ch escape = '\\') noexcept
  : escape_(escape)
  {}

  constexpr Ch escape() const noexcept
  { return escape_; }

  template<class Ch_>
  constexpr bool is_right(Ch_ c) const noexcept
  { return is_delim_(c); }

  template<class Ch_>
  constexpr bool is_left(Ch_ c) const noexcept
  { return is_delim_(c); }

private:
  IsDelim is_delim_;
  Ch escape_;
};


template<class Param>
struct default_quoted_policy_base
: Param
{
  using Param::Param;

  constexpr bool can_be_escaped() const noexcept
  { return this->escape() == typename Param::char_type{}; }

  static constexpr bool delimiter_can_be_escape() noexcept
  { return false; }

  static constexpr bool with_depth() noexcept
  { return true; }

  static constexpr bool with_left() noexcept
  { return true; }

  static constexpr bool keep_escape() noexcept
  { return true; }

  template<class String, class Ch, class Buf>
  static bool push_back(String & str, Ch c, Buf const &)
  {
    str += c;
    return true;
  }

  template<class Ch>
  static constexpr bool is_valid(Ch const &) noexcept
  { return true; }

  // does nothing
  void set_error(quoted_error) const noexcept
  {}
};


template<class Param>
struct normal_quoted_policy_base
: default_quoted_policy_base<Param>
{
  using default_quoted_policy_base<Param>::default_quoted_policy_base;

  static constexpr bool can_be_escaped() noexcept
  { return true; }

  static constexpr bool delimiter_can_be_escape() noexcept
  { return true; }

  static constexpr bool with_depth() noexcept
  { return false; }

  static constexpr bool with_left() noexcept
  { return true; }

  static constexpr bool keep_escape() noexcept
  { return false; }
};


#define USING_POLICY_COPY_CTOR(class_name, inherit, policy_name) \
  class_name(policy_name const & policy) : inherit(policy) {}    \
  class_name(policy_name && policy) : inherit(std::move(policy)) {}

#define USING_POLICY_CTOR(class_name)                \
  USING_POLICY_COPY_CTOR(class_name, Policy, Policy) \
  using Policy::Policy


template<class Policy, bool WithDepth = true>
struct with_depth_policy
: Policy
{
  USING_POLICY_CTOR(with_depth_policy);

  static constexpr bool with_depth() noexcept
  { return WithDepth; }
};


template<class Policy, bool WithDepth = true>
using nodepth_policy = with_depth_policy<Policy, !WithDepth>;


template<class Policy, bool Can = true>
struct can_be_escaped_policy
: Policy
{
  USING_POLICY_CTOR(can_be_escaped_policy);

  static constexpr bool can_be_escaped() noexcept
  { return Can; }
};


template<class Policy, bool Can = true>
using cannot_be_escape_policy
  = can_be_escaped_policy<Policy, !Can>;


template<class Policy, bool WithLeft = true>
struct with_left_policy
: Policy
{
  USING_POLICY_CTOR(with_left_policy);

  static constexpr bool with_left() noexcept
  { return WithLeft; }
};

template<class Policy, bool WithLeft = true>
using noleft_policy = with_left_policy<Policy, !WithLeft>;


template<class Policy>
struct push_back_return_always_true_policy
: Policy
{
  USING_POLICY_CTOR(push_back_return_always_true_policy);

  template<class String, class Ch, class Buf>
  bool interpret_push_back(String & str, Ch c, Buf const & buf) const
  {
    Policy::policy(str, c, buf);
    return true;
  }
};


template<class Policy, bool Keep = true>
struct keep_escape_policy
: Policy
{
  USING_POLICY_CTOR(keep_escape_policy);

  static constexpr bool keep_escape() noexcept
  { return Keep; }
};

template<class Policy, bool Keep = true>
using nokeep_escape_policy = keep_escape_policy<Policy, !Keep>;


template<class Policy, bool Always = true>
struct always_quoted_policy
: Policy
{
  USING_POLICY_CTOR(always_quoted_policy);

  static constexpr bool always_quoted() noexcept
  { return Always; }
};

template<class Policy, bool Optional = true>
using optional_quoted_policy = always_quoted_policy<Policy, !Optional>;


template<class Policy, bool Can = true>
struct delimiter_can_be_escape_policy
: Policy
{
  USING_POLICY_CTOR(delimiter_can_be_escape_policy);

  static constexpr bool delimiter_can_be_escape() noexcept
  { return Can; }
};

template<class Policy, bool Can = true>
using delimiter_cannot_be_escape_policy
  = delimiter_can_be_escape_policy<Policy, !Can>;


template<class Policy>
struct normal_quoted_policy
{
  using normal_policy = std::true_type;

  Policy const & get_normal_policy() const noexcept
  { return policy_; }

  // does nothing
  void set_error(quoted_error) const noexcept
  {}

  Policy policy_;
};

template<class Policy>
struct extended_quoted_policy
{
  using extended_policy = std::true_type;

  Policy const & get_extended_policy() const noexcept
  { return policy_; }

  Policy policy_;
};

template<class NormalPolicy, class ExtendedPolicy>
struct normal_and_extended_quoted_policy
{
  using normal_policy = std::true_type;
  using extended_policy = std::true_type;

  NormalPolicy const & get_normal_policy() const noexcept
  { return normal_policy_; }

  ExtendedPolicy const & get_extended_policy() const noexcept
  { return extended_policy_; }

  NormalPolicy normal_policy_;
  ExtendedPolicy extended_policy_;
};

template<class Policy>
struct long_quoted_policy
{
  using long_policy = std::true_type;

  Policy const & get_long_policy() const noexcept
  { return policy_; }

  Policy policy_;
};

template<class Policy>
struct long_extended_quoted_policy
{
  using long_extended_policy = std::true_type;

  Policy const & get_long_extended_policy() const noexcept
  { return policy_; }

  Policy policy_;
};


template<class Ch>
using simple_escaped_policy_base
= normal_quoted_policy<
  cannot_be_escape_policy<
    nodepth_policy<
      default_quoted_policy_base<quoted_param<Ch>>
    >
  >
>;

#undef USING_POLICY_CTOR
#undef USING_POLICY_COPY_CTOR
}

//  manipulator for const std::basic_string&
template <class Ch, class Tr, class Alloc>
aux_::quoted_proxy<std::basic_string<Ch, Tr, Alloc> const &, Ch>
quoted(
  std::basic_string<Ch, Tr, Alloc> const & s
, Ch delim='\"', Ch escape='\\')
{ return {s, delim, escape}; }

//  manipulator for non-const std::basic_string&
template <class Ch, class Tr, class Alloc>
aux_::quoted_proxy<std::basic_string<Ch, Tr, Alloc> &, Ch>
quoted(std::basic_string<Ch, Tr, Alloc> & s, Ch delim='\"', Ch escape='\\')
{ return {s, delim, escape}; }

//  manipulator for const C-string*
template <class Ch>
aux_::quoted_proxy<Ch const *, Ch>
quoted(Ch const * s, Ch delim='\"', Ch escape='\\')
{ return {s, delim, escape}; }

//  manipulator for const String with iofmts type
template <class String>
typename aux_::make_quoted_with_fmt<String>::type
quoted(
  String const & s
, typename aux_::make_quoted_with_fmt<String>::char_type delim='\"'
, typename aux_::make_quoted_with_fmt<String>::char_type escape='\\')
{ return {s, delim, escape}; }


///\brief  escaped_string(s, delim) == quoted(s, delim, delim)
template<class T, class Ch>
auto escaped_string(T & s, Ch delim='\"')
->decltype(quoted(s, delim, delim))
{ return quoted(s, delim, delim); }


///\brief  force the presence of \a escape
template<class Ch, class Tr, class Alloc>
aux_::pquoted_proxy<
  std::basic_string<Ch, Tr, Alloc> &
, quoted_policies::normal_quoted_policy<
    quoted_policies::always_quoted_policy<
      quoted_policies::default_quoted_policy_base<
        quoted_policies::quoted_param<Ch>
>>>>
aquoted(std::basic_string<Ch, Tr, Alloc> & s, Ch delim='\"', Ch escape='\"')
{ return {s, {delim, escape}}; }


/// \brief  the delimiter is ' or "
template<class Ch, class Tr, class Alloc>
aux_::pquoted_proxy<
  std::basic_string<Ch, Tr, Alloc> &
, quoted_policies::normal_quoted_policy<
    quoted_policies::normal_quoted_policy_base<
      quoted_policies::is_delimeter_quoted_param<
        quoted_policies::quote_fn, Ch
>>>>
squoted(std::basic_string<Ch, Tr, Alloc> & s, Ch escape='\\')
{ return {s, {escape}}; }


/// \brief  force the presence of delimiter ' or "
template<class Ch, class Tr, class Alloc>
aux_::pquoted_proxy<
  std::basic_string<Ch, Tr, Alloc> &
, quoted_policies::normal_quoted_policy_base<
    quoted_policies::always_quoted_policy<
      quoted_policies::is_delimeter_quoted_param<
        quoted_policies::quote_fn, Ch
>>>>
asquoted(std::basic_string<Ch, Tr, Alloc> & s, Ch escape='\\')
{ return {s, escape}; }


template<class Ch, class Tr, class Alloc, class IsDelim>
aux_::pquoted_proxy<
  std::basic_string<Ch, Tr, Alloc> &
, quoted_policies::normal_quoted_policy_base<
    quoted_policies::is_delimeter_quoted_param<IsDelim, Ch>
>>
dquoted(std::basic_string<Ch, Tr, Alloc> & s, IsDelim is_delim, Ch escape='\\')
{ return {s, {is_delim, escape}}; }


template<class Ch, class Tr, class Alloc, class IsDelim>
aux_::pquoted_proxy<
  std::basic_string<Ch, Tr, Alloc> &
, quoted_policies::normal_quoted_policy_base<
    quoted_policies::always_quoted_policy<
      quoted_policies::is_delimeter_quoted_param<IsDelim, Ch>
>>>
adquoted(std::basic_string<Ch, Tr, Alloc> & s, IsDelim is_delim, Ch escape='\\')
{ return {s, {is_delim, escape}}; }


template<
  class Ch, class Tr, class Alloc
, class Policy = quoted_policies::normal_and_extended_quoted_policy<
    quoted_policies::default_quoted_policy_base<
      quoted_policies::quoted_param<Ch>
    >
  , quoted_policies::default_quoted_policy_base<
      quoted_policies::quoted_param<Ch>
    >
>>
aux_::pquoted_proxy<std::basic_string<Ch, Tr, Alloc> &, Policy>
tquoted(std::basic_string<Ch, Tr, Alloc> & s, Policy policy)
{ return {s, policy}; }


template<class Ch, class Tr, class Alloc>
aux_::pquoted_proxy<
  std::basic_string<Ch, Tr, Alloc> &
, quoted_policies::normal_quoted_policy<
    quoted_policies::default_quoted_policy_base<
      quoted_policies::tag_param<Ch>
>>>
qquoted(std::basic_string<Ch, Tr, Alloc> & s, Ch left_delim, Ch right_delim)
{ return {s, {left_delim, right_delim}}; }


template<class Ch, class Tr, class Alloc>
aux_::pquoted_proxy<
  std::basic_string<Ch, Tr, Alloc> &
, quoted_policies::normal_quoted_policy<
    quoted_policies::noleft_policy<
      quoted_policies::default_quoted_policy_base<
        quoted_policies::tag_param<Ch>
>>>>
tag(std::basic_string<Ch, Tr, Alloc> & s, Ch left_delim, Ch right_delim)
{ return {s, {left_delim, right_delim}}; }


template<class Ch, class Tr, class Alloc>
aux_::pquoted_proxy<
  std::basic_string<Ch, Tr, Alloc> &
, quoted_policies::normal_quoted_policy<
    quoted_policies::nodepth_policy<
      quoted_policies::default_quoted_policy_base<
        quoted_policies::tag_param<Ch>
>>>>
qtag(std::basic_string<Ch, Tr, Alloc> & s, Ch left_delim, Ch right_delim)
{ return {s, {left_delim, right_delim}}; }


template<class Ch, class Tr, class Alloc>
aux_::pescaped_proxy<
  std::basic_string<Ch, Tr, Alloc> &
, quoted_policies::simple_escaped_policy_base<Ch>>
escaped(std::basic_string<Ch, Tr, Alloc> & s, Ch delim, Ch escape = '\\')
{ return {s, {delim, escape}}; }


template<class Ch, class Tr, class Alloc>
aux_::ipescaped_proxy<
  std::basic_string<Ch, Tr, Alloc> &
, quoted_policies::simple_escaped_policy_base<Ch>>
iescaped(std::basic_string<Ch, Tr, Alloc> & s, Ch delim, Ch escape = '\\')
{ return {s, {delim, escape}}; }


template<
  class Ch, class Tr, class Alloc
, class Policy = quoted_policies::simple_escaped_policy_base<Ch>>
aux_::pescaped_proxy<std::basic_string<Ch, Tr, Alloc> &, Policy>
pescaped(
  std::basic_string<Ch, Tr, Alloc> & s
, Policy policy = Policy('"', '\\'))
{ return {s, policy}; }


template<
  class Ch, class Tr, class Alloc
, class Policy = quoted_policies::simple_escaped_policy_base<Ch>>
aux_::ipescaped_proxy<std::basic_string<Ch, Tr, Alloc> &, Policy>
ipescaped(
  std::basic_string<Ch, Tr, Alloc> & s
, Policy policy = Policy('"', '\\'))
{ return {s, policy}; }


template<
  class Ch, class Tr, class Alloc
, class Policy = quoted_policies::normal_and_extended_quoted_policy<
    quoted_policies::normal_quoted_policy_base<
      quoted_policies::quoted_param3<Ch>
    >
  , quoted_policies::normal_quoted_policy_base<
      quoted_policies::quoted_param3<Ch>
  >
>>
aux_::pquoted_proxy<std::basic_string<Ch, Tr, Alloc> &, Policy>
pquoted(std::basic_string<Ch, Tr, Alloc> & s, Policy policy)
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


template <class Str, class Ch>
struct quoted_proxy
{
  Str string;
  Ch  delim;
  Ch  escape;

  quoted_proxy& operator=(const quoted_proxy&) = delete;
};

template <class Str, class Policy, escape_mode Mode>
struct pquoted_proxy
{
  Str string;
  Policy policy;

  static const escape_mode mode = Mode;

  pquoted_proxy& operator=(const pquoted_proxy&) = delete;
};

struct count_none {
  count_none& operator = (int) { return *this; }
  count_none& operator++() { return *this; }
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


template <
  bool with_depth, bool with_left, bool can_be_escaped, bool delim_is_escape
, class Ch, class Tr, class String, class SimplePolicy>
void escape_pquoted_impl(
  std::basic_istream<Ch, Tr> & is
, std::basic_streambuf<Ch, Tr> & buf
, String & string, Ch left, SimplePolicy policy)
{
  typedef std::basic_istream<Ch, Tr>      istream_type;
  typedef typename istream_type::int_type int_type;

  constexpr auto eof = Tr::eof();

  for (unsigned depth = 1;;)
  {
    int_type cb = buf.sbumpc();
    if (Tr::eq_int_type(cb, eof)) {
      policy.set_error(quoted_policies::quoted_error::eof);
      is.setstate(std::ios_base::eofbit | std::ios_base::failbit);
      break;
    }

    Ch c = Tr::to_char_type(cb);
    if (can_be_escaped && c == policy.escape()) {
      cb = buf.sbumpc();
      if (Tr::eq_int_type(cb, eof)) {
        if (!delim_is_escape) {
          policy.set_error(quoted_policies::quoted_error::eof);
          is.setstate(std::ios_base::eofbit | std::ios_base::failbit);
        }
        break;
      }
      c = Tr::to_char_type(cb);
      if (delim_is_escape && c != policy.escape()) {
        break;
      }

      // TODO
      /*if ((policy.interpret_mode() || policy.keep_escape())
       && policy.is_right(c)) {
        string += c;
      }
      else*/ {
        policy.push_back(string, c, buf);
      }

      continue;
    }
    else if ((can_be_escaped ? !delim_is_escape : 1) && policy.is_right(c)) {
      if (!with_depth || !--depth) {
        break;
      }
    }
    else if (with_depth && c == left) {
      ++depth;
    }
    else if (!with_left && c == left) {
      policy.set_error(quoted_policies::quoted_error::left_presence);
      is.setstate(std::ios_base::failbit);
      break;
    }

    if (!policy.is_valid(c)) {
      policy.set_error(quoted_policies::quoted_error::invalid_character);
      is.setstate(std::ios_base::failbit);
      break;
    }

    string += c;
  }
}


template <
  bool can_be_escaped, bool delim_is_escape
, class Ch, class Tr, class String, class Policy>
struct escape_pquoted_callable
{
  std::basic_istream<Ch, Tr> & is;
  std::basic_streambuf<Ch, Tr> & buf;
  String & string;
  Ch left;
  Policy const & policy;

  template<class WithDepth, class WithLeft>
  void operator()(WithDepth, WithLeft) const
  {
    escape_pquoted_impl<
      WithDepth::value, WithLeft::value, can_be_escaped, delim_is_escape
    >(is, buf, string, left, policy);
  }
};

template <
  bool can_be_escaped, bool delim_is_escape
, class Ch, class Tr, class String, class Policy>
void escaped_dispath_impl(
  std::basic_istream<Ch, Tr> & is
, std::basic_streambuf<Ch, Tr> & buf
, String & string, Ch left, Policy const & policy)
{
  to_compile_time_expression(
    escape_pquoted_callable<
      can_be_escaped, delim_is_escape, Ch, Tr, String, Policy
    >{is, buf, string, left, policy} // polymophic lambda...
  , policy.with_depth(), policy.with_left());
}

template <class Ch, class Tr, class String, class Policy>
void escaped_impl(
  std::basic_istream<Ch, Tr> & is
, std::basic_streambuf<Ch, Tr> & buf
, String & string, Policy const & policy, Ch left)
{
  if (policy.can_be_escaped()) {
    if (policy.is_right(policy.escape())) {
      if (policy.delimiter_can_be_escape()) {
        escaped_dispath_impl<true, true>(is, buf, string, left, policy);
      }
      else {
        policy.set_error(quoted_policies::quoted_error::escape_is_ambiguous);
        is.setstate(std::ios_base::failbit);
      }
    }
    else {
      escaped_dispath_impl<true, false>(is, buf, string, left, policy);
    }
  }
  else {
    escaped_dispath_impl<false, false>(is, buf, string, left, policy);
  }
}


template<class Policy, bool KeepEscape>
class escaped_char_base
{
protected:
  Policy const & policy;

public:
  constexpr escaped_char_base(Policy const & policy) noexcept
  : policy(policy)
  {}

  constexpr bool can_be_escaped() const noexcept
  { return policy.can_be_escaped(); }

  constexpr auto escape() const noexcept
  -> decltype(this->policy.escape())
  { return policy.escape(); }

  constexpr bool delimiter_can_be_escape() const noexcept
  { return policy.delimiter_can_be_escape(); }

  constexpr bool with_depth() const noexcept
  { return policy.with_depth(); }

  constexpr bool noleft() const noexcept
  { return policy.noleft(); }

  static constexpr bool keep_escape() noexcept
  { return KeepEscape; }

  void set_error(quoted_policies::quoted_error e) const
  { policy.set_error(e); }
};

template<class Policy, bool KeepEscape = true>
struct escaped_simple_char
: escaped_char_base<Policy, KeepEscape>
{
  using escaped_char_base<Policy, KeepEscape>::escaped_char_base;

  template<class Ch>
  constexpr bool is_valid(Ch c) const noexcept
  { return this->policy.simple_char_is_valid(c); }

  template<class String, class Ch>
  void push_back(String & str, Ch c) const
  {
    if (KeepEscape) {
      str += this->policy.escape();
    }
    str += c;
  }

  template<class Ch>
  constexpr bool is_right(Ch c) const noexcept
  { return this->policy.is_simple_right(c); }

  static constexpr bool interpret_mode() noexcept
  { return false; }
};

template<
  class Policy, bool KeepEscape = true
, class Ch = char, class Tr = std::char_traits<Ch>>
struct escaped_interpret_char
: escaped_char_base<Policy, KeepEscape>
{
  constexpr escaped_interpret_char(
    Policy const & policy
  , std::basic_streambuf<Ch, Tr> & buf
  ) noexcept
  : escaped_char_base<Policy, KeepEscape>(policy)
  , buf(buf)
  {}

  constexpr bool is_valid(Ch c) const noexcept
  { return this->policy.interpret_char_is_valid(c); }

  template<class Alloc>
  void push_back(std::basic_string<Ch, Tr, Alloc> & str, Ch c) const
  {
    if (!this->policy.interpret_push_back(str, c, buf) && KeepEscape) {
      str += this->policy.escape();
      str += c;
    }
  }

  constexpr bool is_right(Ch c) const noexcept
  { return this->policy.is_interpret_right(c); }

  static constexpr bool interpret_mode() noexcept
  { return true; }

private:
  std::basic_streambuf<Ch, Tr> & buf;
};


template<class Policy, class = void>
struct enable_normal_policy
: std::false_type
{};

template<class Policy>
struct enable_normal_policy<
  Policy
, enable_type_t<typename Policy::normal_policy>>
: Policy::normal_policy
{
  static auto get(Policy const & policy)
  -> decltype(policy.get_normal_policy())
  { return policy.get_normal_policy(); }
};


template <class Enable, class Ch, class Tr, class String, class Policy>
bool pquoted_extract_impl(
  std::basic_istream<Ch, Tr> const &
, std::basic_streambuf<Ch, Tr> const &
, String const &, Policy const &
, Ch, Enable, std::false_type = typename Enable::type())
{ return false; }

template <class Enable, class Ch, class Tr, class String, class Policy>
bool pquoted_extract_impl(
  std::basic_istream<Ch, Tr> & is
, std::basic_streambuf<Ch, Tr> & buf
, String & string, Policy const & policy
, Ch c, Enable, std::true_type = typename Enable::type())
{
  auto && policy_ = Enable::get(policy);

  if (policy_.is_left(c)) {
    string.clear();
    buf.sbumpc();
    // TODO
    if (policy_.keep_escape()) {
      escaped_impl(is, buf, string, policy_, c);
    }
    else {
      escaped_impl(is, buf, string, policy_, c);
    }
    return true;
  }
  return false;
}


template <class Ch, class Tr, class String, class Policy>
std::basic_istream<Ch, Tr> & pquoted_impl(
  std::basic_istream<Ch, Tr> & is
, String & string, Policy const & policy)
{
  typedef std::basic_istream<Ch, Tr>      istream_type;
  typedef typename istream_type::int_type int_type;

  typename istream_type::sentry cerb(is);
  if (cerb) {
    constexpr auto eof = Tr::eof();

    std::basic_streambuf<Ch, Tr> & buf = *is.rdbuf();

    const int_type cb = buf.sgetc();

    if (Tr::eq_int_type(cb, eof)) {
      policy.set_error(quoted_policies::quoted_error::eof);
      is.setstate(std::ios_base::eofbit | std::ios_base::failbit);
      return is;
    }

    using enable_normal = enable_normal_policy<Policy>;

    const Ch c = Tr::to_char_type(cb);
    if (enable_normal::value
     && pquoted_extract_impl(is, buf, string, policy, c, enable_normal())) {

    }
//     if (policy.is_simple_left(c)) {
//       string.clear();
//       buf.sbumpc();
//       if (policy.simple_keep_escape()) {
//         escaped_impl(is, buf, string, escaped_simple_char<Policy,1>{policy}, c);
//       }
//       else {
//         escaped_impl(is, buf, string, escaped_simple_char<Policy,0>{policy}, c);
//       }
//     }
//     else if (policy.is_interpret_left(c)) {
//       string.clear();
//       buf.sbumpc();
//       if (policy.interpret_keep_escape()) {
//         escaped_impl(
//           is, buf, string
//         , escaped_interpret_char<Policy, 1, Ch, Tr>{policy, buf}
//         , c);
//       }
//       else {
//         escaped_impl(
//           is, buf, string
//         , escaped_interpret_char<Policy, 0, Ch, Tr>{policy, buf}
//         , c);
//       }
//     }

//     else if (policy.always_quoted()) {
//       policy.set_error(quoted_policies::quoted_error::delimiter);
//       is.setstate(std::ios_base::eofbit | std::ios_base::failbit);
//     }
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
    using policy_base = quoted_policies::normal_quoted_policy_base<
      quoted_policies::quoted_param<Ch>
    >;
    if (quoted.delim == quoted.escape) {
      using policy_type = quoted_policies::normal_quoted_policy<policy_base>;
      pquoted_impl(is, x, policy_type{{quoted.escape, quoted.escape}});
    }
    else {
      using policy_type = quoted_policies::normal_quoted_policy<
        quoted_policies::delimiter_cannot_be_escape_policy<policy_base>
      >;
      pquoted_impl(is, x, policy_type{{quoted.delim, quoted.escape}});
    }
  }
};

template<class Quoted>
quoted_fmt_proxy<Quoted>
make_quoted_fmt(Quoted const & quoted) noexcept
{ return {quoted}; }

template <class Str, class Ch, class Tr>
std::basic_ostream<Ch, Tr> &
operator<<(
  std::basic_ostream<Ch, Tr> & os
, quoted_proxy<Str, Ch> const & proxy)
{ return apply_fmt_manipulator(make_quoted_fmt(proxy), os, proxy.string); }

template <class Str, class Ch, class Tr>
std::basic_istream<Ch, Tr> &
operator>>(
  std::basic_istream<Ch, Tr> & is
, quoted_proxy<Str, Ch> const & proxy)
{ return apply_fmt_manipulator(make_quoted_fmt(proxy), is, proxy.string); }


template<class Escaped>
struct pescaped_fmt_proxy
{
  Escaped const & escaped;

  pescaped_fmt_proxy& operator=(const pescaped_fmt_proxy&) = delete;

  template<class Ch, class Policy>
  static constexpr auto get_left(Policy const & policy, int) noexcept
  -> decltype(policy.left())
  { return policy.left(); }

  template<class Ch, class Policy>
  static constexpr Ch get_left(Policy const &, unsigned) noexcept
  { return {}; }

  template<class Ch, class Tr, class T>
  void operator()(std::basic_istream<Ch, Tr> & is, T & x) const
  {
    using policy = decltype(escaped.policy);
    if (Escaped::mode == escape_mode::simple) {
      if (escaped.policy.simple_keep_escape()) {
        escaped_impl(
          is, *is.rdbuf(), x
        , escaped_simple_char<policy, true>{escaped.policy}
        , get_left<Ch>(escaped.policy, 1));
      }
      else {
        escaped_impl(
          is, *is.rdbuf(), x
        , escaped_simple_char<policy, false>{escaped.policy}
        , get_left<Ch>(escaped.policy, 1));
      }
    }
    else if (escaped.policy.interpret_keep_escape()) {
      using real_policy = escaped_interpret_char<policy, true, Ch, Tr>;
      escaped_impl(
        is, *is.rdbuf(), x, real_policy{escaped.policy, *is.rdbuf()}
      , get_left<Ch>(escaped.policy, 1));
    }
    else {
      using real_policy = escaped_interpret_char<policy, false, Ch, Tr>;
      escaped_impl(
        is, *is.rdbuf(), x, real_policy{escaped.policy, *is.rdbuf()}
      , get_left<Ch>(escaped.policy, 1));
    }
  }
};

template<class Str, class Policy>
pescaped_fmt_proxy<pescaped_proxy<Str, Policy>>
make_pquoted_fmt(pescaped_proxy<Str, Policy> const & quoted) noexcept
{ return {quoted}; }

template<class Str, class Policy>
pescaped_fmt_proxy<ipescaped_proxy<Str, Policy>>
make_pquoted_fmt(ipescaped_proxy<Str, Policy> const & quoted) noexcept
{ return {quoted}; }

template<class Quoted>
struct pquoted_fmt_proxy
{
  Quoted const & quoted;

  pquoted_fmt_proxy& operator=(const pquoted_fmt_proxy&) = delete;

  template<class Ch, class Tr, class T>
  void operator()(std::basic_istream<Ch, Tr> & is, T & x) const
  { pquoted_impl(is, x, quoted.policy); }
};

template<class Str, class Policy>
pquoted_fmt_proxy<pquoted_proxy<Str, Policy>>
make_pquoted_fmt(pquoted_proxy<Str, Policy> const & quoted) noexcept
{ return {quoted}; }

template <class Ch, class Tr, class Str, class Policy, aux_::escape_mode Mode>
std::basic_istream<Ch, Tr> &
operator>>(
  std::basic_istream<Ch, Tr> & is
, pquoted_proxy<Str, Policy, Mode> const & proxy)
{ return apply_fmt_manipulator(make_pquoted_fmt(proxy), is, proxy.string); }

} // aux_

}
}

#endif
