#ifndef _FALCON_COORDINATES_INDEX_HPP
#define _FALCON_COORDINATES_INDEX_HPP

#include <falcon/c++/constexpr.hpp>
#include <iterator>

namespace falcon {
namespace coordinates {

template <typename _T>
CPP_CONSTEXPR inline _T index(const _T& width, const _T& x, const _T& y)
{ return y * width + x; }

template <typename _T>
CPP_CONSTEXPR inline _T index(const _T& width, const _T& height,
							  const _T& x, const _T& y, const _T& z)
{ return z * width * height + y * width + x; }

template <typename _ForwardIteratorCoord, typename _ForwardIteratorSize>
typename std::iterator_traits<_ForwardIteratorSize>::value_type index2(
	_ForwardIteratorCoord first_coord, _ForwardIteratorCoord last_coord,
	_ForwardIteratorSize first_size)
{
	typedef typename std::iterator_traits<_ForwardIteratorSize>::value_type value_type;
	if (first_coord == last_coord)
		return value_type(0);
	value_type ret = *first_coord;
	if (++first_coord == last_coord)
		return ret;
	value_type coef = *first_size;
	ret += *first_coord * coef;
	while (++first_coord != last_coord)
	{
		coef *= *++first_size;
		ret += *first_coord * coef;
	}
	return ret;
}


}
}

#endif