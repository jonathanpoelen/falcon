#ifndef FALCON_FUNCTIONAL_IS_TRANSPARENT_INHERITANCE_HPP
#define FALCON_FUNCTIONAL_IS_TRANSPARENT_INHERITANCE_HPP

#include <falcon/helper/has_is_transparent.hpp>
#include <falcon/type_traits/use_if.hpp>
#include <falcon/type_traits/dummy.hpp>
#include <falcon/type_traits/if.hpp>

namespace falcon {

namespace aux_ {
  template<class T>
  struct propage_is_transparence
  { typedef typename T::is_transparence is_transparence; };
}

template<class T>
using is_transparent_inheritance = if_c<
  has_is_transparent<T>
, aux_::propage_is_transparence<T>
, dummy
>;

}

#endif
