#ifndef FALCON_TYPE_TRAITS_USE_DEF_HPP
#define FALCON_TYPE_TRAITS_USE_DEF_HPP

namespace falcon {

template <typename, typename U = void>
struct __enable_if_type
{
  typedef U type;
};

#define FALCON_USE_XXX_TRAIT_NAMED_DEF(trait, name)\
  template <typename T, typename Enable = void>\
  struct name\
  {\
    static const bool value = false;\
  };\
  template <typename T>\
  struct name<T, typename ::falcon::__enable_if_type<typename T::trait>::type>\
  {\
    static const bool value = true;\
    typedef typename T::trait type;\
  };

#define FALCON_USE_XXX_TRAIT_DEF(trait)\
  FALCON_USE_XXX_TRAIT_NAMED_DEF(trait, use_##trait)

}

#endif
