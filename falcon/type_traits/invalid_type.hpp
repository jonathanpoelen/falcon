#ifndef _FALCON_TYPE_TRAITS_INVALID_TYPE_HPP
#define _FALCON_TYPE_TRAITS_INVALID_TYPE_HPP

#include <falcon/type_traits/integral_constant.hpp>

namespace falcon {

struct invalid_type
{};

template<typename>
struct is_invalid
: public false_type { };

template<>
struct is_invalid<invalid_type>
: public true_type { };

}

#endif
