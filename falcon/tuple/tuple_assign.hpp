#ifndef FALCON_TUPLE_TUPLE_ASSIGN_HPP
#define FALCON_TUPLE_TUPLE_ASSIGN_HPP

#include <falcon/utility/unpack.hpp>
#include <falcon/tuple/is_tuple_like.hpp>
#include <falcon/tuple/parameter_index.hpp>
#include <falcon/parameter/parameter_index.hpp>

#include <utility>
#include <tuple>

namespace falcon {

using std::get;

namespace aux_ {
  template<class Tuple1, class Tuple2, class Functor, std::size_t... Indexes>
  void tuple_assign(
    std::false_type, parameter_index<Indexes...>,
    Tuple1& t1, Tuple2 && t2, Functor && func)
  {
    FALCON_UNPACK(
      get<Indexes>(t1) = func(get<Indexes>(std::forward<Tuple2>(t2))));
  }

  template<class Tuple1, class Tuple2, class Functors, std::size_t... Indexes>
  void tuple_assign(
    std::true_type, parameter_index<Indexes...>,
    Tuple1& t1, Tuple2 && t2, Functors && t_func)
  {
    FALCON_UNPACK(
      get<Indexes>(t1)
        = get<Indexes>(std::forward<Functors>(t_func))
        (get<Indexes>(std::forward<Tuple2>(t2))));
  }
}


template<
  class Tuple1, class Tuple2,
  class FunctorOrFunctors, std::size_t... Indexes>
void tuple_assign(
  const parameter_index<Indexes...>&,
  Tuple1 & t1, Tuple2 && t2,
  FunctorOrFunctors && t_func)
{
  aux_::tuple_assign(
    is_tuple_like<FunctorOrFunctors>(),
    parameter_index<Indexes...>(),
    t1,
    std::forward<Tuple2>(t2),
    std::forward<FunctorOrFunctors>(t_func));
}

template<class Tuple1, class Tuple2, class FunctorOrFunctors>
void tuple_assign(Tuple1 & t1, Tuple2 && t2, FunctorOrFunctors && t_func)
{
  aux_::tuple_assign(
    is_tuple_like<FunctorOrFunctors>(),
    build_tuple_index_t<Tuple1>(),
    t1,
    std::forward<Tuple2>(t2),
    std::forward<FunctorOrFunctors>(t_func));
}

}

#endif
