#ifndef FALCON_IOSTREAM_PUT_HPP
#define FALCON_IOSTREAM_PUT_HPP

#include <falcon/c++1x/unpack.hpp>

#include <utility>
#include <iosfwd>

namespace falcon {

template<typename CharT, typename Traits, typename... Args>
std::basic_ostream<CharT, Traits>&
put(std::basic_ostream<CharT, Traits>& os, const Args&... args)
{
  CPP1X_UNPACK(os << args);
  return os;
}

/**
 * \brief Functor for @p falcon::put()
 */
template<typename CharT, typename Traits = std::char_traits<CharT>>
class basic_ostream_function
{
public:
  typedef std::basic_ostream<CharT, Traits> ostream_type;

public:
  basic_ostream_function(ostream_type& os)
  : m_os(&os)
  {}

  basic_ostream_function(const basic_ostream_function& other)
  : m_os(other.m_os)
  {}

  basic_ostream_function& operator=(ostream_type& os)
  {
    m_os = &os;
    return *this;
  }

  basic_ostream_function& operator=(const basic_ostream_function& other)
  {
    m_os = other.m_os;
    return *this;
  }

  template<typename... Args>
  ostream_type& operator()(const Args&... args) const
  { return put(*m_os, args...); }

  ostream_type& base() const
  { return *m_os; }

  void swap(basic_ostream_function& other)
  {
    using std::swap;
    swap(m_os, other.m_os);
  }

private:
  ostream_type* m_os;
};

typedef basic_ostream_function<char> ostream_function;
typedef basic_ostream_function<wchar_t> wostream_function;

template<typename CharT, typename Traits>
basic_ostream_function<CharT, Traits>
make_ostream_function(std::basic_ostream<CharT, Traits>& os)
{ return basic_ostream_function<CharT, Traits>(os); }

template<typename CharT, typename Traits>
void swap(basic_ostream_function<CharT, Traits>& x,
          basic_ostream_function<CharT, Traits>& y)
{ x.swap(y); }

}

#endif
