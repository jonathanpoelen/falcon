#ifndef FALCON_ACCESSOR_TUPLE_GET_HPP
#define FALCON_ACCESSOR_TUPLE_GET_HPP

#include <falcon/tuple/get.hpp>

namespace falcon {
namespace accessors {

template <std::size_t N, typename Tuple = void>
struct tuple_get
{
  typedef typename std::tuple_element<N, Tuple>::type result_type;
  typedef Tuple argument_type;

  static const std::size_t index = N;

  constexpr tuple_get() {}

  constexpr result_type & operator()(Tuple & t) const
  { return get<N>(t); }
};

template <std::size_t N, typename Tuple>
struct tuple_get<N, const Tuple>
{
  typedef typename std::tuple_element<N, Tuple>::type const result_type;
	typedef Tuple argument_type;

	static const std::size_t index = N;

  constexpr tuple_get() {}

  constexpr result_type & operator()(Tuple const & t) const
  { return get<N>(t); }
};

template <std::size_t N>
struct tuple_get<N, void>
{
  static const std::size_t index = N;

  constexpr tuple_get() {}

  template<class Tuple>
  constexpr auto operator()(Tuple & t) const
  -> decltype(get<N>(t))
  { return get<N>(t); }
};

}
}

#endif
