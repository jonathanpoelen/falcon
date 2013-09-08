#ifndef FALCON_TUPLE_TUPLE_TRANSFORM_HPP
#define FALCON_TUPLE_TUPLE_TRANSFORM_HPP

#include <falcon/tuple/detail/is_tuple.hpp>
#include <falcon/tuple/parameter_index.hpp>
#include <falcon/parameter/parameter_index.hpp>

#include <utility>

namespace falcon {

template <std::size_t Index, typename Tuple, typename Functions>
auto __tuple_transform_get(std::true_type, Tuple&& t, Functions&& t_func)
-> decltype(std::get<Index>(std::forward<Functions>(t_func))
  (std::get<Index>(std::forward<Tuple>(t))))
{
  return std::get<Index>(std::forward<Functions>(t_func))
  (std::get<Index>(std::forward<Tuple>(t)));
}

template <std::size_t Index, typename Tuple, typename Functor>
constexpr auto __tuple_transform_get(std::false_type, Tuple&& t, Functor&& func)
-> decltype(func(std::get<Index>(std::forward<Tuple>(t))))
{
  return func(std::get<Index>(std::forward<Tuple>(t)));
}

template<typename Tuple, typename FunctionOrFunctions, std::size_t... Indexes,
typename ResultTuple = std::tuple<decltype(
  __tuple_transform_get<Indexes>(
    typename is_tuple_impl<FunctionOrFunctions>::type(),
    std::declval<Tuple>(),
    std::declval<FunctionOrFunctions>()
  )
)...>>
constexpr ResultTuple tuple_transform(Tuple&& t, FunctionOrFunctions&& funcs, const parameter_index<Indexes...>&)
{
  return ResultTuple(__tuple_transform_get<Indexes>(
    typename is_tuple_impl<FunctionOrFunctions>::type(),
    std::forward<Tuple>(t),
    std::forward<FunctionOrFunctions>(funcs)
  )...);
}

template<typename Tuple, typename FunctionOrFunctions>
constexpr auto tuple_transform(Tuple&& t, FunctionOrFunctions && funcs)
-> decltype(tuple_transform(std::forward<Tuple>(t),
                            std::forward<FunctionOrFunctions>(funcs),
                            build_tuple_index_t<Tuple>()))
{
  return tuple_transform(std::forward<Tuple>(t),
                         std::forward<FunctionOrFunctions>(funcs),
                         build_tuple_index_t<Tuple>());
}

}

#endif
