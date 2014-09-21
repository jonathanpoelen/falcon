#ifndef FALCON_TUPLE_TUPLE_COMPOSE_HPP
#define FALCON_TUPLE_TUPLE_COMPOSE_HPP

#include <falcon/tuple/parameter_index.hpp>

#include <utility>
#include <tuple>

namespace falcon {

  using std::get;

/**
 * \brief Call functors on tuple
 *
 * \param Indexes... indexes arguments of @p targs
 * \param func functor for the results of @p t
 * \param t tuple functor
 * \param targs tuple arguments for each element of @p t
 *
 * \code
 * int answer = tuple_compose(parameter_index<0,2>(),
 *                            function,
 *                            std::forward_as_tuple(g1,g2,g3),
 *                            std::forward_as_tuple(x,y,z));
 * \endcode
 * is equivalent to
 * \code
 * int temp1 = g1(x,z);
 * int temp2 = g2(x,z);
 * int temp3 = g3(x,z);
 * int answer = function(temp1,temp2,temp3);
 * \endcode
 * @{
 */
template <
  class Function, class Operations, class ArgElements,
  std::size_t... Indexes, std::size_t... IndexesOperation>
constexpr auto tuple_compose(
  const parameter_index<Indexes...>&,
  const parameter_index<IndexesOperation...>&,
  Function&& func, Operations&& t, ArgElements&& targs)
-> decltype(std::forward<Function>(func)(
  get<IndexesOperation>(t)(get<Indexes>(
    std::forward<ArgElements>(targs)
  )...)...
))
{
  return std::forward<Function>(func)(
    get<IndexesOperation>(t)(get<Indexes>(
      std::forward<ArgElements>(targs)
    )...)...
  );
}


template <class Function, class Operations,
	class ArgElements, std::size_t... Indexes>
constexpr auto
tuple_compose(
  const parameter_index<Indexes...>& indexes,
  Function&& func,
  Operations&& t,
  ArgElements&& targs)
-> decltype(tuple_compose(
  indexes,
  build_tuple_index_t<Operations>(),
  std::forward<Function>(func),
  std::forward<Operations>(t),
  std::forward<ArgElements>(targs)))
{
  return tuple_compose(
    indexes,
    build_tuple_index_t<Operations>(),
    std::forward<Function>(func),
    std::forward<Operations>(t),
    std::forward<ArgElements>(targs));
}


template <class Function, class Operations, class ArgElements>
constexpr auto
tuple_compose(Function&& func, Operations&& t, ArgElements&& targs)
-> decltype(tuple_compose(
  build_tuple_index_t<ArgElements>(),
  build_tuple_index_t<Operations>(),
  std::forward<Function>(func),
  std::forward<Operations>(t),
  std::forward<ArgElements>(targs)))
{
  return tuple_compose(
    build_tuple_index_t<ArgElements>(),
    build_tuple_index_t<Operations>(),
    std::forward<Function>(func),
    std::forward<Operations>(t),
    std::forward<ArgElements>(targs));
}


template <class Function, class Operations>
constexpr auto
tuple_compose(Function&& func, Operations&& t)
-> decltype(tuple_compose(
  parameter_index<>(),
  build_tuple_index_t<Operations>(),
  std::forward<Function>(func),
  std::forward<Operations>(t),
  std::tuple<>()))
{
  return tuple_compose(
    parameter_index<>(),
    build_tuple_index_t<Operations>(),
    std::forward<Function>(func),
    std::forward<Operations>(t),
    std::tuple<>());
}
//@}

}

#endif
