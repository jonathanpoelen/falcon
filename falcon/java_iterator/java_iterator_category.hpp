#ifndef FALCON_JAVA_ITERATOR_JAVA_ITERATOR_CATEGORY_HPP
#define FALCON_JAVA_ITERATOR_JAVA_ITERATOR_CATEGORY_HPP

namespace falcon {
namespace java_iterator {

template<typename _Iterator>
typename _Iterator::java_iterator_category
java_iterator_category(const _Iterator&)
{ return _Iterator::java_iterator_category(); }

}}

#endif