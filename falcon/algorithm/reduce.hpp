#ifndef _FALCON_ALGORITHM_REDUCE_HPP
#define _FALCON_ALGORITHM_REDUCE_HPP

#include <falcon/c++/boost_or_std.hpp>
#include FALCON_BOOST_OR_STD_TRAITS(remove_reference)
#include <falcon/container/range_access.hpp>

namespace falcon {
namespace algorithm {

template<typename _ForwardIterator, typename _Reducer, typename _Result = typename std::iterator_traits<_ForwardIterator>::value_type>
_Result reduce(_ForwardIterator first, _ForwardIterator last, _Reducer reducer)
{
	if (first == last)
		return _Result();
	_Result r = *first;
	while (++first != last)
		r = reducer(r, *first);
	return r;
}

template<typename _Container, typename _Reducer, typename _Result = typename FALCON_BOOST_OR_STD_NAMESPACE::remove_reference<typename range_access_subtype<_Container>::type>::type>
inline _Result reduce(const _Container& container, _Reducer reducer)
{
	return reduce(begin(container), end(container), reducer);
}

template<typename _ForwardIterator, typename _Reducer, typename _Result>
_Result reduce(_ForwardIterator first, _ForwardIterator last, _Reducer reducer, _Result r = _Result())
{
	for (; first != last; ++first)
		r = reducer(r, *first);
	return r;
}

template<typename _Container, typename _Reducer, typename _Result>
inline _Result reduce(const _Container& container, _Reducer reducer, _Result r = _Result())
{
	return reduce(begin(container), end(container), reducer, r);
}

}
}

#endif
