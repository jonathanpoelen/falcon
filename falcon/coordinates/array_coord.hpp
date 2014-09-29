#ifndef FALCON_COORDINATES_ARRAY_COORD_HPP
#define FALCON_COORDINATES_ARRAY_COORD_HPP

#include <falcon/utility/maker.hpp>

#include <array>

namespace falcon {
namespace coordinates {

template<std::size_t i, std::size_t n, typename Tuple, typename Index, typename CoordType>
struct __tuple_coord
{
  template<typename Coef, typename... Args>
  constexpr static CoordType __call(
    const Tuple& tuple_size, const Index& index,
    const Coef& coef, Args&&... args)
  {
    using std::get;
    return __tuple_coord<i+1, n, Tuple, Index, CoordType>
    ::__call(tuple_size, index,
         coef * get<i-1>(tuple_size),
         std::forward<Args>(args)...,
         (index / coef) % get<i-1>(tuple_size));
  }
};

template<std::size_t n, typename Tuple, typename Index, typename CoordType>
struct __tuple_coord<n, n, Tuple, Index, CoordType>
{
  template<typename Coef, typename... Args>
  constexpr static CoordType __call(
    const Tuple&, const Index& index,
    const Coef& coef, Args&&... args)
  { return maker<CoordType>()(std::forward<Args>(args)..., index / coef); }
};

template<std::size_t n, typename Tuple, typename Index, typename CoordType>
struct __tuple_coord<0, n, Tuple, Index, CoordType>
{
  constexpr static CoordType __call(
    const Tuple& tuple_size, const Index& index)
  {
    using std::get;
    return __tuple_coord<2, n, Tuple, Index, CoordType>
    ::__call(tuple_size, index,
         get<0>(tuple_size),
         index % get<0>(tuple_size));
  }
};

template<typename Tuple, typename Index, typename CoordType>
struct __tuple_coord<0, 1, Tuple, Index, CoordType>
{
  constexpr static CoordType __call(
    const Tuple& tuple_size, const Index& index)
  {
    using std::get;
    return maker<CoordType>()(
      index % get<0>(tuple_size),
      index / get<0>(tuple_size)
    );
  }
};

template<typename Tuple, typename Index, typename CoordType>
struct __tuple_coord<0, 0, Tuple, Index, CoordType>
{
  constexpr static CoordType __call(const Tuple&, const Index& index)
  { return maker<CoordType>()(index); }
};

template <typename _T, std::size_t _N, typename Index,
typename CoordType = std::array<_T, _N + 1> >
constexpr inline CoordType array_coord(
  const std::array<_T, _N>& sizes,
  const Index& index)
{
  return __tuple_coord<
    0,
    _N,
    std::array<_T, _N>,
    Index,
    CoordType
  >::__call(sizes, index);
}

}
}

#endif
