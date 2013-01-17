#ifndef FALCON_CONTAINER_INDIRECT_CONTAINER_HPP
#define FALCON_CONTAINER_INDIRECT_CONTAINER_HPP

#include <falcon/container/container_wrapper.hpp>
#include <falcon/iterator/get_accessor_iterator.hpp>

namespace falcon {

template<typename _Container,
#ifdef __GXX_EXPERIMENTAL_CXX0X__
	template<class...> class _IteratorType, typename... _ArgsIterator
#else
	template<class> class _IteratorType
#endif
>
struct build_indirect_container
{
	typedef container_wrapper<
		_Container,
		range_access_traits<
			_Container,
			typename _IteratorType<
				typename range_access_iterator<_Container>::type
#ifdef __GXX_EXPERIMENTAL_CXX0X__
				, _ArgsIterator...
#endif
			>::type
		>
	> type;
};

#ifdef __GXX_EXPERIMENTAL_CXX0X__
template<typename _Container,
	template<class...>class _IteratorType = falcon::iterator::build_get_accessor_iterator,
	typename... _ArgsIterator>
using indirect_container = typename build_indirect_container<_Container, _IteratorType, _ArgsIterator...>::type;
#endif

}

#endif