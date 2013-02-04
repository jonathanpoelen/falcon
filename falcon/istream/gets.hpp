#ifndef FALCON_ISTREAM_GETS_HPP
#define FALCON_ISTREAM_GETS_HPP

#include <iosfwd>

namespace falcon {
namespace istream {

template <typename _CharT, typename _Traits>
std::size_t gets(std::basic_streambuf<_CharT, _Traits>* buf,
								 const _CharT* s, std::streamsize n)
{ return buf->sgetn(s, n); }

template <typename _CharT, typename _Traits>
std::size_t gets(std::basic_streambuf<_CharT, _Traits>& buf,
								 const _CharT* s, std::streamsize n)
{ return buf.sgetn(s, n); }

template <typename _CharT, typename _Traits>
std::size_t gets(std::basic_ostream<_CharT, _Traits>& out,
								 const _CharT* s, std::streamsize n)
{ return out.rdbuf()->sgetn(s, n); }

}
}

#endif