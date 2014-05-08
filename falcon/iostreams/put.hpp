#ifndef FALCON_IOSTREAM_PUT_HPP
#define FALCON_IOSTREAM_PUT_HPP

#include <falcon/utility/unpack.hpp>

#include <utility>
#include <iosfwd>

namespace falcon {
namespace iostreams {

template<class CharT, class Traits, class... Args>
std::basic_ostream<CharT, Traits>&
put(std::basic_ostream<CharT, Traits>& os, const Args&... args)
{
  FALCON_UNPACK(os << args);
  return os;
}

/**
 * \brief Functor for @p falcon::put()
 */
template<class CharT, class Traits = std::char_traits<CharT>>
struct basic_ostream_function
{
  typedef std::basic_ostream<CharT, Traits> ostream_type;


  basic_ostream_function(ostream_type& os) noexcept
  : m_os(&os)
  {}

  basic_ostream_function& operator=(ostream_type& os) noexcept
  {
    m_os = &os;
    return *this;
  }

  template<class... Args>
  ostream_type& operator()(const Args&... args) const
  { return put(*m_os, args...); }

  ostream_type& base() const noexcept
  { return *m_os; }

private:
  ostream_type* m_os;
};

typedef basic_ostream_function<char> ostream_function;
typedef basic_ostream_function<wchar_t> wostream_function;

template<class CharT, class Traits>
basic_ostream_function<CharT, Traits>
make_ostream_function(std::basic_ostream<CharT, Traits>& os) noexcept
{ return basic_ostream_function<CharT, Traits>(os); }

}
}

#endif
