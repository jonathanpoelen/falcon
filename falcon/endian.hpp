#ifndef FALCON_ENDIAN_HPP
#define FALCON_ENDIAN_HPP

#ifndef _BSD_SOURCE
# include <stdlib.h>
#endif

#ifdef _BSD_SOURCE
// #include <falcon/c++/constexpr.hpp>
#include <endian.h>

namespace falcon {
  /*CPP_CONSTEXPR*/ inline bool little_endian()
  {
#if BYTE_ORDER == LITTLE_ENDIAN
    return true;
#else
    return false;
# endif
  }

  /*CPP_CONSTEXPR*/ inline bool big_endian()
  {
#if BYTE_ORDER == BIG_ENDIAN
    return true;
#else
    return false;
# endif
  }

  /*CPP_CONSTEXPR*/ inline bool pdp_endian()
  {
#if BYTE_ORDER == PDP_ENDIAN
    return true;
#else
    return false;
# endif
  }
}
#else
namespace falcon {
  namespace aux_ {
    inline bool little_endian()
    {
      short tester = 0x0001;
      return *reinterpret_cast<char*>(&tester) != 0;
    }

    inline bool big_endian()
    {
      short tester = 0x0001;
      return *reinterpret_cast<char*>(&tester) == 1;
    }

    inline bool pdp_endian()
    {
      short tester = 0x0100;
      return *reinterpret_cast<char*>(&tester) == 1;
    }
  }

  inline bool little_endian()
  {
    static bool is_little_endian = aux_::little_endian();
    return is_little_endian;
  }

  inline bool big_endian()
  {
    static bool is_big_endian = aux_::big_endian();
    return is_big_endian;
  }

  inline bool pdp_endian()
  {
    static bool is_pdp_endian = aux_::pdp_endian();
    return is_pdp_endian;
  }
}
#endif

#endif
