#ifndef FALCON_IOSTREAM_OMANIP_HPP
#define FALCON_IOSTREAM_OMANIP_HPP

#include <ostream>
#include <falcon/c++/constexpr.hpp>

namespace falcon {
namespace iostreams {

typedef std::ostream&(*omanip_type)(std::ostream&);
typedef std::wostream&(*womanip_type)(std::wostream&);

#define FALCON_CREATE_OMANIP(manipulator)                          \
namespace _aux {                                                   \
struct manipulator##_t                                             \
{                                                                  \
  CPP_CONSTEXPR manipulator##_t() {}                               \
                                                                   \
  template<class CharT, class Traits>                              \
  std::basic_ostream<CharT, Traits>&                               \
  operator()(std::basic_ostream<CharT, Traits>& os) const          \
  { return os << std::manipulator; }                               \
                                                                   \
  operator omanip_type () const                                    \
  { return std::manipulator; }                                     \
                                                                   \
  operator womanip_type () const                                   \
  { return std::manipulator; }                                     \
};                                                                 \
                                                                   \
template<class CharT, class Traits>                                \
std::basic_ostream<CharT, Traits>&                                 \
operator<<(std::basic_ostream<CharT, Traits>& os, manipulator##_t) \
{ return os << std::manipulator; }                                 \
}                                                                  \
                                                                   \
/**                                                                \
 * Manipulator functor for std::manipulator                        \
 */                                                                \
CPP_CONSTEXPR_OR_CONST _aux::manipulator##_t manipulator;

/**
 * Manipulators functors for std::endl, std::ends and std::flush
 * @{
 */
FALCON_CREATE_OMANIP(endl)
FALCON_CREATE_OMANIP(ends)
FALCON_CREATE_OMANIP(flush)
// @}

#undef FALCON_CREATE_OMANIP

}
}

#endif
