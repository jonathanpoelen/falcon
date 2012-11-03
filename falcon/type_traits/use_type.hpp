#ifndef FALCON_TYPE_TRAITS_USE_TYPE_HPP
#define FALCON_TYPE_TRAITS_USE_TYPE_HPP

#include <falcon/type_traits/has.hpp>

namespace falcon
{

#define FALCON_CONVERT_NAME_TYPE(name)\
template <typename _T>\
struct use_##name\
{\
	typedef typename _T::name type;\
	static const bool value = has_##name<_T>::value;\
}

FALCON_CONVERT_NAME_TYPE(type);
FALCON_CONVERT_NAME_TYPE(value_type);
FALCON_CONVERT_NAME_TYPE(reference);
FALCON_CONVERT_NAME_TYPE(const_reference);
FALCON_CONVERT_NAME_TYPE(pointer);
FALCON_CONVERT_NAME_TYPE(difference_type);
FALCON_CONVERT_NAME_TYPE(iterator_category);
FALCON_CONVERT_NAME_TYPE(iterator_type);
FALCON_CONVERT_NAME_TYPE(iterator);
FALCON_CONVERT_NAME_TYPE(const_iterator);
FALCON_CONVERT_NAME_TYPE(reverse_iterator);
FALCON_CONVERT_NAME_TYPE(const_reverse_iterator);
FALCON_CONVERT_NAME_TYPE(argument_type);
FALCON_CONVERT_NAME_TYPE(first_argument_type);
FALCON_CONVERT_NAME_TYPE(second_argument_type);
FALCON_CONVERT_NAME_TYPE(result_type);
FALCON_CONVERT_NAME_TYPE(allocator_type);
FALCON_CONVERT_NAME_TYPE(first_type);
FALCON_CONVERT_NAME_TYPE(second_type);
FALCON_CONVERT_NAME_TYPE(key_compare);
FALCON_CONVERT_NAME_TYPE(compare_type);
FALCON_CONVERT_NAME_TYPE(accessor_type);
FALCON_CONVERT_NAME_TYPE(functor_type);
FALCON_CONVERT_NAME_TYPE(traits_type);
FALCON_CONVERT_NAME_TYPE(char_type);
FALCON_CONVERT_NAME_TYPE(int_type);
FALCON_CONVERT_NAME_TYPE(pos_type);
FALCON_CONVERT_NAME_TYPE(off_type);
FALCON_CONVERT_NAME_TYPE(size_type);

#undef FALCON_CONVERT_NAME_TYPE

}

#endif