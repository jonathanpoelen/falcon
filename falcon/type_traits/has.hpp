#ifndef FALCON_TYPE_TRAITS_HAS_HPP
#define FALCON_TYPE_TRAITS_HAS_HPP

#include <falcon/sfinae/has_type.hpp>

namespace falcon {

FALCON_HAS_TYPE_TRAIT_DEF(type);
FALCON_HAS_TYPE_TRAIT_DEF(value_type);
FALCON_HAS_TYPE_TRAIT_DEF(reference);
FALCON_HAS_TYPE_TRAIT_DEF(const_reference);
FALCON_HAS_TYPE_TRAIT_DEF(pointer);
FALCON_HAS_TYPE_TRAIT_DEF(difference_type);
FALCON_HAS_TYPE_TRAIT_DEF(iterator_category);
FALCON_HAS_TYPE_TRAIT_DEF(iterator_type);
FALCON_HAS_TYPE_TRAIT_DEF(iterator);
FALCON_HAS_TYPE_TRAIT_DEF(const_iterator);
FALCON_HAS_TYPE_TRAIT_DEF(reverse_iterator);
FALCON_HAS_TYPE_TRAIT_DEF(const_reverse_iterator);
FALCON_HAS_TYPE_TRAIT_DEF(argument_type);
FALCON_HAS_TYPE_TRAIT_DEF(first_argument_type);
FALCON_HAS_TYPE_TRAIT_DEF(second_argument_type);
FALCON_HAS_TYPE_TRAIT_DEF(result_type);
FALCON_HAS_TYPE_TRAIT_DEF(allocator_type);
FALCON_HAS_TYPE_TRAIT_DEF(first_type);
FALCON_HAS_TYPE_TRAIT_DEF(second_type);
FALCON_HAS_TYPE_TRAIT_DEF(key_type);
FALCON_HAS_TYPE_TRAIT_DEF(key_compare);
FALCON_HAS_TYPE_TRAIT_DEF(value_compare);
FALCON_HAS_TYPE_TRAIT_DEF(compare_type);
FALCON_HAS_TYPE_TRAIT_DEF(accessor_type);
FALCON_HAS_TYPE_TRAIT_DEF(functor_type);
FALCON_HAS_TYPE_TRAIT_DEF(traits_type);
FALCON_HAS_TYPE_TRAIT_DEF(char_type);
FALCON_HAS_TYPE_TRAIT_DEF(int_type);
FALCON_HAS_TYPE_TRAIT_DEF(pos_type);
FALCON_HAS_TYPE_TRAIT_DEF(off_type);
FALCON_HAS_TYPE_TRAIT_DEF(size_type);

}

#endif
