#ifndef _FALCON_JAVA_ITERATOR_DETAIL_ITERATOR_TRAITS_HPP
#define _FALCON_JAVA_ITERATOR_DETAIL_ITERATOR_TRAITS_HPP

#include <falcon/iterator/detail/to_iterator_traits.hpp>
#include <falcon/type_traits/is_java_iterator.hpp>

namespace falcon {
namespace java_iterator {
namespace detail {

template <typename _Iterator, bool _IsJavaIterator = is_java_iterator<_Iterator>::value>
struct to_iterator_traits
{
	typedef typename falcon::iterator::detail::to_iterator_traits<_Iterator>::type type;
};

template <typename _Iterator>
struct to_iterator_traits<_Iterator, true>
{
	typedef typename _Iterator::iterator type;
};

}
}
}

#endif