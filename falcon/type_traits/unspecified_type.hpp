#ifndef _FALCON_TYPE_TRAITS_UNSPECIFIED_TYPE_HPP
#define _FALCON_TYPE_TRAITS_UNSPECIFIED_TYPE_HPP

#include <falcon/type_traits/integral_constant.hpp>

namespace falcon {

struct unspecified {};

template<typename>
struct is_unspecified
: public false_type { };

template<>
struct is_unspecified<unspecified>
: public true_type { };

}

#endif
