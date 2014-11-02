#ifndef FALCOI_FI_TUPLE_GET_HPP
#define FALCOI_FI_TUPLE_GET_HPP

#include <falcon/tuple/get.hpp>

namespace falcon {
namespace fn {

template <std::size_t I, typename Tuple = void>
struct tuple_get
{
  typedef typename std::tuple_element<I, Tuple>::type result_type;
  typedef Tuple argument_type;

  static const std::size_t index = I;

  constexpr tuple_get() noexcept {}

  constexpr result_type & operator()(Tuple & t) const
  { return ::falcon::get<I>(t); }
};

template <std::size_t I, typename Tuple>
struct tuple_get<I, const Tuple>
{
  typedef typename std::tuple_element<I, Tuple>::type const result_type;
	typedef Tuple argument_type;

	static const std::size_t index = I;

  constexpr tuple_get() noexcept {}

  constexpr result_type & operator()(Tuple const & t) const
  { return ::falcon::get<I>(t); }
};

template <std::size_t I>
struct tuple_get<I, void>
{
  static const std::size_t index = I;

  constexpr tuple_get() noexcept {}

  template<class Tuple>
  constexpr auto operator()(Tuple & t) const
  -> decltype(::falcon::get<I>(t))
  { return ::falcon::get<I>(t); }
};

}
}

#endif
