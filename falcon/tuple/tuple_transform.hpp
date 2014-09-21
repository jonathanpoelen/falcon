#ifndef FALCON_TUPLE_TUPLE_TRANSFORM_HPP
#define FALCON_TUPLE_TUPLE_TRANSFORM_HPP

#include <falcon/tuple/is_tuple_like.hpp>
#include <falcon/tuple/parameter_index.hpp>
#include <falcon/parameter/parameter_index.hpp>

#include <utility>
#include <tuple>

namespace falcon {

namespace aux_ {
  template <std::size_t Index, typename Tuple, typename Functions>
  auto tuple_transform_get(std::true_type, Tuple&& t, Functions&& t_func)
  -> decltype(get<Index>(std::forward<Functions>(t_func))
    (get<Index>(std::forward<Tuple>(t))))
  {
    return get<Index>(std::forward<Functions>(t_func))
    (get<Index>(std::forward<Tuple>(t)));
  }

  template <std::size_t Index, typename Tuple, typename Functor>
  constexpr auto tuple_transform_get(std::false_type, Tuple&& t, Functor&& func)
  -> decltype(func(get<Index>(std::forward<Tuple>(t))))
  {
    return func(get<Index>(std::forward<Tuple>(t)));
  }
}

template<typename Tuple, typename FunctionOrFunctions, std::size_t... Indexes,
typename ResultTuple = std::tuple<decltype(
  aux_::tuple_transform_get<Indexes>(
    typename is_tuple_like<FunctionOrFunctions>::type(),
    std::declval<Tuple>(),
    std::declval<FunctionOrFunctions>()
  )
)...>>
constexpr ResultTuple tuple_transform(parameter_index<Indexes...>,
                                      Tuple&& t, FunctionOrFunctions funcs)
{
  return ResultTuple(aux_::tuple_transform_get<Indexes>(
    typename is_tuple_like<FunctionOrFunctions>::type(),
    std::forward<Tuple>(t),
    funcs
  )...);
}

template<typename Tuple, typename FunctionOrFunctions>
constexpr auto tuple_transform(Tuple&& t, FunctionOrFunctions funcs)
-> decltype(
  tuple_transform(build_tuple_index_t<Tuple>(), std::forward<Tuple>(t), funcs))
{
  return tuple_transform(
    build_tuple_index_t<Tuple>(), std::forward<Tuple>(t), funcs);
}

}

#endif
