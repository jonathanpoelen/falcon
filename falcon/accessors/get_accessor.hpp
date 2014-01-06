#ifndef FALCON_ACCESSOR_GET_ACCESSOR_HPP
#define FALCON_ACCESSOR_GET_ACCESSOR_HPP

#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/noexcept.hpp>

#if __cplusplus >= 201103L
# include <type_traits>
#endif

namespace falcon {

#if __cplusplus >= 201103L
template <class T, class Result = decltype(std::declval<T>().get())>
#else
template <class T, class Result = typename T::type&>
#endif
struct get_accessor
{
	typedef Result result_type;
	typedef T argument_type;

  CPP_CONSTEXPR result_type operator()(T& x) const
  CPP_NOEXCEPT_OPERATOR2(x.get())
	{ return x.get(); }
};

}

#endif
