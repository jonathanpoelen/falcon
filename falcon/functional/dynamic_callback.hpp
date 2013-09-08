#ifndef FALCON_FUNCTIONAL_DYNAMIC_CALLBACK_HPP
#define FALCON_FUNCTIONAL_DYNAMIC_CALLBACK_HPP

#include <falcon/c++1x/unpack.hpp>

#include <initializer_list>
#include <utility>

namespace falcon {

template<typename T, typename... Args>
void __dynamic_callback_elem(Args&&... args)
{ T()(std::forward<Args>(args)...); }

template<typename... Ts, typename... Args>
bool dynamic_callback(std::size_t id, Args&&... args)
{
  std::size_t n = 0;
  bool test = false;
  CPP1X_UNPACK(
    (
      !test&& n == id
      ? (test = true, __dynamic_callback_elem<Ts>(std::forward<Args>(args)...))
      : void()
    ), ++n
  );
  return test;
}

}

#endif
