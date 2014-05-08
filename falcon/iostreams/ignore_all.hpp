#ifndef FALCON_IOSTREAM_IGNORE_ALL_HPP
#define FALCON_IOSTREAM_IGNORE_ALL_HPP

#include <iosfwd>
#include <limits>

namespace falcon {
namespace iostreams {

template<class CharT, class Traits>
std::basic_istream<CharT, Traits>&
ignore_all(std::basic_istream<CharT, Traits>& os)
{ return os.ignore(std::numeric_limits<std::streamsize>::max()); }

}
}

#endif
