#ifndef FALCON_TUPLE_TUPLE_APPLY_HPP
#define FALCON_TUPLE_TUPLE_APPLY_HPP

#include <falcon/tuple/parameter_index.hpp>
#include <falcon/tuple/detail/tuplefwd.hpp>

#include <utility>

namespace falcon {

template <typename Function, typename Tuple, std::size_t... Indexes>
constexpr auto tuple_apply(const parameter_index<Indexes...>&,
                           Function func, Tuple&& t)
-> decltype(func(get<Indexes>(std::forward<Tuple>(t))...))
{ return func(get<Indexes>(std::forward<Tuple>(t))...); }

template <typename Function, typename Tuple,
	typename Indexes = build_tuple_index_t<typename std::decay<Tuple>::type>
>
constexpr auto tuple_apply(Function func, Tuple&& t)
-> decltype(tuple_apply(Indexes(), func, std::forward<Tuple>(t)))
{ return tuple_apply(Indexes(), func, std::forward<Tuple>(t)); }

}

#endif
