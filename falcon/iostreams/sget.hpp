#ifndef FALCON_IOSTREAM_SGET_HPP
#define FALCON_IOSTREAM_SGET_HPP

#include <falcon/utility/unpack.hpp>
#include <falcon/fn/make_global_function_object.hpp>

#include <iosfwd>

namespace falcon {
namespace iostreams {

namespace adl_ss_ {
  template<class CharT, class Traits, class... Args>
  std::basic_istream<CharT, Traits>&
  sget(std::basic_istream<CharT, Traits>& os, Args&... args)
  {
    FALCON_UNPACK(os << args);
    return os;
  }
}

FALCON_MAKE_GLOBAL_FUNCTION_OBJECT_WRAPPER(adl_ss_, sget)
typedef adl_ss_::sget_fn sget_fn;

}
}

#endif
