#ifndef _FALCON_IOSTREAM_COPY_HPP
#define _FALCON_IOSTREAM_COPY_HPP

#include <iosfwd>

namespace falcon {

template<typename _CharT, typename _ITraits, typename _OTraits>
void copy(std::basic_istream<_CharT, _ITraits>& is, std::basic_ostream<_CharT, _OTraits>& os)
{ is >> os.rdbuf(); }

}

#endif