#ifndef FALCON_FUNCTIONAL_DYNAMIC_CALLBACK_HPP
#define FALCON_FUNCTIONAL_DYNAMIC_CALLBACK_HPP

#include <falcon/utility/unpack.hpp>
#include <falcon/tuple/detail/tuplefwd.hpp>
#include <falcon/parameter/parameter_index.hpp>

#include <utility>

namespace falcon {

template<typename Callbacks, std::size_t... Indexes, typename... Args>
bool dynamic_callback(parameter_index<Indexes...>, Callbacks callbacks,
                      std::size_t id, Args&&... args)
{
  bool test = false;
  FALCON_UNPACK((
    Indexes == id
    ? void((test = true, get<Indexes>(callbacks)(std::forward<Args>(args)...)))
    : void()
  ));
  return test;
}

template<typename Callbacks, typename... Args>
bool dynamic_callback(Callbacks callbacks, std::size_t id, Args&&... args)
{
  return dynamic_callback<Callbacks&>(
    build_parameter_index_t<std::tuple_size<Callbacks>::value>(),
    callbacks, id, std::forward<Args>(args)...
  );
}

template<typename T, typename... Args>
void __dynamic_callback_elem(Args&&... args)
{ T()(std::forward<Args>(args)...); }

template<typename... Ts, std::size_t... Indexes, typename... Args>
bool dynamic_callback(parameter_index<Indexes...>, std::size_t id, Args&&... args)
{
  bool test = false;
  FALCON_UNPACK((
    Indexes == id
    ? (test = true, __dynamic_callback_elem<Ts>(std::forward<Args>(args)...))
    : void()
  ));
  return test;
}

template<typename... Ts, typename... Args>
bool dynamic_callback(std::size_t id, Args&&... args)
{
  return dynamic_callback<Ts...>(build_parameter_index_t<sizeof...(Ts)>(),
                                 id, std::forward<Args>(args)...);
}

}

#endif
