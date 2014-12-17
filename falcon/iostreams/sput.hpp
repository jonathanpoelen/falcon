#ifndef FALCON_IOSTREAM_SPUT_HPP
#define FALCON_IOSTREAM_SPUT_HPP

#include <falcon/utility/unpack.hpp>
#include <falcon/fn/make_global_function_object.hpp>

#include <iosfwd>

namespace falcon {
namespace iostreams {

namespace adl_ss_ {
  template<class CharT, class Traits, class... Args>
  std::basic_ostream<CharT, Traits>&
  sput(std::basic_ostream<CharT, Traits>& os, const Args&... args)
  {
    FALCON_UNPACK(os << args);
    return os;
  }
}

FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_WRAPPER(adl_ss_, sput)
typedef adl_ss_::sput_fn sput_fn;

}
}

#endif
