#ifndef FALCON_TYPE_TRAITS_USE_TYPE_HPP
#define FALCON_TYPE_TRAITS_USE_TYPE_HPP

#include <falcon/type_traits/use_def.hpp>

namespace falcon
{

#define FALCON_USE_XXX_TRAIT(name)\
  FALCON_USE_XXX_TRAIT_NAMED_DEF(name, __use_##name)\
  template <typename T>\
  struct use_##name\
  : __use_##name<T>\
  {}

FALCON_USE_XXX_TRAIT(type);
FALCON_USE_XXX_TRAIT(value_type);
FALCON_USE_XXX_TRAIT(reference);
FALCON_USE_XXX_TRAIT(const_reference);
FALCON_USE_XXX_TRAIT(pointer);
FALCON_USE_XXX_TRAIT(difference_type);
FALCON_USE_XXX_TRAIT(iterator_category);
FALCON_USE_XXX_TRAIT(iterator_type);
FALCON_USE_XXX_TRAIT(iterator);
FALCON_USE_XXX_TRAIT(const_iterator);
FALCON_USE_XXX_TRAIT(reverse_iterator);
FALCON_USE_XXX_TRAIT(const_reverse_iterator);
FALCON_USE_XXX_TRAIT(argument_type);
FALCON_USE_XXX_TRAIT(first_argument_type);
FALCON_USE_XXX_TRAIT(second_argument_type);
FALCON_USE_XXX_TRAIT(result_type);
FALCON_USE_XXX_TRAIT(allocator_type);
FALCON_USE_XXX_TRAIT(first_type);
FALCON_USE_XXX_TRAIT(second_type);
FALCON_USE_XXX_TRAIT(key_type);
FALCON_USE_XXX_TRAIT(key_compare);
FALCON_USE_XXX_TRAIT(value_compare);
FALCON_USE_XXX_TRAIT(compare_type);
FALCON_USE_XXX_TRAIT(accessor_type);
FALCON_USE_XXX_TRAIT(functor_type);
FALCON_USE_XXX_TRAIT(traits_type);
FALCON_USE_XXX_TRAIT(char_type);
FALCON_USE_XXX_TRAIT(int_type);
FALCON_USE_XXX_TRAIT(pos_type);
FALCON_USE_XXX_TRAIT(off_type);
FALCON_USE_XXX_TRAIT(size_type);

#undef FALCON_USE_XXX_TRAIT

}

#endif
