#ifndef FALCON_FUNCTIONAL_IS_TRANSPARENT_INHERITANCE_HPP
#define FALCON_FUNCTIONAL_IS_TRANSPARENT_INHERITANCE_HPP

#include <falcon/helper/restrict_is_transparent.hpp>
#include <falcon/helper/has_is_transparent.hpp>
#include <falcon/type_traits/use_if.hpp>
#include <falcon/type_traits/dummy.hpp>
#include <falcon/type_traits/if.hpp>

namespace falcon {

template<class T>
using is_transparent_inheritance = if_c<
  has_is_transparent<T>
, restrict_is_transparent<T>
, dummy
>;

}

#endif
