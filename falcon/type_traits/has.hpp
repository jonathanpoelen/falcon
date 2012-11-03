#ifndef FALCON_TYPE_TRAITS_HAS_HPP
#define FALCON_TYPE_TRAITS_HAS_HPP

#include <falcon/sfinae/has_type.hpp>
#include <falcon/type_traits/use_type.hpp>

namespace falcon {

FALCON_CREATE_HAS_TYPE(has, type);

#define FALCON_HAS_NAME_TYPE(name)\
template <typename _T>\
struct has_##name\
: has<use_##name<_T> >\
{}

FALCON_HAS_NAME_TYPE(value_type);
FALCON_HAS_NAME_TYPE(reference);
FALCON_HAS_NAME_TYPE(const_reference);
FALCON_HAS_NAME_TYPE(pointer);
FALCON_HAS_NAME_TYPE(difference_type);
FALCON_HAS_NAME_TYPE(iterator_category);
FALCON_HAS_NAME_TYPE(iterator_type);
FALCON_HAS_NAME_TYPE(iterator);
FALCON_HAS_NAME_TYPE(const_iterator);
FALCON_HAS_NAME_TYPE(reverse_iterator);
FALCON_HAS_NAME_TYPE(const_reverse_iterator);
FALCON_HAS_NAME_TYPE(argument_type);
FALCON_HAS_NAME_TYPE(first_argument_type);
FALCON_HAS_NAME_TYPE(second_argument_type);
FALCON_HAS_NAME_TYPE(result_type);
FALCON_HAS_NAME_TYPE(allocator_type);
FALCON_HAS_NAME_TYPE(first_type);
FALCON_HAS_NAME_TYPE(second_type);
FALCON_HAS_NAME_TYPE(key_compare);
FALCON_HAS_NAME_TYPE(compare_type);
FALCON_HAS_NAME_TYPE(accessor_type);
FALCON_HAS_NAME_TYPE(functor_type);
FALCON_HAS_NAME_TYPE(compare_type);
FALCON_HAS_NAME_TYPE(traits_type);
FALCON_HAS_NAME_TYPE(char_type);
FALCON_HAS_NAME_TYPE(int_type);
FALCON_HAS_NAME_TYPE(pos_type);
FALCON_HAS_NAME_TYPE(off_type);
FALCON_HAS_NAME_TYPE(size_type);

#undef FALCON_HAS_NAME_TYPE

}

#endif