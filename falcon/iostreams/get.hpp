#ifndef FALCON_IOSTREAM_GET_HPP
#define FALCON_IOSTREAM_GET_HPP

#include <falcon/utility/unpack.hpp>

#include <utility>
#include <iosfwd>

namespace falcon {
namespace iostreams {

template<typename CharT, typename Traits, typename... Args>
std::basic_istream<CharT, Traits>&
get(std::basic_istream<CharT, Traits>& is, Args&... args)
{
  FALCON_UNPACK(is >> args);
  return is;
}

/**
 * \brief Functor for @p falcon::get()
 */
template<typename CharT, typename Traits = std::char_traits<CharT>>
struct basic_istream_function
{
  typedef std::basic_istream<CharT, Traits> istream_type;


  basic_istream_function(istream_type& is) noexcept
  : m_is(&is)
  {}

  basic_istream_function& operator=(istream_type& is) noexcept
  {
    m_is = &is;
    return *this;
  }

  template<typename... Args>
  istream_type& operator()(Args&... args) const
  { return get(*m_is, args...); }

  istream_type& base() const noexcept
  { return *m_is; }

private:
  istream_type* m_is;
};

typedef basic_istream_function<char> istream_function;
typedef basic_istream_function<wchar_t> wistream_function;

template<typename CharT, typename Traits>
basic_istream_function<CharT, Traits>
make_istream_function(std::basic_istream<CharT, Traits>& is) noexcept
{ return basic_istream_function<CharT, Traits>(is); }

}
}

#endif
