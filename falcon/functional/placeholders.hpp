#ifndef FALCON_FUNCTIONAL_PLACEHOLDERS_HPP
#define FALCON_FUNCTIONAL_PLACEHOLDERS_HPP

#include <falcon/type_traits/static_const.hpp>

#include <functional>

namespace falcon {
template<int N>
struct placeholder { constexpr placeholder() noexcept {} };

namespace placeholders {
  FALCON_GLOBAL_OBJECT(_1, placeholder<1>);
  FALCON_GLOBAL_OBJECT(_2, placeholder<2>);
  FALCON_GLOBAL_OBJECT(_3, placeholder<3>);
  FALCON_GLOBAL_OBJECT(_4, placeholder<4>);
  FALCON_GLOBAL_OBJECT(_5, placeholder<5>);
  FALCON_GLOBAL_OBJECT(_6, placeholder<6>);
  FALCON_GLOBAL_OBJECT(_7, placeholder<7>);
  FALCON_GLOBAL_OBJECT(_8, placeholder<8>);
  FALCON_GLOBAL_OBJECT(_9, placeholder<9>);
  FALCON_GLOBAL_OBJECT(_10, placeholder<10>);
  FALCON_GLOBAL_OBJECT(_11, placeholder<11>);
  FALCON_GLOBAL_OBJECT(_12, placeholder<12>);
  FALCON_GLOBAL_OBJECT(_13, placeholder<13>);
  FALCON_GLOBAL_OBJECT(_14, placeholder<14>);
  FALCON_GLOBAL_OBJECT(_15, placeholder<15>);
}
}

namespace std {
template<int N>
struct is_placeholder<::falcon::placeholder<N>>
: public integral_constant<int, N>
{};
}

#endif
