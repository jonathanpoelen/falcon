#ifndef _FALCON_TYPE_TRAITS_UNSPECIFIED_TYPE_HPP
#define _FALCON_TYPE_TRAITS_UNSPECIFIED_TYPE_HPP

#include <falcon/type_traits/integral_constant.hpp>
#include <falcon/c++/constexpr.hpp>

namespace falcon {

struct unspecified_type {};
typedef unspecified_type unspecified_t;

CPP_USE_CONSTEXPR unspecified_type unspecified;

template<typename>
struct is_unspecified
: public false_type { };

template<>
struct is_unspecified<unspecified_t>
: public true_type { };

}

#endif
