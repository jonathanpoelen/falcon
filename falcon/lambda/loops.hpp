#ifndef FALCON_LAMBDA_LOOPS_HPP
#define FALCON_LAMBDA_LOOPS_HPP

#include <falcon/lambda/lambda.hpp>

namespace falcon {
namespace lambda {

namespace _aux {

  template<class...>
  class for_t;

  template<class Init, class Condition, class Increment, class Part>
  struct lambda<for_t<Init, Condition, Increment, Part>>
  : lambda_with_tuple<Init, Condition, Increment, Part>
  {
    using lambda_with_tuple<Init, Condition, Increment, Part>::lambda_with_tuple;

    template<class... Args>
    void operator()(Args&&... args) const {
      for (auto x = std::get<0>(this->t)(std::forward<Args>(args)...)
      ; std::get<1>(this->t)(x, std::forward<Args>(args)...)
      ; std::get<2>(this->t)(x, std::forward<Args>(args)...)) {
        std::get<3>(this->t)(x, std::forward<Args>(args)...);
      }
    }
  };

  template<class>
  class while_t;

  template<class Condition, class Part>
  struct lambda<while_t<Condition>, Part>
  : lambda_with_tuple<Condition, Part>
  {
    using lambda_with_tuple<Condition, Part>::lambda_with_tuple;

    template<class... Args>
    void operator()(Args&&... args) const {
      while (std::get<0>(this->t)(std::forward<Args>(args)...)) {
        std::get<1>(this->t)(std::forward<Args>(args)...);
      }
    }
  };

  template<class>
  class do_while_t;

  template<class Condition, class Part>
  struct lambda<do_while_t<Condition>, Part>
  : lambda_with_tuple<Condition, Part>
  {
    using lambda_with_tuple<Condition, Part>::lambda_with_tuple;

    template<class... Args>
    void operator()(Args&&... args) const {
      do {
        std::get<1>(this->t)(std::forward<Args>(args)...);
      } while (std::get<0>(this->t)(std::forward<Args>(args)...));
    }
  };

}

template<class Init, class Condition, class Increment, class Part>
constexpr
_aux::lambda<_aux::for_t<Init, Condition, Increment, Part>>
for_(Init && x, Condition && c, Increment && next, Part && part)
{ return {
  std::forward<Init>(x)
, std::forward<Condition>(c)
, std::forward<Increment>(next)
, std::forward<Part>(part)
}; }

template<class Condition, class Part>
constexpr
_aux::lambda<_aux::while_t<Condition>, Part>
while_(Condition && c, Part && part)
{ return {
  std::forward<Condition>(c)
, std::forward<Part>(part)
}; }

template<class Condition, class Part>
constexpr
_aux::lambda<_aux::do_while_t<Condition>, Part>
do_while(Condition && c, Part && part)
{ return {
  std::forward<Condition>(c)
, std::forward<Part>(part)
}; }

}
}

#endif

