#ifndef FALCON_IOSTREAM_SGETN_HPP
#define FALCON_IOSTREAM_SGETN_HPP

#include <iosfwd>

namespace falcon {
namespace iostreams {

/// \brief call \a buf->sgetn(\a s, \a n)
template <class CharT, class Traits>
std::streamsize sgetn(
  std::basicstreambuf<CharT, Traits>* buf
, const CharT* s, std::streamsize n)
{ return buf->sgetn(s, n); }

/// \brief call \a buf.sgetn(\a s, \a n)
template <class CharT, class Traits>
std::streamsize sgetn(
  std::basicstreambuf<CharT, Traits>& buf
, const CharT* s, std::streamsize n)
{ return buf.sgetn(s, n); }

/// \brief call \a out.rdbuf()->sgetn(\a s, \a n)
template <class CharT, class Traits>
std::streamsize sgetn(
  std::basicostream<CharT, Traits>& out
, const CharT* s, std::streamsize n)
{ return out.rdbuf()->sgetn(s, n); }

}
}

#endif
