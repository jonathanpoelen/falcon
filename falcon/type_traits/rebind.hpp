#ifndef FALCON_TYPE_TRAITS_REBIND_HPP
#define FALCON_TYPE_TRAITS_REBIND_HPP

#include <falcon/type_traits/enable_type.hpp>

namespace falcon {

namespace _aux {
  template<class T, class U, class = void>
  struct rebind_helper
  { typedef T type; };

  template<class T, class U>
  struct rebind_helper<
    T, U
  , typename enable_type<typename T::template rebind<U>::other>::type>
  { typedef typename T::template rebind<U>::other type; };
}

template<class T, class RebindWith>
struct rebind
{ typedef typename _aux::rebind_helper<T, RebindWith>::type type; };

}

#endif
