#ifndef FALCON_FN_FUNC_HPP
#define FALCON_FN_FUNC_HPP

#include <falcon/functional/parameter_index_adapter.hpp>

namespace falcon {
namespace fn {

template<class F, std::size_t... Ints>
using func_fn = parameter_index_adapter<
  F
, specified_parameter_index_tag<parameter_index<(Ints-1)...>>
>;

template<std::size_t... Ints, class F>
func_fn<F, Ints...> func(F && f)
{ return func_fn<F, Ints...>{std::forward<F>(f)}; }

}
}

#endif
