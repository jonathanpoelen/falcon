#ifndef FALCON_LAMBDA2_LOOPS_HPP
#define FALCON_LAMBDA2_LOOPS_HPP

#include <falcon/lambda2/lambda.hpp>

namespace falcon {
namespace lambda2 {

namespace _aux {

  template<class...>
  class for_t;

  template<class Init, class Condition, class Increment, class Part>
  struct lambda<for_t<Init, Condition, Increment, Part>>
  : lambda_with_tuple<Init, Condition, Increment, Part>
  {
    using lambda::with_tuple_type::lambda_with_tuple;

    template<class... Args>
    constexpr void operator()(Args&&... args) const {
      for (auto x = std::get<0>(this->t)(std::forward<Args>(args)...)
      ; std::get<1>(x, this->t)(std::forward<Args>(args)...)
      ; std::get<2>(x, this->t)(std::forward<Args>(args)...)) {
        std::get<3>(x, this->t)(std::forward<Args>(args)...);
      }
    }
  };

  template<class>
  class while_t;

  template<class Condition, class Increment>
  struct lambda<while_t<Condition>, Increment>
  : lambda_with_tuple<Condition, Increment>
  {
    using lambda::with_tuple_type::lambda_with_tuple;

    template<class... Args>
    constexpr void operator()(Args&&... args) const {
      while (std::get<0>(this->t)(std::forward<Args>(args)...)) {
        std::get<1>(this->t)(std::forward<Args>(args)...);
      }
    }
  };

  template<class>
  class do_while_t;

  template<class Condition, class Increment>
  struct lambda<do_while_t<Condition>, Increment>
  : lambda_with_tuple<Condition, Increment>
  {
    using lambda::with_tuple_type::lambda_with_tuple;

    template<class... Args>
    constexpr void operator()(Args&&... args) const {
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

