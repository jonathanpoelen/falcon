#ifndef FALCON_TUPLE_TUPLE_ASSIGN_HPP
#define FALCON_TUPLE_TUPLE_ASSIGN_HPP

#include <falcon/utility/unpack.hpp>
#include <falcon/tuple/detail/is_tuple.hpp>
#include <falcon/tuple/parameter_index.hpp>
#include <falcon/parameter/parameter_index.hpp>

#include <utility>

namespace falcon {

template<typename Tuple1, typename Tuple2, typename Functor, std::size_t... Indexes>
void __tuple_assign(std::false_type, parameter_index<Indexes...>,
                    Tuple1& t1, Tuple2 && t2, Functor && func)
{
  FALCON_UNPACK(
    get<Indexes>(t1)
    = func(get<Indexes>(std::forward<Tuple2>(t2))));
}

template<typename Tuple1, typename Tuple2, typename Functors, std::size_t... Indexes>
void __tuple_assign(std::true_type, parameter_index<Indexes...>,
                    Tuple1& t1, Tuple2 && t2, Functors && t_func)
{
  FALCON_UNPACK(
    get<Indexes>(t1)
    = get<Indexes>(std::forward<Functors>(t_func))
    (get<Indexes>(std::forward<Tuple2>(t2))));
}


template<typename Tuple1, typename Tuple2,
  typename FunctorOrFunctors, std::size_t... Indexes>
void tuple_assign(const parameter_index<Indexes...>&,
				  Tuple1 & t1, Tuple2 && t2,
                  FunctorOrFunctors && t_func)
{
  __tuple_assign(is_tuple_impl<FunctorOrFunctors>(),
                 parameter_index<Indexes...>(),
                 t1,
                 std::forward<Tuple2>(t2),
                 std::forward<FunctorOrFunctors>(t_func));
}

template<typename Tuple1, typename Tuple2, typename FunctorOrFunctors>
void tuple_assign(Tuple1 & t1, Tuple2 && t2, FunctorOrFunctors && t_func)
{
  __tuple_assign(is_tuple_impl<FunctorOrFunctors>(),
                 build_tuple_index_t<Tuple1>(),
                 t1,
                 std::forward<Tuple2>(t2),
                 std::forward<FunctorOrFunctors>(t_func));
}

}

#endif
