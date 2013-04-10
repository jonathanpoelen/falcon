#ifndef FALCON_ITERATOR_GET_ACCESSOR_ITERATOR_HPP
#define FALCON_ITERATOR_GET_ACCESSOR_ITERATOR_HPP

#include <iterator>
#include <falcon/accessor/get_accessor.hpp>
#include <falcon/iterator/indirect_iterator.hpp>

namespace falcon {
namespace iterator {

template<typename _Iterator>
struct build_get_accessor_iterator
{
	typedef typename std::iterator_traits<_Iterator>::value_type __value_type;

	typedef falcon::iterator::indirect_iterator<
		_Iterator,
		falcon::get_accessor<__value_type>,
		typename __value_type::type
	> type;
};

#if __cplusplus > 201100L
template<typename _Iterator>
using get_accessor_iterator = typename build_get_accessor_iterator<_Iterator>::type;
#endif

}
}

#endif