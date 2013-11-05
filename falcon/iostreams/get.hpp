#ifndef FALCON_IOSTREAM_GET_HPP
#define FALCON_IOSTREAM_GET_HPP

#include <falcon/c++1x/unpack.hpp>

#include <utility>
#include <iosfwd>

namespace falcon {

template<typename CharT, typename Traits, typename... Args>
std::basic_istream<CharT, Traits>&
get(std::basic_istream<CharT, Traits>& is, Args&... args)
{
  CPP1X_UNPACK(is >> args);
  return is;
}

/**
 * \brief Functor for @p falcon::get()
 */
template<typename CharT, typename Traits = std::char_traits<CharT>>
class basic_istream_function
{
public:
  typedef std::basic_istream<CharT, Traits> istream_type;

public:
  basic_istream_function(istream_type& is)
  : m_is(&is)
  {}

  basic_istream_function(const basic_istream_function& other)
  : m_is(other.m_is)
  {}

  basic_istream_function& operator=(istream_type& is)
  {
    m_is = &is;
    return *this;
  }

  basic_istream_function& operator=(const basic_istream_function& ither)
  {
    m_is = ither.m_is;
    return *this;
  }

  template<typename... Args>
  istream_type& operator()(Args&... args) const
  { return get(*m_is, args...); }

  istream_type& base() const
  { return *m_is; }

  void swap(basic_istream_function& other)
  {
    using std::swap;
    swap(m_is, other.m_is);
  }

private:
  istream_type* m_is;
};

typedef basic_istream_function<char> istream_function;
typedef basic_istream_function<wchar_t> wistream_function;

template<typename CharT, typename Traits>
basic_istream_function<CharT, Traits>
make_istream_function(std::basic_istream<CharT, Traits>& is)
{ return basic_istream_function<CharT, Traits>(is); }

template<typename CharT, typename Traits>
void swap(basic_istream_function<CharT, Traits>& x,
          basic_istream_function<CharT, Traits>& y)
{ x.swap(y); }

}

#endif
