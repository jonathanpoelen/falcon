#ifndef FALCON_TUPLE_TUPLE_FOR_EACH_HPP
#define FALCON_TUPLE_TUPLE_FOR_EACH_HPP

#include <falcon/utility/unpack.hpp>
#include <falcon/tuple/parameter_index.hpp>
#include <falcon/parameter/parameter_index.hpp>

#include <utility>
#include <tuple>

namespace falcon {

using std::get;

namespace aux_ {
  template<typename Tuple, typename Functor, std::size_t... Indexes>
  void tuple_for_each(parameter_index<Indexes...>, Tuple && t, Functor && func)
  {
    using ::falcon::get;
    FALCON_UNPACK(
      std::forward<Functor>(func)(get<Indexes>(std::forward<Tuple>(t))));
  }
}

template<typename Tuple, typename Functor, std::size_t... Indexes>
Functor tuple_for_each(parameter_index<Indexes...>, Tuple && t, Functor && func)
{
  FALCON_UNPACK(
    std::forward<Functor>(func)(get<Indexes>(std::forward<Tuple>(t))));
  return std::move(func);
}

template<typename Tuple, typename Functor>
Functor tuple_for_each(Tuple && t, Functor func)
{
  aux_::tuple_for_each(
    build_tuple_index_t<Tuple>(), std::forward<Tuple>(t),
    std::forward<Functor>(func));
  return std::move(func);
}

}

#endif
