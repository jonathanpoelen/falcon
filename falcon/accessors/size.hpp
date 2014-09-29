#ifndef FALCON_ACCESSOR_SIZE_HPP
#define FALCON_ACCESSOR_SIZE_HPP

#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/conditional_cpp.hpp>
#include <falcon/helper/use_size_type.hpp>
#include <falcon/type_traits/default_or_type.hpp>

#if __cplusplus >= 201103L
# include <falcon/c++1x/syntax.hpp>
#endif

#include <cstddef>

namespace falcon {
namespace accessors {

template <typename T = void, typename Result = void>
struct size
{
  typedef typename default_or_type<use_size_type<T>, Result, void>::type result_type;
  typedef T argument_type;

  CPP_CONSTEXPR size() {}

  CPP_CONSTEXPR result_type operator()(const T& x) const
  CPP_NOEXCEPT_OPERATOR2(x.size())
  { return x.size(); }
};

template <class T, std::size_t N, class Result>
struct size<T[N], Result>
{
	typedef typename default_or_type<use_size_type<T>, Result, void>::type result_type;
  typedef T argument_type[N];

  CPP_CONSTEXPR size() {}

  template<class T, std::size_t N>
  CPP_CONSTEXPR std::size_t operator()(const T (&)[N]) const
  { return N; }
};

template <>
struct size<void, void>
{
  CPP_CONSTEXPR size() {}

  template<class T>
#if __cplusplus >= 201103L
  constexpr CPP1X_DELEGATE_FUNCTION_NOEXCEPT(
    operator()(const T& x) const
  , x.size())
#else
  std::size_t operator()(const T& x) const
  { return x.size(); }
#endif

  template<class T, std::size_t N>
  CPP_CONSTEXPR std::size_t operator()(const T (&)[N]) const
  { return N; }
};

CPP_GLOBAL_CONSTEXPR size<> size_f;

}
}

#endif
