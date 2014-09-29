#ifndef FALCON_COORDINATES_ARRAY_INDEX_HPP
#define FALCON_COORDINATES_ARRAY_INDEX_HPP

#include <array>

namespace falcon {
namespace coordinates {

template<std::size_t i, std::size_t n, typename TupleSize, typename TupleCoord, typename IndexType>
struct __tuple_index
{
  template<typename Coef>
  constexpr static IndexType __call(
    const TupleSize& sizes, const TupleCoord& coord,
    const Coef& coef, IndexType index)
  {
    using std::get;
    return __tuple_index<i+1, n, TupleSize, TupleCoord, IndexType>
    ::__call(sizes, coord, coef * get<i-1>(sizes), index + get<i-1>(coord) * coef);
  }
};

template<std::size_t n, typename TupleSize, typename TupleCoord, typename IndexType>
struct __tuple_index<n, n, TupleSize, TupleCoord, IndexType>
{
  template<typename Coef>
  constexpr static IndexType __call(
    const TupleSize&, const TupleCoord& coord,
    const Coef& coef, IndexType index)
  { using std::get; return index + get<n-1>(coord) * coef; }
};

template<std::size_t n, typename TupleSize, typename TupleCoord, typename IndexType>
struct __tuple_index<0, n, TupleSize, TupleCoord, IndexType>
{
  constexpr static IndexType __call(
    const TupleSize& sizes, const TupleCoord& coord)
  {
    using std::get;
    return __tuple_index<2, n, TupleSize, TupleCoord, IndexType>
    ::__call(sizes, coord, get<0>(sizes), get<0>(coord));
  }
};

template<typename TupleSize, typename TupleCoord, typename IndexType>
struct __tuple_index<0,1, TupleSize, TupleCoord, IndexType>
{
  constexpr static IndexType __call(
    const TupleSize&, const TupleCoord& coord)
  { using std::get; return get<0>(coord); }
};

template<typename TupleSize, typename TupleCoord, typename IndexType>
struct __tuple_index<0,0, TupleSize, TupleCoord, IndexType>
{
  constexpr static IndexType __call(const TupleSize&,
                     const TupleCoord&)
  { return static_cast<IndexType>(0); }
};

template <typename _T, std::size_t _N, typename _T2, std::size_t _N2, typename Index = _T>
constexpr inline Index array_index(
  const std::array<_T, _N>& sizes,
  const std::array<_T2, _N2>& coord)
{
  return __tuple_index<
    0,
    _N2,
    std::array<_T, _N>,
    std::array<_T2, _N2>,
    Index
  >::__call(sizes, coord);
}

}
}

#endif
