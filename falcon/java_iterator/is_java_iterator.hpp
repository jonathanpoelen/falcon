#ifndef FALCON_JAVA_ITERATOR_IS_JAVA_ITERATOR_HPP
#define FALCON_JAVA_ITERATOR_IS_JAVA_ITERATOR_HPP

#include <falcon/sfinae/has_type.hpp>

namespace falcon {
namespace java_iterator {

FALCON_HAS_TYPE_TRAIT_NAMED_DEF(is_java_iterator, java_iterator_category);

}}

#endif
