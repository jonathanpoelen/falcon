#ifndef FALCON_ACCESSOR_PAIR_HPP
#define FALCON_ACCESSOR_PAIR_HPP

#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/conditional_cpp.hpp>
#include <falcon/type_traits/cv_selector.hpp>

namespace falcon {
namespace accessors {

template <class T CPP_IF_CPP1X(= void)>
struct first_t
{
  typedef T pair_type;
  typedef pair_type argument_type;
  typedef typename match_cv_qualifiers<T, typename T::first_type>::type result_type;

  CPP_CONSTEXPR result_type& operator()(pair_type& pair) const CPP_NOEXCEPT
  { return pair.first; }
};

template <class T CPP_IF_CPP1X(= void)>
struct second_t
{
	typedef T pair_type;
	typedef pair_type argument_type;
  typedef typename match_cv_qualifiers<T, typename T::second_type>::type result_type;

  CPP_CONSTEXPR result_type& operator()(pair_type& pair) const CPP_NOEXCEPT
  { return pair.second; }
};

#if __cplusplus >= 201103L
template <>
struct first_t<void>
{
  template<class T>
  CPP_CONSTEXPR auto operator()(T& pair) const CPP_NOEXCEPT
  -> decltype((pair.first))
  { return pair.first; }
};

template <>
struct second_t<void>
{
  template<class T>
  CPP_CONSTEXPR auto operator()(T& pair) const CPP_NOEXCEPT
  -> decltype((pair.second))
  { return pair.second; }
};

CPP_GLOBAL_CONSTEXPR first_t<> first;
CPP_GLOBAL_CONSTEXPR second_t<> second;
#endif

}
}

#endif
