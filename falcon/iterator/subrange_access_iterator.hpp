#ifndef _FALCON_ITERATOR_SUBRANGE_ACCESS_ITERATOR_HPP
#define _FALCON_ITERATOR_SUBRANGE_ACCESS_ITERATOR_HPP

#include <falcon/container/range_access.hpp>
#include <falcon/type_traits/subtype.hpp>

namespace falcon {

	template<typename _T>
	struct subrange_access_iterator
	{
		typedef typename range_access_iterator<typename subtype<_T>::type>::type type;
	};
}

#endif