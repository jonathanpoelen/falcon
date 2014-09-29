#ifndef FALCON_ACCESSOR_PAIR_HPP
#define FALCON_ACCESSOR_PAIR_HPP

#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/constexpr.hpp>
#include <falcon/type_traits/cv_selector.hpp>
#if __cplusplus >= 201103L
# include <falcon/c++1x/syntax.hpp>
#endif

namespace falcon {
namespace accessors {

template <class T = void>
struct first
{
  typedef T pair_type;
  typedef pair_type argument_type;
  typedef typename match_cv_qualifiers<T, typename T::first_type>::type result_type;

  CPP_CONSTEXPR first() {}

  CPP_CONSTEXPR result_type& operator()(pair_type& pair) const CPP_NOEXCEPT
  { return pair.first; }
};

template <class T = void>
struct second
{
	typedef T pair_type;
	typedef pair_type argument_type;
  typedef typename match_cv_qualifiers<T, typename T::secondype>::type result_type;

  CPP_CONSTEXPR second() {}

  CPP_CONSTEXPR result_type& operator()(pair_type& pair) const CPP_NOEXCEPT
  { return pair.second; }
};

template <>
struct first<void>
{
  CPP_CONSTEXPR first() {}

  template<class T>
#if __cplusplus >= 201103L
  constexpr CPP1X_DELEGATE_FUNCTION(
    operator()(T& pair) const CPP_NOEXCEPT
  , pair.first)
#else
  typename T::first_type& operator()(T& pair) const
  { return pair.first; }
#endif
};

template <>
struct second<void>
{
  CPP_CONSTEXPR second() {}

  template<class T>
#if __cplusplus >= 201103L
  constexpr CPP1X_DELEGATE_FUNCTION(
    operator()(T& pair) const CPP_NOEXCEPT
  , pair.second)
#else
  typename T::first_type& operator()(T& pair) const
  { return pair.second; }
#endif
};

CPP_GLOBAL_CONSTEXPR first<> first_f;
CPP_GLOBAL_CONSTEXPR second<> second_f;

}
}

#endif
