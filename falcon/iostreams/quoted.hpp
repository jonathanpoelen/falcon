#ifndef FALCON_IOSTREAMS_QUOTED_HPP
#define FALCON_IOSTREAMS_QUOTED_HPP

#include <falcon/type_traits/enable_type.hpp>
#include <falcon/iostreams/ostream_fill.hpp>
#include <falcon/iostreams/fmt_manipulator.hpp>

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

namespace aux_ {
  template <class Ch>
  struct is_valid_and_interpret_push_back_policy_base
  {
    template<class String, class Buf>
    static bool interpret_push_back(String & str, Ch c, Buf const &)
    {
      switch (c) {
        case 'n': str += '\n'; break;
        case 't': str += '\t'; break;
        case 'r': str += '\r'; break;
        default: return false;
      }
      return true;
    }

    static constexpr bool simple_char_is_valid(Ch const &) noexcept
    { return true; }

    static constexpr bool interpret_char_is_valid(Ch const &) noexcept
    { return true; }
  };
}

template<class Ch>
struct escaped_policy_base
: aux_::is_valid_and_interpret_push_back_policy_base<Ch>
{
  constexpr escaped_policy_base(Ch right, Ch escape = Ch{}) noexcept
  : right_(right)
  , escape_(escape)
  {}

  constexpr bool can_be_escaped() const noexcept
  { return Ch{} != escape_; }

  constexpr Ch escape() const noexcept
  { return escape_; }

  static constexpr bool delimiter_can_be_escape() noexcept
  { return false; }

  static constexpr bool with_depth() noexcept
  { return true; }

  static constexpr bool noleft() noexcept
  { return false; }

  constexpr bool is_simple_right(Ch c) const noexcept
  { return c == right_; }

  static constexpr bool is_interpret_right(Ch) noexcept
  { return false; }

  static constexpr bool simple_keep_escape() noexcept
  { return true; }

  static constexpr bool interpret_keep_escape() noexcept
  { return true; }

private:
  Ch right_;
  Ch escape_;
};


template<class Ch>
struct quoted_policy_base
: escaped_policy_base<Ch>
{
  constexpr quoted_policy_base(Ch left, Ch right, Ch escape = Ch{}) noexcept
  : escaped_policy_base<Ch>(right, escape)
  , left_(left)
  {}

  static constexpr bool always_quoted() noexcept
  { return true; }

  constexpr bool is_simple_left(Ch c) const noexcept
  { return c == left_; }

  static constexpr bool is_interpret_left(Ch) noexcept
  { return false; }

private:
  Ch left_;
};

#define USING_POLICY_COPY_CTOR(class_name, inherit, policy_name) \
  class_name(policy_name const & policy) : inherit(policy) {}    \
  class_name(policy_name && policy) : inherit(std::move(policy)) {}

#define USING_POLICY_CTOR(class_name)                \
  USING_POLICY_COPY_CTOR(class_name, Policy, Policy) \
  using Policy::Policy

template<class Policy>
struct nodepth_policy
: Policy
{
  USING_POLICY_CTOR(nodepth_policy);

  static constexpr bool with_depth() noexcept
  { return false; }
};


template<class Policy>
struct noleft_policy
: nodepth_policy<Policy>
{
  USING_POLICY_COPY_CTOR(
    noleft_policy
  , nodepth_policy<Policy>
  , Policy);
  using nodepth_policy<Policy>::nodepth_policy;

  static constexpr bool noleft() noexcept
  { return true; }
};


template<class Policy, bool Can = true>
struct can_be_escaped_policy
: Policy
{
  USING_POLICY_CTOR(can_be_escaped_policy);

  static constexpr bool can_be_escaped() noexcept
  { return Can; }
};

template<class Ch, bool Can = true>
using cannot_be_escape_policy
  = can_be_escaped_policy<quoted_policy_base<Ch>, !Can>;


template<class Policy>
struct interpret_push_back_return_always_true_policy
: Policy
{
  USING_POLICY_CTOR(interpret_push_back_return_always_true_policy);

  template<class String, class Ch, class Buf>
  bool interpret_push_back(String & str, Ch c, Buf const & buf) const
  {
    Policy::policy(str, c, buf);
    return true;
  }
};


template<class Policy, bool Keep = true>
struct simple_keep_escape_policy
: Policy
{
  USING_POLICY_CTOR(simple_keep_escape_policy);

  static constexpr bool simple_keep_escape() noexcept
  { return Keep; }
};

template<class Policy, bool Keep = false>
using simple_nokeep_escape_policy
  = simple_keep_escape_policy<Policy, !Keep>;


template<class Policy, bool Keep = true>
struct interpret_keep_escape_policy
: Policy
{
  USING_POLICY_CTOR(interpret_keep_escape_policy);

  static constexpr bool interpret_keep_escape() noexcept
  { return Keep; }
};

template<class Policy, bool Keep = false>
using interpret_nokeep_escape_policy
  = interpret_keep_escape_policy<Policy, !Keep>;


template<class Policy, bool Keep = true>
struct keep_escape_policy
: Policy
{
  USING_POLICY_CTOR(keep_escape_policy);

  static constexpr bool simple_keep_escape() noexcept
  { return Keep; }

  static constexpr bool interpret_keep_escape() noexcept
  { return Keep; }
};


template<class Policy, bool Keep = false>
using nokeep_escape_policy
  = keep_escape_policy<Policy, !Keep>;


template<class Ch>
struct normal_quoted_policy_base
: aux_::is_valid_and_interpret_push_back_policy_base<Ch>
{
  constexpr normal_quoted_policy_base(Ch escape = '\\') noexcept
  : escape_(escape)
  {}

  constexpr Ch escape() const noexcept
  { return escape_; }

  static constexpr bool always_quoted() noexcept
  { return false; }

  static constexpr bool delimiter_can_be_escape() noexcept
  { return true; }

  static constexpr bool is_simple_delimiter(Ch c) noexcept
  { return c == Ch('\''); }

  static constexpr bool is_interpret_delimiter(Ch c) noexcept
  { return c == Ch('"'); }

  static constexpr bool simple_keep_escape() noexcept
  { return false; }

  static constexpr bool interpret_keep_escape() noexcept
  { return false; }

private:
  Ch escape_;
};


template<class Policy>
struct simple_is_delimiter_be_is_left_and_right_policy
: Policy
{
  USING_POLICY_CTOR(simple_is_delimiter_be_is_left_and_right_policy);

  template<class Ch>
  constexpr bool is_simple_left(Ch c) const noexcept
  { return Policy::is_simple_delimiter(c); }

  template<class Ch>
  constexpr bool is_simple_right(Ch c) const noexcept
  { return Policy::is_simple_delimiter(c); }
};


template<class Policy>
struct interpret_is_delimiter_be_is_left_and_right_policy
: Policy
{
  USING_POLICY_CTOR(interpret_is_delimiter_be_is_left_and_right_policy);

  template<class Ch>
  constexpr bool is_interpret_left(Ch c) const noexcept
  { return Policy::is_interpret_delimiter(c); }

  template<class Ch>
  constexpr bool is_interpret_right(Ch c) const noexcept
  { return Policy::is_interpret_delimiter(c); }
};


template<class Policy>
using is_delimiter_be_is_left_and_right_policy
= simple_is_delimiter_be_is_left_and_right_policy<
    interpret_is_delimiter_be_is_left_and_right_policy<
      Policy
    >
>;


template<class Policy>
struct uninterpretable_policy
: Policy
{
  USING_POLICY_CTOR(uninterpretable_policy);

  template<class Ch>
  static constexpr bool is_interpret_delimiter(Ch) noexcept
  { return false; }
};


template<class Ch>
struct simple_quoted_policy_base
: normal_quoted_policy_base<Ch>
{
  constexpr simple_quoted_policy_base(Ch escape = '\\') noexcept
  : normal_quoted_policy_base<Ch>(escape)
  {}

  static constexpr bool is_interpret_delimiter(Ch) noexcept
  { return false; }
};


template<class Policy>
struct always_quoted_policy
: Policy
{
  USING_POLICY_CTOR(always_quoted_policy);

  static constexpr bool always_quoted() noexcept
  { return true; }
};


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


template<class IsDelim, class Policy>
struct is_simple_delimiter_policy
: Policy
{
  template<class Func, class... Ts>
  constexpr is_simple_delimiter_policy(Func && f, Ts && ... args)
  : Policy(std::forward<Ts>(args)...)
  , fdelim_{std::forward<Func>(f)}
  {}

  is_simple_delimiter_policy() = default;
  is_simple_delimiter_policy(is_simple_delimiter_policy const &) = default;
  is_simple_delimiter_policy(is_simple_delimiter_policy &&) = default;
  USING_POLICY_COPY_CTOR(is_simple_delimiter_policy, Policy, Policy)

  template<class Ch>
  constexpr bool is_simple_delimiter(Ch c) const noexcept
  { return fdelim_(c); }

private:
  IsDelim fdelim_;
};


namespace aux_ {
template<class Ch>
struct cmp_1 {
  Ch c_;
  constexpr bool operator()(Ch c) const noexcept
  { return c_ == c; }
};
}

template<class Ch, class Policy>
using simple_delimiter_policy
  = is_simple_delimiter_policy<aux_::cmp_1<Ch>, Policy>;


template<class Policy>
struct normal_quoted_policy_to_quoted_policy
: is_delimiter_be_is_left_and_right_policy<
  can_be_escaped_policy<noleft_policy<Policy>>
>
{
  USING_POLICY_COPY_CTOR(
    normal_quoted_policy_to_quoted_policy
  , is_delimiter_be_is_left_and_right_policy<
    can_be_escaped_policy<noleft_policy<Policy>>
  >
  , Policy)
  using is_delimiter_be_is_left_and_right_policy<
    can_be_escaped_policy<noleft_policy<Policy>>
  >::is_delimiter_be_is_left_and_right_policy;
};

#undef USING_POLICY_CTOR
#undef USING_POLICY_COPY_CTOR
}

namespace aux_ {
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

}

//  manipulator for const std::basic_string&
template <class Ch, class Tr, class Alloc>
aux_::quoted_proxy<std::basic_string<Ch, Tr, Alloc> const &, Ch>
quoted(
  std::basic_string<Ch, Tr, Alloc> const & s
, Ch escape='\\', Ch delim='\"')
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


///\brief  escaped_string(s, delim) == quoted(s, delim, delim)
template<class T, class Ch>
auto escaped_string(T & s, Ch delim='\"')
->decltype(quoted(s, delim, delim))
{ return quoted(s, delim, delim); }


///\brief  force the presence of \a escape
template<class Ch, class Tr, class Alloc>
aux_::pquoted_proxy<
  std::basic_string<Ch, Tr, Alloc> &
, quoted_policies::normal_quoted_policy_to_quoted_policy<
    quoted_policies::simple_delimiter_policy<
      Ch
    , quoted_policies::always_quoted_policy<
        quoted_policies::simple_quoted_policy_base<Ch>
>>>>
aquoted(std::basic_string<Ch, Tr, Alloc> & s, Ch escape='\"', Ch delim='\"')
{ return {s, {delim, escape}}; }


/// \brief  the delimiter is ' or "
template<class Ch, class Tr, class Alloc>
aux_::pquoted_proxy<
  std::basic_string<Ch, Tr, Alloc> &
, quoted_policies::normal_quoted_policy_to_quoted_policy<
    quoted_policies::normal_quoted_policy_base<Ch>
>>
squoted(std::basic_string<Ch, Tr, Alloc> & s, Ch escape='\\')
{ return {s, escape}; }


/// \brief  force the presence of delimiter ' or "
template<class Ch, class Tr, class Alloc>
aux_::pquoted_proxy<
  std::basic_string<Ch, Tr, Alloc> &
, quoted_policies::normal_quoted_policy_to_quoted_policy<
    quoted_policies::always_quoted_policy<quoted_policies::normal_quoted_policy_base<Ch>>
>>
asquoted(std::basic_string<Ch, Tr, Alloc> & s, Ch escape='\\')
{ return {s, escape}; }


template<class Ch, class Tr, class Alloc, class IsDelim>
aux_::pquoted_proxy<
  std::basic_string<Ch, Tr, Alloc> &
, quoted_policies::normal_quoted_policy_to_quoted_policy<
    quoted_policies::is_simple_delimiter_policy<
      IsDelim
    , quoted_policies::simple_quoted_policy_base<Ch>
>>>
dquoted(std::basic_string<Ch, Tr, Alloc> & s, IsDelim is_delim, Ch escape='\\')
{ return {s, {is_delim, escape}}; }


template<class Ch, class Tr, class Alloc, class IsDelim>
aux_::pquoted_proxy<
  std::basic_string<Ch, Tr, Alloc> &
, quoted_policies::normal_quoted_policy_to_quoted_policy<
    quoted_policies::is_simple_delimiter_policy<
      IsDelim
    , quoted_policies::always_quoted_policy<
        quoted_policies::simple_quoted_policy_base<Ch>
>>>>
adquoted(std::basic_string<Ch, Tr, Alloc> & s, IsDelim is_delim, Ch escape='\\')
{ return {s, {is_delim, escape}}; }


template<
  class Ch, class Tr, class Alloc
, class Policy = quoted_policies::normal_quoted_policy_base<Ch>>
aux_::pquoted_proxy<
  std::basic_string<Ch, Tr, Alloc> &
, quoted_policies::normal_quoted_policy_to_quoted_policy<Policy>>
tquoted(std::basic_string<Ch, Tr, Alloc> & s, Policy policy = Policy())
{ return {s, policy}; }


template<class Ch, class Tr, class Alloc>
aux_::pquoted_proxy<
  std::basic_string<Ch, Tr, Alloc> &
, quoted_policies::cannot_be_escape_policy<quoted_policies::quoted_policy_base<Ch>>>
qquoted(std::basic_string<Ch, Tr, Alloc> & s, Ch left_delim, Ch right_delim)
{ return {s, {left_delim, right_delim}}; }


template<class Ch, class Tr, class Alloc>
aux_::pquoted_proxy<
  std::basic_string<Ch, Tr, Alloc> &
, quoted_policies::cannot_be_escape_policy<
    quoted_policies::noleft_policy<quoted_policies::quoted_policy_base<Ch>>
>>
tag(std::basic_string<Ch, Tr, Alloc> & s, Ch left_delim, Ch right_delim)
{ return {s, {left_delim, right_delim}}; }


template<class Ch, class Tr, class Alloc>
aux_::pquoted_proxy<
  std::basic_string<Ch, Tr, Alloc> &
, quoted_policies::cannot_be_escape_policy<
    quoted_policies::nodepth_policy<quoted_policies::quoted_policy_base<Ch>>
>>
qtag(std::basic_string<Ch, Tr, Alloc> & s, Ch left_delim, Ch right_delim)
{ return {s, {left_delim, right_delim}}; }


template<class Ch, class Tr, class Alloc>
aux_::pescaped_proxy<
  std::basic_string<Ch, Tr, Alloc> &
, quoted_policies::cannot_be_escape_policy<
    quoted_policies::nodepth_policy<quoted_policies::escaped_policy_base<Ch>>
>>
escaped(std::basic_string<Ch, Tr, Alloc> & s, Ch delim, Ch escape = '\\')
{ return {s, {delim, escape}}; }


template<class Ch, class Tr, class Alloc>
aux_::ipescaped_proxy<
  std::basic_string<Ch, Tr, Alloc> &
, quoted_policies::cannot_be_escape_policy<
    quoted_policies::nodepth_policy<quoted_policies::escaped_policy_base<Ch>>
>>
iescaped(std::basic_string<Ch, Tr, Alloc> & s, Ch delim, Ch escape = '\\')
{ return {s, {delim, escape}}; }


template<class Ch, class Tr, class Alloc, class Policy>
aux_::pescaped_proxy<std::basic_string<Ch, Tr, Alloc> &, Policy>
pescaped(std::basic_string<Ch, Tr, Alloc> & s, Policy policy)
{ return {s, policy}; }


template<class Ch, class Tr, class Alloc, class Policy>
aux_::ipescaped_proxy<std::basic_string<Ch, Tr, Alloc> &, Policy>
ipescaped(std::basic_string<Ch, Tr, Alloc> & s, Policy policy)
{ return {s, policy}; }


template<class Ch, class Tr, class Alloc, class Policy>
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
  Ch  escape;
  Ch  delim;

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
  bool with_depth, bool noleft, bool can_be_escaped, bool delim_is_escape
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
      is.setstate(std::ios_base::eofbit | std::ios_base::failbit);
      break;
    }

    Ch c = Tr::to_char_type(cb);
    if (can_be_escaped && c == policy.escape()) {
      cb = buf.sbumpc();
      if (Tr::eq_int_type(cb, eof)) {
        if (!delim_is_escape) {
          is.setstate(std::ios_base::eofbit | std::ios_base::failbit);
        }
        break;
      }
      c = Tr::to_char_type(cb);
      if (delim_is_escape && c != policy.escape()) {
        break;
      }

      if ((policy.interpret_mode() || policy.keep_escape())
       && policy.is_right(c)) {
        string += c;
      }
      else {
        policy.push_back(string, c);
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
    else if (noleft && c == left) {
      is.setstate(std::ios_base::eofbit | std::ios_base::failbit);
      break;
    }

    if (!policy.is_valid(c)) {
      is.setstate(std::ios_base::eofbit | std::ios_base::failbit);
      break;
    }

    string += c;
  }
}

template <
  bool can_be_escaped, bool delim_is_escape
, class Ch, class Tr, class String, class Policy>
void pquoted_optleft_impl(
  std::basic_istream<Ch, Tr> & is
, std::basic_streambuf<Ch, Tr> & buf
, String & string, Ch left, Policy const & policy)
{
  if (policy.with_depth()) {
    if (policy.noleft()) {
      escape_pquoted_impl<true, true, can_be_escaped, delim_is_escape>(
        is, buf, string, left, policy
      );
    }
    else {
      escape_pquoted_impl<true, false, can_be_escaped, delim_is_escape>(
        is, buf, string, left, policy
      );
    }
  }
  else if (policy.noleft()) {
    escape_pquoted_impl<false, true, can_be_escaped, delim_is_escape>(
      is, buf, string, left, policy
    );
  }
  else {
    escape_pquoted_impl<false, false, can_be_escaped, delim_is_escape>(
      is, buf, string, left, policy
    );
  }
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
        pquoted_optleft_impl<true, true>(is, buf, string, left, policy);
      }
      else {
        is.setstate(std::ios_base::eofbit | std::ios_base::failbit);
      }
    }
    else {
      pquoted_optleft_impl<true, false>(is, buf, string, left, policy);
    }
  }
  else {
    pquoted_optleft_impl<false, false>(is, buf, string, left, policy);
  }
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
      is.setstate(std::ios_base::eofbit | std::ios_base::failbit);
      return is;
    }

    const Ch c = Tr::to_char_type(cb);
    if (policy.is_simple_left(c)) {
      string.clear();
      buf.sbumpc();
      if (policy.simple_keep_escape()) {
        escaped_impl(is, buf, string, escaped_simple_char<Policy,1>{policy}, c);
      }
      else {
        escaped_impl(is, buf, string, escaped_simple_char<Policy,0>{policy}, c);
      }
    }
    else if (policy.is_interpret_left(c)) {
      string.clear();
      buf.sbumpc();
      if (policy.interpret_keep_escape()) {
        escaped_impl(
          is, buf, string
        , escaped_interpret_char<Policy, 1, Ch, Tr>{policy, buf}
        , c);
      }
      else {
        escaped_impl(
          is, buf, string
        , escaped_interpret_char<Policy, 0, Ch, Tr>{policy, buf}
        , c);
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
    using policy_type = quoted_policies::normal_quoted_policy_to_quoted_policy<
      quoted_policies::simple_delimiter_policy<
        Ch, quoted_policies::simple_quoted_policy_base<Ch>
    >>;
    if (quoted.delim == quoted.escape) {
      pquoted_impl(is, x, policy_type{quoted.escape, quoted.escape});
    }
    else {
      using policy_type2
        = quoted_policies::delimiter_cannot_be_escape_policy<policy_type>;
      pquoted_impl(is, x, policy_type2{quoted.delim, quoted.escape});
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
