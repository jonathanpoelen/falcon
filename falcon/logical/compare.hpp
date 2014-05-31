#ifndef FALCON_LOGICAL_COMPARE_HPP
#define FALCON_LOGICAL_COMPARE_HPP

#include <falcon/c++/constexpr.hpp>

namespace falcon {

template<int Lesser, int Greater, int Equal, typename T, typename U>
CPP_CONSTEXPR int compare(const T& a, const U& b)
{
  return a == b ? Equal : a < b ? Lesser : Greater;
}

template<int Lesser, int Greater, typename T, typename U>
CPP_CONSTEXPR int compare(const T& a, const U& b)
{
  return compare<Lesser, Greater, 0>(a, b);
}

template<int Lesser, typename T, typename U>
CPP_CONSTEXPR int compare(const T& a, const U& b)
{
  return compare<Lesser, -Lesser, 0>(a, b);
}

template<typename T, typename U>
CPP_CONSTEXPR int compare(const T& a, const U& b)
{
  return compare<-1, 1, 0>(a, b);
}


template<typename T, typename U, typename Result>
CPP_CONSTEXPR const Result & compare(
  const T& a, const U& b,
  Result const & is_equal, Result const & is_less, Result const & is_greater)
{
  return a == b ? is_equal : a < b ? is_less : is_greater;
}

#if __cplusplus >= 201103L
template<int Lesser, int Greater, int Equal, typename T, typename U>
constexpr int mcompare(const T& a, const U& b)
{
  return compare<Lesser, Greater, Equal, T, U>(a,b);
}

template<int Lesser, int Greater, int Equal, typename T, typename U, typename... Others>
constexpr int mcompare(const T& a, const U& b, const Others&... other)
{
  return compare<Lesser, Greater, Equal, T, U>(a,b)
    + mcompare<Lesser, Greater, Equal>(a, other...);
}

template<typename T, typename... Others>
inline constexpr int mcompare(const T& a, const Others&... other)
{
  return mcompare<-1, 1, 0>(a, other...);
}
#endif

}

#endif
