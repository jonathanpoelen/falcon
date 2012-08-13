#ifndef _FALCON_ISTREAM_IGNORE_ALL_HPP
#define _FALCON_ISTREAM_IGNORE_ALL_HPP

#include <iosfwd>
#include <limits>

namespace falcon {
namespace istream {

template<typename _CharT, typename _Traits>
std::basic_istream<_CharT, _Traits>& ignore_all(std::basic_istream<_CharT, _Traits>& os)
{ return os.ignore(std::numeric_limits<std::streamsize>::max()); }

}
}

#endif