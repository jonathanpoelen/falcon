#ifndef FALCON_IO_HEXU_HPP
#define FALCON_IO_HEXU_HPP

#include <ios>

namespace falcon {
namespace io {

inline std::ios_base & hexu(std::ios_base & ios)
{
  ios.setf(
    std::ios_base::uppercase | std::ios_base::hex
  , std::ios_base::uppercase | std::ios_base::basefield);
  return ios;
}

}
}

#endif
