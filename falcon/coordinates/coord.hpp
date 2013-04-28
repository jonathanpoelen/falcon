#ifndef _FALCON_COORDINATES_COORD_HPP
#define _FALCON_COORDINATES_COORD_HPP

#include <iterator>
#include <falcon/c++/constexpr.hpp>
#if __cplusplus >= 201103L
#include <falcon/utility/maker.hpp>
#endif

namespace falcon {
namespace coordinates {

template <typename _T>
CPP_CONSTEXPR inline _T coord_x(const _T& width, const _T& index)
{ return index % width; }

template <typename _T>
CPP_CONSTEXPR inline _T coord_y(const _T& width, const _T& index)
{ return index / width; }

template <typename _T>
CPP_CONSTEXPR inline _T coord_y(const _T& width, const _T& height,
								const _T& index)
{ return (index / width) % height; }

template <typename _T>
CPP_CONSTEXPR inline _T coord_z(const _T& width, const _T& height,
								const _T& index)
{ return index / (width * height); }

template <typename _Coord, typename _T>
CPP_CONSTEXPR inline _Coord coord(const _T& width, const _T& index) {
	return
#if __cplusplus >= 201103L
	maker<_Coord>()
#else
	_Coord
#endif
	(
		coord_x<>(width, index),
		coord_y<>(width, index)
	);
}

template <typename _Coord, typename _T>
CPP_CONSTEXPR inline _Coord coord(const _T& width, const _T& height,
								  const _T& index) {
	return
#if __cplusplus >= 201103L
	maker<_Coord>()
#else
	_Coord
#endif
	(
		coord_x<>(width, height, index),
		coord_y<>(width, height, index),
		coord_z<>(width, height, index)
	);
}

template <typename _ForwardIteratorSize, typename _ForwardIteratorCopy, typename _Index>
_ForwardIteratorCopy coord2(
	_ForwardIteratorSize first_size, _ForwardIteratorSize last_size,
	_ForwardIteratorCopy cpy, const _Index& index)
{
	typedef typename std::iterator_traits<_ForwardIteratorSize>::value_type value_type;
	*cpy = index;
	if (first_size == last_size)
		return cpy;
	value_type coef = *first_size;
	for (;;)
	{
		*cpy %= *first_size;
		*++cpy = index / coef;
		if (++first_size == last_size)
			break;
		coef *= *first_size;
	}
	return cpy;
}

}
}

#endif