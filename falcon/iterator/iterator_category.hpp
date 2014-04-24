#ifndef FALCON_ITERATOR_ITERATOR_CATEGORY_HPP
#define FALCON_ITERATOR_ITERATOR_CATEGORY_HPP

#include <iterator>

namespace falcon {
namespace iterator {
  template<typename Iterator>
  typename std::iterator_traits<Iterator>::iterator_category
  iterator_category(const Iterator&)
  { return std::iterator_traits<Iterator>::iterator_category(); }

	template<typename Iterator>
	typename std::iterator_traits<Iterator>::iterator_category
	iterator_category()
	{ return std::iterator_traits<Iterator>::iterator_category(); }
}}

#endif
