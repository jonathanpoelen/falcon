#ifndef FALCON_ALGORITHM_FIND_FIRST_NOT_OF_HPP
#define FALCON_ALGORITHM_FIND_FIRST_NOT_OF_HPP

#include <falcon/utility/move.hpp>

namespace falcon {

template <typename _Iterator, typename _T>
_Iterator find_first_not_of(_Iterator first, _Iterator last, const _T& v)
{
	for (; first != last; ++first){
		if (*first != v)
			break;
	}
	return FALCON_MOVE(first);
}

}

#endif