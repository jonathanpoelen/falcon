#ifndef FALCON_TYPE_TRAITS_USE_DEF_HPP
#define FALCON_TYPE_TRAITS_USE_DEF_HPP

#include <falcon/type_traits/enable_type.hpp>

namespace falcon {

#define FALCON_USE_XXX_TRAIT_NAMED_DEF(Type, name)\
  template <typename T, typename Enable = void>\
  struct name\
  {\
    static const bool value = false;\
  };\
  template <typename T>\
  struct name<T, typename ::falcon::enable_type<typename T::Type>::type>\
  {\
    static const bool value = true;\
    typedef typename T::Type type;\
  };

#define FALCON_USE_XXX_TRAIT_DEF(Type)\
  FALCON_USE_XXX_TRAIT_NAMED_DEF(Type, use_##trait)

}

#endif
