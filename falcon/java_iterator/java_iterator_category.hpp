#ifndef FALCON_JAVA_ITERATOR_JAVA_ITERATOR_CATEGORY_HPP
#define FALCON_JAVA_ITERATOR_JAVA_ITERATOR_CATEGORY_HPP

#include <falcon/sfinae/has_type.hpp>

namespace falcon {
namespace java_iterator {

FALCON_CREATE_HAS_TYPE(is_java_iterator_category, java_iterator_category);

template<typename _Iterator>
typename _Iterator::java_iterator_category
java_iterator_category(const _Iterator&)
{ return _Iterator::java_iterator_category(); }

}}

#endif