#ifndef _FALCON_ACCESSOR_NEXT_ACCESSOR_HPP
#define _FALCON_ACCESSOR_NEXT_ACCESSOR_HPP

#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/noexcept.hpp>

#if __cplusplus >= 201103L
# include <type_traits>
#else
# include <falcon/detail/inner_reference.hpp>
#endif

namespace falcon {

template <class T, class Result =
#if __cplusplus >= 201103L
  decltype(std::declval<T>().next())
#else
  typename __detail::inner_reference<T>::type
#endif
>
struct next_accessor
{
	typedef Result result_type;
	typedef T argument_type;

  CPP_CONSTEXPR result_type operator()(T& x) const
  CPP_NOEXCEPT_OPERATOR2(x.next())
  { return x.next(); }
};

}

#endif
