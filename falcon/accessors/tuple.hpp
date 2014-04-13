#ifndef FALCON_ACCESSOR_TUPLE_GET_HPP
#define FALCON_ACCESSOR_TUPLE_GET_HPP

#include <falcon/tuple/detail/tuplefwd.hpp>

namespace falcon {
namespace accessors {

template <std::size_t N, typename Tuple = void>
struct tuple_get
{
  typedef typename std::tuple_element<N, Tuple>::type result_type;
  typedef Tuple argument_type;

  static const std::size_t index = N;

  constexpr result_type & operator()(Tuple & t) const
  { return ::falcon::__detail::get<N>(t); }
};

template <std::size_t N, typename Tuple>
struct tuple_get<N, const Tuple>
{
  typedef typename std::tuple_element<N, Tuple>::type const result_type;
	typedef Tuple argument_type;

	static const std::size_t index = N;

  constexpr result_type & operator()(Tuple const & t) const
  { return ::falcon::__detail::get<N>(t); }
};

template <std::size_t N>
struct tuple_get<N, void>
{
  static const std::size_t index = N;

  template<class Tuple>
  constexpr auto operator()(Tuple & t) const
  -> decltype(::falcon::__detail::get<N>(t))
  { return ::falcon::__detail::get<N>(t); }
};

}
}

#endif
