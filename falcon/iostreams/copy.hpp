#ifndef _FALCON_IOSTREAM_COPY_HPP
#define _FALCON_IOSTREAM_COPY_HPP

#include <iosfwd>

namespace falcon {

template<typename _CharT, typename _ITraits, typename _OTraits>
void copy(std::basic_istream<_CharT, _ITraits>& is, std::basic_ios<_CharT, _OTraits>& os)
{ is >> os.rdbuf(); }

template<typename _CharT, typename _ITraits, typename _OTraits>
void copy(std::basic_istream<_CharT, _ITraits>& is,
          std::basic_streambuf<_CharT, _OTraits>* dbuf)
{ is >> dbuf; }

}

#endif
