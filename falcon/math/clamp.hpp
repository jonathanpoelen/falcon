#ifndef FALCON_MATH_CLAMP_HPP
#define FALCON_MATH_CLAMP_HPP

#include <cassert>

namespace falcon {

template <class T>
T const & clamp(T const & min, T const & x, T const & max)
{
  assert(!(max < min));
  return x < min ? min : x > max ? max : x;
}

template <class T, class Compare>
T const & clamp(T const & min, T const & x, T const & max, Compare comp)
{
  assert(!comp(max, min));
  return comp(x, min) ? min : comp(max, x) ? max : x;
}

template <class T>
T const & clamp_unordered(T const & min, T const & x, T const & max)
{
  return min < max ? clamp(min, x, max) : clamp(max, x, min);
}

template <class T, class Compare>
T const & clamp_unordered(T const & min, T const & x, T const & max, Compare comp)
{
  return min < max ? clamp(min, x, max, comp) : clamp(max, x, min, comp);
}

}

#endif
