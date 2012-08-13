#ifndef _FALCON_COORDINATES_ARRAY_COORD_HPP
#define _FALCON_COORDINATES_ARRAY_COORD_HPP

#include <array>
#include <falcon/utility/maker.hpp>

namespace falcon {
namespace coordinates {

template<std::size_t i, std::size_t n, typename _Tuple, typename _Index, typename _CoordType>
struct __tuple_coord
{
	template<typename _Coef, typename... _Args>
	constexpr static _CoordType __call(const _Tuple& tuple_size,
									   const _Index& index,
									   const _Coef& coef,
									   _Args&&... args)
	{
		return __tuple_coord<i+1, n, _Tuple, _Index, _CoordType>
		::__call(tuple_size, index,
				 coef * std::get<i-1>(tuple_size),
				 std::forward<_Args>(args)...,
				 (index / coef) % std::get<i-1>(tuple_size));
	}
};

template<std::size_t n, typename _Tuple, typename _Index, typename _CoordType>
struct __tuple_coord<n, n, _Tuple, _Index, _CoordType>
{
	template<typename _Coef, typename... _Args>
	constexpr static _CoordType __call(const _Tuple& ,
									   const _Index& index,
									   const _Coef& coef,
									   _Args&&... args)
	{ return maker<_CoordType>()(std::forward<_Args>(args)..., index / coef); }
};

template<std::size_t n, typename _Tuple, typename _Index, typename _CoordType>
struct __tuple_coord<0, n, _Tuple, _Index, _CoordType>
{
	constexpr static _CoordType __call(const _Tuple& tuple_size,
									   const _Index& index)
	{
		return __tuple_coord<2, n, _Tuple, _Index, _CoordType>
		::__call(tuple_size, index,
				 std::get<0>(tuple_size),
				 index % std::get<0>(tuple_size));
	}
};

template<typename _Tuple, typename _Index, typename _CoordType>
struct __tuple_coord<0, 1, _Tuple, _Index, _CoordType>
{
	constexpr static _CoordType __call(const _Tuple& tuple_size,
									   const _Index& index)
	{
		return maker<_CoordType>()(
			index % std::get<0>(tuple_size),
			index / std::get<0>(tuple_size)
		);
	}
};

template<typename _Tuple, typename _Index, typename _CoordType>
struct __tuple_coord<0, 0, _Tuple, _Index, _CoordType>
{
	constexpr static _CoordType __call(const _Tuple&, const _Index& index)
	{ return maker<_CoordType>()(index); }
};

template <typename _T, std::size_t _N, typename _Index,
typename _CoordType = std::array<_T, _N + 1> >
constexpr inline _CoordType array_coord(
	const std::array<_T, _N>& sizes,
	const _Index& index)
{
	return __tuple_coord<
		0,
		_N,
		std::array<_T, _N>,
		_Index,
		_CoordType
	>::__call(sizes, index);
}

}
}

#endif