#ifndef FALCON_TPL_INTEGRAL_TEST_HPP
#define FALCON_TPL_INTEGRAL_TEST_HPP

#include <falcon/tpl/sequence.hpp>

#include <type_traits>

namespace falcon {
namespace tpl {

template<typename T, template<T, T> class Comp, template<class...> class... Temps>
class integral_test
{
  template<T Val, typename, typename... Args>
  struct __with
  { static const T value = Val; };

  template<
    T Val,
    template<class...> class Temp,
    template<class...> class... TempOthers,
    typename... Args
  >
  struct __with<Val, sequence<Temp, TempOthers...>, Args...>
  {
    static const T value = __with<
      Comp<Val, Temp<Args...>::value>::value,
      sequence<TempOthers...>,
      Args...
    >::value;
  };

  template<T Val, template<class...> class Temp, typename... Args>
  struct __with<Val, sequence<Temp>, Args...>
  { static const T value = Comp<Val, Temp<Args...>::value>::value; };

public:
  template<typename... Args>
  struct with
  : std::integral_constant<T, __with<T(0), sequence<Temps...>, Args...>::value>
  {};
};

template<typename TestTemp, typename... Args>
struct test_with
: TestTemp::template with<Args...>
{};

}
}

#endif
