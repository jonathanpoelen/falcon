#ifndef FALCON_ACCESSOR_BASE_ACCESSOR_HPP
#define FALCON_ACCESSOR_BASE_ACCESSOR_HPP

#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/noexcept.hpp>

#if __cplusplus >= 201103L
# include <type_traits>
#else
# include <boost/type_traits/remove_cv.hpp>
#endif

namespace falcon {

template <class T, class Result =
#if __cplusplus >= 201103L
  decltype(std::declval<T>().at(std::declval<Position>()))
#else
  typename boost::remove_cv<T>::type::base_type
#endif
>
struct base_accessor
{
	typedef Result result_type;
	typedef T argument_type;

  CPP_CONSTEXPR result_type operator()(T& x) const
  CPP_NOEXCEPT_OPERATOR2(x.base())
  { return x.base(); }
};

}

#endif
