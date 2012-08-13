#ifndef _FALCON_COORDINATES_ARRAY_INDEX_HPP
#define _FALCON_COORDINATES_ARRAY_INDEX_HPP

namespace falcon {
namespace coordinates {

template<std::size_t i, std::size_t n, typename _TupleSize, typename _TupleCoord, typename _IndexType>
struct __tuple_index
{
	template<typename _Coef>
	constexpr static _IndexType __call(const _TupleSize& sizes,
									   const _TupleCoord& coord,
									   const _Coef& coef,
									   _IndexType index)
	{
		return __tuple_index<i+1, n, _TupleSize, _TupleCoord, _IndexType>
		::__call(sizes, coord, coef * std::get<i-1>(sizes), index + std::get<i-1>(coord) * coef);
	}
};

template<std::size_t n, typename _TupleSize, typename _TupleCoord, typename _IndexType>
struct __tuple_index<n, n, _TupleSize, _TupleCoord, _IndexType>
{
	template<typename _Coef>
	constexpr static _IndexType __call(const _TupleSize& ,
									   const _TupleCoord& coord,
									   const _Coef& coef,
									   _IndexType index)
	{ return index + std::get<n-1>(coord) * coef; }
};

template<std::size_t n, typename _TupleSize, typename _TupleCoord, typename _IndexType>
struct __tuple_index<0, n, _TupleSize, _TupleCoord, _IndexType>
{
	constexpr static _IndexType __call(const _TupleSize& sizes,
									   const _TupleCoord& coord)
	{
		return __tuple_index<2, n, _TupleSize, _TupleCoord, _IndexType>
		::__call(sizes, coord, std::get<0>(sizes), std::get<0>(coord));
	}
};

template<typename _TupleSize, typename _TupleCoord, typename _IndexType>
struct __tuple_index<0,1, _TupleSize, _TupleCoord, _IndexType>
{
	constexpr static _IndexType __call(const _TupleSize&,
									   const _TupleCoord& coord)
	{ return std::get<0>(coord); }
};

template<typename _TupleSize, typename _TupleCoord, typename _IndexType>
struct __tuple_index<0,0, _TupleSize, _TupleCoord, _IndexType>
{
	constexpr static _IndexType __call(const _TupleSize&,
									   const _TupleCoord&)
	{ return static_cast<_IndexType>(0); }
};

template <typename _T, std::size_t _N, typename _T2, std::size_t _N2, typename _Index = _T>
constexpr inline _Index array_index(
	const std::array<_T, _N>& sizes,
	const std::array<_T2, _N2>& coord)
{
	return __tuple_index<
		0,
		_N2,
		std::array<_T, _N>,
		std::array<_T2, _N2>,
		_Index
	>::__call(sizes, coord);
}

}
}

#endif