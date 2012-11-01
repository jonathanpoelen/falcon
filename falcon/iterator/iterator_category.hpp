#ifndef FALCON_ITERATOR_ITERATOR_CATEGORY_HPP
#define FALCON_ITERATOR_ITERATOR_CATEGORY_HPP

#include <iterator>

namespace falcon {
namespace iterator {
	template<typename _Iterator>
	typename std::iterator_traits<_Iterator>::iterator_category
	iterator_category(const _Iterator&)
	{ return std::iterator_traits<_Iterator>::iterator_category(); }
}}

#endif