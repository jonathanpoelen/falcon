#ifndef FALCON_OSTREAM_PUTS_HPP
#define FALCON_OSTREAM_PUTS_HPP

#include <iosfwd>

namespace falcon {
namespace ostream {

template <typename _CharT, typename _Traits>
std::size_t puts(std::basic_streambuf<_CharT, _Traits>* buf,
								 const _CharT* s, std::streamsize n)
{ return buf->sputn(s, n); }

template <typename _CharT, typename _Traits>
std::size_t puts(std::basic_streambuf<_CharT, _Traits>& buf,
								 const _CharT* s, std::streamsize n)
{ return buf.sputn(s, n); }

template <typename _CharT, typename _Traits>
std::size_t puts(std::basic_ostream<_CharT, _Traits>& out,
								 const _CharT* s, std::streamsize n)
{ return out.rdbuf()->sputn(s, n); }

}
}

#endif