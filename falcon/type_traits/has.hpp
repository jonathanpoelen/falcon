#ifndef FALCON_TYPE_TRAITS_HAS_HPP
#define FALCON_TYPE_TRAITS_HAS_HPP

#include <falcon/sfinae/has_type.hpp>

namespace falcon {

FALCON_CLASS_HAS_TYPE(type);
FALCON_CLASS_HAS_TYPE(value_type);
FALCON_CLASS_HAS_TYPE(reference);
FALCON_CLASS_HAS_TYPE(const_reference);
FALCON_CLASS_HAS_TYPE(pointer);
FALCON_CLASS_HAS_TYPE(difference_type);
FALCON_CLASS_HAS_TYPE(iterator_category);
FALCON_CLASS_HAS_TYPE(iterator_type);
FALCON_CLASS_HAS_TYPE(iterator);
FALCON_CLASS_HAS_TYPE(const_iterator);
FALCON_CLASS_HAS_TYPE(reverse_iterator);
FALCON_CLASS_HAS_TYPE(const_reverse_iterator);
FALCON_CLASS_HAS_TYPE(argument_type);
FALCON_CLASS_HAS_TYPE(first_argument_type);
FALCON_CLASS_HAS_TYPE(second_argument_type);
FALCON_CLASS_HAS_TYPE(result_type);
FALCON_CLASS_HAS_TYPE(allocator_type);
FALCON_CLASS_HAS_TYPE(first_type);
FALCON_CLASS_HAS_TYPE(second_type);
FALCON_CLASS_HAS_TYPE(key_compare);
FALCON_CLASS_HAS_TYPE(compare_type);
FALCON_CLASS_HAS_TYPE(accessor_type);
FALCON_CLASS_HAS_TYPE(functor_type);
FALCON_CLASS_HAS_TYPE(traits_type);
FALCON_CLASS_HAS_TYPE(char_type);
FALCON_CLASS_HAS_TYPE(int_type);
FALCON_CLASS_HAS_TYPE(pos_type);
FALCON_CLASS_HAS_TYPE(off_type);
FALCON_CLASS_HAS_TYPE(size_type);

}

#endif