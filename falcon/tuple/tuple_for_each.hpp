#ifndef FALCON_TUPLE_TUPLE_FOR_EACH_HPP
#define FALCON_TUPLE_TUPLE_FOR_EACH_HPP

#include <falcon/c++1x/unpack.hpp>
#include <falcon/tuple/parameter_index.hpp>
#include <falcon/tuple/detail/tuplefwd.hpp>
#include <falcon/parameter/parameter_index.hpp>

#include <utility>

namespace falcon {

template<typename Tuple, typename Functor, std::size_t... Indexes>
void __tuple_for_each(parameter_index<Indexes...>, Tuple && t, Functor & func)
{
  CPP1X_UNPACK(func(get<Indexes>(std::forward<Tuple>(t))));
}

template<typename Tuple, typename Functor>
Functor tuple_for_each(Tuple && t, Functor func)
{
  __tuple_for_each(build_tuple_index_t<Tuple>(), std::forward<Tuple>(t), func);
  return std::move(func);
}

}

#endif
