#ifndef FALCON_ACCESSOR_AT_ACCESSOR_HPP
#define FALCON_ACCESSOR_AT_ACCESSOR_HPP

#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/noexcept.hpp>

#if __cplusplus >= 201103L
# include <type_traits>
#else
# include <falcon/detail/inner_reference.hpp>
#endif

#include <cstddef>

namespace falcon {

template <class T, class Position = std::size_t, class Result =
#if __cplusplus >= 201103L
  decltype(std::declval<T>().at(std::declval<Position>()))
#else
  typename __detail::inner_reference<T>::type
#endif
>
struct at_accessor
{
	typedef Result result_type;
	typedef T first_argument_type;
	typedef Position second_argument_type;

  CPP_CONSTEXPR result_type operator()(T& cont, const Position& pos) const
  CPP_NOEXCEPT_OPERATOR2(cont.at(pos))
  { return cont.at(pos); }
};

}

#endif
