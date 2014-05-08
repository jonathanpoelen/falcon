#ifndef FALCON_IOSTREAM_SPUTS_HPP
#define FALCON_IOSTREAM_SPUTS_HPP

#include <iosfwd>

namespace falcon {
namespace iostreams {

template<class CharT, class Traits>
std::size_t
sputs(
  std::basic_streambuf<CharT, Traits>* buf
, const CharT* s
, std::streamsize n)
{ return buf->sputn(s, n); }

template<class CharT, class Traits>
std::size_t
sputs(
  std::basic_streambuf<CharT, Traits>& buf
, const CharT* s
, std::streamsize n)
{ return buf.sputn(s, n); }

template<class CharT, class Traits>
std::size_t
sputs(
  std::basic_ostream<CharT, Traits>& out
, const CharT* s
, std::streamsize n)
{ return out.rdbuf()->sputn(s, n); }

}
}

#endif
