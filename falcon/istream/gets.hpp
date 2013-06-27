#ifndef FALCON_ISTREAM_GETS_HPP
#define FALCON_ISTREAM_GETS_HPP

#include <iosfwd>

namespace falcon {
namespace istream {

template <typename CharT, typename Traits>
std::streamsize gets(std::basicstreambuf<CharT, Traits>* buf,
                     const CharT* s, std::streamsize n)
{ return buf->sgetn(s, n); }

template <typename CharT, typename Traits>
std::streamsize gets(std::basicstreambuf<CharT, Traits>& buf,
                     const CharT* s, std::streamsize n)
{ return buf.sgetn(s, n); }

template <typename CharT, typename Traits>
std::streamsize gets(std::basicostream<CharT, Traits>& out,
                     const CharT* s, std::streamsize n)
{ return out.rdbuf()->sgetn(s, n); }

}
}

#endif
