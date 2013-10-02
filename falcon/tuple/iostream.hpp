#ifndef FALCON_TUPLE_IOSTREAM_HPP
#define FALCON_TUPLE_IOSTREAM_HPP

#include <falcon/tuple/istream.hpp>
#include <falcon/tuple/ostream.hpp>

namespace falcon {
  namespace tuple {
    namespace iostream {
      using ::falcon::tuple::istream::operator>>;
      using ::falcon::tuple::ostream::operator<<;
    }
  }
}

#endif
