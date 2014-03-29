#ifndef FALCON_ITERATOR_GET_ACCESSOR_ITERATOR_HPP
#define FALCON_ITERATOR_GET_ACCESSOR_ITERATOR_HPP

#include <iterator>
#include <falcon/accessors/get.hpp>
#include <falcon/iterator/indirect_iterator.hpp>

namespace falcon {
namespace iterator {

template<typename Iterator>
class build_get_accessor_iterator
{
	typedef typename std::iterator_traits<Iterator>::value_type __value_type;
public:
	typedef falcon::iterator::indirect_iterator<
		Iterator,
		falcon::accessors::get<__value_type>,
		typename __value_type::type
	> type;
};

#if __cplusplus >= 201103L
template<typename Iterator>
using get_accessor_iterator = typename build_get_accessor_iterator<Iterator>::type;
#endif

template<typename Iterator>
typename build_get_accessor_iterator<Iterator>::type
make_get_accessor_iterator(Iterator iter)
{
  typedef typename build_get_accessor_iterator<Iterator>::type iterator_type;
  return iterator_type(iter);
}

}
}

#endif
