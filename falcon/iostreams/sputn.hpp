#ifndef FALCON_IOSTREAM_SPUTN_HPP
#define FALCON_IOSTREAM_SPUTN_HPP

#include <iosfwd>

namespace falcon {
namespace iostreams {

/// \brief call \a buf->sputn(\a s, \a n)
template<class CharT, class Traits>
std::streamsize
sputn(
  std::basic_streambuf<CharT, Traits>* buf
, const CharT * s, std::streamsize n)
{ return buf->sputn(s, n); }

/// \brief call \a buf.sputn(\a s, \a n)
template<class CharT, class Traits>
std::streamsize
sputn(
  std::basic_streambuf<CharT, Traits>& buf
, const CharT * s, std::streamsize n)
{ return buf.sputn(s, n); }

/// \brief call \a out.rdbuf()->sputn(\a s, \a n)
template<class CharT, class Traits>
std::streamsize
sputn(
  std::basic_ostream<CharT, Traits>& out
, const CharT * s, std::streamsize n)
{ return out.rdbuf()->sputn(s, n); }

}
}

#endif
