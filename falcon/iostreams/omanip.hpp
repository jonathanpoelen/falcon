#ifndef FALCON_IOSTREAM_OMANIP_HPP
#define FALCON_IOSTREAM_OMANIP_HPP

#include <ostream>
#include <falcon/type_traits/static_const.hpp>

namespace falcon {
namespace iostreams {

typedef std::ostream&(*omanip_type)(std::ostream&);
typedef std::wostream&(*womanip_type)(std::wostream&);

#define FALCON_CREATE_OMANIP(manipulator)                          \
namespace aux_ {                                                   \
struct manipulator##_t                                             \
{                                                                  \
  constexpr manipulator##_t() noexcept {}                          \
                                                                   \
  template<class CharT, class Traits>                              \
  std::basic_ostream<CharT, Traits>&                               \
  operator()(std::basic_ostream<CharT, Traits>& os) const          \
  { return os << std::manipulator; }                               \
                                                                   \
  operator omanip_type () const noexcept                           \
  { return std::manipulator; }                                     \
                                                                   \
  operator womanip_type () const noexcept                          \
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
FALCON_GLOBAL_OBJECT(manipulator, aux_::manipulator##_t)

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
