#ifndef _FALCON_IOSTREAM_PUT_AND_GET_HPP
#define _FALCON_IOSTREAM_PUT_AND_GET_HPP

#include <iosfwd>
#include <falcon/functional/call_partial_param_loop.hpp>
#include <falcon/functional/placeholder_for_argument.hpp>
#include <falcon/functional/operators.hpp>

namespace falcon {

//@{
template<typename CharT, typename Traits, typename... Args>
std::basic_ostream<CharT, Traits>&
put(std::basic_ostream<CharT, Traits>& os, const Args&... args)
{
  return call_partial_param_loop<1>(
    placeholder_for_argument<
      0,
      left_shift<
        std::basic_ostream<CharT, Traits>&,
        late_parameter_t
      >,
      std::basic_ostream<CharT, Traits>&
    >(os),
    args...
  );
}

template<typename CharT, typename Traits, typename... Args>
std::basic_istream<CharT, Traits>&
get(std::basic_istream<CharT, Traits>& is, Args&... args)
{
  return call_partial_param_loop<1>(
    placeholder_for_argument<
      0,
      right_shift<
        std::basic_istream<CharT, Traits>&,
        late_parameter_t
      >,
      std::basic_istream<CharT, Traits>&
    >(is),
    args...
  );
}
//@}

/**
 * \brief Functor for @p falcon::put<>()
 */
template<typename CharT, typename Traits = std::char_traits<CharT>>
class basic_ostream_functor
{
public:
  typedef std::basic_ostream<CharT, Traits> ostream_type;

public:
  basic_ostream_functor(ostream_type& os)
  : m_os(&os)
  {}

  basic_ostream_functor(const basic_ostream_functor& other)
  : m_os(other.m_os)
  {}

  basic_ostream_functor& operator=(ostream_type& os)
  {
    m_os = &os;
    return *this;
  }

  basic_ostream_functor& operator=(const basic_ostream_functor& other)
  {
    m_os = other.m_os;
    return *this;
  }

  template<typename... Args>
  ostream_type& operator()(const Args&... args) const
  { return put<>(*m_os, args...); }

  ostream_type& base() const
  { return *m_os; }

  void swap(basic_ostream_functor& other)
  {
    using std::swap;
    swap(m_os, other.m_os);
  }

private:
  ostream_type* m_os;
};

typedef basic_ostream_functor<char> ostream_functor;
typedef basic_ostream_functor<wchar_t> wostream_functor;

template<typename CharT, typename Traits>
basic_ostream_functor<CharT, Traits>
make_ostream_functor(std::basic_ostream<CharT, Traits>& os)
{ return basic_ostream_functor<CharT, Traits>(os); }

/**
 * \brief Functor for @p falcon::get<>()
 */
template<typename CharT, typename Traits = std::char_traits<CharT>>
class basic_istream_functor
{
public:
  typedef std::basic_istream<CharT, Traits> istream_type;

public:
  basic_istream_functor(istream_type& is)
  : m_is(&is)
  {}

  basic_istream_functor(const basic_istream_functor& other)
  : m_is(other.m_is)
  {}

  basic_istream_functor& operator=(istream_type& is)
  {
    m_is = &is;
    return *this;
  }

  basic_istream_functor& operator=(const basic_istream_functor& ither)
  {
    m_is = ither.m_is;
    return *this;
  }

  template<typename... Args>
  istream_type& operator()(Args&... args) const
  { return get<>(*m_is, args...); }

  istream_type& base() const
  { return *m_is; }

  void swap(basic_istream_functor& other)
  {
    using std::swap;
    swap(m_is, other.m_is);
  }

private:
  istream_type* m_is;
};

typedef basic_istream_functor<char> istream_functor;
typedef basic_istream_functor<wchar_t> wistream_functor;

template<typename CharT, typename Traits>
basic_istream_functor<CharT, Traits>
make_istream_functor(std::basic_istream<CharT, Traits>& is)
{ return basic_istream_functor<CharT, Traits>(is); }

template<typename CharT, typename Traits>
void swap(basic_istream_functor<CharT, Traits>& x,
          basic_istream_functor<CharT, Traits>& y)
{ x.swap(y); }

template<typename CharT, typename Traits>
void swap(basic_ostream_functor<CharT, Traits>& x,
          basic_ostream_functor<CharT, Traits>& y)
{ x.swap(y); }
}

#endif
