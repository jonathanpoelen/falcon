#ifndef FALCON_TUPLE_TUPLE_GET_HPP
#define FALCON_TUPLE_TUPLE_GET_HPP

#include <falcon/type_traits/static_const.hpp>
#include <falcon/tuple/get.hpp>

namespace falcon {

/// \brief call get< I>(T)
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

namespace {
  constexpr auto const & t0 = static_const<tuple_get<0>>::value;
  constexpr auto const & t1 = static_const<tuple_get<1>>::value;
  constexpr auto const & t2 = static_const<tuple_get<2>>::value;
  constexpr auto const & t3 = static_const<tuple_get<3>>::value;
  constexpr auto const & t4 = static_const<tuple_get<4>>::value;
  constexpr auto const & t5 = static_const<tuple_get<5>>::value;
  constexpr auto const & t6 = static_const<tuple_get<6>>::value;
  constexpr auto const & t7 = static_const<tuple_get<7>>::value;
  constexpr auto const & t8 = static_const<tuple_get<8>>::value;
  constexpr auto const & t9 = static_const<tuple_get<9>>::value;
  constexpr auto const & t10 = static_const<tuple_get<10>>::value;
  constexpr auto const & t11 = static_const<tuple_get<11>>::value;
  constexpr auto const & t12 = static_const<tuple_get<12>>::value;
  constexpr auto const & t13 = static_const<tuple_get<13>>::value;
  constexpr auto const & t14 = static_const<tuple_get<14>>::value;
  constexpr auto const & t15 = static_const<tuple_get<15>>::value;
}

}

#endif
