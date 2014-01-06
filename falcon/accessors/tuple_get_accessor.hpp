#ifndef FALCON_ACCESSOR_TUPLE_GET_ACCESSOR_HPP
#define FALCON_ACCESSOR_TUPLE_GET_ACCESSOR_HPP

#include <falcon/tuple/detail/tuplefwd.hpp>
#include <type_traits>

namespace falcon {

template <typename Tuple, std::size_t N>
struct tuple_get_accessor
{
  typedef typename std::tuple_element<N, Tuple>::type result_type;
  typedef Tuple argument_type;

  static const std::size_t index = N;

  constexpr result_type & operator()(Tuple & t) const noexcept
  { return get<N>(t); }
};

template <typename Tuple, std::size_t N>
struct tuple_get_accessor<const Tuple, N>
{
  typedef typename std::tuple_element<N, Tuple>::type const result_type;
	typedef Tuple argument_type;

	static const std::size_t index = N;

	constexpr result_type & operator()(Tuple const & t) const noexcept
	{ return get<N>(t); }
};

}

#endif
